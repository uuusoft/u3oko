/**
\file       ut-libs-helpers-check.cxx
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2026
\project    u3_helpers_lib

U3_COMMERCIAL_PART_SOURCE
*/
#include <gtest/gtest.h>
#include "../../helpers-lib-includes_int"

// Demonstrate some basic assertions.
TEST (LibsHelpersCheckTest2, BasicAssertions2)
{
  // Expect two strings not to be equal.
  EXPECT_STRNE ("hello", "world");
  // Expect equality.
  EXPECT_EQ (7 * 6, 42);
}
