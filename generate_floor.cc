#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fstream>
#include "generate_floor.h"
#include "generate_helper.h"
using namespace std;

GenerateFloor::GenerateFloor(int height, int width): board(height, vector<char>(width, ' ')) {}



void GenerateFloor::createFloor(){
	ofstream out{"randomfloor.txt"};
	for (int i = 0; i < board.size(); i++){
		for (int j =  0; j < board[i].size(); j++){
			out << board[i][j];
            cout << board[i][j];
		}
        cout << endl;
		out << endl;
	}
	out.close();
}

void GenerateFloor::addDoor( int num){
	int r,c;
	for (int j = 0; j < 2*2*num; j++){
		do {
			r = getRandom(4, 22);
			c = getRandom(4, 76);
		} while (board[r][c] != '|' && board[r][c] != '-');
		board[r][c] = '+';
	}
}

/*bool compare(pair<int,int> p1, pair<int, int> p2){
	if (p1.first < p2.first){
	gretur,gtrue;
	} else if (p1.first == p2.first){
		if (p1.second <= p2.second){
			return true;
	air<int,int> target_p;
		} else {
			return false;
		}
	} else {
		return false;
	}
}*/

void GenerateFloor::addPassage( pair<int,int> p1, pair<int,int> p2) {
//	sort(positions.begin(), positions.end(), compare);
	if(distance(p1, p2) <= 1) return;
	int n;
	int target_r, target_c;
	pair<int,int> target_p;
	do{
	//	cout << p1.first << " " <<  p1.second<< endl;
		n = getRandom(0,3);
		switch (n){
			case 0:
				target_r = p1.first + 1;
				target_c = p1.second;
				break;
			case 1:
				target_r = p1.first - 1;
				target_c = p1.second;
				break;
			case 2:
				target_r = p1.first;
				target_c = p1.second +1;
                break;
			case 3:
				target_r = p1.first;
				target_c = p1.second -1;
				break;
		}
		target_p ={target_r, target_c};	
	} while (distance(target_p, p2) > distance(p1, p2));
	if (board[target_r][target_c] == ' '){
		board[target_r][target_c] = '#';
	} else if (board[target_r][target_c] == '-'){
		board[target_r][target_c] = '+';
	} else if (board[target_r][target_c] == '|'){
		board[target_r][target_c] = '+';
	}	
	addPassage(target_p, p2);
}
	



void GenerateFloor::rectangle(int height, int width,int r, int c){
    int boundr = min(r+height, 24);
    int boundc = min(c+width, 78);
    for(int i = r; i < boundr; i++){
        for(int j = c; j < boundc;j++){
            //			if (board[i][j] != '-') && board[i][j] != '|'){
            board[i][j] = '.';
                //cout << i << ' ' << j << endl;
            if (i == (boundr + r) / 2 && j == (boundc + c) /2){
               // board[i][j] = '%';
                pair<int,int> p (i, j);
                positions.emplace_back(p);
            }
        }
    }
   // cout << p.first << ' ' << p.second << endl;
}

void GenerateFloor::addWall( int boardr, int boardc){
	for(int i = 1; i < boardr; i++){
		for (int j = 1; j < boardc; j++){
		   if (i+2 < boardr &&  board[i][j] == ' ' && board[i+1][j] == '.'){

				board[i+1][j] = '-';
		   } else if (i+2 < boardr &&  board[i][j] == '.' && board[i+1][j] == ' '){

			   board[i][j] = '-';
		   }
		}
	}
	for(int i = 1; i < boardr; i++){
		for (int j = 1; j < boardc; j++){
		   if (j+2 < boardc &&  (board[i][j] == '-' || board[i][j] == ' ') && board[i][j+1] == '.'){

				board[i][j+1] = '|';
		   } else if (j+2 < boardc &&  board[i][j] == '.' &&
                   (board[i][j+1] == '-' || board[i][j+1] == ' ')){

			   board[i][j] = '|';
		   } else if (j+2 < boardc &&  board[i][j] == ' ' && board[i][j+1] == '-'){

			   board[i][j+1] = '|'; 
		   } else if (j+2 < boardc &&  board[i][j] == '-' && board[i][j+1] == ' '){

			   board[i][j] = '|';
		   }
		}
	}
    for(int i = 0; i < boardr; i++){
        for (int j = 0; j < boardc; j++) {
            if (i == 0) {
                if (board[i+1][j] == '.') board[i+1][j] = '-';
                board[i][j] = '-';
            } else if (i == boardr-1) {
                if (board[i-1][j] == '.') board[i-1][j] = '-';
                board[i][j] = '-';
            }
            if (j == 0) {
                if (i != 0 && i != boardr-1) {
                    if (board[i][j+1] == '.' || board[i][j+1] == '-') board[i][j+1] = '|';
                }
                board[i][j] = '|';
            } else if (j == boardc-1) {
                if (i != 0 && i != boardr-1) {
                    if (board[i][j-1] == '.'|| board[i][j-1] == '-') board[i][j-1] = '|';
                }
                board[i][j] = '|';
            }
        }
    }
	// for(int i = 1; i < boardr-1; i++){
	// 	for (int j = 1; j < boardc-1; j++){
	// 	   if (i+3 < boardc-1 &&  board[i][j] == '.' && board[i][j+1] == '|' && board[i][j+2] == '.'){
	// 			board[i][j+1] = '.';
	// 	   }
	// 	}
	// }
}

void GenerateFloor::moreChamber(int times){
	int height, width, r, c;
	int average = times / 2;
	vector<pair<int,int>> position;
	for (int i = 0; i < average; i++){
		height = getRandom(4, 10);
		width = getRandom(8,20);
		r = getRandom(1, 6);
		c = getRandom(1, 30);
		rectangle(height, width, r, c);
	}
	for (int j = 0; j < average; j++){
		height = getRandom(4, 10);
		width = getRandom(8,20);
		r = getRandom(11, 20);
		c = getRandom(36, 70);
		rectangle(height, width, r, c);
	}
	for (int i = 0; i < average; i++){
		height = getRandom(4, 10);
		width = getRandom(8,20);
		r = getRandom(1, 6);
		c = getRandom(36, 70);
		rectangle(height, width, r, c);
	}
	for (int j = 0; j < average; j++){
		height = getRandom(4, 10);
		width = getRandom(8,20);
		r = getRandom(11, 20);
		c = getRandom(1, 30);
		rectangle(height, width, r, c);
	}
	if (board[9][30] == ' ' && board[15][40] == ' '){
		height = getRandom(5, 6);
		width = getRandom(8,10);
		r = getRandom(9, 15);
		c = getRandom(30, 40);
		rectangle(height, width, r, c);
	}
	addWall(25,79);	
}

	
// void GenerateFloor::clearPositionHelper(int r, int c) {
//     //cout << "clearPosition" << board[r][c]->getPos().isRead << endl;
//     //cout << board[r][c]->getPos().style;
//     board[r][c]->flip();
//     arr.emplace_back(&board[r][c]);
//     if (board[r-1][c]->getPos().style == TILE && !(board[r-1][c]->getPos().isRead)) {
//         clearPosition(r-1, c, arr);
//     }
//     if (board[r+1][c]->getPos().style == TILE && !(board[r+1][c]->getPos().isRead)) {
//         clearPosition(r+1,c, arr);
//     }
//     if (board[r][c-1]->getPos().style == TILE && !(board[r][c-1]->getPos().isRead)){ 
//         clearPosition(r,c-1, arr);
//     }
//     if (board[r][c+1]->getPos().style == TILE && !(board[r][c+1]->getPos().isRead)) { 
//         clearPosition(r,c+1, arr);
//     }
// }

// void GenerateFloor::clearPosition() {
// 	for (int t = 0; t < 5; t++) {
//         clearPositionHelper(r,c);
// 	}
// }


