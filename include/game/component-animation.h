//
// Created by mac on 5/19/24.
//

#ifndef PAC_PLUS_COMPONENT_ANIMATION_H
#define PAC_PLUS_COMPONENT_ANIMATION_H

#include "game/animation.h"
#include "game/component-sprite.h"
#include "game/component.h"

enum class AnimationState { None, Idle, Walk };

class ComponentAnimation : public Component {
   public:
    ComponentAnimation(Object *tOwner);

    void Awake() override;

    void Update(float tDeltaTime) override;

    void AddAnimation(AnimationState tState, const std::shared_ptr<Animation> &tAnimation);

    void SetAnimationState(AnimationState tState);

    const AnimationState &GetAnimationState() const;

   private:
    std::shared_ptr<ComponentSprite> mSprite;
    std::map<AnimationState, std::shared_ptr<Animation>> mAnimations;

    // mCurrentAnimation stores a reference to the current animation, so we can quickly update and
    // draw it
    std::pair<AnimationState, std::shared_ptr<Animation>> mCurrentAnimation;
};

#endif  // PAC_PLUS_COMPONENT_ANIMATION_H
