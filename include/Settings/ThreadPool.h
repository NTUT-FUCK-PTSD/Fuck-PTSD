//
// Created by 陳世昂 on 2024/4/30.
//

#ifndef FUCK_PTSD_THREADPOOL_H
#define FUCK_PTSD_THREADPOOL_H

#include <future>
#include <iostream>

namespace Settings {
class ThreadPool {
public:
    explicit ThreadPool();
    ~ThreadPool();

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
};
}  // namespace Settings

#endif  // FUCK_PTSD_THREADPOOL_H
