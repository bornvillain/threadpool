#include <iostream>
#include "thread_pool.h"

void example_task1() {
    std::cout << __FUNCTION__ << ": task is executed on thread: " << std::this_thread::get_id() << std::endl;
}

void example_task2() {
    std::cout << __FUNCTION__ << ": task is executed on thread: " << std::this_thread::get_id() << std::endl;
}

int main() {

    thread_pool pool;

    for (int i = 0; i < 5; ++i) {
        pool.submit(example_task1);
        pool.submit(example_task2);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}