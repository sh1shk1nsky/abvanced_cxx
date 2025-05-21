#ifndef EXPRESSION_FACTORY_H
#define EXPRESSION_FACTORY_H

#include <map>
#include <string>
#include <unordered_set>

class Expression;
class Constant;
class Variable;

class ExpressionFactory {
 private:
  std::map<std::string, Variable*> variables;
  std::map<double, Constant*> constants;
  std::unordered_set<Constant*> precreatedConstants;

  ExpressionFactory();
  ~ExpressionFactory();

 public:
  static ExpressionFactory& getInstance();
  Constant* createConstant(double value);
  Variable* createVariable(const std::string& name);
  void unregisterVariable(const std::string& name);
  void unregisterConstant(Constant* c);
};

#endif  // EXPRESSION_FACTORY_H