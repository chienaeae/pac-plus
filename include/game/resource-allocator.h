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

    auto Add(const std::string& tFilePath) -> int {
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

    auto Get(int tID) -> std::shared_ptr<T> {
        for (auto it = mResources.begin(); it != mResources.end(); it++) {
            if (it->second.first == tID) {
                return it->second.second;
            }
        }

        return nullptr;
    }

    auto Has(int tID) -> bool {
        return (Get(tID) != nullptr);
    }

   private:
    int mCurrentID;
    std::map<std::string, std::pair<int, std::shared_ptr<T>>> mResources;
};

#endif  // MAIN_RESOURCEALLOCATOR_H
