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

class Timer {
   public:
    Timer();

    void start();

    void stop();

    void pause();

    void unpause();

    [[nodiscard]] auto getTicks() const -> Uint64;

    [[nodiscard]] auto isStarted() const -> bool;

    [[nodiscard]] auto isPaused() const -> bool;

   private:
    // The clock time when the timer started
    Uint64 mStartTicks{0};
    // The ticks stored when the timer was paused
    Uint64 mPausedTicks{0};

    bool mPaused{false};
    bool mStarted{false};
};

#endif  // MAIN_LTIMER_H
