#pragma once
#include <iostream>
#include <string>

class TruthTable;

class LogicalOperators {
public:
  static const std::string AND;
  static const std::string OR;
  static const std::string NOT;
  static const std::string XOR;
  static const std::string WHITE_SPACE;
  static const std::string LEFT_PARENTHESIS;
  static const std::string RIGHT_PARENTHESIS;
  static const std::string COMMA;
  static const std::string TRUE;
  static const std::string FALSE;

  static bool AND_OPERATOR(std::string c, std::string d);
  static bool OR_OPERATOR(std::string c, std::string d);
  static bool NOT_OPERATOR(std::string c);
  static bool XOR_OPERATOR(std::string c, std::string d);
  static bool is_variable(std::string c);
  static bool is_operator(std::string c);
  static bool apply_operator(std::string operator_, std::string first_operand,
                             std::string second_operand);
  static int precedence(std::string op);
};