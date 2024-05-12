//
// Created by mac on 2024/5/12.
//

#ifndef MAIN_RESOURCEALLOCATOR_H
#define MAIN_RESOURCEALLOCATOR_H

#include <map>
#include <memory>
#include <string>

template<typename T>
class ResourceAllocator{

public:
    ResourceAllocator(): currentID(0){};

    int Add(const std::string& filePath) {
        auto it = resources.find(filePath);
        if(it != resources.end()){
            return it->second.first;
        }

        std::shared_ptr<T> resource = std::make_shared<T>();
        if(!resource -> LoadFromFile(filePath)){
            return -1;
        }

        resources.insert(
                std::make_pair(filePath, std::make_pair(currentID, resource))
                );

        return currentID ++;
    }

    void Remove(int id) {
        for(auto it = resources.begin(); it != resources.end(); it ++) {
            if(it->second.first == id){
                resources.erase(it->first);
            }
        }
    }

    std::shared_ptr<T> Get(int id) {
        for(auto it = resources.begin(); it != resources.end(); it++) {
            if(it -> second.first == id) {
                return it->second.second;
            }
        }

        return nullptr;
    }

    bool Has(int id) {
        return (Get(id) != nullptr);
    }

private:
    int currentID;
    std::map<std::string, std::pair<int, std::shared_ptr<T>>> resources;
};

#endif //MAIN_RESOURCEALLOCATOR_H
