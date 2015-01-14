//N Queens Problem 

//@Author: Zhe Wang, N19544698

//version: 1.6



//The code starts here:

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;


// create a Queen class
class Queen{

public:
	// row and col represent the placement of a Queen on the chessboard
	int row;
	int col;


	//initiliaze the row and col to zero
	Queen(){
	row =0;
	col =0;
	}


	//put the queen in the current position, usually called after make sure this is a safe placement
	void advance(int board[]){// board[] index is row number, it stores the column number
	board[row] = col;
	row++;
	col =0;
	}


	//move back to the previous placement
	void retreat(int board[]){
	row--;
	col = board[row]+1;
	}

	//check whether the placement is safe or not, if safe, return true, else return false
	bool isSafe(int board[]){
	bool safe = true;
	for(int i=0;i<row;i++){
	if (( (board[i] + i) == (row + col) ) || ( (board[i] - i) == (col - row) ) || (board[i] == col) ) {//these are unsafe positions 
        safe = false;
     }
	}
	return safe;
	}

};


//rotate the placement by 90 degree 
void rotateBoard(int board[], int length){

    int* tmp = new int[length];
	for(int i=0; i<length;i++){
	tmp[board[i]]=length-1-i;
		}
	for(int i=0; i<length;i++){
	board[i]=tmp[i];
	}
	
}


//get the mirror image of the placement
void mirrorImage(int board[], int length){

	for(int i =0; i<length;i++){
	board[i]=length-1-board[i];
	}
	
}


//check whether board1's sum is greater than board2's sum
bool compareArray(int board1[], int board2[], int n){
	int a =0, b=0;
	for(int i=0;i<n;i++){
		a=a*10+board1[i];
		b=b*10+board2[i];
		}
	if(a>b)
		return true;
	else
		return false;
}

//check whether the placement is isomorphic
bool isIso(int board[], int n){
	int* trans = new int[n];
	for (int i = 0 ; i <n ; i++) {
		trans[i] = board[i]; }
	for(int i=0; i<7;i++){
	if(i!=3)
		rotateBoard(trans, n);
	else
		mirrorImage(trans, n);
	if(compareArray(board, trans, n))
		return true;
	}
	return false;
}


// print the result 
void printResult(vector<int *> result, int n){ 
	
	for (int i=0; i<result.size();i++){
		for (int k =0; k< n; k++){
			for (int j = 0; j < n; j++){
				if (result[i][k]==j) 
					cout << " Q "; //Q means this placed has a Queen
				else 
					cout << " * "; // * means nothing is on this position 
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
}



// provide the solution for N queen problem
void solveNqueen(int n){
		Queen* queen = new Queen();
		int* board = new int[n];
		vector<int*> result;// store all the unique placements
		int count =0;//count how many safe placements
		while(true){// when all the placements are found, a return statement will break this while loop
		while(queen->row<n&&queen->row>=0){//before n queens was safely put on the board, continue the loop
			while(queen->row<n&&queen->col<n){
				if(queen->isSafe(board)){
					queen->advance(board);
				}
				else{
				    queen->col++;
					if(board[0]==n-1&&queen->row==1&&queen->col==n-1){//tried all safe placements and break the while loop output the total number of safe placements
					cout<<"When n = "<<n<<", the number of total safe placements is: "<<count<<endl;
					cout<<"The number of unique placements is: "<<result.size()<<endl;
					cout<<"The unique placements are: "<<endl;
					printResult(result, n);// display all the results
				    return;// break the loop
					}	
				}
			}
			if(queen->col==n){// if queen is placed outside of the board, return to previous step
				queen->retreat(board);}
		}
		if(queen->row ==n){// found one safe placement
			count++; //increment the count 
			int* curr = new int[n];
			for(int i=0;i<n; i++){//copy the placement to curr
				curr[i]=board[i];
			}
			if(!isIso(curr, n))// check whether this placement is unique(NOT isomorphic!)
			  result.push_back(curr); //if unique, put it in the result!

			queen->retreat(board);//move backwards to check whether there are any other safe placement	
		}	
				}
		
}


// main function starts here
int main()

{   
	// test when n equals 4, 5, 6, and 8.
	solveNqueen(4);
	solveNqueen(5);
	solveNqueen(6);
	solveNqueen(8);


    return 0;
}

