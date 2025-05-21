#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "expression.hpp"
class ExpressionFactory;  // Forward declaration

class Variable : public Expression {
 private:
  std::string name;
  int refCount = 0;

  Variable(const std::string& name) : name(name) {}
  friend class ExpressionFactory;

 public:
  void addRef() override { refCount++; }
  void release() override {
    if (--refCount == 0) {
      ExpressionFactory::getInstance().unregisterVariable(name);
      delete this;
    }
  }

  double calculate(
      const std::map<std::string, double>& context) const override {
    auto it = context.find(name);
    if (it == context.end())
      throw std::runtime_error("Variable not found: " + name);
    return it->second;
  }

  void print(std::ostream& os) const override { os << name; }

  const std::string& getName() const { return name; }
};

#endif  // VARIABLE_HPP
