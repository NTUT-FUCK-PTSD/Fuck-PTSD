//
// Created by adven on 2024/3/24.
//
#include "music/music.h"
#include "Util/Logger.hpp"

#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"

void music::test() {
//    // Define a couple of variables
//    SoLoud::Soloud soloud;  // SoLoud engine core
//    SoLoud::Speech speech;  // A sound source (speech, in this case)
//
//    // Configure sound source
//    speech.setText("1 2 3   1 2 3   Hello world. Welcome to So-Loud.");
//
//    // initialize SoLoud.
//    soloud.init();
//
//    // Play the sound source (we could do this several times if we wanted)
//    soloud.play(speech);
//
//    // Wait until sounds have finished
//    while (soloud.getActiveVoiceCount() > 0)
//    {
//        LOG_DEBUG("1");
//
//        // Still going, sleep for a bit
////        SoLoud::Thread::sleep(100);
//    }
//
//    // Clean up SoLoud
//    soloud.deinit();
}