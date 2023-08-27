#include "logger.hpp"
#include <iostream>
#include <string>

Logger::Logger() {}

Logger &Logger::get_instance() {
  static Logger instance;
  return instance;
}

void Logger::log(const std::string &message) {
  std::cout << message << std::endl;
}

void Logger::line_jump() { std::cout << std::endl; }

void Logger::log_not_jump(const std::string &message) { std::cout << message; }

void Logger::log_title() {
  log("╔════════════════════════╗");
  log("║  Truth Table Generator ║");
  log("╚════════════════════════╝");
}

void Logger::log_menu() {
  log_title();
  log("[1] Select an existing file");
  log("[2] Load truth table from file");
  log_not_jump("[+] Select an option: ");
}

std::string Logger::get_user_input() {
  std::string userOption;
  std::cin >> userOption;
  return userOption;
}

void Logger::clear_console() { system("clear"); }