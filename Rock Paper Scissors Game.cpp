#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enGame_Choice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRound_Info {
	short Round_Number = 0;
	enGame_Choice Player1_Choice;
	enGame_Choice Computer_Choice;
	enWinner Winner;
	string Winner_Name;
};

struct stGame_Results {
	short Game_Rounds = 0;
	short Player1_Win_Times = 0;
	short Computer2_Win_Times = 0;
	short Draw_Times = 0;
	enWinner Game_Winner;
	string Winner_Name = "";
};

int Random_Number(int From, int To) {
	int Random_Number = rand() % (To - From + 1) + From;
	return Random_Number;
}

string Winner_Name(enWinner Winner) {
	string Arr_Winner_Name[3] = { "Player1" , "Computer" , "No Winner" };
	return Arr_Winner_Name[Winner - 1];
}

enWinner Who_Won_The_Round(stRound_Info Round_Info) {
	if (Round_Info.Player1_Choice == Round_Info.Computer_Choice) {
		return enWinner::Draw;
	}

	switch (Round_Info.Player1_Choice) {
	case enGame_Choice::Stone:
		if (Round_Info.Computer_Choice == enGame_Choice::Paper) {
			return enWinner::Computer;
		}
		break;
	case enGame_Choice::Paper:
		if (Round_Info.Computer_Choice == enGame_Choice::Scissors) {
			return enWinner::Computer;
		}
		break;
	case enGame_Choice::Scissors:
		if (Round_Info.Computer_Choice == enGame_Choice::Stone) {
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player1;
}

string Choice_Name(enGame_Choice Choice) {
	string arr_Game_Choices[3] = { "Stone", "Paper", "Scissors" };
	return arr_Game_Choices[Choice - 1];
}

void Set_Winner_Screen_Color(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << '\a';
		break;
	default:
		system("color 6F");
		break;
	}
}

void Print_Round_Results(stRound_Info Round_Info) {
	cout << "\n________________Round [" << Round_Info.Round_Number << "] _______________\n\n";
	cout << "Player1  Choice: " << Choice_Name(Round_Info.Player1_Choice) << endl;
	cout << "Computer Choice: " << Choice_Name(Round_Info.Computer_Choice) << endl;
	cout << "Round Winner   : " << Round_Info.Winner_Name << endl;
	cout << "_________________________________________\n" << endl;
	Set_Winner_Screen_Color(Round_Info.Winner);
}

enWinner Who_Won_The_Game(short Player1_Win_Times, short Computer_Win_Times) {
	if (Player1_Win_Times > Computer_Win_Times)
		return enWinner::Player1;
	else if (Computer_Win_Times > Player1_Win_Times)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGame_Results Fill_Game_Results(int  Game_Rounds, short Player1_Win_Times, short Computer_Win_Times, short Draw_Times) {
	stGame_Results Game_Results;
	Game_Results.Game_Rounds = Game_Rounds;
	Game_Results.Player1_Win_Times = Player1_Win_Times;
	Game_Results.Computer2_Win_Times = Computer_Win_Times;
	Game_Results.Draw_Times = Draw_Times;
	Game_Results.Game_Winner = Who_Won_The_Game(Player1_Win_Times, Computer_Win_Times);
	Game_Results.Winner_Name = Winner_Name(Game_Results.Game_Winner);

	return Game_Results;
}

enGame_Choice Read_Player1_Choice() {
	short Choice = 1;
	do {
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGame_Choice)Choice;
}

enGame_Choice Get_Computer_Choice() {
	return (enGame_Choice)Random_Number(1, 3);
}

stGame_Results Play_Game(short How_Many_Rounds) {
	stRound_Info Round_Info;
	short Player1_Win_Times = 0, Computer_Win_Times = 0, Draw_Times = 0;

	for (short Game_Round = 1; Game_Round <= How_Many_Rounds; Game_Round++) {
		cout << "\nRound [" << Game_Round << "] begins:\n";
		Round_Info.Round_Number = Game_Round;
		Round_Info.Player1_Choice = Read_Player1_Choice();
		Round_Info.Computer_Choice = Get_Computer_Choice();
		Round_Info.Winner = Who_Won_The_Round(Round_Info);
		Round_Info.Winner_Name = Winner_Name(Round_Info.Winner);

		if (Round_Info.Winner == enWinner::Player1)
			Player1_Win_Times++;
		else if (Round_Info.Winner == enWinner::Computer)
			Computer_Win_Times++;
		else
			Draw_Times++;

		Print_Round_Results(Round_Info);
	}
	return Fill_Game_Results(How_Many_Rounds, Player1_Win_Times, Computer_Win_Times, Draw_Times);
}

string Tabs(short Number_Of_Tabs) {
	string t = "";
	for (int i = 1; i < Number_Of_Tabs; i++) {
		t = t + "\t";
		cout << t;
	}
	return t;
}

void Show_Game_Over_Screen() {
	cout << Tabs(2) << "____________________________________________________________________________\n\n";
	cout << Tabs(2) << "                         +++ G a m e   O v e r +++\n";
	cout << Tabs(2) << "____________________________________________________________________________\n\n";
}

void Show_Final_Game_Results(stGame_Results Game_Results) {
	cout << Tabs(2) << "____________________________ [Game Result ] ________________________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << Game_Results.Game_Rounds << endl;
	cout << Tabs(2) << "Player1 Won Times  :" << Game_Results.Player1_Win_Times << endl;
	cout << Tabs(2) << "Computer Won Times :" << Game_Results.Computer2_Win_Times << endl;;
	cout << Tabs(2) << "Draw Times :" << Game_Results.Draw_Times << endl;;
	cout << Tabs(2) << "Final Winner :" << Game_Results.Winner_Name << endl;;
	cout << Tabs(2) << "____________________________________________________________________________\n\n";
	Set_Winner_Screen_Color(Game_Results.Game_Winner);
}

short Read_How_Many_Rounds() {
	short Game_Rounds = 1;
	do {
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> Game_Rounds;
	} while (Game_Rounds < 1 || Game_Rounds > 10);
	return Game_Rounds;
}

void Reset_Screen() {
	system("cls");
	system("color 0F");
}

void Start_Game() {
	char Play_Again = 'Y';
	do {
		Reset_Screen();
		stGame_Results Game_Results = Play_Game(Read_How_Many_Rounds());
		Show_Game_Over_Screen();
		Show_Final_Game_Results(Game_Results);

		cout << endl << Tabs(3) << "Do you want to play again ? Y/N ? ";
		cin >> Play_Again;

	} while (Play_Again == 'Y' || Play_Again == 'y');
}

int main() {
	srand((unsigned)time(NULL));
	Start_Game();
	return 0;
}