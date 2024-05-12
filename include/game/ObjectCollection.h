//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_OBJECTCOLLECTION_H
#define MAIN_OBJECTCOLLECTION_H

#include <memory>
#include <vector>

#include <SDL.h>

#include "game/Object.h"

class ObjectCollection {
public:
    void Add(std::shared_ptr<Object> object);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void EventUpdate(SDL_Event *e);
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

#endif //MAIN_OBJECTCOLLECTION_H
