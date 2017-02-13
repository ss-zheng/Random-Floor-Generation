#include "generate_helper.h"
#include <cstdlib>
#include <cmath>

using namespace std;


int getRandom(int min, int max){
	int n = max - min + 1;
	int rn = rand() % n + min;
	return rn;
}

int distance(pair<int,int> p1, pair<int, int> p2){
	int rn = abs(p1.first - p2.first) + abs(p1.second - p2.second);	
	return rn;
}


