#ifndef ADDITION_H
#define ADDITION_H

#include "expression.h"

class Addition : public Expression {
 private:
  Expression* left;
  Expression* right;

 public:
  Addition(Expression* l, Expression* r) : left(l), right(r) {
    left->addRef();
    right->addRef();
  }

  ~Addition() {
    left->release();
    right->release();
  }

  double calculate(
      const std::map<std::string, double>& context) const override {
    return left->calculate(context) + right->calculate(context);
  }

  void print(std::ostream& os) const override {
    os << "(";
    left->print(os);
    os << " + ";
    right->print(os);
    os << ")";
  }

  void addRef() override {}
  void release() override {}
};

#endif  // ADDITION_H
