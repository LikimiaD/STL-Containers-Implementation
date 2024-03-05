#include <gtest/gtest.h>

#include "custom_list.h"

TEST(CustomListTest, ConstructorAndSize) {
  CustomList<int> list1;
  EXPECT_EQ(list1.size(), 0);

  CustomList<int> list2(5);
  EXPECT_EQ(list2.size(), 5);

  CustomList<int> list3{1, 2, 3, 4, 5};
  EXPECT_EQ(list3.size(), 5);
}
TEST(CustomListTest, PushBackAndFront) {
  CustomList<int> list;
  list.push_back(1);
  list.push_back(2);

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.size(), 2);
}
TEST(CustomListTest, PushFrontAndBack) {
  CustomList<int> list;
  list.push_front(1);
  list.push_front(2);

  EXPECT_EQ(list.back(), 1);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.size(), 2);
}
TEST(CustomListTest, Clear) {
  CustomList<int> list{1, 2, 3, 4, 5};
  list.clear();

  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}
TEST(CustomListTest, Erase) {
  CustomList<int> list{1, 2, 3, 4, 5};
  auto it = list.begin();
  ++it;
  list.erase(it);

  EXPECT_EQ(list.size(), 4);
  auto newIt = list.begin();
  EXPECT_EQ(*newIt, 1);
  ++newIt;
  EXPECT_EQ(*newIt, 3);
}
TEST(CustomListTest, PopFrontEmptyList) {
  CustomList<int> list;
  EXPECT_EQ(list.size(), 0);
  list.pop_front();
  EXPECT_EQ(list.size(), 0);
}
TEST(CustomListTest, PopFrontSingleElement) {
  CustomList<int> list;
  list.push_front(1);
  EXPECT_EQ(list.size(), 1);
  list.pop_front();
  EXPECT_EQ(list.size(), 0);
}
TEST(CustomListTest, PopFrontMultipleElements) {
  CustomList<int> list;
  list.push_front(1);
  list.push_front(2);
  EXPECT_EQ(list.size(), 2);
  list.pop_front();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 1);
}