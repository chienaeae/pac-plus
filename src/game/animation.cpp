//
// Created by mac on 5/19/24.
//

#include "game/animation.h"

Animation::Animation() : mFrames(0), mCurrentFrameIndex(0), mCurrentFrameTime(0) {}

void Animation::AddFrame(int tTextureID, int tX, int tY, int tWidth, int tHeight,
                         float tFrameTime) {
    FrameData data{};
    data.id = tTextureID;
    data.x = tX;
    data.y = tY;
    data.width = tWidth;
    data.height = tHeight;
    data.displayTimeSeconds = tFrameTime;

    mFrames.push_back(data);
}
auto Animation::GetCurrentFrame() const -> const FrameData* {
    if (mFrames.size() > 0) {
        return &mFrames[mCurrentFrameIndex];
    }

    return nullptr;
}

auto Animation::UpdateFrame(float tDeltaTime) -> bool {
    if (mFrames.size() > 0) {
        mCurrentFrameTime += tDeltaTime;
        if (mCurrentFrameTime >= mFrames[mCurrentFrameIndex].displayTimeSeconds) {
            mCurrentFrameTime = 0.f;
            incrementFrame();
            return true;
        }
    }

    return false;
}

void Animation::Reset() {
    mCurrentFrameIndex = 0;
    mCurrentFrameTime = 0.f;
}

void Animation::incrementFrame() {
    mCurrentFrameIndex = (mCurrentFrameIndex + 1) % static_cast<int>(mFrames.size());
}
