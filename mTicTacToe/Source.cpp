#include<conio.h>
#include<iostream>
#include<dos.h>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <chrono>
#include <thread>
#include <stdlib.h>






struct Move
{
	unsigned int row = 0;
	unsigned int col = 0;
};
enum class BOX
{
	None = '-',// empty
	Human = 'X',
	Agent = 'O'
};
class TicTacToeGame
{




	BOX mBoard[3][3];
	bool DRAW = false;
public:
	TicTacToeGame()
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				mBoard[i][j] = BOX::None;
			}
		}
	}


	void Print() const // print the current board
	{
		system("cls");
		std::cout << "\n\n\tTic Tac Toe\n\n";

		std::cout << "Human (X)  -  BESO 's Agent  (O)\n\n\n" ;
		int Number = 1;
		for (unsigned int i = 0; i < 3; i++)
		{
			std::cout << "\n   |";// COL
			for (unsigned int j = 0; j < 3; j++)
			{
				std::cout << "\t";
			//	SetColor(1);
	
				if (mBoard[i][j] == BOX::None)
				{
					std::cout << Number;
				}
				else
				{
				
					std::cout << static_cast<char>(mBoard[i][j]);
				}
				std::cout << "\t" << " |";
				Number++;

			}
		}
	}
	bool isDraw()  const
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (mBoard[i][0] == BOX::None || mBoard[i][1] == BOX::None || mBoard[i][2] == BOX::None)
				return false;
		}
		return true;
	}
	bool checkWin(BOX player)const // does a box makes a  win ?
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			// Check horizontals
			if (mBoard[i][0] == player && mBoard[i][1] == player && mBoard[i][2] == player)
				return true;

			// Check verticals
			if (mBoard[0][i] == player && mBoard[1][i] == player && mBoard[2][i] == player)
				return true;
		}

		// Check diagonals
		if (mBoard[0][0] == player && mBoard[1][1] == player && mBoard[2][2] == player)
			return true;

		if (mBoard[0][2] == player && mBoard[1][1] == player && mBoard[2][0] == player)
			return true;

		return false;
	}
	Move minimax()
	{
		int score = INT_MAX;// virtual  min score
		// root choose max
		Move CurrMove;

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (mBoard[i][j] == BOX::None)//free
				{
					mBoard[i][j] = BOX::Agent;

					int IsMax = maxSearch(-1);

					if (IsMax < score)//  this my move now this make a largest score at root 
					{
						score = IsMax;
						CurrMove.row = i;
						CurrMove.col = j;
					}
					mBoard[i][j] = BOX::None;
				}
			}
		}

		return CurrMove;
	}

	int maxSearch(int level)
	{
		if (checkWin(BOX::Human)) { return 100; } // any price for wining  
		else if (checkWin(BOX::Agent)) { return -100; }
		else if (isDraw()) { return 0; }

		int score = INT_MIN;

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (mBoard[i][j] == BOX::None)
				{
					mBoard[i][j] = BOX::Human;
					score = std::max(score, minSearch(level+1)-level);
					mBoard[i][j] = BOX::None;
				}
			}
		}

		return score;
	}

	int minSearch(int level)
	{
		if (checkWin(BOX::Human)) { return 100; } // any price for wining  
		else if (checkWin(BOX::Agent)) { return -100; }
		else if (isDraw()) { return 0; }

		int score = INT_MAX;

		for (unsigned int i = 0; i < 3; i++)
		{	
			for (unsigned int j = 0; j < 3; j++)
			{
				if (mBoard[i][j] == BOX::None)
				{
					mBoard[i][j] = BOX::Agent;
					score = std::min(score, maxSearch(level+1)+level);
					mBoard[i][j] = BOX::None;
				}
			}
		}

		return score;
	}

	void setBOX(Move rM, BOX Player)
	{

		// =>Add validation
		this->mBoard[rM.row][rM.col] = Player;
	}
	BOX getBOX(int row, int col)const
	{
		return this->mBoard[row][col];
	}




};
void getHumanMove(TicTacToeGame &rGame)
{
	bool inValidMove = false;
	Move aMove;
	int mNumber;
	do
	{
		inValidMove = false;
		std::cout << "\n Enter a Number ranged 1-9\n";
		std::cout << "\nYour Move: ";
		char c;
		std::cin >> c;
		mNumber = c - '0';
		switch (mNumber)
		{
		case 1:aMove.row = 0; aMove.col = 0; break;
		case 2:aMove.row = 0; aMove.col = 1; break;
		case 3:aMove.row = 0; aMove.col = 2; break;
		case 4:aMove.row = 1; aMove.col = 0; break;
		case 5:aMove.row = 1; aMove.col = 1; break;
		case 6:aMove.row = 1; aMove.col = 2; break;
		case 7:aMove.row = 2; aMove.col = 0; break;
		case 8:aMove.row = 2; aMove.col = 1; break;
		case 9:aMove.row = 2; aMove.col = 2; break;
		default:
			inValidMove = true;
			std::cout << "Entered inValid Number please choose 1-9";
			break;
		}
		if (!inValidMove)
		{
			if (rGame.getBOX(aMove.row, aMove.col) == BOX::None)
			{
				rGame.setBOX(aMove, BOX::Human);
				inValidMove = false;
			}
			else
			{
				inValidMove = true;
				std::cout << "This box is Already Assigned , Choose Another box Please\n";
			}
		}


	} while (inValidMove);


}
//void SetColor(int value) {
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
//}

int main()
{
	TicTacToeGame mGame;
	mGame.Print();
	bool AgentTurn = true;
	bool End = false;
	mGame.Print();
	char turn;
	while (1)
	{
		std::cout << "\nDo you want to start ? y/n \n";
		std::cin >> turn;
		if (turn == 'y')
			AgentTurn = false;
		break;
	}
	do
	{
		// human move
		if (AgentTurn)
		{

			std::cout << "\nComputer Move: ";

			Move aimove = mGame.minimax();
			mGame.setBOX(aimove, BOX::Agent);

			if (mGame.checkWin(BOX::Agent))
			{
				std::cout << "\n*** Beso win ***\n";
				End = true;
			}
			std::this_thread::sleep_for(std::chrono::seconds(2));
		
		}
		else
		{
			getHumanMove(mGame);

			if (mGame.checkWin(BOX::Human))
			{
				std::cout << "\n*** HUMAN ***\n";
				End = true;
			}
			
	
		}

		if (mGame.isDraw())
		{
			std::cout << "\n*** DRAW ***\n";
			End = true;
		}
		AgentTurn ^= 1;
		mGame.Print();
		std::this_thread::sleep_for(std::chrono::seconds(2));

	} while (!End);














}