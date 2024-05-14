#include <gtest/gtest.h>

#include "game/ObjectCollection.h"
#include "game/Object.h"

class ObjectCollectionTest : public ::testing::Test {
protected:
    ObjectCollection collection;

    void SetUp() override {

    }

    void TearDown() override {
        collection.Clear();
    }
};

TEST_F(ObjectCollectionTest, TestObjectCollectionAddMethodNotProcessed) {
    auto object = std::make_shared<Object>();
    collection.Add(object);
    EXPECT_EQ(collection.Size(), 0);  // check if object has not yet been processed
}

TEST_F(ObjectCollectionTest, TestObjectCollectionProcessNewObjectsMethod) {
    auto object = std::make_shared<Object>();
    collection.Add(object);
    collection.ProcessNewObjects();
    EXPECT_EQ(collection.Size(), 1);  // check if object is successfully processed
}

TEST_F(ObjectCollectionTest, TestObjectCollectionProcessRemovalsMethod) {
    auto object = std::make_shared<Object>();
    collection.Add(object);
    collection.ProcessNewObjects();
    object->QueueForRemoval();  // assuming that QueueForRemoval method exists in your Object class
    collection.ProcessRemovals();
    EXPECT_EQ(collection.Size(), 0);  // check if object is successfully removed
}

TEST_F(ObjectCollectionTest, TestProcessNewObjectsTwice) {
    auto object1 = std::make_shared<Object>();
    collection.Add(object1);
    collection.ProcessNewObjects();
    collection.ProcessNewObjects();  // processing again should not add any new objects
    EXPECT_EQ(collection.Size(), 1);
}

TEST_F(ObjectCollectionTest, TestProcessRemovalsTwice) {
    auto object1 = std::make_shared<Object>();
    collection.Add(object1);
    object1->QueueForRemoval();
    collection.ProcessRemovals();
    collection.ProcessRemovals();  // processing again should not remove any more objects
    EXPECT_EQ(collection.Size(), 0);
}

TEST_F(ObjectCollectionTest, TestObjectNotInCollection) {
    auto object1 = std::make_shared<Object>();
    auto object2 = std::make_shared<Object>();
    collection.Add(object1);
    collection.ProcessNewObjects();
    object2->QueueForRemoval();
    collection.ProcessRemovals();  // object2 is not in collection, so size should be still 1
    EXPECT_EQ(collection.Size(), 1);
}
