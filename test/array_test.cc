#include "Array.h"
#include <gtest/gtest.h>

namespace {

TEST(Array, Construction) {
  Array<int> array;
  EXPECT_EQ(0, array.size());
  EXPECT_EQ(10, array.capacity());
}

} // namespace

