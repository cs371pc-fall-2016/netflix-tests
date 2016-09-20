// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ---------------
// truncate_double
// ---------------

TEST(NetflixFixture, truncate_double_1) {
  double result =  truncate_double(5.2213, 2);
  ASSERT_EQ(5.22,result);
}

TEST(NetflixFixture, truncate_double_2) {
  double result =  truncate_double(0.3165, 2);
  ASSERT_EQ(0.31,result);
}

TEST(NetflixFixture, truncate_double_3) {
  double result =  truncate_double(1.99, 1);
  ASSERT_EQ(1.9,result);
}

TEST(NetflixFixture, truncate_double_4) {
  double result =  truncate_double(3.99, 2);
  ASSERT_EQ(3.99,result);
}

TEST(NetflixFixture, truncate_double_5) {
  double result =  truncate_double(5.12345, 3);
  ASSERT_EQ(5.123,result);
}

TEST(NetflixFixture, truncate_double_6) {
  double result =  truncate_double(0.31, 2);
  ASSERT_EQ(0.31,result);
}

TEST(NetflixFixture, truncate_double_7) {
  double result =  truncate_double(1.9, 1);
  ASSERT_EQ(1.9,result);
}

TEST(NetflixFixture, truncate_double_8) {
  double result =  truncate_double(3.99999998, 4);
  ASSERT_EQ(3.9999,result);
}

TEST(NetflixFixture, truncate_double_9) {
  double result =  truncate_double(0.0,1);
  ASSERT_EQ(0.0,result);
}

TEST(NetflixFixture, truncate_double_10) {
  double result =  truncate_double(1.66234, 4);
  ASSERT_EQ(1.6623,result);
}

TEST(NetflixFixture, truncate_double_11) {
  double result =  truncate_double(5.65, 2);
  ASSERT_EQ(5.65,result);
}

TEST(NetflixFixture, truncate_double_12) {
  double result =  truncate_double(0.0032, 2);
  ASSERT_EQ(0.00,result);
}

TEST(NetflixFixture, truncate_double_13) {
  double result =  truncate_double(1.9114, 1);
  ASSERT_EQ(1.9,result);
}

TEST(NetflixFixture, truncate_double_14) {
  double result =  truncate_double(9.00, 1);
  ASSERT_EQ(9.0,result);
}
