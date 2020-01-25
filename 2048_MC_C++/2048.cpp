#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class game{
	int score, tile;
	bool lose;
	vector<vector<int> > board;

public:
	game(): score(0), tile(0), lose(false), board(4,vector<int>(4)){
		//Initialize board with a 2 at a random location
		int i = rand()%4;
		int j = rand()%4;
		board[i][j] = 2; 
		// Add a second 2 at a different location
		int k=i, l = j;
		while(i==k and l==j){
			k = rand()%4;
			l = rand()%4;
		}
		board[k][l] = 2;
	};
	int get_score(){return score;}
	bool get_lost(){return lose;}

	void print_board(){       
		 for (auto i: board){
                	cout<<"{";
               	 	for (auto j: i){
                        	cout<<j<<" ";
                	}
                cout<<"}\n";
	        }
	}


private:
	void shift(){
		vector<vector<int> > current(4, vector<int>(4));
		for (int i = 0; i<4; i++){
			int position = 0;
			for (int j = 0; j<4; j++){
				if (board[i][j] !=0){
					current[i][position] = board[i][j];
					position++;
				}
			}
		}
		board = current;
	}
	void merge(){
		shift();
		for (int i=0; i<4; i++){
			for (int j=0; j<3; j++){
				if (board[i][j] == board[i][j+1] and board[i][j]!=0){
					board[i][j] *=2;
					score+= board[i][j];
					if (board[i][j] > tile)
						tile = board[i][j];
					board[i][j+1] = 0;
				}
			}
		}
		shift();
	}

		
};


int main(){
	srand(1);
	game example;
	cout<<example.get_score()<<endl;
	cout<<example.get_lost()<<endl;
	example.print_board();
//	example.merge();
//	example.print_board();
}
