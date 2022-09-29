#include <thread>
#include <iostream>

// C++ I love U!
/*  PLAN:
        1. Read about asynchronous  libs in c++
        2. Thread pool check
        3. Coroutines realisation check
        4. Make architecture of application + shared lib
        5. Start coding!
 */
int main() {
    const unsigned int processor_count = std::thread::hardware_concurrency();
    std::cout << processor_count << std::endl;
    return 0;
}