#include <gtest/gtest.h>

#include <memory>

#include "game/Object.h"
#include "game/ObjectCollection.h"

class ObjectCollectionTest : public ::testing::Test {
   protected:
    // 如果确实需要在派生类中访问 collection，可以使用受保护的访问函数
    ObjectCollection& getCollectionProtected() {
        return collection;
    }

    void SetUp() override {}

    void TearDown() override {
        collection.Clear();
    }

   private:
    ObjectCollection collection;
};

TEST_F(ObjectCollectionTest, TestObjectCollectionAddMethodNotProcessed) {
    auto object = std::make_shared<Object>();
    getCollectionProtected().Add(object);
    EXPECT_EQ(getCollectionProtected().Size(), 0);  // check if object has not yet been processed
}

TEST_F(ObjectCollectionTest, TestObjectCollectionProcessNewObjectsMethod) {
    auto object = std::make_shared<Object>();
    getCollectionProtected().Add(object);
    getCollectionProtected().ProcessNewObjects();
    EXPECT_EQ(getCollectionProtected().Size(), 1);  // check if object is successfully processed
}

TEST_F(ObjectCollectionTest, TestObjectCollectionProcessRemovalsMethod) {
    auto object = std::make_shared<Object>();
    getCollectionProtected().Add(object);
    getCollectionProtected().ProcessNewObjects();
    object->QueueForRemoval();  // assuming that QueueForRemoval method exists in your Object class
    getCollectionProtected().ProcessRemovals();
    EXPECT_EQ(getCollectionProtected().Size(), 0);  // check if object is successfully removed
}

TEST_F(ObjectCollectionTest, TestProcessNewObjectsTwice) {
    auto object1 = std::make_shared<Object>();
    getCollectionProtected().Add(object1);
    getCollectionProtected().ProcessNewObjects();
    getCollectionProtected()
        .ProcessNewObjects();  // processing again should not add any new objects
    EXPECT_EQ(getCollectionProtected().Size(), 1);
}

TEST_F(ObjectCollectionTest, TestProcessRemovalsTwice) {
    auto object1 = std::make_shared<Object>();
    getCollectionProtected().Add(object1);
    object1->QueueForRemoval();
    getCollectionProtected().ProcessRemovals();
    getCollectionProtected()
        .ProcessRemovals();  // processing again should not remove any more objects
    EXPECT_EQ(getCollectionProtected().Size(), 0);
}

TEST_F(ObjectCollectionTest, TestObjectNotInCollection) {
    auto object1 = std::make_shared<Object>();
    auto object2 = std::make_shared<Object>();
    getCollectionProtected().Add(object1);
    getCollectionProtected().ProcessNewObjects();
    object2->QueueForRemoval();
    getCollectionProtected()
        .ProcessRemovals();  // object2 is not in collection, so size should be still 1
    EXPECT_EQ(getCollectionProtected().Size(), 1);
}
