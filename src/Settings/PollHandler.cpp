//
// Created by adven on 2024/3/10.
//
#include "PollHandler.h"

void PollHandler::listen() {
    for (int i = 0; i < condition_list.size(); i++) {
        if (condition_list[i]()) {
            func_list[i]();
        }
    }
}
PollHandler::PollHandler(){

};
