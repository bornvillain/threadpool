#pragma once

#include <vector>
#include <thread>
#include <functional>
#include "safe_queue.h"

class thread_pool final {
public:
    explicit thread_pool(size_t thread_count = std::thread::hardware_concurrency());

    thread_pool(const thread_pool &) = delete;

    thread_pool(const thread_pool &&) = delete;

    thread_pool &operator=(const thread_pool &) = delete;

    thread_pool &operator=(thread_pool &&) = delete;

    ~thread_pool();

    void submit(const std::function<void()> &task);

private:
    std::vector<std::thread> threads_;
    safe_queue<std::function<void()>> safe_queue_;

    void work();
};
