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
  parse_variables();
  return *this;
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
  load_table(*this);
  display_variables_and_expressions();
  return *this;
}

void TruthTable::display_variables_and_expressions() {
  for (int i = 0; i < num_rows; ++i) {
    int index = variables.size() - 1;
    Logger::get_instance().log_not_jump("|");

    for (const std::string &var : variables) {
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

TruthTable &TruthTable::load_table(TruthTable &truth_table) {
  num_rows = truth_table.get_num_rows();
  num_vars = truth_table.get_num_variables();

  table.resize(num_rows, std::vector<int>(num_vars));

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_vars; ++j) {
      table[i][j] = truth_table.get_value(i, j);
    }
  }
  return *this;
}

bool TruthTable::evaluate_expression(const std::string &expr, int i) {
  std::stack<std::string> operators;
  std::stack<std::string> operands;

  for (char c : expr) {
    std::string token(1, c);
    if (LogicalOperators::is_variable(token)) {
      operands.push(std::to_string(get_value(i, get_variable(token))));
    } else if (LogicalOperators::is_operator(token)) {
      while (!operators.empty() &&
             LogicalOperators::precedence(operators.top()) >=
                 LogicalOperators::precedence(token)) {
        std::string value_d = operands.top();
        operands.pop();

        std::string value_c = operands.top();
        operands.pop();

        std::string operator_ = operators.top();
        operators.pop();

        operands.push(std::to_string(
            LogicalOperators::apply_operator(operator_, value_c, value_d)));
      }
      operators.push(token);
    } else if (token == LogicalOperators::LEFT_PARENTHESIS) {
      operators.push(token);
    } else if (token == LogicalOperators::RIGHT_PARENTHESIS) {
      while (!operators.empty() &&
             operators.top() != LogicalOperators::LEFT_PARENTHESIS) {
        std::string value_d = operands.top();
        operands.pop();

        std::string value_c = operands.top();
        operands.pop();

        std::string operator_ = operators.top();
        operators.pop();

        operands.push(std::to_string(
            LogicalOperators::apply_operator(operator_, value_c, value_d)));
      }
      operators.pop();
    }
  }

  while (!operators.empty()) {
    std::string value_d = operands.top();
    operands.pop();

    std::string value_c = operands.top();
    operands.pop();

    std::string operator_ = operators.top();
    operators.pop();

    operands.push(std::to_string(
        LogicalOperators::apply_operator(operator_, value_c, value_d)));
  }

  return operands.top() == LogicalOperators::TRUE;
}

int TruthTable::get_value(int row, int var) {
  int index = variables.size() - 1;
  for (const std::string &v : variables) {
    if (index == var) {
      return (row >> index) & 1;
    }
    --index;
  }
  return 0;
}

int TruthTable::get_variable(const std::string &token) {
  int index = 0;
  for (const std::string &var : variables) {
    if (var == token) {
      return index;
    }
    ++index;
  }
  return -1;
}

int TruthTable::get_num_rows() const { return num_rows; }
int TruthTable::get_num_variables() const { return variables.size(); }