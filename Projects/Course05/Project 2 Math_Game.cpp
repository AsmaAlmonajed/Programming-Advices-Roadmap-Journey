#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionsLevel { EsayLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	int Number1;
	int Number2;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionsLevel QuestionsLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionsLevel - 1];
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions;

	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 1;

	do
	{
		cout << "\nEnter Questions Level [1] Esay, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionsLevel;

	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionsLevel)QuestionsLevel;
}

enOperationType ReadOpType()
{
	short OpType = 1;

	do
	{
		cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul [4] Div [5] Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
	default:
		return Number1 + Number2;
	}
}

enOperationType GitRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestions(enQuestionsLevel QuestionsLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GitRandomOperationType();
	}

	Question.OperationType = OpType;
	Question.QuestionLevel = QuestionsLevel;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EsayLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		return Question;
	}

	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestions(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Questin [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n__________" << endl;

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The right answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionsListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "______________________________\n\n";
	cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n______________________________\n\n";
	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionsListAnswers(Quizz);
	PrintQuizzResults(Quizz);
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
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}

