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

  static bool AND_OPERATOR(int index, std::string c, std::string d,
                           TruthTable &truth_table);
  static bool OR_OPERATOR(int index, std::string c, std::string d,
                          TruthTable &truth_table);
  static bool NOT_OPERATOR(std::string c);
  static bool XOR_OPERATOR(int index, std::string c, std::string d,
                           TruthTable &truth_table);
  static bool is_variable(std::string c);
  static bool is_operator(std::string c);
  static bool apply_operator(int index, std::string operator_,
                             std::string first_operand,
                             std::string second_operand,
                             TruthTable &truth_table);
  static int precedence(std::string op);
};