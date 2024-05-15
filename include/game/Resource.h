//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_RESOURCE_H
#define MAIN_RESOURCE_H

#include <string>

class Resource {
   public:
    Resource() : mIsOn(false) {}

    virtual bool LoadFromFile(std::string) {
        return true;
    };

    virtual void Free() {};

    virtual bool isOn() {
        return mIsOn;
    };

   protected:
    int mIsOn;
};
#endif  // MAIN_RESOURCE_H
