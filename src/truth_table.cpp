#include "truth_table.hpp"
#include "logical_operators.hpp"

TruthTable::TruthTable() {}

TruthTable &TruthTable::parse_expression(const std::string &expression) {
  expressions.clear();
  size_t start = 0;
  size_t end = expression.find(LogicalOperators::COMMA);
  while (end != std::string::npos) {
    expressions.push_back(expression.substr(start, end - start));
    start = end + 1;
    end = expression.find(LogicalOperators::COMMA, start);
  }
  expressions.push_back(expression.substr(start));
  expressions = separate_expressions();
  expressions.push_back(expression);
  parse_literals();
  parse_variables();
  return *this;
}

void TruthTable::parse_literals() {
  for (const std::string &expr : expressions) {
    for (char c : expr) {
      std::string token(1, c);
      std::string next_token(1, expr[expr.find(token) + 1]);
      if (token != LogicalOperators::NOT &&
          LogicalOperators::is_variable(token)) {
        if (next_token == LogicalOperators::NOT) {
          literals.insert(token + next_token);
        } else {
          literals.insert(token);
        }
      }
    }
  }
}

std::vector<std::string> TruthTable::separate_expressions() {
  std::vector<std::string> separated_expressions;
  for (const std::string &expression : expressions) {
    size_t start = 0;
    size_t end = expression.find(LogicalOperators::OR);

    while (end != std::string::npos) {
      separated_expressions.push_back(expression.substr(start, end - start));
      start = end + 1;
      end = expression.find(LogicalOperators::OR, start);
    }
    if (start < expression.length()) {
      separated_expressions.push_back(expression.substr(start));
    }
  }

  return separated_expressions;
}

void TruthTable::parse_variables() {
  for (const std::string &expr : expressions) {
    for (char c : expr) {
      std::string token(1, c);
      if (token != LogicalOperators::NOT &&
          LogicalOperators::is_variable(token)) {
        variables.insert(token);
      }
    }
  }
}

TruthTable &TruthTable::show_variables() {
  Logger::get_instance().log_not_jump("Variables: ");
  for (const std::string &var : variables) {
    Logger::get_instance().log_not_jump(var);
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
  calculate_table();
  return *this;
}

void TruthTable::calculate_table() {
  clean_table();
  calculate_variables_truth_values();
  clean_resolved_table();
  for (int i = 0; i < num_rows; ++i) {
    Logger::get_instance().log_not_jump(
        "|" + format_cell(table[i][0], max_expr_length) + "|");
    for (int j = 1; j < variables.size(); ++j) {
      Logger::get_instance().log_not_jump(
          format_cell(table[i][j], max_expr_length) + "|");
    }
    for (int j = variables.size(); j < variables.size() + expressions.size();
         ++j) {
      Logger::get_instance().log_not_jump(
          format_cell(evaluate_expression(expressions[j - variables.size()], i),
                      max_expr_length) +
          "|");
    }
    Logger::get_instance().line_jump();
  }
  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");
}

void TruthTable::clean_table() {
  table = new bool *[num_rows];
  for (int i = 0; i < num_rows; ++i) {
    table[i] = new bool[num_rows];
    for (int j = 0; j < variables.size(); ++j) {
      table[i][j] = false;
    }
  }
}

void TruthTable::clean_resolved_table() {
  resolved_table = new bool *[num_rows];
  for (int i = 0; i < num_rows; ++i) {
    resolved_table[i] = new bool[num_rows];
    for (int j = 0; j < expressions.size(); ++j) {
      resolved_table[i][j] = false;
    }
  }
}

void TruthTable::calculate_variables_truth_values() {
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < variables.size(); ++j) {
      table[i][j] = (i & (1 << j)) ? true : false;
    }
  }
}

void TruthTable::calculate_expressions_truth_values() {
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < expressions.size(); ++j) {
      resolved_table[i][j] = evaluate_expression(expressions[j], i);
    }
  }
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

std::string TruthTable::format_header(const std::set<std::string> &items,
                                      int max_expr_length) {
  std::string formatted = "";
  for (std::string item : items) {
    formatted += " " + item + std::string(max_expr_length - 1, ' ') + " |";
  }
  return formatted;
}

std::string TruthTable::format_cell(bool value, int max_expr_length) {
  return " " + std::to_string(value) + std::string(max_expr_length - 1, ' ') +
         " ";
}

bool TruthTable::evaluate_expression(std::string const &expr, int row) {
  std::stack<bool> operands;
  std::stack<std::string> operators;
  for (char c : expr) {
    std::string token(1, c);
    bool variable_value = get_variable_value(row, c);
    if (token == LogicalOperators::WHITE_SPACE) {
      continue;
    }
    if (LogicalOperators::is_variable(token)) {
      operands.push(variable_value);

    } else if (LogicalOperators::is_operator(token)) {
      while (!operators.empty() &&
             LogicalOperators::precedence(operators.top()) >=
                 LogicalOperators::precedence(token)) {
        bool second_operand = operands.top();
        operands.pop();
        bool first_operand = operands.top();
        operands.pop();
        std::string operator_ = operators.top();
        operators.pop();
        operands.push(LogicalOperators::apply_operator(operator_, first_operand,
                                                       second_operand));
      }
      operators.push(token);
    } else if (token == LogicalOperators::LEFT_PARENTHESIS) {
      operators.push(token);
    } else if (token == LogicalOperators::RIGHT_PARENTHESIS) {
      while (!operators.empty() &&
             operators.top() != LogicalOperators::LEFT_PARENTHESIS) {
        bool second_operand = operands.top();
        operands.pop();
        bool first_operand = operands.top();
        operands.pop();
        std::string operator_ = operators.top();
        operators.pop();
        operands.push(LogicalOperators::apply_operator(operator_, first_operand,
                                                       second_operand));
      }
      operators.pop();
    }
  }
  while (!operators.empty()) {
    std::string operator_ = operators.top();
    operators.pop();
    if (operator_ == LogicalOperators::NOT) {
      bool operand = operands.top();
      operands.pop();
      bool result = !operand;
      operands.push(result);
    } else {
      bool second_operand = operands.top();
      operands.pop();
      bool first_operand = operands.top();
      operands.pop();
      if (operator_ == LogicalOperators::AND) {
        bool result = first_operand && second_operand;
        operands.push(result);
      } else {
        bool result = LogicalOperators::apply_operator(operator_, first_operand,
                                                       second_operand);
        operands.push(result);
      }
    }
  }
  bool final_first_op = operands.top();
  operands.pop();
  bool final_second_op = operands.top();
  operands.pop();
  bool final_result = final_first_op && final_second_op;
  return final_result;
}

int TruthTable::get_num_rows() const { return num_rows; }
int TruthTable::get_num_variables() const { return variables.size(); }
std::string TruthTable::get_expression(int index) const {
  return expressions[index];
}

bool TruthTable::get_variable_value(int row, char c) const {
  return table[row][get_column_by_variable(c)];
}

int TruthTable::get_column_by_variable(char variable) const {
  int column = 0;
  for (const std::string &var : variables) {
    if (var[0] == variable) {
      return column;
    }
    ++column;
  }
  return -1;
}