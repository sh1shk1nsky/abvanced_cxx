#include "expressionfactory.hpp"

#include <cmath>
#include <stdexcept>

#include "constant.hpp"
#include "variable.hpp"

// Реализация методов фабрики
ExpressionFactory::ExpressionFactory() {
  // Предварительное создание констант от -5 до 256
  for (int i = -5; i <= 256; ++i) {
    Constant* c = new Constant(i, true);
    constants[i] = c;
    precreatedConstants.insert(c);
  }
}

ExpressionFactory::~ExpressionFactory() {
  // Удаление всех переменных
  for (auto& pair : variables) {
    delete pair.second;
  }

  // Удаление не-предсозданных констант
  for (auto& pair : constants) {
    if (precreatedConstants.count(pair.second) == 0) {
      delete pair.second;
    }
  }

  // Удаление предсозданных констант
  for (Constant* c : precreatedConstants) {
    delete c;
  }
}

// Получение экземпляра фабрики (синглтон)
ExpressionFactory& ExpressionFactory::getInstance() {
  static ExpressionFactory instance;
  return instance;
}

// Создание константы
Constant* ExpressionFactory::createConstant(double value) {
  // Проверка на предсозданные целочисленные константы
  if (value == std::floor(value) && value >= -5 && value <= 256) {
    auto it = constants.find(value);
    if (it != constants.end()) {
      return it->second;
    }
  }

  // Поиск существующей константы
  auto it = constants.find(value);
  if (it != constants.end()) {
    it->second->addRef();
    return it->second;
  }

  // Создание новой константы
  Constant* c = new Constant(value, false);
  constants[value] = c;
  c->addRef();  // Увеличиваем счётчик ссылок
  return c;
}

// Создание переменной
Variable* ExpressionFactory::createVariable(const std::string& name) {
  auto it = variables.find(name);
  if (it != variables.end()) {
    it->second->addRef();
    return it->second;
  }

  // Создание новой переменной
  Variable* v = new Variable(name);
  variables[name] = v;
  v->addRef();  // Увеличиваем счётчик ссылок
  return v;
}

// Удаление переменной из регистрации
void ExpressionFactory::unregisterVariable(const std::string& name) {
  variables.erase(name);
}

// Удаление константы из регистрации
void ExpressionFactory::unregisterConstant(Constant* c) {
  if (!c->isPrecreated) {
    constants.erase(c->getValue());
  }
}