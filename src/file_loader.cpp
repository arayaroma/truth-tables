#include "file_loader.hpp"

FileLoader::FileLoader() { setup_function_map(); }

void FileLoader::setup_function_map() {
  function_map["1"] = std::bind(&FileLoader::select_existing_file, this);
}

void FileLoader::handle_user_input(const std::string &user_option) {
  auto function = function_map.find(user_option);
  if (function != function_map.end()) {
    function->second();
  } else {
    Logger::get_instance().log("[!] Invalid option.");
  }
}

FileLoader &FileLoader::load_existing_files() {
  for (const auto &entry : std::filesystem::directory_iterator{directoryPath}) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
      files.push_back(entry.path().filename().string());
    }
  }
  return *this;
}

void FileLoader::display_files() {
  Logger::get_instance().clear_console();
  Logger::get_instance().log("Available files:");
  int number = 1;
  for (const std::string &file : files) {
    Logger::get_instance().log("[" + std::to_string(number) + "] " + file);
    number++;
  }
}

void FileLoader::select_existing_file() {
  load_existing_files().display_files();
  Logger::get_instance().log_not_jump("[+] Select a file: ");
  std::string userInput = Logger::get_instance().get_user_input();

  int selectedNumber = std::stoi(userInput);
  if (selectedNumber >= 1 && selectedNumber <= files.size()) {
    load_file(files[selectedNumber - 1]);
  } else {
    Logger::get_instance().log("[!] Invalid file number.");
  }
}

void FileLoader::load_file(const std::string &file) {
  std::ifstream input_file(directoryPath / file);
  std::string line;
  TruthTable truthTable;
  while (std::getline(input_file, line)) {
    truthTable.parse_expression(line).show_variables().build_table();
  }
  input_file.close();
}

void FileLoader::create_file(const std::string &file,
                             const std::string &expression) {
  std::ofstream output_file(directoryPath / (file + ".txt"));
  output_file << expression;
  output_file.close();
}