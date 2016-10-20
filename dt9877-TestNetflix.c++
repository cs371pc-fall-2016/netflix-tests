// --------------------------------
// projects/netflix/TestNetflix.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <math.h>
#include <cmath>
#include "gtest/gtest.h"
#include <unordered_map>
#include "Netflix.h"

using namespace std;

  unordered_map <int, unordered_map<int, int> > actualScores;
  unordered_map <int, float> userBias;
  unordered_map <int, float> movieAverages;


// ----
// read
// ----

TEST(NetflixFixture, read1) {
  istringstream r("1:\n12\n13\n");
  int movieId;
  vector<int> users;
  const bool b = netflix_read(r, movieId, users);
  ASSERT_TRUE(b);
  ASSERT_EQ(movieId, 1);
  ASSERT_EQ(users.size(), 2);
  ASSERT_EQ(users[0], 12);
  ASSERT_EQ(users[1], 13);
}

TEST(NetflixFixture, read2) {
  istringstream r("");
  int movieId;
  vector<int> users;
  const bool b = netflix_read(r, movieId, users);
  ASSERT_FALSE(b);
}

TEST(NetflixFixture, read3) {
  istringstream r("1:\n12\n13\n2:\n1\n2\n");
  int movieId;
  vector<int> users;
  const bool b = netflix_read(r, movieId, users);
  ASSERT_TRUE(b);
  ASSERT_EQ(movieId, 1);
  ASSERT_EQ(users.size(), 2);
  ASSERT_EQ(users[0], 12);
  ASSERT_EQ(users[1], 13);
  users.clear();
  const bool c = netflix_read(r, movieId, users);
  ASSERT_TRUE(c);
  ASSERT_EQ(movieId, 2);
  ASSERT_EQ(users.size(), 2);
  ASSERT_EQ(users[0], 1);
  ASSERT_EQ(users[1], 2);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval1) {
  movieAverages[10] = 3;
  userBias[1952305] = 0.5;
  userBias[1531863] = - 0.7;
  actualScores[10][1952305] = 3;
  actualScores[10][1531863] = 3;
  int movieId = 10;
  int a[] = {1531863, 1952305};
  vector<int> ids(a,a+2); 
  vector<float> result = netflix_eval(movieId, ids, userBias, movieAverages);
  ASSERT_EQ(result.size(), 2);
  ASSERT_TRUE(abs(result[0] - 2.475) < 0.001);
  ASSERT_TRUE(abs(result[1] - 3.675) < 0.001);
}
TEST(NetflixFixture, eval2) {
  movieAverages[12] = 3.23451;
  userBias[3123] = 0.8726;
  actualScores[12][1323] = 1;
  int movieId = 12;
  int a[] = {3123};
  vector<int> ids(a,a+1); 
  vector<float> result = netflix_eval(movieId, ids, userBias, movieAverages);
  ASSERT_EQ(result.size(), 1);
  ASSERT_TRUE(abs(result[0] - 4.22348) < 0.001);
  
}
TEST(NetflixFixture, eval3) {
  movieAverages[1] = 4.99999;
  userBias[1012] = -0.0001;
  userBias[1000] = - 0.7;
  actualScores[1][1012] = 4;
  actualScores[1][1000] = 3;
  int movieId = 1;
  int a[] = {1012, 1000};
  vector<int> ids(a,a+2); 
  vector<float> result = netflix_eval(movieId, ids, userBias, movieAverages);
  ASSERT_EQ(result.size(), 2);
  ASSERT_TRUE(abs(result[0] - 4.67489) < 0.001);
  ASSERT_TRUE(abs(result[1] - 3.97499) < 0.001);
  
  
}
TEST(NetflixFixture, eval4) {
  movieAverages[2] = 1.1111;
  actualScores[2][1012] = 1;
  actualScores[2][1000] = 2;
  int movieId = 2;
  int a[] = {1012,1000};
  vector<int> ids(a,a+2); 
  vector<float> result = netflix_eval(movieId, ids, userBias, movieAverages);
  ASSERT_EQ(result.size(), 2);
  ASSERT_TRUE(abs(result[0] - 1.75822) < 0.001);
  ASSERT_TRUE(abs(result[1] - 1.05832) < 0.001);
  
}


// -----------
// squared_error
// -----------
TEST(NetflixFixture, squared_error_0) {
	const float sqerr = netflix_squared_error(3.7, 4);
	ASSERT_TRUE(abs(0.09 - sqerr) < 0.001);
}
TEST(NetflixFixture, squared_error_1) {
  const float sqerr = netflix_squared_error(1.1, 1);
  ASSERT_TRUE(abs(0.01 - sqerr) < 0.001);
}
TEST(NetflixFixture, squared_error_2) {
  const float sqerr = netflix_squared_error(3.888, 3);
  ASSERT_TRUE(abs(0.788544 - sqerr) < 0.0001);
}
// -----
// print
// -----
TEST(NetflixFixture, print1) {
  ostringstream w;
  float a[] = {1,2,3,4,5};
  vector<float> b(a,a+5); 
  netflix_print(w, 1, b);
  ASSERT_EQ("1:\n1.0\n2.0\n3.0\n4.0\n5.0\n", w.str());
}

TEST(NetflixFixture, print2) {
  ostringstream w;
  float a[] = {1};
  vector<float> b(a,a+1); 
  netflix_print(w, 1, b);
  ASSERT_EQ("1:\n1.0\n", w.str());
}

TEST(NetflixFixture, print3) {
  ostringstream w;
  float a[] = {0, 3.3333, 4.9};
  vector<float> b(a,a+3); 
  netflix_print(w, 1, b);
  ASSERT_EQ("1:\n0.0\n3.3\n4.9\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve1) {
  istringstream r("10:\n1952305\n1531863");
	ostringstream w;
	netflix_solve(r, w, actualScores, userBias, movieAverages);
	ASSERT_EQ("10:\n3.7\n2.5\nRMSE: 0.60\n", w.str());
}
TEST(NetflixFixture, solve2) {
  istringstream r("12:\n3123");
  ostringstream w;
  netflix_solve(r, w, actualScores, userBias, movieAverages);
  ASSERT_EQ("12:\n4.2\nRMSE: 4.22\n", w.str());
}
TEST(NetflixFixture, solve3) {
  istringstream r("1:\n1012\n1000");
  ostringstream w;
  netflix_solve(r, w, actualScores, userBias, movieAverages);
  ASSERT_EQ("1:\n4.7\n4.0\nRMSE: 0.84\n", w.str());
}
TEST(NetflixFixture, solve4) {
  istringstream r("2:\n1012\n1000");
  ostringstream w;
  netflix_solve(r, w, actualScores, userBias, movieAverages);
  ASSERT_EQ("2:\n1.8\n1.1\nRMSE: 0.85\n", w.str());
}
