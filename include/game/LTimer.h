//
// Created by mac on 2024/4/10.
//

#ifndef MAIN_LTIMER_H
#define MAIN_LTIMER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <sstream>
#include <string>

class LTimer {
   public:
    LTimer();

    void start();

    void stop();

    void pause();

    void unpause();

    Uint64 getTicks() const;

    bool isStarted() const;

    bool isPaused() const;

   private:
    // The clock time when the timer started
    Uint64 mStartTicks;
    // The ticks stored when the timer was paused
    Uint64 mPausedTicks;

    bool mPaused;
    bool mStarted;
};

#endif  // MAIN_LTIMER_H
