//
// Created by adven on 2024/5/2.
//

#ifndef FUCK_PTSD_ISC_H
#define FUCK_PTSD_ISC_H

#include "HEIS.h"
#include "HPIS.h"
#include "Signal.h"

#include <iostream>

namespace Game::Systems {
/**
 * @note internal-system-communication
 */
class ISC final {
public:
    template <class... Args>
    static void Handle(Systems::Signal signal, Args&&... args) {
        switch (signal) {
        case Systems::Signal::ADD_DROP_WEAPON:
            HEIS::MakeTile(std::forward<Args>(args)...);
            break;
        }
    };

private:
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_ISC_H
