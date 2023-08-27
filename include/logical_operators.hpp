#pragma once
#include <iostream>

class LogicalOperators {
public:
  static const char AND;
  static const char OR;
  static const char NOT;
  static const char XOR;
  static const char WHITE_SPACE;
  static const char LEFT_PARENTHESIS;
  static const char RIGHT_PARENTHESIS;
  static const char COMMA;
  static const char TRUE;
  static const char FALSE;

  static bool AND_OPERATOR(char c, char d);
  static bool OR_OPERATOR(char c, char d);
  static bool NOT_OPERATOR(char c);
  static bool XOR_OPERATOR(char c, char d);
  static bool is_variable(char c);
  static bool is_operator(char c);
  static bool apply_operator(char operator_, bool first_operand,
                             bool second_operand);
  static int precedence(char op);
};