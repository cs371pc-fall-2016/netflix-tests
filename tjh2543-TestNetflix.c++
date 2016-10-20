#include <iostream> // endl, istream, ostream
#include <fstream> // read file
#include <sstream> //istringstream, ostringstream
#include <string> // string	
#include "Netflix.h"
#include "gtest/gtest.h"

using namespace std;

const string user = "320159 4.04\n910198 3.36\n654681 5.0\n546449 3.13\n654861 4.61\n951729 3.78\n2643288 3.6\n138561 3.49\n2007667 4.03\n1174466 3.16\n";
const string movie = "1:3.75\n6008:3.1\n12626:3.45\n6138:4.19\n152:3.93\n";

istringstream userCache(user);
istringstream movieCache(movie);

TEST(Netflix, print_1) {
	string pathOut = "TestNetflix.tmp";
	initMap(userCache, movieCache);
	istringstream r("1:\n320159\n910198\n");
	ofstream outfile;
	outfile.open(pathOut);
	printFile(r, outfile);                           	//Tests created file
	ifstream infile;
	infile.open(pathOut.c_str()); 
	const bool b = infile.good();
	ASSERT_EQ(b, true);
	
	string i = "";
	string j = "";
	getline(infile, j);								//Tests data in file
	
	while((!j.empty())) {
		i += j + "\n";
		getline(infile, j);
	}	
	infile.close();
	ASSERT_EQ(i, "1:\n3.8\n3.5\n");
}

TEST(Netflix, print_2) {
	string pathOut = "TestNetflix.tmp";
	initMap(userCache, movieCache);
	istringstream r("6008:\n654681\n546449\n12626:\n654861\n951729\n");
	ofstream outfile;
	outfile.open(pathOut);
	printFile(r, outfile);                           	//Tests created file
	ifstream infile;
	infile.open(pathOut.c_str()); 
	const bool b = infile.good();
	ASSERT_EQ(b, true);
	
	string i = "";
	string j = "";
	getline(infile, j);								//Tests data in file
	
	while((!j.empty())) {
		i += j + "\n";
		getline(infile, j);
	}	
	infile.close();
	ASSERT_EQ(i, "6008:\n4.0\n3.1\n12626:\n4.0\n3.6\n");
}

TEST(Netflix, print_3) {
	string pathOut = "TestNetflix.tmp";
	initMap(userCache, movieCache);
	istringstream r("6138:\n2643288\n138561\nNot_a_real_ID\n2007667");
	ofstream outfile;
	outfile.open(pathOut);
	printFile(r, outfile);                           	//Tests created file
	ifstream infile;
	infile.open(pathOut.c_str()); 
	const bool b = infile.good();
	ASSERT_EQ(b, true);
	
	string i = "";
	string j = "";
	getline(infile, j);								//Tests data in file
	
	while((!j.empty())) {
		i += j + "\n";
		getline(infile, j);
	}	
	infile.close();
	ASSERT_EQ(i, "6138:\n3.8\n3.8\n4.1\n4.1\n");
}

TEST(Netflix, calculateRating_1) {
	initMap(userCache, movieCache);
	ostringstream answer;
	string movieID = "152:";
	string userID = "1174466";
	double prediction = calculateRating(movieID, userID);
	answer << fixed << setprecision(1) << prediction;
	ASSERT_EQ(answer.str(), "3.5");

}

TEST(Netflix, calculateRating_2) {	// test that return value is average of user in the even of an unknown movieID
	initMap(userCache, movieCache);
	ostringstream answer;
	string movieID = "Not_a_real_ID";
	string userID = "1174466";
	double prediction = calculateRating(movieID, userID);
	answer << fixed << setprecision(1) << prediction;
	ASSERT_EQ(answer.str(), "3.2");
}

TEST(Netflix, calculateRating_3) {	// test that return value is average of movie in the event of an unknown userID
	initMap(userCache, movieCache);
	ostringstream answer;
	string movieID = "152:";
	string userID = "Not_a_real_ID";
	double prediction = calculateRating(movieID, userID);
	answer << fixed << setprecision(1) << prediction;
	ASSERT_EQ(answer.str(), "3.9");
}

TEST(Netflix, calculateRating_4) {	// test for default result
	initMap(userCache, movieCache);
	ostringstream answer;
	string movieID = "Not_a_real_ID";
	string userID = "Not_a_real_ID";
	double prediction = calculateRating(movieID, userID);
	answer << fixed << setprecision(1) << prediction;
	ASSERT_EQ(answer.str(), "3.7");
}

TEST(Netflix, compare_1) {      // tests comparison/calculates RMSE of provided input stream
        initMap(userCache, movieCache);
        string answer;
        istringstream input("1: 152, 3.0\n");
        answer = compare(input);
        ASSERT_EQ(answer, "RMSE: 3.77\n");
}

TEST(Netflix, compare_2) {      // tests comparison/calculates RMSE of provided input stream
        initMap(userCache, movieCache);
        string answer;
        istringstream input("6008: 152, 1.0\n6008: 741, 4.0\n");
        answer = compare(input);
        ASSERT_EQ(answer, "RMSE: 3.77\n");
}

TEST(Netflix, compare_3) {      // tests comparison/calculates RMSE of provided input stream
        initMap(userCache, movieCache);
        string answer;
        istringstream input("1: 252, 3.0\n 6002: 741, 22.6\n");
        answer = compare(input);
        ASSERT_EQ(answer, "RMSE: 3.77\n");
}

TEST(Netflix, RMSE_1) {		//tests simple, positive ints
	vector<double> inputActual = {2, 3, 5, 9, 10, 13};
	vector<double> inputExpected = {1,1,1,1,1,1};
	int size = inputActual.size();
	string answer = calculateRMSE(inputActual, size, inputExpected);
	ASSERT_EQ(answer, "RMSE: 7.18\n");
}

TEST(Netflix, RMSE_2) {		//tests unordered ints
	vector<double> inputActual = {2, 13, -10, -5, 9, 0, 3, 0, 0, 0};
	vector<double> inputExpected = {-1, -1, 4, -1, 5, 6, 1, 0, 0, 0};
	int size = inputActual.size();
	string answer = calculateRMSE(inputActual, size, inputExpected);
	ASSERT_EQ(answer, "RMSE: 6.87\n");
}

TEST(Netflix, RMSE_3) { //tests doubles
	vector<double> inputActual = {2.25, 13.33, -10.75, -5.5, 9, 3.00};
	vector<double> inputExpected = {2.0, 210.87, -10.75, -5.0, 8.8, 3.33};
	int size = inputActual.size();
	string answer = calculateRMSE(inputActual, size, inputExpected);
	ASSERT_EQ(answer, "RMSE: 80.64\n");
}

TEST(Netflix, split_1) {
	string input = "Hello World!";
	vector<string> answer = split(input,  ' ');
	ASSERT_EQ(answer[0], "Hello");
}

TEST(Netflix, split_2) {
	string input = "Hello World!";
	vector<string> answer = split(input, ' ');
	ASSERT_EQ(answer[1], "World!");
}

TEST(Netflix, split_3) {
	string input = "Hello World!";
	vector<string> answer = split(input, '?');
	ASSERT_EQ(answer[0], "Hello World!");
}

TEST(Netflix, truncate_1) {
	double input = 0.00232;
	int places = 4;
	string answer = truncate(input, places);
	ASSERT_EQ(answer, "0.0023");
}

TEST(Netflix, truncate_2) {
        double input = 3.1;
        int places = 3;
        string answer = truncate(input, places);
        ASSERT_EQ(answer, "3.100");
}

TEST(Netflix, truncate_3) {
        double input = 12.34612345678;
        int places = 3;
        string answer = truncate(input, places);
        ASSERT_EQ(answer, "12.346");
}

