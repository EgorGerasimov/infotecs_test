#include "../include/task_manager.hpp"

Logger::Logger(const std::string& filename) {
  this->filename = filename;
  namespace fs = std::filesystem;
  try {
    fs::create_directory(this->log_path);
  } catch (const fs::filesystem_error& error) {
    std::cerr << "Ошибка при создании директории " << log_path << ": "
              << error.what() << std::endl;
  }
}

void Logger::create_log(Event event, const std::string& message) {
  std::fstream logfile;
  logfile.open(log_path + this->filename, std::ios::app);
  std::string new_log;
  switch (event) {
    case INFO:
      new_log = "[INFO] ";
      break;
    case WARNING:
      new_log = "[WARNING] ";
      break;
    case ERROR:
      new_log = "[ERROR] ";
      break;
    default:
      new_log = "[UNKNOWN TYPE] ";
  }
  logfile << '[' + get_current_time() + "] " + new_log + message + "\n";
  logfile.close();
}

std::string Logger::get_current_time() {
  auto now = std::chrono::system_clock::now();
  auto now_ms = std::chrono::round<std::chrono::milliseconds>(now);
  auto seconds = std::chrono::floor<std::chrono::seconds>(now_ms);
  auto ms = (now_ms.time_since_epoch() % std::chrono::seconds(1)).count();
  return std::format("{:%Y-%m-%d %H:%M:%S}.{:03d}", seconds, ms);
}
