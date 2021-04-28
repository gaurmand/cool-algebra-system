add_executable(
  gmpLearningTests
  mpzLearningTest.cc
  mpqLearningTest.cc
)

target_link_libraries(
  gmpLearningTests
  gtest_main
  gmpxx
  gmp
)

gtest_discover_tests(gmpLearningTests)