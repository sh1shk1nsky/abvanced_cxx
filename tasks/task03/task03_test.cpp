#include <iostream>

#include "type_map.hpp"

struct DataA {
  std::string value;
};

struct DataB {
  int value;
};

int main() {
  // Создаем TypeMap с парами ключ-тип_значения
  TypeMap::TypeMap<int, int, double, double, DataA, DataA, DataB, DataB>
      myTypeMap;

  // Добавление элементов
  myTypeMap.AddValue<int>(42);
  myTypeMap.AddValue<double>(3.14);
  myTypeMap.AddValue<DataA>({"Hello, TypeMap!"});
  myTypeMap.AddValue<DataB>({10});

  // Получение и вывод значений
  std::cout << "Value for int: " << myTypeMap.GetValue<int>() << std::endl;
  std::cout << "Value for double: " << myTypeMap.GetValue<double>()
            << std::endl;
  std::cout << "Value for DataA: " << myTypeMap.GetValue<DataA>().value
            << std::endl;
  std::cout << "Value for DataB: " << myTypeMap.GetValue<DataB>().value
            << std::endl;

  // Проверка наличия
  std::cout << "Contains int? " << (myTypeMap.Contains<int>() ? "Yes" : "No")
            << std::endl;

  // Удаление
  myTypeMap.RemoveValue<double>();

  // Попытка получения удаленного элемента (выбросит исключение)
  try {
    std::cout << "Value for double after removal: "
              << myTypeMap.GetValue<double>() << std::endl;
  } catch (const std::runtime_error& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  return 0;
}