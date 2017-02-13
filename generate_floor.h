#include <iostream>
#include <utility>
#include <vector>


class GenerateFloor{
	std::vector<std::vector<char>> board;	
	public:
	std::vector<std::pair<int,int>> positions;
	GenerateFloor(int height, int width);
	void addDoor( int num);
	void createFloor();
	void addPassage( std::pair<int,int> p1,std::pair<int,int> p2);
	void rectangle(int height, int width,int r, int c);
	void addWall( int boardr, int boardc);
	void moreChamber( int times);
  //  void clearPosition();
 //   void clearPositionHelper(int r, int c);
};
