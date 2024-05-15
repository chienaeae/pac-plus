//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_RESOURCEALLOCATOR_H
#define MAIN_RESOURCEALLOCATOR_H

#include <map>
#include <memory>
#include <string>

template <typename T>
class ResourceAllocator {
   public:
    ResourceAllocator() : mCurrentID(0) {};

    int Add(const std::string& tFilePath) {
        auto it = mResources.find(tFilePath);
        if (it != mResources.end()) {
            return it->second.first;
        }

        std::shared_ptr<T> resource = std::make_shared<T>();
        if (!resource->LoadFromFile(tFilePath)) {
            return -1;
        }

        mResources.insert(std::make_pair(tFilePath, std::make_pair(mCurrentID, resource)));

        return mCurrentID++;
    }

    void Remove(int tID) {
        for (auto it = mResources.begin(); it != mResources.end(); it++) {
            if (it->second.first == tID) {
                mResources.erase(it->first);
            }
        }
    }

    std::shared_ptr<T> Get(int tID) {
        for (auto it = mResources.begin(); it != mResources.end(); it++) {
            if (it->second.first == tID) {
                return it->second.second;
            }
        }

        return nullptr;
    }

    bool Has(int tID) {
        return (Get(tID) != nullptr);
    }

   private:
    int mCurrentID;
    std::map<std::string, std::pair<int, std::shared_ptr<T>>> mResources;
};

#endif  // MAIN_RESOURCEALLOCATOR_H
