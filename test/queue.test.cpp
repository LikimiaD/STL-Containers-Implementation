#include <gtest/gtest.h>

#include "custom_queue.h"

TEST(CustomQueueTest, DefaultConstructor_EmptyQueue) {
  CustomQueue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(CustomQueueTest, InitializerListConstructor) {
  CustomQueue<int> q({1, 2, 3});
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(CustomQueueTest, PushAndPop) {
  CustomQueue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 2);
}

TEST(CustomQueueTest, FrontAndBack) {
  CustomQueue<int> q({10, 20, 30});
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 30);
  q.pop();
  EXPECT_EQ(q.front(), 20);
}

TEST(CustomQueueTest, CopyConstructor) {
  CustomQueue<int> q1({1, 2, 3});
  CustomQueue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(CustomQueueTest, MoveConstructor) {
  CustomQueue<int> q1(CustomQueue<int>({4, 5, 6}));
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 6);
}

TEST(CustomQueueTest, CopyAssignment) {
  CustomQueue<int> q1({7, 8, 9});
  CustomQueue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 7);
  EXPECT_EQ(q2.back(), 9);
}

TEST(CustomQueueTest, MoveAssignment) {
  CustomQueue<int> q1;
  q1 = CustomQueue<int>({10, 11, 12});
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 10);
  EXPECT_EQ(q1.back(), 12);
}
