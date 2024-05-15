//
// Created by mac on 2024/5/11.
//

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <SDL.h>

#include <memory>
#include <vector>

#include "game/Component.h"
#include "game/ComponentTransform.h"

class Object {
   public:
    Object();

    void Awake();

    void Start();

    void Update(float deltaTime);

    void LateUpdate(float deltaTime);

    void RenderUpdate();

    void EventUpdate(SDL_Event* e);

    void QueueForRemoval();

    bool IsQueuedForRemoval() const;

    template <typename T>
    std::shared_ptr<T> AddComponent() {
        // This ensures that we only try to add a class the derives
        // from Component. This is tested at compile time.
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existingComponent : components) {
            // Currently we prevent adding the same component twice.
            // This may be something we will change in the future.
            if (std::dynamic_pointer_cast<T>(existingComponent)) {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components.push_back(newComponent);
        return newComponent;
    }

    template <typename T>
    std::shared_ptr<T> GetComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existingComponent : components) {
            if (std::dynamic_pointer_cast<T>(existingComponent)) {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }

        return nullptr;
    }

    std::shared_ptr<ComponentTransform> transform;

   private:
    std::vector<std::shared_ptr<Component>> components;

    bool queuedForRemoval;
};

#endif  // MAIN_OBJECT_H
