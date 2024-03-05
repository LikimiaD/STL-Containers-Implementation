#include <gtest/gtest.h>

#include "custom_vector.h"

TEST(CustomVectorTest, DefaultConstructor) {
  CustomVector<int> vec;
  EXPECT_EQ(0, vec.size());
}
TEST(CustomVectorTest, InitialCapacityConstructor) {
  CustomVector<int> vec(10);
  EXPECT_EQ(0, vec.size());
  EXPECT_GE(vec.capacity(), 10);
}
TEST(CustomVectorTest, CopyConstructor) {
  CustomVector<int> vec1(10);
  vec1.push_back(1);
  CustomVector<int> vec2 = vec1;
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1[0], vec2[0]);
}
TEST(CustomVectorTest, MoveConstructor) {
  CustomVector<int> vec1(10);
  vec1.push_back(1);
  CustomVector<int> vec2 = std::move(vec1);
  EXPECT_EQ(1, vec2.size());
  EXPECT_EQ(1, vec2[0]);
}
TEST(CustomVectorTest, CopyAssignmentOperator) {
  CustomVector<int> vec1(10);
  vec1.push_back(1);
  CustomVector<int> vec2;
  vec2 = vec1;
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1[0], vec2[0]);
}
TEST(CustomVectorTest, MoveAssignmentOperator) {
  CustomVector<int> vec1(10);
  vec1.push_back(1);
  CustomVector<int> vec2;
  vec2 = std::move(vec1);
  EXPECT_EQ(1, vec2.size());
  EXPECT_EQ(1, vec2[0]);
}
TEST(CustomVectorTest, AccessWithAt) {
  CustomVector<int> vec(10);
  vec.push_back(42);
  EXPECT_EQ(42, vec.at(0));
  EXPECT_THROW(vec.at(1), std::out_of_range);
}
TEST(CustomVectorTest, AccessWithOperator) {
  CustomVector<int> vec(10);
  vec.push_back(42);
  EXPECT_EQ(42, vec[0]);
}