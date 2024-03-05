#include <gtest/gtest.h>

#include "custom_multiset.h"

TEST(MultiSetTest, DefaultConstructor) {
  MultiSet<int> mset;
  EXPECT_TRUE(mset.empty());
}

TEST(MultiSetTest, InitializerListConstructor) {
  MultiSet<int> mset({1, 2, 3});
  EXPECT_EQ(mset.size(), 3);
}

TEST(MultiSetTest, InsertAndCount) {
  MultiSet<int> mset;
  mset.insert(1);
  mset.insert(2);
  mset.insert(3);
  EXPECT_EQ(mset.count(1), 1);
  EXPECT_EQ(mset.count(2), 1);
  EXPECT_EQ(mset.count(3), 1);
}

TEST(MultiSetTest, Erase) {
  MultiSet<int> mset({1, 2, 3});
  auto it = mset.find(2);
  mset.erase(it);
  EXPECT_EQ(mset.size(), 3);
  EXPECT_EQ(mset.count(2), 0);
}

TEST(MultiSetTest, Clear) {
  MultiSet<int> mset({1, 2, 3});
  mset.clear();
  EXPECT_TRUE(mset.empty());
}

TEST(MultiSetTest, Contains) {
  MultiSet<int> mset({1, 2, 3});
  EXPECT_TRUE(mset.contains(1));
  EXPECT_FALSE(mset.contains(4));
}

TEST(MultiSetTest, Iterators) {
  MultiSet<int> mset({1, 2, 3});
  int sum = 0;
  for (auto it = mset.begin(); it != mset.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

TEST(MultiSetTest, Bounds) {
  MultiSet<int> mset({1, 2, 3, 4});
  auto lower = mset.lower_bound(3);
  auto upper = mset.upper_bound(3);
  EXPECT_EQ(*lower, 3);
  EXPECT_EQ(*upper, 4);
}

TEST(MultiSetTest, Swap) {
  MultiSet<int> mset1({1, 2});
  MultiSet<int> mset2({3, 4});
  mset1.swap(mset2);
  EXPECT_TRUE(mset1.contains(3));
  EXPECT_TRUE(mset2.contains(1));
}

TEST(MultiSetTest, Merge) {
  MultiSet<int> mset1({1, 2});
  MultiSet<int> mset2({3, 4});
  mset1.merge(mset2);
  EXPECT_EQ(mset1.size(), 4);
  EXPECT_TRUE(mset2.empty());
}