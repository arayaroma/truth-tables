#include "file_loader.hpp"
#include "logger.hpp"

int main() {
  FileLoader fileLoader;
  while (true) {
    Logger::get_instance().log_menu();
    std::string user_option = Logger::get_instance().get_user_input();
    if (user_option == "3") {
      break;
    } else if (user_option == "1") {
      fileLoader.handle_user_input(user_option);
    } else if (user_option == "2") {
      Logger::get_instance().log_not_jump("[+] Enter file name: ");
      std::string file_name = Logger::get_instance().get_user_input();
      Logger::get_instance().log_not_jump("[+] Enter expression: ");
      std::string expression = Logger::get_instance().get_user_input();
      fileLoader.create_file(file_name, expression);
    } else {
      Logger::get_instance().log("[!] Invalid option.");
    }
    Logger::get_instance().log_not_jump("Want to continue? (y/n): ");
    std::string user_input = Logger::get_instance().get_user_input();
    if (user_input == "n") {
      break;
    } else {
      fileLoader.clear_files();
      Logger::get_instance().clear_console();
    }
  }
  return EXIT_SUCCESS;
}