#include "include/buffer.hpp"
#include "include/helper.hpp"
#include "include/task_manager.hpp"

int main() {
  Buffer<int> buffer;
  TaskManager TasksChange("change.log");
  TaskManager TasksRead("read.log");
  int input = -1;
  bool stop = false;

  PrintMenu();

  while (stop != true) {
    std::cout << "write num between 0 and 9\n";
    std::cin >> input;
    switch (input) {
      case 1:
        TasksChange.logger.create_log(Logger::INFO,
                                      "Inserting 100000 elements started");
        for (int i = 0; i < 100'000; i++)
          TasksChange.add_task([&buffer, i]() { buffer.insert(i); });
        break;
      case 2:
        if (buffer.lenght() >= 100'000) {
          TasksChange.logger.create_log(Logger::INFO,
                                        "Removing 100000 elements started");
          for (int i = 0; i < 100'000; i++)
            TasksChange.add_task([&buffer]() { buffer.remove(); });
        } else {
          TasksChange.logger.create_log(
              Logger::ERROR, "There are not 100000 elements in the buffer");
          std::cout << "You haven't added the elements yet\n";
        }
        break;
      case 3:
        TasksChange.logger.create_log(Logger::INFO,
                                      "Removing all elements started");
        TasksChange.add_task([&buffer]() { buffer.remove_all(); });
        break;
      case 4:
        TasksChange.logger.create_log(Logger::INFO, "ASC sorting started");
        TasksChange.add_task([&buffer]() { buffer.sort_ascending(); });
        break;
      case 5:
        TasksChange.logger.create_log(Logger::INFO, "DESC sorting started");
        TasksChange.add_task([&buffer]() { buffer.sort_descending(); });
        break;
      case 6:
        TasksChange.logger.create_log(Logger::INFO, "Reversing started");
        TasksChange.add_task([&buffer]() { buffer.reverse(); });
        break;
      case 7:
        TasksChange.logger.create_log(Logger::INFO, "Counting even started");
        TasksChange.add_task([&buffer]() {
          std::cout << buffer.count_even_positioned() << " even elements\n";
        });
        break;
      case 8:
        TasksChange.logger.create_log(Logger::INFO, "Counting odd started");
        TasksChange.add_task([&buffer]() {
          std::cout << buffer.count_odd_positioned() << " odd elements\n";
        });
        break;
      case 9:
        TasksRead.logger.create_log(Logger::INFO, "Reading started");
        TasksRead.add_task([&buffer]() { buffer.read(); });
        break;
      case 0:
        TasksChange.stop_thread();
        TasksRead.stop_thread();
        stop = true;
        break;
      default:
        TasksChange.logger.create_log(Logger::WARNING, "Wrong input");
        std::cout << "Wrong input\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
  }

  return 0;
}