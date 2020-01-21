#include <iostream>
#include <vector>
using namespace std;

class game{
        int score;
        bool lose;
        vector<vector<int> > board;

public:
        game(): score(0), lose(false), board(4,vector<int>(4)){};
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
};


int main(){
        game example;
        cout<<example.get_score()<<endl;
        cout<<example.get_lost()<<endl;
        example.print_board();
}
