#pragma once

#include <queue>
#include <condition_variable>

template<typename T>
class safe_queue final {
public:

    safe_queue() = default;

    safe_queue(const safe_queue &&) = delete;

    safe_queue(const safe_queue &) = delete;

    safe_queue &operator=(const safe_queue &) = delete;

    safe_queue &operator=(safe_queue &&) = delete;

    void push(const T &value);

    T pop();

    void terminate();

private:
    std::mutex m_;
    std::queue<T> tasks_;
    std::condition_variable cv_;
    bool terminate_ = false;
};

template<typename T>
void safe_queue<T>::push(const T &value) {
    {
        std::lock_guard<std::mutex> guard{m_};
        tasks_.push(value);
    }
    cv_.notify_one();
}

template<typename T>
T safe_queue<T>::pop() {
    std::unique_lock<std::mutex> lock(m_);
    cv_.wait(lock, [this] { return !tasks_.empty() || terminate_; });
    if (terminate_ && tasks_.empty()) {
        throw std::runtime_error("Terminate signal received");
    }
    T value = tasks_.front();
    tasks_.pop();
    return value;
}

template<typename T>
void safe_queue<T>::terminate() {
    {
        std::lock_guard<std::mutex> guard{m_};
        terminate_ = true;
    }
    cv_.notify_all();
}