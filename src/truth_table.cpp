#include "truth_table.hpp"
#include <string>

TruthTable::TruthTable() {}

TruthTable &TruthTable::parse_expression(const std::string &expression) {
  expressions.clear();
  size_t start = 0;
  size_t end = expression.find(',');
  while (end != std::string::npos) {
    expressions.push_back(expression.substr(start, end - start));
    start = end + 1;
    end = expression.find(',', start);
  }
  expressions.push_back(expression.substr(start));
  parse_variables();
  return *this;
}

void TruthTable::parse_variables() {
  for (const std::string &expr : expressions) {
    for (char c : expr) {
      if (c != '\'' && LogicalOperators::is_variable(c)) {
        variables.insert(c);
      }
    }
  }
}

TruthTable &TruthTable::show_variables() {
  Logger::get_instance().log_not_jump("Variables: ");
  for (const char &var : variables) {
    Logger::get_instance().log_not_jump(std::string(1, var));
  }
  Logger::get_instance().line_jump();
  return *this;
}

void TruthTable::display_header(int max_expr_lenght, int separator_width) {
  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");

  Logger::get_instance().log("|" + format_header(variables, max_expr_lenght) +
                             format_header(expressions, max_expr_lenght));

  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");
}

void TruthTable::calculate_num_rows() {
  num_rows = static_cast<int>(std::pow(2, variables.size()));
}

void TruthTable::calculate_separator_width(int max_expr_length) {
  separator_width =
      (variables.size() + expressions.size()) * (max_expr_length + 3) - 1;
}

void TruthTable::calculate_max_expr_length() {
  max_expr_length = 0;
  for (const std::string &expr : expressions) {
    max_expr_length =
        std::max(max_expr_length, static_cast<int>(expr.length()));
  }
}

TruthTable &TruthTable::build_table() {
  calculate_num_rows();
  calculate_max_expr_length();
  calculate_separator_width(max_expr_length);
  display_header(max_expr_length, separator_width);
  display_variables_and_expressions();
  return *this;
}

void TruthTable::display_variables_and_expressions() {
  for (i = 0; i < num_rows; ++i) {
    int index = variables.size() - 1;
    Logger::get_instance().log_not_jump("|");
    for (char var : variables) {
      bool value = (i >> index) & 1;
      Logger::get_instance().log_not_jump(format_cell(value, max_expr_length) +
                                          "|");
      --index;
    }
    for (const std::string &expr : expressions) {
      bool value = evaluate_expression(expr, i);
      Logger::get_instance().log_not_jump(format_cell(value, max_expr_length) +
                                          "|");
    }
    Logger::get_instance().line_jump();
  }
  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");
}
std::string TruthTable::format_header(const std::vector<std::string> &items,
                                      int max_expr_length) {
  std::string formatted = "";
  for (const std::string &item : items) {
    formatted +=
        " " + item + std::string(max_expr_length - item.length(), ' ') + " |";
  }
  return formatted;
}

std::string TruthTable::format_header(const std::set<char> &items,
                                      int max_expr_length) {
  std::string formatted = "";
  for (char item : items) {
    formatted +=
        " " + std::string(1, item) + std::string(max_expr_length - 1, ' ') + " |";
  }
  return formatted;
}

std::string TruthTable::format_cell(bool value, int max_expr_length) {
  return " " + std::to_string(value) + std::string(max_expr_length - 1, ' ') +
         " ";
}

bool TruthTable::evaluate_expression(const std::string &expr, int i) {
  std::stack<bool> operands;
  std::stack<char> operators;

  for (char c : expr) {
    if (LogicalOperators::is_variable(c)) {
      operands.push(get_value(i, c));
    } else if (LogicalOperators::is_operator(c)) {
      while (!operators.empty() &&
             operators.top() != LogicalOperators::LEFT_PARENTHESIS &&
             LogicalOperators::precedence(c) <=
                 LogicalOperators::precedence(operators.top())) {
        char op = operators.top();
        operators.pop();

        bool second_operand = operands.top();
        operands.pop();
        bool first_operand = operands.top();
        operands.pop();

        operands.push(LogicalOperators::apply_operator(op, first_operand,
                                                       second_operand));
      }
      operators.push(c);
    } else if (c == LogicalOperators::LEFT_PARENTHESIS) {
      operators.push(c);
    } else if (c == LogicalOperators::RIGHT_PARENTHESIS) {
      while (!operators.empty() &&
             operators.top() != LogicalOperators::LEFT_PARENTHESIS) {
        char op = operators.top();
        operators.pop();

        bool second_operand = operands.top();
        operands.pop();
        bool first_operand = operands.top();
        operands.pop();

        operands.push(LogicalOperators::apply_operator(op, first_operand,
                                                       second_operand));
      }
      operators.pop(); // Pop the left parenthesis
    }
  }

  while (!operators.empty()) {
    char op = operators.top();
    operators.pop();

    bool second_operand = operands.top();
    operands.pop();
    bool first_operand = operands.top();
    operands.pop();

    operands.push(
        LogicalOperators::apply_operator(op, first_operand, second_operand));
  }

  return operands.top(); // The final result of the expression evaluation
}

bool TruthTable::get_value(int row, char var) {
  int index = variables.size() - 1;
  for (char v : variables) {
    if (v == var) {
      return (row >> index) & 1;
    }
    --index;
  }
  return false;
}