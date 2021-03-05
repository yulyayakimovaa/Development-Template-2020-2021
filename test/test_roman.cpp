#include "roman.h"

#include <gtest.h>


TEST(test_convertor_to_arabic, test_one)
{
	roman R("I");
	arabic v = toArabic(R);
	EXPECT_EQ(1, v);
}

TEST(test_convertor_to_arabic, test_five)
{
	roman R("V");
	arabic v = toArabic(R);
	EXPECT_EQ(5, v);
}

TEST(test_convertor_to_arabic, test_12)
{
	roman R("XII");
	arabic v = toArabic(R);
	EXPECT_EQ(12, v);
}

TEST(test_convertor, test_nineteen)
{
	roman R("XIX");
	arabic v = toArabic(R);
	EXPECT_EQ(v, 19);
}
TEST(test_convertor, test_thirty)
{
	roman r("XXX");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 30);
}
TEST(test_convertor, test_fourty)
{
	roman r("XL");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 40);
}
TEST(test_convertor, test_fifty)
{
	roman r("L");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 50);
}
TEST(test_convertor, test_seventy_two)
{
	roman r("LXXII");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 72);
}
TEST(test_convertor, test_ninety_four)
{
	roman r("XCIV");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 94);
}
TEST(test_convertor, test_one_hundred)
{
	roman r("C");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 100);
}
TEST(test_convertor, test_three_hundred_ninety)
{
	roman r("CCCXC");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 390);
}
TEST(test_convertor, test_four_hundred_forty_four)
{
	roman r("CDXLIV");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 444);
}
TEST(test_convertor, test_five_hundred)
{
	roman r("D");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 500);
}
TEST(test_convertor, test_nine_hundred)
{
	roman r("CM");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 900);
}
TEST(test_convertor, test_2017)
{
	roman r("MMXVII");
	arabic v = toArabic(r);
	EXPECT_EQ(v, 2017);
}

TEST(test_convertor, test_3)
{
	arabic v(3);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "III");
}

TEST(test_convertor, test_8)
{
	arabic v(8);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "VIII");
}
TEST(test_convertor, test_14)
{
	arabic v(14);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "XIV");
}
TEST(test_convertor, test_19)
{
	arabic v(19);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "XIX");
}

TEST(test_convertor, test_40)
{
	arabic v(40);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "XL");
}
TEST(test_convertor, test_50)
{
	arabic v(50);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "L");
}
TEST(test_convertor, test_72)
{
	arabic v(72);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "LXXII");
}
TEST(test_convertor, test_94)
{
	arabic v(94);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "XCIV");
}
TEST(test_convertor, test_390)
{
	arabic v(390);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "CCCXC");
}
TEST(test_convertor, test_444)
{
	arabic v(444);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "CDXLIV");
}
TEST(test_convertor, test_500)
{
	arabic v(500);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "D");
}
TEST(test_convertor, test_900)
{
	arabic v(900);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "CM");
}
TEST(test_convertor, test_3017)
{
	arabic v(3017);
	roman r = toRoman(v);
	EXPECT_EQ(r.value, "MMMXVII");
}

