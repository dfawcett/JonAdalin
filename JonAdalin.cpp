#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


struct location {
	int col;
	int row;
	int paths;
};

bool operator== (const location &loc1, const location &loc2)
{
    return (loc1.col == loc2.col &&
            loc1.row == loc2.row);
}

bool isFinished(vector<location> currLocations, int nrows, int ncols){
	if(currLocations.size() == 1 && currLocations[0].row == (nrows-1) && currLocations[0].col == (ncols-1)){
		return true;
	}
	return false;
}

bool isOnBoard(char board[4][4], location loc, int nrows, int ncols){
	if(loc.row < nrows && loc.col < ncols && board[loc.row][loc.col] != 'X'){
		return true;
	}
	return false;
}


int main(){
	const int nrows = 4;
	const int ncols = 4;
	char board[nrows][ncols] = {{'S','O','O','O'},
              	                {'X','O','O','O'},
              	                {'O','O','O','X'},
              	                {'O','O','O','D'}};

	vector<location> currLocations;
	vector<location> nextLocations;
	location start = {0,0,1};
	currLocations.push_back(start);

	while(!isFinished(currLocations, nrows, ncols)){
		nextLocations.clear();
		for(int i = 0; i < currLocations.size(); i++){
			location currLocation = currLocations.at(i);
			location down = {currLocation.col, currLocation.row + 1, currLocation.paths};
			if(isOnBoard(board, down, nrows, ncols)){
				vector<location>::iterator it = find(nextLocations.begin(), nextLocations.end(), down);
				if(it != nextLocations.end()){
					it->paths += down.paths;
				}
				else{
					nextLocations.push_back(down);
				}
			}
			location right = {currLocation.col + 1, currLocation.row, currLocation.paths};
			if(isOnBoard(board, right, nrows, ncols)){
				vector<location>::iterator it = find(nextLocations.begin(), nextLocations.end(), right);
				if(it != nextLocations.end()){
					it->paths += right.paths;
				}
				else{
					nextLocations.push_back(right);
				}
			}
		}
		currLocations = nextLocations;
	}
	cout<<"The number of paths is: "<<currLocations[0].paths<<endl;
	return 0;
}