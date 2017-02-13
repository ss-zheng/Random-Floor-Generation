#include "generate_floor.h"
#include "generate_helper.h"
#include <fstream>
#include <algorithm>

using namespace std;


int main(){
	GenerateFloor gf {25,79};
	srand(time(NULL));
	int times = getRandom(4, 6);
	//ifstream file {"plainfloor.txt"};
	//string ss;
	/*cout << board.size() << " " << board[0].size() << endl;
	for (int i = 0; i < 25; i++){
		getline(file, ss);
		for(int j = 0; j < 79; j++){
			board[i][j] = ss[j];
		}
	}*/
	gf.moreChamber(times);
    random_shuffle(gf.positions.begin(), gf.positions.end());
    for (int i = 0; i < gf.positions.size()-1; i++){
        pair<int,int> p1 = gf.positions[i];
        pair<int,int> p2 = gf.positions[i+1];
        gf.addPassage(p1, p2);
    }
	gf.createFloor();
}
