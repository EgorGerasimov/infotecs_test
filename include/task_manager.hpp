#pragma once

#include <chrono>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

class Logger {
 public:
  enum Event { ERROR, WARNING, INFO };

  explicit Logger(const std::string& filename);
  void create_log(Event event, const std::string& message);

 private:
  std::string filename;
  std::string log_path = "log/";

  std::string get_current_time();
};

class TaskManager {
 public:
  explicit TaskManager(const std::string& filename);
  ~TaskManager();
  void stop_thread();
  void add_task(std::function<void()> task);

  Logger logger;

 private:
  std::thread thr;
  std::mutex mtxTask;
  std::condition_variable cv;
  std::queue<std::function<void()>> tasks;
  bool stopThread = false;
};