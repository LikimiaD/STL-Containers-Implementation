#include "rb_tree.h"

#include <gtest/gtest.h>

TEST(RBTreeTest, InsertAndFind) {
  RBTree<int, std::string> map;
  map.insert(1, "one");
  auto* result = map.find(1);
  EXPECT_EQ(result->value, "one");
}
TEST(RBTreeTest, Containment) {
  RBTree<int, std::string> map;
  map.insert(2, "two");
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}
TEST(RBTreeTest, Removal) {
  RBTree<int, std::string> map;
  map.insert(3, "three");
  map.remove(3);
  EXPECT_FALSE(map.contains(3));
}
TEST(RBTreeTest, RemovalError) {
  RBTree<int, std::string> map;
  map.insert(3, "three");
  EXPECT_ANY_THROW(map.remove(4));
}
TEST(RBTreeTest, Clear) {
  RBTree<int, std::string> map;
  map.insert(4, "four");
  map.insert(5, "five");
  map.clear();
  EXPECT_EQ(map.size(), 0);
}
TEST(RBTreeTest, Size) {
  RBTree<int, std::string> map;
  EXPECT_EQ(map.size(), 0);
  map.insert(6, "six");
  EXPECT_EQ(map.size(), 1);
  map.insert(7, "seven");
  EXPECT_EQ(map.size(), 2);
}
TEST(RBTreeTest, Find) {
  RBTree<int, std::string> map;
  map.insert(1, "one");
  auto* result = map.find(1);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->value, "one");
  EXPECT_EQ(map.find(2), nullptr);
}
TEST(RBTreeTest, MinimumAndMaximum) {
  RBTree<int, std::string> map;
  map.insert(10, "ten");
  map.insert(20, "twenty");
  map.insert(5, "five");
  auto* min = map.minimum();
  auto* max = map.maximum();
  ASSERT_NE(min, nullptr);
  ASSERT_NE(max, nullptr);
  EXPECT_EQ(min->value, "five");
  EXPECT_EQ(max->value, "twenty");
}