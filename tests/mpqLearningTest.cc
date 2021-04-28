#include <gmpxx.h>
#include <gtest/gtest.h>
#include <string>

TEST(mpqTest, DefaultConstructor) {
    mpq_class a;
    EXPECT_EQ(a, 0);
}

TEST(mpqTest, ConstructorSingleNumericArgs) {
    long int arg1 = 1234;    
    mpq_class a(arg1);
    EXPECT_EQ(a, 1234);

    double arg2 = -0.5;
    mpq_class b(arg2);
    EXPECT_EQ(b, -0.5);
}

TEST(mpqTest, ConstructorDoubleNumericArgs) {
    mpq_class a(-5, 1);
    EXPECT_EQ(a, -5);

    mpz_class b(-5);
    mpz_class c(1);
    mpq_class d(b, c);
    EXPECT_EQ(d, a);
}

TEST(mpqTest, ConstructorStringArgs) {
    mpq_class a("1234");
    EXPECT_EQ(a, 1234);

    std::string arg("-1/2");
    mpq_class b(arg);
    mpq_class c(-1, 2);
    EXPECT_EQ(b, c);
}

TEST(mpqTest, ConstructorStringArgsWithDifferentBases) {
    mpq_class a("0372/-0b01100100");
    mpq_class b("250/-100");
    mpq_class c("FA/-64", 16);
    EXPECT_EQ(a, b);
    EXPECT_EQ(a, c);
}

TEST(mpqTest, ConstructorVeryLongStringArgs) {
    mpz_class a("18446744073709551616"); //2^64 (min integer that doesn't fit in 64-bit unsigned integer)
    mpz_class b("340282366920938463463374607431768211456"); //2^128
    mpq_class c(a, b);
}

TEST(mpqTest, CopyConstructor) {
    mpq_class a(1234);
    mpq_class b(a);
    EXPECT_EQ(b, 1234);
}

TEST(mpqTest, ImplicitConversion) {
    mpq_class a = 1234;
    EXPECT_EQ(a, 1234);
}

TEST(mpqTest, CopyAssignment) {
    mpq_class a(1234);
    mpq_class b = a;
    EXPECT_EQ(a, b);
}

TEST(mpqTest, SpecialConstructorSyntax) {
    mpq_class a = 1234_mpq;
    EXPECT_EQ(a, 1234);

    mpq_class b = 0x4D2_mpq/-10_mpq;
    mpq_class c(1234, -10);
    EXPECT_NE(b, c);
    c.canonicalize();
    EXPECT_EQ(b, c);
}

TEST(mpqTest, GetNumAndDen) {
    mpq_class a(1, 2);
    EXPECT_EQ(a.get_num(), 1);
    EXPECT_EQ(a.get_den(), 2);

    mpq_class b(-2, -4);
    EXPECT_EQ(b.get_num(), -2);
    EXPECT_EQ(b.get_den(), -4);
}

TEST(mpqTest, Canonicalize) {
    mpq_class a(1, 2);
    mpq_class b(-2, -4);
    EXPECT_NE(b, a);
    b.canonicalize();
    EXPECT_EQ(b, a);
}

TEST(mpqTest, ZeroDenom) {
    mpq_class a(1, 0);  //denom of 0 allowed
    EXPECT_EQ(a.get_num(), 1);
    EXPECT_EQ(a.get_den(), 0);
    // c.canonicalize();   //ERROR: division by 0
}

TEST(mpqTest, Swap) {
    mpq_class a(1234);
    mpq_class b(2345);
    a.swap(b);

    EXPECT_EQ(a, 2345);
    EXPECT_EQ(b, 1234);
}

TEST(mpqTest, Compare) {
    mpq_class a(1, 10);
    mpq_class b(1);
    mpq_class c(-1, 10);
    
    EXPECT_EQ(cmp(a, a), 0);
    EXPECT_LT(cmp(a, b), 0);
    EXPECT_GT(cmp(a, c), 0);

    EXPECT_EQ(cmp(b, 1), 0);
    EXPECT_LT(cmp(a, 10), 0);
    EXPECT_GT(cmp(10, a), 0);
}

TEST(mpqTest, Add) {
    mpq_class a(1, 2);
    mpq_class b(-1, 4);
    mpq_class c(1, 4);
    EXPECT_EQ(a + a, 1);
    EXPECT_EQ(a + 0, a);
    EXPECT_EQ(a + b, c);
    EXPECT_EQ(b + c, 0);
}

TEST(mpqTest, Negate) {
    mpq_class a(1, 2);
    mpq_class b(-1, 2);
    mpq_class c(0);
    EXPECT_EQ(-a, b);
    EXPECT_EQ(-b, a);
    EXPECT_EQ(-c, 0);
}

TEST(mpqTest, Subtract) {
    mpq_class a(1, 2);
    mpq_class b(-1, 4);
    mpq_class c(1, 4);
    EXPECT_EQ(a - a, 0);
    EXPECT_EQ(a - 0, a);
    EXPECT_EQ(a - c, c);
    EXPECT_EQ(c - b, a);
}

TEST(mpqTest, Multiply) {
    mpq_class a(1, 2);
    mpq_class b(-1, 2);
    mpq_class c(1, 4);
    mpq_class d(-1, 4);
    EXPECT_EQ(a * a, c);
    EXPECT_EQ(b * b, c);
    EXPECT_EQ(a * b, d);
    EXPECT_EQ(a * 0, 0);
}

TEST(mpqTest, Divide) {
    mpq_class a(1, 2);
    mpq_class b(-1, 4);
    EXPECT_EQ(a / a, 1);
    EXPECT_EQ(b / a, -a);
    EXPECT_EQ(a / b, -2);
    EXPECT_EQ(0 / a, 0);
    // EXPECT_EQ(a / 0, 0); //ERROR: division by 0
}

TEST(mpqTest, AbsoluteValue) {
    mpq_class a(1, 2);
    mpq_class b(-1, 2);
    mpq_class c(0);
    EXPECT_EQ(abs(a), a);
    EXPECT_EQ(abs(b), a);
    EXPECT_EQ(abs(c), 0);
}

TEST(mpqTest, Sign) {
    mpq_class a;
    mpq_class b(1, 2);
    mpq_class c(-1, 2);
    EXPECT_EQ(sgn(a), 0);
    EXPECT_GT(sgn(b), 0);
    EXPECT_LT(sgn(c), 0);
}
