#include <iostream>
#include <cstdlib>

using namespace std;

enum enDiceNumber { One = 1, Two = 2, Three = 3, Four = 4, Five = 5, Six = 6 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enDiceNumber Player1Choice;
	enDiceNumber ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResults
{
	short GameRound = 0;
	short Player1WonTimes = 0;
	short Computer2WonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

string  WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer" , "No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	else if (RoundInfo.Player1Choice > RoundInfo.ComputerChoice)
	{
		return enWinner::Player1;
	}
	else
	{
		return enWinner::Computer;
	}
}

string ChoiceName(enDiceNumber Choice)
{
	string arrGameChoices[6] = { "One" , "Two" , "Three" , "Four" , "Five", "Six" };
	return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
	cout << "___________________________________\n" << endl;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short GameRound, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;
	GameResults.GameRound = GameRound;
	GameResults.Player1WonTimes = Player1WinTimes;
	GameResults.Computer2WonTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

enDiceNumber ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour Choice: [1]:One, [2]:Two, [3]:Three, [4]:Four, [5]:Five, [6]:Six ? ";
		cin >> Choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "\nInvalide Number, Enter a valid one: ";
			cin >> Choice;
		}

	} while (Choice < 1 || Choice > 6);

	return (enDiceNumber)Choice;
}

enDiceNumber GetComputerChoice()
{
	return (enDiceNumber)RandomNumber(1, 6);
}

stGameResults PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (int GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins: \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		SetWinnerScreenColor(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOverScreen()
{
	cout << "_________________________________________________________\n\n";
	cout << "                 +++ G a m e  O v e r +++\n\n";
	cout << "_________________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << "_____________________ [Game Results]_____________________\n\n";
	cout << "Game Rounds        : " << GameResults.GameRound << endl;
	cout << "Player1 won times  : " << GameResults.Player1WonTimes << endl;
	cout << "Computer won times : " << GameResults.Computer2WonTimes << endl;
	cout << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << "___________________________________________________________\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRound()
{
	short GameRound;

	do
	{
		cout << "\nHow Many Round 1 to 10 ? ";
		cin >> GameRound;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "\nInvalide Number, Enter a valid one: ";
			cin >> GameRound;
		}

	} while (GameRound < 1 || GameRound > 10);

	return GameRound;
}

void ReastScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ReastScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRound());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}

