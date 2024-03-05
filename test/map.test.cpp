#include <gtest/gtest.h>

#include "custom_map.h"

TEST(MapTest, InsertAndFind) {
  Map<int, std::string> map;
  auto [iter, success] = map.insert(1, "one");
  ASSERT_TRUE(success);
  ASSERT_EQ(iter->second, "one");
  ASSERT_EQ(map.at(1), "one");
}
TEST(MapTest, InsertOrAssign) {
  Map<int, std::string> map;
  map.insert(2, "two");
  auto [iter, success] = map.insert_or_assign(2, "second");
  ASSERT_FALSE(success);
  ASSERT_EQ(iter->second, "second");
  ASSERT_EQ(map.at(2), "second");
}
TEST(MapTest, Erase) {
  Map<int, std::string> map;
  map.insert(3, "three");
  auto iter = map.begin();
  map.erase(iter);
  ASSERT_TRUE(map.empty());
}
TEST(MapTest, AccessAndMissingKey) {
  Map<int, std::string> map;
  map[4] = "four";
  ASSERT_EQ(map.at(4), "four");
  EXPECT_THROW(map.at(5), std::out_of_range);
}
TEST(MapTest, SizeAndEmpty) {
  Map<int, std::string> map;
  ASSERT_TRUE(map.empty());
  map.insert(5, "five");
  ASSERT_EQ(map.size(), 1);
  ASSERT_FALSE(map.empty());
}
TEST(MapTest, SwapAndMerge) {
  Map<int, std::string> map1, map2;
  map1.insert(1, "one");
  map2.insert(2, "two");
  map1.swap(map2);
  ASSERT_TRUE(map1.contains(2));
  ASSERT_TRUE(map2.contains(1));

  map1.merge(map2);
  ASSERT_TRUE(map1.contains(1));
  ASSERT_EQ(map1.size(), 2);
}
TEST(MapTest, InsertMany) {
  Map<int, std::string> map;
  auto results =
      map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"));
  ASSERT_EQ(results.size(), 2);
  ASSERT_TRUE(results[0].second);
  ASSERT_TRUE(results[1].second);
  ASSERT_EQ(map.size(), 2);
}
