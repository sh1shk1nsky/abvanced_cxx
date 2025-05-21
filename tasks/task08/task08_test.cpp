#include "addition.hpp"
#include "constant.hpp"
#include "expression.hpp"
#include "expressionfactory.hpp"
#include "variable.hpp"

int main() {
  ExpressionFactory& factory = ExpressionFactory::getInstance();
  Constant* c = factory.createConstant(2);
  Variable* v = factory.createVariable("x");
  Addition* expression = new Addition(c, v);

  std::map<std::string, double> context{{"x", 3}};
  std::cout << "Result: " << expression->calculate(context) << std::endl;  // 5

  delete expression;
  return 0;
}