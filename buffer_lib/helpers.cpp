#include "../include/helper.hpp"

void clearScreen() { std::cout << CLEAR_SCREEN; }

void PrintMenu() {
  clearScreen();
  std::cout << "        ==== MENU ====\n\n";
  std::cout << "0 - exit.\n"
            << "1 - add 100 000 elements in buffer.\n"
            << "2 - remove 100 000 elements.\n"
            << "3 - remove all elements.\n"
            << "4 - ASC sort buffer.\n"
            << "5 - DESC sort buffer.\n"
            << "6 - reverse data.\n"
            << "7 - count even indexes of buffer.\n"
            << "8 - count odd indexes of buffer.\n"
            << "9 - read (count elements num).\n";
}