//
// Created by mac on 5/19/24.
//

#include "game/component-animation.h"

#include "game/object.h"

ComponentAnimation::ComponentAnimation(Object *tOwner)
    : Component(tOwner), mCurrentAnimation(AnimationState::None, nullptr) {}

void ComponentAnimation::Awake() {
    mSprite = mOwner->GetComponent<ComponentSprite>();
}

void ComponentAnimation::Update(float tDeltaTime) {
    if (mCurrentAnimation.first != AnimationState::None) {
        bool newFrame = mCurrentAnimation.second->UpdateFrame(tDeltaTime);

        if (newFrame) {
            const FrameData &data = *mCurrentAnimation.second->GetCurrentFrame();

            mSprite->Load(data.id);

            mSprite->SetTextureRect(data.x, data.y, data.width, data.height);
        }
    }
}

void ComponentAnimation::AddAnimation(AnimationState state,
                                      const std::shared_ptr<Animation> &animation) {
    mAnimations.insert(std::make_pair(state, animation));

    if (mCurrentAnimation.first == AnimationState::None) {
        SetAnimationState(state);
    }
}

void ComponentAnimation::SetAnimationState(AnimationState tState) {
    if (mCurrentAnimation.first == tState) {
        return;
    }

    auto animation = mAnimations.find(tState);
    if (animation != mAnimations.end()) {
        mCurrentAnimation.first = animation->first;
        mCurrentAnimation.second = animation->second;

        mCurrentAnimation.second->Reset();
    }
}

void ComponentAnimation::SetAnimationDirection(FacingDirection dir) {
    if (mCurrentAnimation.first != AnimationState::None) {
        mCurrentAnimation.second->SetDirection(dir);
    }
    if (dir == FacingDirection::Right) {
        mSprite->SetRotation(0);
    } else if (dir == FacingDirection::Left) {
        const int SEMICIRCLE_ANGLE_DEGREE = 180;
        mSprite->SetRotation(SEMICIRCLE_ANGLE_DEGREE);
    } else if (dir == FacingDirection::Down) {
        const int RIGHT_ANGLE_DEGREE = 90;
        mSprite->SetRotation(RIGHT_ANGLE_DEGREE);
    } else if (dir == FacingDirection::Up) {
        const int RIGHT_ANGLE_DEGREE = 90;
        mSprite->SetRotation(-RIGHT_ANGLE_DEGREE);
    }
}

auto ComponentAnimation::GetAnimationState() const -> const AnimationState & {
    // Returns out current animation state. We can use this to compare the objects current state to
    // a desired state.
    return mCurrentAnimation.first;
}

auto ComponentAnimation::GetAnimationDirection() const -> const FacingDirection {
    return mCurrentAnimation.second->GetDirection();
}
