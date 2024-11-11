#include "thread_pool.h"

thread_pool::thread_pool(size_t thread_count) {
    for (int i = 0; i < thread_count; ++i) {
        threads_.emplace_back([this] { work(); });
    }
}

thread_pool::~thread_pool() {
    safe_queue_.terminate();
    for (std::thread &t: threads_) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void thread_pool::submit(const std::function<void()> &task) {
    safe_queue_.push(task);
}

void thread_pool::work() {
    while (true) {
        try {
            auto task = safe_queue_.pop();
            task();
        }
        catch (const std::runtime_error &) {
            break;
        }
    }
}

