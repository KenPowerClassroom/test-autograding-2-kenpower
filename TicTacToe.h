#pragma once
class TicTacToe
{
	char grid[9];
public:
	TicTacToe(char* b);
	
	int move(char player);
	
	TicTacToe play(int i, char player);
	
	char winner();
};

