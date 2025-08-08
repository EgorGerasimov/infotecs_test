#include "../include/task_manager.hpp"

TaskManager::TaskManager(const std::string& filename) : logger(filename) {
  this->thr = std::thread([this]() {
    while (true) {
      std::unique_lock<std::mutex> lock(this->mtxTask);

      cv.wait(lock, [this]() { return !tasks.empty() || stopThread; });
      if (stopThread && this->tasks.empty()) return;

      while (!tasks.empty()) {
        auto func = std::move(tasks.front());
        tasks.pop();
        lock.unlock();
        func();
        lock.lock();
      }
      logger.create_log(Logger::INFO, "Tasks completed");
    }
  });
}

void TaskManager::stop_thread() {
  this->stopThread = true;
  cv.notify_one();
}

void TaskManager::add_task(std::function<void()> func) {
  std::unique_lock<std::mutex> lock(mtxTask);
  bool wasEmpty = this->tasks.empty();
  tasks.push(func);
  if (wasEmpty) cv.notify_one();
}

TaskManager::~TaskManager() {
  this->thr.join();
  logger.create_log(Logger::INFO, "===== EXIT =====");
}