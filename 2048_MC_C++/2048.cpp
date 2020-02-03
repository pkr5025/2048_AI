#include<utility>		//pair
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

	void transpose(){
		for (int i=0; i<4; i++){
			for (int j=0; j<i; j++){
				swap(board[i][j],board[j][i]);
			}
		}
	}
	void flip(){
		for (int i=0; i<4; i++){
			swap(board[i][0],board[i][3]);
			swap(board[i][1],board[i][2]);
		}
	}
public:
	void move(char direction){
		if (direction == 'u'){
			transpose();
			merge();
			transpose();
		}
		else if (direction == 'd'){
			transpose();
			flip();
			merge();
			flip();
			transpose();
		}
		else if (direction == 'r'){
			flip();
			merge();
			flip();
		}
		else
			merge();
	}
	void lost(){
		lose = true;
		for (int i=0; i<4; i++){
			if (lose == false)
				break;
			for (int j=0; j<4; j++){
				if (board[i][j] == 0)
					lose = false;
				if (i<2 and board[i][j] == board[i+1][j])
					lose = false;
				if (j<2 and board[i][j] == board[i][j+1])
					lose = false;


				if (lose == false)
					break;
			}
		}
	}
	void add_tile(){
		int random_tile = rand()%100;
		if (random_tile >=90) random_tile = 4;
		else random_tile = 2;
		vector<pair<int, int> > possibilities;
		for (int i =0; i<4; i++){
			for (int j=0; j<4; j++){
				if (board[i][j] == 0) possibilities.push_back({i,j});
			}
		}
		int square = rand() % possibilities.size();
		board[possibilities[square].first][possibilities[square].second] = random_tile;
	}
	
	vector<char> legal_move(){
		vector<vector<int> > temp_board = board;
		int temp_score = score;
		vector<char> moves;
		move('l');
		if (board != temp_board)
			moves.push_back('l');
		board = temp_board;
		move('r');
		if (board != temp_board)
			moves.push_back('r');
		board = temp_board;
		move('u');
		if (board != temp_board)
			moves.push_back('u');
		board = temp_board;
		move('d');
		if (board != temp_board)
			moves.push_back('d');
		board = temp_board;
		score = temp_score;
		return moves;
	}


		
};


int main(){
//	srand(1);
	srand(time(NULL));
	game example;
	cout<<example.get_score()<<endl;
	cout<<example.get_lost()<<endl;
	cout<<endl;
	example.print_board();
	cout<<endl;
	example.move('r');
	example.print_board();
	cout<<endl;
	example.move('d');
	example.print_board();
	cout<<endl;
	example.lost();
	cout<<example.get_lost()<<endl;
	example.add_tile();
	example.print_board();

	for (auto i: example.legal_move()){
		cout<<i<<endl;
	}
}
