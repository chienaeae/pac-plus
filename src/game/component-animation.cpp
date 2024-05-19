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

auto ComponentAnimation::GetAnimationState() const -> const AnimationState & {
    // Returns out current animation state. We can use this to compare the objects current state to
    // a desired state.
    return mCurrentAnimation.first;
}
