#include <gtest/gtest.h>

#include "custom_array.h"

TEST(CustomArrayTest, DefaultConstructor) {
  CustomArray<int, 5> arr;
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], int{}) << "Elements should be value-initialized";
  }
}
TEST(CustomArrayTest, InitializerListConstructor) {
  CustomArray<int, 5> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 0);
}
TEST(CustomArrayTest, AtMethod) {
  CustomArray<int, 5> arr;
  arr[0] = 1;
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}
TEST(CustomArrayTest, SubscriptOperator) {
  CustomArray<int, 5> arr;
  arr[0] = 1;
  EXPECT_EQ(arr[0], 1);
}
TEST(CustomArrayTest, FrontMethod) {
  CustomArray<int, 5> arr{1, 2, 3};
  EXPECT_EQ(arr.front(), 1);
}
TEST(CustomArrayTest, BackMethod) {
  CustomArray<int, 5> arr{1, 2, 3};
  EXPECT_EQ(arr.back(), 0);
}
TEST(CustomArrayTest, EmptyMethod) {
  CustomArray<int, 1> arr;
  EXPECT_FALSE(arr.empty());
}
TEST(CustomArrayTest, SizeMethod) {
  CustomArray<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
}
TEST(CustomArrayTest, MaxSizeMethod) {
  CustomArray<int, 5> arr;
  EXPECT_GE(arr.max_size(), 5);
}
TEST(CustomArrayTest, SwapMethod) {
  CustomArray<int, 2> arr1{1, 2}, arr2{3, 4};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 3);
  EXPECT_EQ(arr2[0], 1);
}
TEST(CustomArrayTest, FillMethod) {
  CustomArray<int, 5> arr;
  arr.fill(1);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 1) << "All elements should be set to 1";
  }
}