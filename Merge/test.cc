#include <iostream>
#include <random>

int main() {
  int seed=0;
  srand(seed);
    int ran = rand();
    std::cout << "Randome: " << ran << std::endl;
    srand(seed);
    int t = rand();
    std::cout << "second rand: " << t << std::endl;
    srand(seed);
    std::cout << "third rand: " << rand() << std::endl;
}
