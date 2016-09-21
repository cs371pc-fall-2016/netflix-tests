
// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -----
// solve
// -----

TEST(NetflixFixture, solve) {
    istringstream r("22:\n2275708\n370642\n2414681\n");
    ostringstream w;
    netflix_solve(r, w);
ASSERT_EQ("22:\n2.97\n3.25\n3.43\nRMSE: 1.81\n", w.str());}