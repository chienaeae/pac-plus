//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_OBJECTCOLLECTION_H
#define MAIN_OBJECTCOLLECTION_H

#include <SDL.h>

#include <memory>
#include <vector>

#include "game/object.h"

class ObjectCollection {
   public:
    void Add(const std::shared_ptr<Object>& tObject);

    void Update(float tDeltaTime);
    void LateUpdate(float tDeltaTime);
    void EventUpdate(SDL_Event* tEvent);
    void RenderUpdate();

    int Size();
    void Clear();

    // ProcessNewObjects: It separates the processing of new objects into its own method,
    // so it can be run at a convenient time (such as end of a frame). This method will
    // be moving objects added from a temporary new object collection to the main object
    // collection.
    void ProcessNewObjects();

    void ProcessRemovals();

   private:
    std::vector<std::shared_ptr<Object>> mObjects;

    // mNewObject: It used to temporarily store recently added objects.
    std::vector<std::shared_ptr<Object>> mNewObjects;
};

#endif  // MAIN_OBJECTCOLLECTION_H
