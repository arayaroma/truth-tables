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

  static bool is_variable(std::string c);
  static bool is_operator(std::string c);
  static bool apply_operator(std::string operator_, bool first_operand,
                             bool second_operand);
  static bool apply_negation(bool first_operand);
  static bool apply_and(bool first_operand, bool second_operand);
  static bool apply_or(bool first_operand, bool second_operand);
  static bool apply_xor(bool first_operand, bool second_operand);
  static int precedence(std::string token);
};