#include <gtest/gtest.h>

#include "custom_set.h"

TEST(CustomSetTest, DefaultConstructor) {
  CustomSet<int> set;
  EXPECT_TRUE(set.empty());
}
TEST(CustomSetTest, InitializerListConstructor) {
  CustomSet<int> set({1, 2, 3});
  EXPECT_EQ(set.size(), 3);
}
TEST(CustomSetTest, InsertAndFind) {
  CustomSet<int> set;
  auto result = set.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(*set.find(1), 1);
  EXPECT_EQ(set.size(), 1);
}
TEST(CustomSetTest, Erase) {
  CustomSet<int> set({1, 2, 3});
  set.erase(2);
  EXPECT_EQ(set.size(), 2);
  EXPECT_EQ(set.find(2), set.end());
}
TEST(CustomSetTest, Clear) {
  CustomSet<int> set({1, 2, 3});
  set.clear();
  EXPECT_TRUE(set.empty());
}
TEST(CustomSetTest, EmplaceHint) {
  CustomSet<int> set;
  set.insert(1);
  set.insert(3);
  auto it = set.find(3);
  set.emplace_hint(it, 2);
  EXPECT_EQ(set.size(), 3);
  EXPECT_EQ(set.find(2), set.end());
}