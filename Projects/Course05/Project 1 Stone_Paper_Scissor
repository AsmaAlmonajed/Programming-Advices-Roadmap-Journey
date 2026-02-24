#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
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
		return enWinner::Draw;

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
	}

	//if you reach here then player1 is the winner
	return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone", "Paper" , "Scissors" };
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
	if(Player1WinTimes > ComputerWinTimes)
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

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1,3);
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

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(1) << "_________________________________________________________\n\n";
	cout << Tabs(1) << "                 +++ G a m e  O v e r +++\n\n";
	cout << Tabs(1) << "_________________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(1) << "_____________________ [Game Results]_____________________\n\n";
	cout << Tabs(1) << "Game Rounds        : " << GameResults.GameRound << endl;
	cout << Tabs(1) << "Player1 won times  : " << GameResults.Player1WonTimes << endl;
	cout << Tabs(1) << "Computer won times : " << GameResults.Computer2WonTimes << endl;
	cout << Tabs(1) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(1) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(1) <<"___________________________________________________________\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRound()
{
	short GameRound;

	do
	{
		cout << "How Many Round 1 to 10 ?\n";
		cin >> GameRound;

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

		cout << endl << Tabs(1) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
  
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}

