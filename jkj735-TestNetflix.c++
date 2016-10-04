#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --------------------
// solutions_cache_test
// --------------------

TEST(NetflixFixture, build_solutions_cache_test_1) {
	istringstream r("1:\n4\n5\n3\n2\n");
	std::vector<int> v = { 4,5,3,2 };
	build_solutions_cache(r);
	ASSERT_EQ(v, solutions_cache_map[1]);
	solutions_cache_map.clear();
}

TEST(NetflixFixture, build_solutions_cache_test_2) {
	istringstream r("1:\n4\n5\n3\n2\n2:\n4\n5\n3\n2\n");
	std::vector<int> v = { 4,5,3,2 };
	build_solutions_cache(r);
	ASSERT_EQ(v, solutions_cache_map[2]);
	ASSERT_EQ(v, solutions_cache_map[1]);
	solutions_cache_map.clear();
}

TEST(NetflixFixture, build_solutions_cache_test_3) {
	istringstream r("1:\n4\n2:\n2\n2\n10:\n1\n5\n");
	std::vector<int> v = { 1,5 };
	build_solutions_cache(r);
	ASSERT_EQ(v, solutions_cache_map[10]);
	solutions_cache_map.clear();
}

// ---------------
// user_cache_test
// ---------------

TEST(NetflixFixture, build_user_cache_test_1) {
	istringstream r("11 1.5382647\n");
	float f = 1.5382647;
	build_user_deviation_cache(r);
	ASSERT_EQ(f, user_deviation_cache_map[11]);
	user_deviation_cache_map.clear();
}

TEST(NetflixFixture, build_user_cache_test_2) {
	istringstream r("11 1.5382647\n59844 -0.345\n");
	float f = -0.345;
	build_user_deviation_cache(r);
	ASSERT_EQ(f, user_deviation_cache_map[59844]);
	user_deviation_cache_map.clear();
}

TEST(NetflixFixture, build_user_cache_test_3) {
	istringstream r("12 1.4\n3949 0.0000001\n1 -2.300021");
	float f = 0.0000001;
	float f2 = -2.300021;
	build_user_deviation_cache(r);
	ASSERT_EQ(f, user_deviation_cache_map[3949]);
	ASSERT_EQ(f2, user_deviation_cache_map[1]);
	user_deviation_cache_map.clear();
}

// ------------------------
// movie_average_cache_test
// ------------------------

TEST(NetflixFixture, build_movie_cache_test_1) {
	istringstream r("1 1.50\n");
	float f = 1.50;
	build_avg_cache(r);
	ASSERT_EQ(f, avg_cache_map[1]);
	avg_cache_map.clear();
}

TEST(NetflixFixture, build_movie_cache_test_2) {
	istringstream r("1 1.50\n10 3.18\n11 3.03\n12 3.42\n13 4.55\n14 3.03\n");
	float f = 3.42;
	build_avg_cache(r);
	ASSERT_EQ(f, avg_cache_map[12]);
	avg_cache_map.clear();
}

TEST(NetflixFixture, build_movie_cache_test_3) {
	istringstream r("1 1.50\n10 3.18\n11 3.03\n12 3.42\n13 4.55\n14 3.03\n");
	float f = 4.55;
	float f2 = 3.03;
	build_avg_cache(r);
	ASSERT_EQ(f, avg_cache_map[13]);
	ASSERT_EQ(f2, avg_cache_map[11]);
	avg_cache_map.clear();
}

// -----------------
// guess_rating_test
// -----------------

TEST(NetflixFixture, guess_rating_test_1) {
	istringstream r("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18\n");
	build_avg_cache(r);
	istringstream r2("6 -0.272068\n7 0.407417\n8 0.629183\n");
	build_user_deviation_cache(r2);
	float f = 3.4;
	
	float guess = guess_rating(6, 1);
	ASSERT_EQ(f, guess);
	avg_cache_map.clear();
	user_deviation_cache_map.clear();
}

TEST(NetflixFixture, guess_rating_test_2) {
	istringstream r("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18\n");
	build_avg_cache(r);
	istringstream r2("6 -0.272068\n7 0.407417\n8 0.629183\n10 1.50011\n");
	build_user_deviation_cache(r2);
	float f = 5.0;
	
	float guess = guess_rating(10, 5);
	ASSERT_EQ(f, guess);
	avg_cache_map.clear();
	user_deviation_cache_map.clear();
}

TEST(NetflixFixture, guess_rating_test_3) {
	istringstream r("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18\n");
	build_avg_cache(r);
	istringstream r2("6 -0.272068\n7 0.407417\n8 0.629183\n111 -2.20");
	build_user_deviation_cache(r2);
	float f = 1.0;
	
	float guess = guess_rating(111, 7);
	ASSERT_EQ(f, guess);
	avg_cache_map.clear();
	user_deviation_cache_map.clear();
}

// ------------------
// netflix_solve_test
// ------------------

TEST(NetflixFixture, solve_1) {
  istringstream r("1 3.75\n");
	build_avg_cache(r);
	istringstream r2("6 -0.75\n");
	build_user_deviation_cache(r2);
	istringstream r3("1:\n3\n");
	build_solutions_cache(r3);

	istringstream i("1:\n6\n");
  ostringstream w;
  netflix_solve(i, w);
  ASSERT_EQ("1:\n3.0\nRMSE: 0.00\n", w.str());
  avg_cache_map.clear();
	user_deviation_cache_map.clear();
	solutions_cache_map.clear();
}

TEST(NetflixFixture, solve_2) {
  istringstream r("1 3.75\n2 3.50\n3 3.00\n");
	build_avg_cache(r);
	istringstream r2("6 -0.75\n178 0.05\n12 1.2\n");
	build_user_deviation_cache(r2);
	istringstream r3("1:\n3.3\n3.9\n4.2\n");
	build_solutions_cache(r3);

	istringstream i("1:\n6\n178\n12\n");
  ostringstream w;
  netflix_solve(i, w);
  ASSERT_EQ("1:\n3.0\n3.8\n4.9\nRMSE: 0.69\n", w.str());
  avg_cache_map.clear();
	user_deviation_cache_map.clear();
	solutions_cache_map.clear();
}

TEST(NetflixFixture, solve_3) {
  istringstream r("1 3.75\n2 3.50\n3 3.00\n");
	build_avg_cache(r);
	istringstream r2("6 -0.75\n178 0.05\n12 1.2\n");
	build_user_deviation_cache(r2);
	istringstream r3("1:\n3.3\n3.9\n4.2\n2:\n2.5\n3:\n4.3\n");
	build_solutions_cache(r3);

	istringstream i("1:\n6\n178\n12\n2:\n12\n3:\n6\n");
  ostringstream w;
  netflix_solve(i, w);
  ASSERT_EQ("1:\n3.0\n3.8\n4.9\n2:\n4.7\n3:\n2.2\nRMSE: 1.54\n", w.str());
  avg_cache_map.clear();
	user_deviation_cache_map.clear();
	solutions_cache_map.clear();
}

// ----------
// print_test
// ----------

TEST(NetflixFixture, print_test_1) {
	ostringstream w;
	float v = 3.6009;
	print(v, w);
	ASSERT_EQ("3.6009\n", w.str());
}

TEST(NetflixFixture, print_test_2) {
	ostringstream w;
	float v = 0.001;
	print(v, w);
	ASSERT_EQ("0.001\n", w.str());
}

TEST(NetflixFixture, print_test_3) {
	ostringstream w;
	string s = "Netflix";
	print(s, w);
	ASSERT_EQ("Netflix\n", w.str());
}





