//
// Created by adven on 2024/3/10.
//

#ifndef FUCK_PTSD_EVENTLISTENER_H
#define FUCK_PTSD_EVENTLISTENER_H

#include <functional>
#include <iostream>

class PollHandler final {
private:
    std::vector<std::function<void()>> func_list;

public:
    explicit PollHandler();

    void add(bool condition, std::function<void()> func) {
        func_list.push_back(func);
    };
};

#endif // FUCK_PTSD_EVENTLISTENER_H
