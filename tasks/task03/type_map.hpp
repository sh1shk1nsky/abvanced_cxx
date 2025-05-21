#pragma once

#include <optional>
#include <stdexcept>
#include <tuple>
#include <utility>  // Для std::forward

#include "../task02/type_list.h"

namespace TypeMap {

// Вспомогательная метафункция для разделения пар ключ-значение
template <typename... Ts>
struct SplitPairs {
  static_assert(
      sizeof...(Ts) % 2 == 0,
      "TypeMap requires even number of template parameters (key-value pairs)");
  using Keys = TypeList::TypeList<>;
  using Values = TypeList::TypeList<>;
};

template <typename K, typename V, typename... Rest>
struct SplitPairs<K, V, Rest...> {
  using RestSplit = SplitPairs<Rest...>;
  using Keys = typename TypeList::Prepend<K, typename RestSplit::Keys>::type;
  using Values =
      typename TypeList::Prepend<V, typename RestSplit::Values>::type;
};

// Преобразование TypeList в tuple с optional
template <typename TList>
struct ToOptionalTuple;

template <typename... Vs>
struct ToOptionalTuple<TypeList::TypeList<Vs...>> {
  using type = std::tuple<std::optional<Vs>...>;
};

// Основной класс TypeMap
template <typename... Pairs>
class TypeMap {
  using Split = SplitPairs<Pairs...>;
  using Keys = typename Split::Keys;
  using Values = typename Split::Values;

  template <typename K>
  using ValueType =
      typename TypeList::Get<TypeList::IndexOf<K, Keys>::value, Values>::type;

  using StorageTuple = typename ToOptionalTuple<Values>::type;
  StorageTuple storage;

 public:
  // Добавление значения по ключу
  template <typename K, typename T = ValueType<K>>
  void AddValue(T&& value) {
    static_assert(TypeList::Contains<K, Keys>::value,
                  "Key not found in TypeMap");
    constexpr std::size_t index = TypeList::IndexOf<K, Keys>::value;
    std::get<index>(storage).emplace(std::forward<T>(value));
  }

  // Получение значения по ключу
  template <typename K>
  ValueType<K>& GetValue() {
    static_assert(TypeList::Contains<K, Keys>::value,
                  "Key not found in TypeMap");
    constexpr std::size_t index = TypeList::IndexOf<K, Keys>::value;
    auto& opt = std::get<index>(storage);
    if (!opt.has_value()) {
      throw std::runtime_error("Value not present");
    }
    return *opt;
  }

  // Константная версия GetValue
  template <typename K>
  const ValueType<K>& GetValue() const {
    return const_cast<TypeMap*>(this)->template GetValue<K>();
  }

  // Проверка наличия значения
  template <typename K>
  bool Contains() const {
    static_assert(TypeList::Contains<K, Keys>::value,
                  "Key not found in TypeMap");
    constexpr std::size_t index = TypeList::IndexOf<K, Keys>::value;
    return std::get<index>(storage).has_value();
  }

  // Удаление значения
  template <typename K>
  void RemoveValue() {
    static_assert(TypeList::Contains<K, Keys>::value,
                  "Key not found in TypeMap");
    constexpr std::size_t index = TypeList::IndexOf<K, Keys>::value;
    std::get<index>(storage).reset();
  }
};

}  // namespace TypeMap