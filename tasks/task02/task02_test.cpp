#include <iostream>

#include "type_list.hpp"

int main() {
  // Тестирование реализации TypeList

  // Создаем TypeList с несколькими типами
  using MyTypeList = TypeList::TypeList<int, double, char>;

  // Проверка размера
  static_assert(TypeList::Size<MyTypeList>::value == 3,
                "Размер списка должен быть 3");

  // Получение типа по индексу
  static_assert(
      std::is_same_v<typename TypeList::Get<0, MyTypeList>::type, int>,
      "Первый тип должен быть int");
  static_assert(
      std::is_same_v<typename TypeList::Get<1, MyTypeList>::type, double>,
      "Второй тип должен быть double");
  static_assert(
      std::is_same_v<typename TypeList::Get<2, MyTypeList>::type, char>,
      "Третий тип должен быть char");

  // Проверка наличия типа в списке
  static_assert(TypeList::Contains<int, MyTypeList>::value,
                "TypeList должен содержать int");
  static_assert(!TypeList::Contains<float, MyTypeList>::value,
                "TypeList не должен содержать float");

  // Получение индекса типа
  static_assert(TypeList::IndexOf<int, MyTypeList>::value == 0,
                "Индекс int должен быть 0");
  static_assert(TypeList::IndexOf<double, MyTypeList>::value == 1,
                "Индекс double должен быть 1");
  static_assert(TypeList::IndexOf<char, MyTypeList>::value == 2,
                "Индекс char должен быть 2");

  // Для типа, которого нет в списке
  static_assert(TypeList::IndexOf<float, MyTypeList>::value ==
                    std::numeric_limits<std::size_t>::max(),
                "Индекс float должен быть 'max'");

  // Добавление типов в конец и начало
  using MyTypeListAppended = typename TypeList::Append<float, MyTypeList>::type;
  static_assert(TypeList::Size<MyTypeListAppended>::value == 4,
                "Размер списка после добавления в конец должен быть 4");
  static_assert(
      std::is_same_v<typename TypeList::Get<3, MyTypeListAppended>::type,
                     float>,
      "Последний тип должен быть float");

  using MyTypeListPrepended =
      typename TypeList::Prepend<float, MyTypeList>::type;
  static_assert(TypeList::Size<MyTypeListPrepended>::value == 4,
                "Размер списка после добавления в начало должен быть 4");
  static_assert(
      std::is_same_v<typename TypeList::Get<0, MyTypeListPrepended>::type,
                     float>,
      "Первый тип должен быть float");

  std::cout << "Все тесты прошли успешно!" << std::endl;

  return 0;
}