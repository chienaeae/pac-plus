//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <SDL.h>

#include <memory>
#include <vector>

#include "game/component-transform.h"
#include "game/component.h"

class Object {
   public:
    Object();

    void Awake();

    void Start();

    void Update(float tDeltaTime);

    void LateUpdate(float tDeltaTime);

    void RenderUpdate(SDL_Renderer* tRenderer);

    void EventUpdate(SDL_Event* tEvent);

    void QueueForRemoval();

    [[nodiscard]] auto IsQueuedForRemoval() const -> bool;

    template <typename T>
    auto AddComponent() -> std::shared_ptr<T> {
        // This ensures that we only try to add a class the derives
        // from Component. This is tested at compile time.
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existingComponent : mComponents) {
            // Currently we prevent adding the same component twice.
            // This may be something we will change in the future.
            if (std::dynamic_pointer_cast<T>(existingComponent)) {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        mComponents.push_back(newComponent);
        return newComponent;
    }

    template <typename T>
    auto GetComponent() -> std::shared_ptr<T> {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existingComponent : mComponents) {
            if (std::dynamic_pointer_cast<T>(existingComponent)) {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }

        return nullptr;
    }

    std::shared_ptr<ComponentTransform> Transform;

   private:
    std::vector<std::shared_ptr<Component>> mComponents;

    bool mQueuedForRemoval;
};

#endif  // MAIN_OBJECT_H
