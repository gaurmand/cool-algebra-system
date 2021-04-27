#include <gmpxx.h>
#include <gtest/gtest.h>

TEST(Test, BasicAssertions1) {
    mpz_class a, b;

    a = 1234;
    b = "1234";
}

TEST(Test, BasicAssertions2) {
    mpz_class a, b, c;

    a = 1234;
    b = "1234";
    c = a+b;
}