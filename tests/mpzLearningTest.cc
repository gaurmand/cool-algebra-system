#include <gmpxx.h>
#include <gtest/gtest.h>
#include <string>

TEST(mpzTest, DefaultConstructor) {
    mpz_class a;
    EXPECT_EQ(a, 0);
}

TEST(mpzTest, ConstructorNumericArgs) {
    long int arg1 = 1234;    
    mpz_class a(arg1);
    EXPECT_EQ(a, 1234);

    double arg2 = -1234;
    mpz_class b(arg2);
    EXPECT_EQ(b, -1234);
}

TEST(mpzTest, ConstructorStringArgs) {
    mpz_class a("1234");
    EXPECT_EQ(a, 1234);

    std::string str("-1234");
    mpz_class b(str);
    EXPECT_EQ(b, -1234);
}

TEST(mpzTest, ConstructorStringArgsWithDifferentBases) {
    mpz_class a("1234");
    mpz_class b("0x4D2");
    mpz_class c("2322", 8);
    mpz_class d("010011010010", 2);
    EXPECT_EQ(a, b);
    EXPECT_EQ(a, c);
    EXPECT_EQ(a, d);
}

TEST(mpzTest, ConstructorVeryLongStringArgs) {
    mpz_class a("4294967295"); //2^32 - 1 (max integer that fits in 32-bit unsigned integer)
    EXPECT_TRUE(a.fits_ulong_p());

    mpz_class b("18446744073709551616"); //2^64 (min integer that doesn't fit in 64-bit unsigned integer)
    EXPECT_FALSE(b.fits_ulong_p());

    mpz_class c("115792089237316195423570985008687907853269984665640564039457584007913129639936"); //2^256
    EXPECT_FALSE(c.fits_ulong_p());
}

TEST(mpzTest, CopyConstructor) {
    mpz_class a(1234);
    mpz_class b(a);
    EXPECT_EQ(b, 1234);
}

TEST(mpzTest, ImplicitConversion) {
    mpz_class a = 1234;
    EXPECT_EQ(a, 1234);
}

TEST(mpzTest, CopyAssignment) {
    mpz_class a(1234);
    mpz_class b = a;
    EXPECT_EQ(b, 1234);
}

TEST(mpzTest, SpecialConstructorSyntax) {
    mpz_class a = 1234_mpz;
    EXPECT_EQ(a, 1234);

    mpz_class b = 0x4D2_mpz;
    EXPECT_EQ(b, 1234);
}

TEST(mpzTest, Swap) {
    mpz_class a(1234);
    mpz_class b(2345);
    a.swap(b);

    EXPECT_EQ(a, 2345);
    EXPECT_EQ(b, 1234);
}

TEST(mpzTest, Compare) {
    mpz_class a(10);
    mpz_class b(100);
    mpz_class c(-10);
    
    EXPECT_EQ(cmp(a, a), 0);
    EXPECT_LT(cmp(a, b), 0);
    EXPECT_GT(cmp(a, c), 0);

    EXPECT_EQ(cmp(a, 10), 0);
    EXPECT_LT(cmp(a, 100), 0);
    EXPECT_GT(cmp(100, a), 0);
}

TEST(mpzTest, Add) {
    mpz_class a(100);
    mpz_class b(-100);
    mpz_class c(0);
    EXPECT_EQ(a + a , 200);
    EXPECT_EQ(a + b, 0);
    EXPECT_EQ(a + c, 100);
    EXPECT_EQ(b - a, -200);
}

TEST(mpzTest, Negate) {
    mpz_class a(100);
    mpz_class b(-100);
    mpz_class c(0);
    EXPECT_EQ(-a, -100);
    EXPECT_EQ(-b, 100);
    EXPECT_EQ(-c, 0);
}

TEST(mpzTest, Subtract) {
    mpz_class a(100);
    mpz_class b(-100);
    mpz_class c(0);
    EXPECT_EQ(a - a , 0);
    EXPECT_EQ(a - b, 200);
    EXPECT_EQ(a - c, 100);
    EXPECT_EQ(b - a, -200);
}

TEST(mpzTest, Multiply) {
    mpz_class a(100);
    mpz_class b(-100);
    mpz_class c(0);
    EXPECT_EQ(a * a , 10000);
    EXPECT_EQ(a * b, -10000);
    EXPECT_EQ(a * c, 0);
}

TEST(mpzTest, Divide) {
    mpz_class a(100);
    mpz_class b(-50);
    EXPECT_EQ(a / a , 1);
    EXPECT_EQ(a / b, -2);
    EXPECT_EQ(b / a, 0);
    EXPECT_EQ(0 / a, 0);
    //EXPECT_EQ(cmp(a / 0, 0), 0); //ERROR: division by 0
}

TEST(mpzTest, Mod) {
    mpz_class a(100);
    mpz_class b(3);
    mpz_class c(-2);
    mpz_class d(0);
    EXPECT_EQ(a % b, 1);
    EXPECT_EQ(a % c, 0);
    EXPECT_EQ(d % a, 0);
    // EXPECT_EQ(cmp(a % d, 0), 0); //ERROR: division by 0
}

TEST(mpzTest, AbsoluteValue) {
    mpz_class a(10);
    mpz_class b(-10);
    mpz_class c(0);
    EXPECT_EQ(abs(a), 10);
    EXPECT_EQ(abs(b), 10);
    EXPECT_EQ(abs(c), 0);
}

TEST(mpzTest, Sign) {
    mpz_class a;
    mpz_class b(10);
    mpz_class c(-10);
    EXPECT_EQ(sgn(a), 0);
    EXPECT_GT(sgn(b), 0);
    EXPECT_LT(sgn(c), 0);
}

TEST(mpzTest, Sqrt) {
    mpz_class a(100);
    mpz_class b(99);
    EXPECT_EQ(sqrt(a), 10);
    EXPECT_EQ(sqrt(b), 9);
}

TEST(mpzTest, Factorial) {
    mpz_class a(0);
    mpz_class b(10);
    EXPECT_EQ(factorial(a), 1);
    EXPECT_EQ(factorial(b), 3628800);
}

TEST(mpzTest, Gcd) {
    mpz_class a(0);
    mpz_class b(10);
    mpz_class c(15);
    mpz_class d(-15);
    EXPECT_EQ(gcd(a, a), 0);
    EXPECT_EQ(gcd(b, b), 10);
    EXPECT_EQ(gcd(b, a), 10);
    EXPECT_EQ(gcd(b, c), 5);
    EXPECT_EQ(gcd(b, d), 5);
}

TEST(mpzTest, Lcm) {
    mpz_class a(0);
    mpz_class b(10);
    mpz_class c(15);
    mpz_class d(-15);
    EXPECT_EQ(lcm(a, a), 0);
    EXPECT_EQ(lcm(b, b), 10);
    EXPECT_EQ(lcm(b, a), 0);
    EXPECT_EQ(lcm(b, c), 30);
    EXPECT_EQ(lcm(b, d), 30);
}