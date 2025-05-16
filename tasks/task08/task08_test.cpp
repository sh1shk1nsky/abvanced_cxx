#include "addition.h"
#include "constant.h"
#include "expression.h"
#include "expressionfactory.h"
#include "variable.h"

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