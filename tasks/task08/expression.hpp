#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>

class Expression {
 public:
  virtual ~Expression() = default;
  virtual double calculate(
      const std::map<std::string, double>& context) const = 0;
  virtual void print(std::ostream& os) const = 0;
  virtual void addRef() = 0;
  virtual void release() = 0;
};

#endif  // EXPRESSION_HPP
