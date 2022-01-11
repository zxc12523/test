#include<bits/stdc++.h>
#include "connect4.h"
//ref b09902028！
using namespace std;
//vector<vector<int> >board;
const int rows=6;
const int cols=7;
const int connectLen=4;
int yp_token=2;
int my_token=1;
vector< vector<int> > board;
// The columns are numbered from 0 to 6

bool validLocation(int col){
    return board[rows-1][col]==0;
}
vector<int> getValidLocations(){
    vector<int>valid;
    for(int col=0;col<cols;col++){
        if(validLocation(col))
            valid.push_back(col);
    }
    return valid;
}
int getNextRow(int col){
    for(int row=0;row<rows;row++){
        if(board[row][col]==0)return row;
    }
}
int winMove(int token){
    //horizontal  
    for(int col=0;col<cols-3;col++){
        for(int row=0;row<rows;row++){
            if(board[row][col]==token && board[row][col+1]==token && board[row][col+2]==token && board[row][col+3]==token)
                return true;
        }
    }
    //vertical 
    for(int col=0;col<cols;col++){
        for(int row=0;row<rows-3;row++){
            if(board[row][col]==token && board[row+1][col]==token && board[row+2][col]==token && board[row+3][col]==token)
                return true;
        }
    }
    //斜向上
    for(int col=0;col<cols-3;col++){
        for(int row=0;row<rows-3;row++){
            if(board[row][col]==token && board[row+1][col+1]==token && board[row+2][col+2]==token && board[row+3][col+3]==token)
                return true;
        }
    }
    //斜向下
    for(int col=0;col<cols-3;col++){
        for(int row=3;row<rows;row++){
            if(board[row][col]==token && board[row-1][col+1]==token && board[row-2][col+2]==token && board[row-3][col+3]==token)
                return true;
        }
    }
    return false;
}
int evaluate(vector<int>& window,int token){
    int opp_token=my_token==token?yp_token:my_token;
    int countZero=0;
    int countOpp=0;
    int countTok=0;
    int score=0;
    for(auto tmpToken:window){
        if(tmpToken==0)countZero++;
        if(tmpToken==opp_token)countOpp++;
        else countTok++;
    }
    if(countTok==4)score+=100000;
    else if(countTok==3 && countZero==1)score+=50000;
    else if(countTok==2 && countZero==2)score+=20000;
    if(countOpp==3 && countZero==1)score-=400000;
    return score;
}
long long scoreUp(int token){
    long long score=0;
    //count Center
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col+=3){
            if(board[row][col]==token)score+=30000;
        }
    }
    vector<int>window;
    //count horizontal
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols-3;col++){
            for(int i=0;i<connectLen;i++){
                window.push_back(board[row][col+i]);
            }
            score+=evaluate(window,token);
            window.clear();
        }
    }
    //count vertical
    for(int col=0;col<cols;col++){
        for(int row=0;row<rows-3;row++){
            for(int i=0;i<connectLen;i++){
                window.push_back(board[row+i][col]);
            }
            score+=evaluate(window,token);
            window.clear();
        }
    }

    for(int row=0;row<rows-3;row++){
        for(int col=0;col<cols-3;col++){
            for(int i=0;i<connectLen;i++){
                window.push_back(board[row+i][col+i]);
            }
            score+=evaluate(window,token);
            window.clear();
        }
    }

    for(int row=0;row<rows-3;row++){
        for(int col=0;col<cols-3;col++){
            for(int i=0;i<connectLen;i++){
                window.push_back(board[row+3-i][col+i]);
            }
            score+=evaluate(window,token);
            window.clear();
        }
    }
    return score;
}
bool gameOver(){
    return winMove(my_token) || winMove(yp_token) || sizeof(getValidLocations())==0;
}
void putToken(int row,int col,int token){
    board[row][col]=token;
}
pair<int,long long> miniMax(int depth,long long alpha,long long beta,int maximizingPlayer){
    vector<int> validLocations=getValidLocations();
    bool gameover=gameOver();
    if(depth==0 || gameover){
        if(gameover){
            if(winMove(my_token)){
                return make_pair(-1,100000000000000LL);
            }
            else if(winMove(yp_token)){
                return make_pair(-1,-100000000000000LL);
            }
            else return make_pair(-1,0LL);
        }
        return make_pair(-2,scoreUp(my_token));
    }
    if(maximizingPlayer){
        long long value=INT64_MIN,newScore;
        vector< vector<int> >copyBoard;
        int curCol;
        for(auto col:validLocations){
            int row=getNextRow(col);
            copyBoard=board;
            putToken(row,col,my_token);
            newScore=miniMax(depth-1,alpha,beta,false).second;
            board=copyBoard;
            if(newScore>value){
                value=newScore;
                curCol=col;
            }
            alpha=max(alpha,value);
            if(alpha>=beta)
                break;
        }
        return make_pair(curCol,value);
    }
    else{//minimizing
        long long value=INT64_MAX,newScore;
        int curCol;
        vector< vector<int> > copyBoard;
        for(auto col:validLocations){
            int row=getNextRow(col);
            copyBoard=board;
            putToken(row,col,yp_token);
            newScore=miniMax(depth-1,alpha,beta,true).second;
            board=copyBoard;
            if(newScore<value){
                value=newScore;
                curCol=col;
            }
            beta=min(value,beta);
            if(alpha>=beta)
                break;
        }
        return make_pair(curCol,value);
    }
}
void print(){
    for(auto i:board){
        for(auto j:i)
            cout<<j<<' ';
        cout<<'\n';
    }
}

int decide(int yp_move) {
    if (yp_move == -1) {
        // A new game starts
        board.clear();
        for(int i=0;i<rows;i++){//init 
            vector<int> tmp;
            board.push_back(tmp);
            for(int j=0;j<cols;j++){
                board[i].push_back(0);
            }
        }
        putToken(0,3,my_token);
        print();
        return 3; 
    }
    else {
        // YP placed his piece at column `yp_move` 
        int row=getNextRow(yp_move);
        putToken(row,yp_move,yp_token);
        pair<int,long long>info=miniMax(5,INT64_MIN,INT64_MAX,true);
        int col=info.first;
        //int miniMaxScore=info.second;
        if(col>=0 && validLocation(col)){
            row=getNextRow(col);
            putToken(row,col,my_token);
            print();
            return col;
        }
        else {
            col=getValidLocations().back();
            putToken(getNextRow(col),col,my_token);
            print();
            return col;
        }
            
    }
   
}
