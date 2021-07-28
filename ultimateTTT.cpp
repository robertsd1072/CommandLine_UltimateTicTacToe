#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <stdlib.h>
using namespace std;

char board[9][9];
bool openBoards[9];
int numPlayerWins = 0;
int numCompWins = 0;
int numTiedBoards = 0;
int winningConfigs[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
int whichForPlayer = 0;
int whichForComp = 0;
int previousWhichForPlayer = 0;
int miniBoardCompIsPlaying = 4;

void setupBoardAndConfigs()
{
	numPlayerWins = 0;
	numCompWins = 0;
	for (int i=0; i<9; i++)
	{
		openBoards[i] = true;
		for (int j=0; j<9; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void printBoard()
{
	for (int i=0; i<9; i+=3)
	{
		cout << " ";
		cout << "           " << " | " << "           " << " | " << "           " << endl;

		cout << " ";
		cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " ";
		cout << " | ";
		cout << " " << board[i+1][0] << " | " << board[i+1][1] << " | " << board[i+1][2] << " ";
		cout << " | ";
		cout << " " << board[i+2][0] << " | " << board[i+2][1] << " | " << board[i+2][2] << " ";
		cout << endl;

		cout << " ";
		cout << "---+---+---" << " | " << "---+---+---" << " | " << "---+---+---" << endl;

		cout << " ";
		cout << " " << board[i][3] << " | " << board[i][4] << " | " << board[i][5] << " ";
		cout << " | ";
		cout << " " << board[i+1][3] << " | " << board[i+1][4] << " | " << board[i+1][5] << " ";
		cout << " | ";
		cout << " " << board[i+2][3] << " | " << board[i+2][4] << " | " << board[i+2][5] << " ";
		cout << endl;

		cout << " ";
		cout << "---+---+---" << " | " << "---+---+---" << " | " << "---+---+---" << endl;

		cout << " ";
		cout << " " << board[i][6] << " | " << board[i][7] << " | " << board[i][8] << " ";
		cout << " | ";
		cout << " " << board[i+1][6] << " | " << board[i+1][7] << " | " << board[i+1][8] << " ";
		cout << " | ";
		cout << " " << board[i+2][6] << " | " << board[i+2][7] << " | " << board[i+2][8] << " ";
		cout << endl;

		cout << " ";
		cout << "           " << i << "| " << "           " << i+1 << "| " << "           " << i+2 << endl;

		if (i < 6)
			cout << "-------------+-------------+-------------" << endl;
	}
}

void printWelcomeAndRules()
{
	cout << "" << endl;
    cout << "Welcome to ULTIMATE Tic-Tac-Toe!!" << endl;
    cout << "The board looks like this:" << endl;
    printBoard();
    cout << "To win, win more mini Tic-Tac-Toe boards than the computer."  << endl;
    cout << "Play each mini Tic-Tac-Toe board like normal, ";
    cout << "but on each turn, you can play in any mini Tic-Tac-Toe board on screen." << endl;
    cout << "You are x, the computer is o." << endl;
    cout << "To select location, input two integers: 0 and 0 for example" << endl;
    cout << "The first int represents which mini board: the top left mini board for 0." << endl;
    cout << "The second int represents which location in that mini board." << endl;
    cout << "To end program, enter -1" << endl;
    cout << "To play, hit enter. ";
    getch();
    cout << "\n";
}

int numOpenMiniBoards()
{
	int numOpenBoards = 0;
	for (int i=0; i<9; i++)
	{
		if (openBoards[i])
			numOpenBoards++;
	}
	return numOpenBoards;
}

int playerGoingToWin(int i)
{
	for (int j=0; j<8; j++)
	{
		if (board[i][winningConfigs[j][0]] == 'x' && board[i][winningConfigs[j][1]] == 'x' && board[i][winningConfigs[j][2]] == ' ')
			return j;
		if (board[i][winningConfigs[j][0]] == 'x' && board[i][winningConfigs[j][2]] == 'x' && board[i][winningConfigs[j][1]] == ' ')
			return j;
		if (board[i][winningConfigs[j][1]] == 'x' && board[i][winningConfigs[j][2]] == 'x' && board[i][winningConfigs[j][0]] == ' ')
			return j;
	}
	return -1;
}

int compGoingToWin()
{
	for (int i=0; i<9; i++)
	{
		for (int j=0; j<8; j++)
		{
			if (board[i][winningConfigs[j][0]] == 'o' && board[i][winningConfigs[j][1]] == 'o' && board[i][winningConfigs[j][2]] == ' ')
				return i;
			if (board[i][winningConfigs[j][0]] == 'o' && board[i][winningConfigs[j][2]] == 'o' && board[i][winningConfigs[j][1]] == ' ')
				return i;
			if (board[i][winningConfigs[j][1]] == 'o' && board[i][winningConfigs[j][2]] == 'o' && board[i][winningConfigs[j][0]] == ' ')
				return i;
		}
	}
	return -1;
}

int findLocWhereCompAboutToWin(int miniBoardWhereCompGoingToWin)
{
	for (int i=0; i<8; i++)
	{
		if (board[miniBoardWhereCompGoingToWin][winningConfigs[i][0]] == 'o' && 
			board[miniBoardWhereCompGoingToWin][winningConfigs[i][1]] == 'o' && 
			board[miniBoardWhereCompGoingToWin][winningConfigs[i][2]] == ' ')
		{
			return winningConfigs[i][2];
		}
		if (board[miniBoardWhereCompGoingToWin][winningConfigs[i][0]] == 'o' && 
			board[miniBoardWhereCompGoingToWin][winningConfigs[i][2]] == 'o' && 
			board[miniBoardWhereCompGoingToWin][winningConfigs[i][1]] == ' ')
		{
			return winningConfigs[i][1];
		}
		if (board[miniBoardWhereCompGoingToWin][winningConfigs[i][1]] == 'o' && 
			board[miniBoardWhereCompGoingToWin][winningConfigs[i][2]] == 'o' && 
			board[miniBoardWhereCompGoingToWin][winningConfigs[i][0]] == ' ')
		{
			return winningConfigs[i][0];
		}
	}

	return -1;
}

bool isUnwinnable(int i)
{
	if (!openBoards[i])
		return true;

	for (int j=0; j<8; j++)
	{
		if ((board[i][winningConfigs[j][0]] == ' ' || board[i][winningConfigs[j][0]] == 'o') && 
			(board[i][winningConfigs[j][1]] == ' ' || board[i][winningConfigs[j][1]] == 'o') && 
			(board[i][winningConfigs[j][2]] == ' ' || board[i][winningConfigs[j][2]] == 'o'))
			{
				return false;
			}
	}
	return true;
}

bool playerHasUnbeatableConfig(int i)
{
	int numAlmostWonConfigs = 0;
	for (int j=0; j<8; j++)
	{
		if (board[i][winningConfigs[j][0]] == 'x' && board[i][winningConfigs[j][1]] == 'x' && board[i][winningConfigs[j][2]] == ' ')
			numAlmostWonConfigs++;
		if (board[i][winningConfigs[j][0]] == 'x' && board[i][winningConfigs[j][2]] == 'x' && board[i][winningConfigs[j][1]] == ' ')
			numAlmostWonConfigs++;
		if (board[i][winningConfigs[j][1]] == 'x' && board[i][winningConfigs[j][2]] == 'x' && board[i][winningConfigs[j][0]] == ' ')
			numAlmostWonConfigs++;
	}

	if (numAlmostWonConfigs > 1)
		return true;

	return false;
}

int findIfBestLocationOfNewConfig(int config[], int miniBoardOfInterest)
{
	vector<int> compPlayedSpotsInMiniBoard;
	for (int j=0; j<9; j++)
	{
		if (board[miniBoardOfInterest][j] == 'o')
			compPlayedSpotsInMiniBoard.push_back(j);
	}
	//cout << "Number of comp plays in " << miniBoardOfInterest << ": " << compPlayedSpotsInMiniBoard.size() << endl;
	if (compPlayedSpotsInMiniBoard.size() < 1)
		return -1;
	//compPlayedSpotsInMiniBoard; 1,2
	//config: 3,4,5
	//to win: {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}
	vector<int> numWinnableConfigsIfPlayInLocationArr;
	for (int j=0; j<3; j++)
	{
		//cout << "Config[j]: " << config[j] << endl;
		int numWinnableConfigsIfPlayInLocation = 0;
		for (int k=0; k<compPlayedSpotsInMiniBoard.size(); k++)
		{
			//cout << "compPlayedSpotsInMiniBoard[k]: " << compPlayedSpotsInMiniBoard[k] << endl;
			for (int l=0; l<8; l++)
			{
				if ((config[j] == winningConfigs[l][0] && compPlayedSpotsInMiniBoard[k] == winningConfigs[l][1]) || 
					(config[j] == winningConfigs[l][0] && compPlayedSpotsInMiniBoard[k] == winningConfigs[l][2]) ||
					(config[j] == winningConfigs[l][1] && compPlayedSpotsInMiniBoard[k] == winningConfigs[l][0]) ||
					(config[j] == winningConfigs[l][1] && compPlayedSpotsInMiniBoard[k] == winningConfigs[l][2]) ||
					(config[j] == winningConfigs[l][2] && compPlayedSpotsInMiniBoard[k] == winningConfigs[l][0]) ||
					(config[j] == winningConfigs[l][2] && compPlayedSpotsInMiniBoard[k] == winningConfigs[l][1]))
				{
					//cout << "Found match in config " << l+1 << endl;
					numWinnableConfigsIfPlayInLocation++;
				}
			}
		}
		numWinnableConfigsIfPlayInLocationArr.push_back(numWinnableConfigsIfPlayInLocation);
	}
	/*
	cout << "numWinnableConfigsIfPlayInLocationArr:" << endl;
	for (int i=0; i<numWinnableConfigsIfPlayInLocationArr.size(); i++)
	{
		cout << numWinnableConfigsIfPlayInLocationArr[i] << endl;
	}
	*/

	int biggest = 0;
	int indexOfBiggest = 0;
	for (int i=0; i<numWinnableConfigsIfPlayInLocationArr.size(); i++)
	{
		if (numWinnableConfigsIfPlayInLocationArr[i] > biggest)
		{
			biggest = numWinnableConfigsIfPlayInLocationArr[i];
			indexOfBiggest = i;
		}
	}

	//cout << "Returning " << config[indexOfBiggest] << endl;

	return config[indexOfBiggest];
}

int compPlays()
{
	int aboutToWinConfig = playerGoingToWin(whichForPlayer);
	int miniBoardWhereCompGoingToWin = compGoingToWin();
	if (miniBoardWhereCompGoingToWin == whichForPlayer)
		goto win;

	if (aboutToWinConfig > -1)
	{
		if (!playerHasUnbeatableConfig(whichForPlayer))
		{
			//cout << "Player about to win in " << whichForPlayer << endl;
			for (int i=0; i<3; i++)
			{
				if (board[whichForPlayer][winningConfigs[aboutToWinConfig][i]] == ' ')
				{
					board[whichForPlayer][winningConfigs[aboutToWinConfig][i]] = 'o';
				
					cout << "The computer played " << whichForPlayer << "," << winningConfigs[aboutToWinConfig][i] << endl;

					return whichForPlayer;
				}
			}
		}
		//else
			//cout << "Player has unbeatable config in " << whichForPlayer << endl;
	}
	if (miniBoardWhereCompGoingToWin > -1)
	{
		win:
		//cout << "Computer about to win in " << miniBoardWhereCompGoingToWin << endl;

		int winningLocation = findLocWhereCompAboutToWin(miniBoardWhereCompGoingToWin);
		board[miniBoardWhereCompGoingToWin][winningLocation] = 'o';

		cout << "The computer played " << miniBoardWhereCompGoingToWin << "," << winningLocation << endl;

		return miniBoardWhereCompGoingToWin;
	}
	else
	{
		while (!openBoards[miniBoardCompIsPlaying] || isUnwinnable(miniBoardCompIsPlaying) || 
			   playerHasUnbeatableConfig(miniBoardCompIsPlaying))
		{
			//cout << "Computer is finding new mini board to win" << endl;

			vector<int> whichOpenBoard;
			for (int i=0; i<9; i++)
			{
				if (openBoards[i])
					whichOpenBoard.push_back(i);
			}

			miniBoardCompIsPlaying = whichOpenBoard[rand() % whichOpenBoard.size()];

			int numOpenAndWinnableBoards = 0;
			for (int i=0; i<9; i++)
			{
				if (openBoards[i])
				{
					if (!playerHasUnbeatableConfig(i) && !isUnwinnable(i))
						numOpenAndWinnableBoards++;
				}
			}

			if (playerHasUnbeatableConfig(miniBoardCompIsPlaying) && numOpenAndWinnableBoards == 0)
			{
				vector<int> openSpotsInBoard;
				for (int j=0; j<9; j++)
				{
					if (board[miniBoardCompIsPlaying][j] == ' ')
						openSpotsInBoard.push_back(j);
				}

				int where = rand() % openSpotsInBoard.size();
				board[miniBoardCompIsPlaying][openSpotsInBoard[where]] = 'o';

				cout << "The computer played " << miniBoardCompIsPlaying << "," << openSpotsInBoard[where] << endl;

				return miniBoardCompIsPlaying;
			}
		}
		
		//cout << "Computer is trying to win mini board " << miniBoardCompIsPlaying << endl;

		int config[3];
		for (int j=0; j<8; j++)
		{
			if ((board[miniBoardCompIsPlaying][winningConfigs[j][0]] == ' ' || board[miniBoardCompIsPlaying][winningConfigs[j][0]] == 'o') && 
				(board[miniBoardCompIsPlaying][winningConfigs[j][1]] == ' ' || board[miniBoardCompIsPlaying][winningConfigs[j][1]] == 'o') && 
				(board[miniBoardCompIsPlaying][winningConfigs[j][2]] == ' ' || board[miniBoardCompIsPlaying][winningConfigs[j][2]] == 'o'))
			{
				config[0] = winningConfigs[j][0];
				config[1] = winningConfigs[j][1];
				config[2] = winningConfigs[j][2];
				//cout << "Config is " << config[0] << "," << config[1] << "," << config[2] << endl;
				break;
			}
		}

		int foundBestLocOfNewConfig = findIfBestLocationOfNewConfig(config, miniBoardCompIsPlaying);
		if (foundBestLocOfNewConfig > -1)
		{
			board[miniBoardCompIsPlaying][foundBestLocOfNewConfig] = 'o';

			cout << "The computer played " << miniBoardCompIsPlaying << "," << foundBestLocOfNewConfig << endl;

			return miniBoardCompIsPlaying;
		}

		vector<int> openSpotsInConfig;
		for (int j=0; j<3; j++)
		{
			if (board[miniBoardCompIsPlaying][config[j]] == ' ')
				openSpotsInConfig.push_back(config[j]);
		}
		//cout << "Number of open spots in config: " << numOpenSpotsInConfig << endl;

		int where = rand() % openSpotsInConfig.size();
		board[miniBoardCompIsPlaying][openSpotsInConfig[where]] = 'o';

		cout << "The computer played " << miniBoardCompIsPlaying << "," << openSpotsInConfig[where] << endl;

		return miniBoardCompIsPlaying;
	}
}

bool playerWins(int i)
{
	for (int j=0; j<8; j++)
	{
		if (board[i][winningConfigs[j][0]] == 'x')
		{
			if (board[i][winningConfigs[j][1]] == 'x')
			{
				if (board[i][winningConfigs[j][2]] == 'x')
					return true;
			}
		}
	}
	return false;
}

bool compWins(int i)
{
	for (int j=0; j<8; j++)
	{
		if (board[i][winningConfigs[j][0]] == 'o')
		{
			if (board[i][winningConfigs[j][1]] == 'o')
			{
				if (board[i][winningConfigs[j][2]] == 'o')
					return true;
			}
		}
	}
	return false;
}

void fillMiniBoard(int i, char c)
{
	for (int j=0; j<9; j++)
		board[i][j] = c;
}

bool tieInMiniBoard(int i)
{
	for (int j=0; j<9; j++)
	{
		if (board[i][j] == ' ')
			return false;
	}
	return true;
}

bool endIsInevitable()
{
	int numUnwinnableButPlayableBoards = 0;
	for (int i=0; i<9; i++)
	{
		if (openBoards[i])
		{
			if (isUnwinnable(i))
				numUnwinnableButPlayableBoards++;
		}
	}

	int remainingWinnableBoards = 9 - numTiedBoards - numPlayerWins - numCompWins - numUnwinnableButPlayableBoards;

	if (numPlayerWins > numCompWins + remainingWinnableBoards)
		return true;
	else if (numCompWins > numPlayerWins + remainingWinnableBoards)
		return true;
	else if (remainingWinnableBoards == 0)
		return true;
	else
		return false;
}

int main()
{
	cout << "Skip Rules? Y or N? ";
	string yOrN;
    getline(cin, yOrN);
	if (yOrN == "N")
		printWelcomeAndRules();

	restart:
	setupBoardAndConfigs();
	while (numOpenMiniBoards() > 0 && numPlayerWins < 5 && numCompWins < 5)
	{
    	printBoard();

    	previousWhichForPlayer = whichForPlayer;

    	reenterWhich:
    	cout << "Input which mini board: ";
    	string input;
    	getline(cin, input);
    	stringstream(input) >> whichForPlayer;

    	if (whichForPlayer == -1)
    		return 0;
    	if (whichForPlayer < 0 || whichForPlayer > 8)
    	{
    		cout << "Not a valid loaction." << endl;
    		goto reenterWhich;
    	}
    	if (!openBoards[whichForPlayer])
    	{
    		cout << "That mini board is unplayable." << endl;
    		goto reenterWhich;
    	}

       	reenterLocation:
       	cout << "Input mini board location: ";
    	string input2;
    	getline(cin, input2);
    	int location;
    	stringstream(input2) >> location;

    	if (location < 0 || location > 8)
    	{
			cout << "Not a valid location." << endl;
    		goto reenterLocation;
    	}

    	if (board[whichForPlayer][location] == ' ')
    		board[whichForPlayer][location] = 'x';
    	else
    	{
    		cout << "That location is not playable." << endl;
    		goto reenterLocation;
    	}

    	if (playerWins(whichForPlayer))
    	{
			fillMiniBoard(whichForPlayer, 'x');
			openBoards[whichForPlayer] = false;
			numPlayerWins++;
			if (numPlayerWins > 4)
				break;
			cout << "You won mini board " << whichForPlayer << endl;
    		cout << "That mini board is now unplayable." << endl;
    	}
    	else if (tieInMiniBoard(whichForPlayer))
    	{
    		numTiedBoards++;
    		cout << "No one won mini board " << whichForPlayer << endl;
    		cout << "That mini board is now unplayable." << endl;
    		openBoards[whichForPlayer] = false;
    	}

    	if (numOpenMiniBoards() == 0 || endIsInevitable())
    		break;

    	cout << "Computer's turn." << endl;
    	whichForComp = compPlays();

    	if (compWins(whichForComp))
		{
			fillMiniBoard(whichForComp, 'o');
			openBoards[whichForComp] = false;
			numCompWins++;
			if (numCompWins > 4)
				break;
			cout << "You lost mini board " << whichForComp << endl;
    		cout << "That mini board is now unplayable." << endl;
		}
		else if (tieInMiniBoard(whichForComp))
    	{
    		numTiedBoards++;
    		cout << "No one won mini board " << whichForComp << endl;
    		cout << "That mini board is now unplayable." << endl;
    		openBoards[whichForComp] = false;
    	}

    	if (numOpenMiniBoards() == 0 || endIsInevitable())
    		break;

    	cout << "Your turn." << endl;
	}

	printBoard();

	if (endIsInevitable())
		cout << "The end result is inevitable. The game is over." << endl;

	if (numPlayerWins > 4 || numPlayerWins > numCompWins)
		cout << "You won!!!" << endl;
	else if (numCompWins > 4 || numCompWins > numPlayerWins)
		cout << "You lost:(" << endl;
	else
		cout << "No one won" << endl;

	cout << "Play again? Y or N? ";
    getline(cin, yOrN);
    if (yOrN == "Y")
    	goto restart;

	return 0;
}