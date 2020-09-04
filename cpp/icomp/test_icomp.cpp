#include <gtest/gtest.h>

#include "icomp.hpp"

TEST(IComp, returns_0_if_compare_two_empty_strings) {
	EXPECT_EQ(icmp2("", ""), 0);
}

TEST(IComp, returns_0_if_two_nonempty_string_equal) {
	EXPECT_EQ(icmp2("abc", "abc"), 0);
}

TEST(IComp, returns_plus_if_first_string_longer_than_second) {
	EXPECT_GT(icmp2("12345", "123"), 0);
}

TEST(IComp, returns_minus_if_first_string_shorter_than_second) {
	EXPECT_LT(icmp2("123", "12345"), 0);
}

TEST(IComp, return_plus_if_first_lexically_after_second) {
	EXPECT_GT(icmp2("aaaaab", "aaaaaa"), 0);
}

TEST(IComp, return_minus_if_first_lexically_before_second) {
	EXPECT_LT(icmp2("aaaaaa", "aaaaab"), 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
