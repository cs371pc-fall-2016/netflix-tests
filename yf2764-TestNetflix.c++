
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

TEST(NetflixFixture, solve_1) {
    istringstream r("22:\n2275708\n370642\n2414681\n");
    ostringstream w;
    netflix_solve(r, w);
ASSERT_EQ("22:\n2.97\n3.25\n3.43\nRMSE: 1.81\n", w.str());}

TEST(NetflixFixture, solve_2) {
    istringstream r("7284:\n2195992\n1701133\n239421\n709154\n2182356\n236481\n1454636\n2066628\n2487766\n914833\n964414\n120151\n");
    ostringstream w;
    netflix_solve(r, w);
ASSERT_EQ("7284:\n2.72\n3.76\n3.28\n3.67\n2.88\n3.73\n2.94\n2.79\n3.79\n3.23\n3.32\n3.47\nRMSE: 1.36\n", w.str());}

TEST(NetflixFixture, solve_3) {
    istringstream r("10006:\n1093333\n1982605\n1534853\n1632583\n");
    ostringstream w;
    netflix_solve(r, w);
ASSERT_EQ("10006:\n4.22\n3.68\n4.51\n3.17\nRMSE: 2.62\n", w.str());}