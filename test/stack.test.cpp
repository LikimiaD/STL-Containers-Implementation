#include <custom_stack.h>
#include <gtest/gtest.h>

#include <ostream>
#include <stack>

typedef struct Amogus {
  bool is_impostor;
  Amogus() : is_impostor(false) {}
  Amogus(bool impostor) : is_impostor(impostor) {}
} Amogus;

bool operator==(const Amogus& lhs, const Amogus& rhs) {
  return lhs.is_impostor == rhs.is_impostor;
}

bool operator==(const Amogus& lhs, bool rhs) { return lhs.is_impostor == rhs; }

std::ostream& operator<<(std::ostream& o, const Amogus& a) {
  o << std::boolalpha << a.is_impostor;
  return o;
}

TEST(custom_stack, compliance) {
  CustomStack<Amogus> stack;
  CustomStack<Amogus> stack2;
  std::stack<Amogus> stl;

  stack.push(Amogus(true));
  stack.push(Amogus(false));
  stack.push(Amogus(true));
  stack.push(Amogus(false));
  stack.push(Amogus(true));
  stack.push(Amogus(false));
  stack.push(Amogus(true));
  stack.push(Amogus(false));
  stack.push(Amogus(true));

  stl.push(Amogus(true));
  stl.push(Amogus(false));
  stl.push(Amogus(true));
  stl.push(Amogus(false));
  stl.push(Amogus(true));
  stl.push(Amogus(false));
  stl.push(Amogus(true));
  stl.push(Amogus(false));
  stl.push(Amogus(true));

  EXPECT_EQ(stack.size(), stl.size());

  stack2.swap(stack);

  EXPECT_EQ(stack.size(), 0ul);
  EXPECT_EQ(stack2.size(), stl.size());

  while (!stack2.empty()) {
    EXPECT_EQ(stack2.top(), stl.top());

    stack2.pop();
    stl.pop();
  }

  EXPECT_EQ(stack2.size(), 0ul);
  EXPECT_EQ(stack2.size(), 0ul);

  stack2.emplace(true);

  EXPECT_EQ(stack2.size(), 1ul);
  EXPECT_EQ(stack2.top(), true);
}
