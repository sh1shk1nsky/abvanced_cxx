#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "expression.hpp"
#include "expressionfactory.hpp"

class Constant : public Expression {
 private:
  double value;
  bool isPrecreated;
  int refCount = 0;

  Constant(double value, bool precreated)
      : value(value), isPrecreated(precreated) {}
  friend class ExpressionFactory;

 public:
  void addRef() override {
    if (!isPrecreated) refCount++;
  }

  void release() override {
    if (!isPrecreated && --refCount == 0) {
      ExpressionFactory::getInstance().unregisterConstant(this);
      delete this;
    }
  }

  double calculate(const std::map<std::string, double>&) const override {
    return value;
  }

  void print(std::ostream& os) const override { os << value; }

  double getValue() const { return value; }
};

#endif  // CONSTANT_HPP
