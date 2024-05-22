//
// Created by mac on 5/19/24.
//

#ifndef PAC_PLUS_ANIMATION_H
#define PAC_PLUS_ANIMATION_H

#include <vector>

enum class FacingDirection {
    None,
    Left,
    Right,
    Down,
    Up,

};

struct FrameData {
    int id;                    // Texture id (retrieved from our texture allocator
    int x;                     // x position of sprite in the texture
    int y;                     // y position of sprite in the texture
    int width;                 // width of sprite
    int height;                // height of sprite
    float displayTimeSeconds;  // How long to display the frame
};

class Animation {
   public:
    Animation(FacingDirection tDirection);

    void AddFrame(int tTextureID, int tX, int tY, int tWidth, int tHeight, float tFrameTime);

    const FrameData* GetCurrentFrame() const;

    bool UpdateFrame(float tDeltaTime);

    void SetDirection(FacingDirection dir);

    FacingDirection GetDirection() const;

    void Reset();

   private:
    void incrementFrame();

    FacingDirection mDirection;

    // mFrames stores all frames for our animation
    std::vector<FrameData> mFrames;

    int mCurrentFrameIndex;

    // mCurrentFrameTime is to decide when to transition to the next frame
    float mCurrentFrameTime;
};

#endif  // PAC_PLUS_ANIMATION_H
