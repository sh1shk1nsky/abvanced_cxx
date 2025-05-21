#pragma once

#include <limits>
#include <type_traits>

// Пространство имен для реализации TypeList
namespace TypeList {
// Определяем структуру TypeList
template <typename... Types>
struct TypeList {};

// Получение элемента списка по индексу
template <std::size_t Index, typename TypeList>
struct Get;

template <std::size_t Index, typename Head, typename... Tail>
struct Get<Index, TypeList<Head, Tail...>> {
  using type = typename Get<Index - 1, TypeList<Tail...>>::type;
};

template <typename Head, typename... Tail>
struct Get<0, TypeList<Head, Tail...>> {
  using type = Head;
};

// Получение размера списка
template <typename TypeList>
struct Size;

template <typename... Types>
struct Size<TypeList<Types...>> {
  static constexpr std::size_t value = sizeof...(Types);
};

// Проверка наличия типа в списке
template <typename Type, typename TypeList>
struct Contains;

template <typename Type>
struct Contains<Type, TypeList<>> : std::false_type {};

template <typename Type, typename Head, typename... Tail>
struct Contains<Type, TypeList<Head, Tail...>>
    : std::conditional_t<std::is_same_v<Type, Head>, std::true_type,
                         Contains<Type, TypeList<Tail...>>> {};

// Получение индекса типа в списке
template <typename Type, typename TypeList>
struct IndexOf;

template <typename Type>
struct IndexOf<Type, TypeList<>>
    : std::integral_constant<std::size_t,
                             std::numeric_limits<std::size_t>::max()> {};

template <typename Type, typename Head, typename... Tail>
struct IndexOf<Type, TypeList<Head, Tail...>>
    : std::conditional_t<
          std::is_same_v<Type, Head>, std::integral_constant<std::size_t, 0>,
          typename std::conditional_t<
              Contains<Type, TypeList<Tail...>>::value,
              std::integral_constant<
                  std::size_t, 1 + IndexOf<Type, TypeList<Tail...>>::value>,
              std::integral_constant<
                  std::size_t, std::numeric_limits<std::size_t>::max()>>> {};

// Добавление типа в конец списка
template <typename Type, typename TypeList>
struct Append;

template <typename Type>
struct Append<Type, TypeList<>> {
  using type = TypeList<Type>;
};

template <typename Type, typename Head, typename... Tail>
struct Append<Type, TypeList<Head, Tail...>> {
  using type = TypeList<Head, Tail..., Type>;
};

// Добавление типа в начало списка
template <typename Type, typename TypeList>
struct Prepend;

template <typename Type, typename... Types>
struct Prepend<Type, TypeList<Types...>> {
  using type = TypeList<Type, Types...>;
};
}  // namespace TypeList