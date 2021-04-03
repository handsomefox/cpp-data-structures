#include "src/Array.h"
#include "src/String.h"
#include "src/Vector.h"
#include <iostream>

int main() {
  mango::RunVectorTest();
  std::cin.get();
  system("CLS");
  mango::RunArrayTest();
  std::cin.get();
  system("CLS");
  mango::RunStringTest();
  std::cin.get();
}
