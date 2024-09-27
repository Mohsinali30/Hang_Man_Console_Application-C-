
	#include <Windows.h>
	#include <conio.h>
	#include<iostream>
	using namespace std;
	
	class Hangman
	{	
	private:
	char *response="";
	string shown="";
	string hint;
	int p1_count= 0 ;
	int p2_count = 0 ;
	int count = 1 ;
	string p1 = "Player 1" ;
	string p2 = "Player 2" ;
	public :
	HANDLE H_Console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	void gotoXY(int X, int Y) 
	{
	COORD position;
	position.X = X;
	position.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	}
	
	void hangmanGame()
	{
	while (true)
	{
	system("cls");
	gotoXY(31, 10);
	cout << "(1)->  Play game ";
	gotoXY(31, 12);
	cout << "(2)->  Change Names ";
	gotoXY(31, 14);
	cout << "(3)-> How to play";
	gotoXY(31, 16);
	cout << "(4)-> Store Word and Hint";
	gotoXY(31, 18);
	cout << "(5)->    Exit    ";
	gotoXY(18, 23);
	cout << p1 << " : " << p1_count;
	gotoXY(50, 23);
	cout << p2 << " : " << p2_count;
	gotoXY(0, 29);
	char ch = getch();
	if (ch == '1')
	startGame();
	else if (ch == '2')
	{
	SetConsoleTextAttribute(H_Console, 12);
	system("cls");
	gotoXY(31, 16);
	cout << "Player 1 : ";
	gotoXY(31, 18);
	getline(cin, p1);
	gotoXY(31, 20);
	cout << "Player 2 : ";
	gotoXY(31, 22);
	getline(cin, p2);
	continue;
	}
	else if (ch == '3')
	instructions();
	else if (ch == '4')
	{
	SetConsoleTextAttribute(H_Console, 12);
	system("cls");
	char word1[100];
	gotoXY(31, 16);
	cout << "Enter the secret word";
	gotoXY(31, 18);
	cin >> word1;
	storetheword(word1);
	gotoXY(31, 20);
	cout << "Enter a hint : ";
	cout<<"give hint like  h or h****r"<<endl;
	scanf("\n");
	gotoXY(31, 22);
	getline(cin, hint);
	continue;
	}
	else if (ch == '5')
	exit(0);
	else
	continue;
	}
	}
	
	void startGame()
	{
	if(response=="" or strlen(response)<=1)
	{
	SetConsoleTextAttribute(H_Console, 12);
	system("cls");
	gotoXY(25, 12);
	cout<<"Enter a valid word first! TO start The Game ";
	gotoXY(25, 14);
	cout<<"Press any key to return to Menu";
	char any = getch();
	return ;
	}
	while (true) 
	{
	count+=1 ;
	playGame();
	char chek = getch() ;
	break ;
	}
	hangmanGame();
	}
	
	void playGame()
	{
	system("cls");
	int lives = 0, check = 0;
	char guess[100], input ;
	char *word ;
	word = getWord();
	encryptWord(word, guess);
	while (true)
	{
	gotoXY(12, 4);
	cout << "Word : ";
	puts(guess);
	gotoXY(12,6) ;
	cout<< "Hint : " ;
	cout<<hint ;
	gotoXY(58, 4);
	cout << "Lives : " << (7 - lives);
	hanging(lives);
	if (lives == 7)
	break;
	if (checkWord(word, guess))
	{
	check = 1;
	break;
	}
	gotoXY(12, 11);
	cout<<endl;
	cout <<"    Enter your guess : ";
	input = getche();
	gotoXY(14, 14);
	if (checkGuess(word, guess, input))
	{
	cout << "                        ";
	gotoXY(14, 14);
	cout << "Good guess!";
	}
	else
	{
	cout << "One step closer to death";
	lives++;
	}
	}
	SetConsoleTextAttribute(H_Console, 12);
	gotoXY(18, 20);
	if (check == 1)
	{
	cout << "YOU WIN!";
	if (!(count&1))
	p1_count+=1 ;
	else
	p2_count+=1 ;
	}
	else
	cout << "YOU LOSE!";
	cout<<endl;
	SetConsoleTextAttribute(H_Console, 9);
	}
	
	char* getWord() 
	{
	return response ;
	}
	
	void encryptWord(char* word, char *guess) 
	{
	int i = 1;
	guess[0] = word[0];
	while (word[i] != '\0')
	{
	guess[i] = '*';
	i++;
	}
	guess[i] = '\0';
	}
	
	void hanging(int wrong)
	{
	static char hang[12][20];
	if (wrong == 0) 
	{
	strcpy(hang[0], " _____________    ");
	strcpy(hang[1], " |           |    ");
	strcpy(hang[2], " |           |    ");
	strcpy(hang[3], "             |   ");
	strcpy(hang[4], "             |   ");
	strcpy(hang[5], "             |    ");
	strcpy(hang[6], "             |   ");
	strcpy(hang[7], "             |    ");
	strcpy(hang[8], "             |    ");
	strcpy(hang[9], "             |    ");
	strcpy(hang[10], "             |    ");
	strcpy(hang[11], "         ---------");
	}
	else if (wrong == 1)
	strcpy(hang[3], " O           |    ");
	else if (wrong == 2)
	strcpy(hang[4], " |           |   ");
	else if (wrong == 3)
	strcpy(hang[4], "/|           |   ");
	else if (wrong == 4)
	strcpy(hang[4], "/|\\          |   ");
	else if (wrong == 5)
	strcpy(hang[5], " |           |    ");
	else if (wrong == 6)
	strcpy(hang[6], "/            |   ");
	else
	strcpy(hang[6], "/ \\          |   ");
	for (int i = 0; i < 12; i++) 
	{
	if (wrong == 7)
	SetConsoleTextAttribute(H_Console, 12);
	gotoXY(49, 11 + i);	puts(hang[i]);
	}
	if (wrong == 7)
	SetConsoleTextAttribute(H_Console, 9);
	}
	
	bool checkGuess(char* word , char *guess, char ch) 
	{
	bool check = false;
	int i = 0;
	ch = toupper(ch);
	char temp ;
	while (word[i] != '\0')
	{
	temp = toupper(word[i]);
	if (temp == ch)  
	{	
	guess[i] = word[i];
	check = true;
	}
	i++;
	}
	return check;
	}
	
	bool checkWord(string word, char *guess) 
	{
	int i = 0;
	while (word[i] != '\0') {
	if (word[i] != guess[i])
	return false;
	i++;
	}
	return true;
	}
	
	void instructions() 
	{
	SetConsoleTextAttribute(H_Console, 12);
	system("cls");
	char about[19][78];
	strcpy(about[0], "                                :: HANGMAN ::                                ");
	strcpy(about[1], "                                                                             ");
	strcpy(about[2], "                   In this game, you have to guess a word!                   ");
	strcpy(about[3], "             													               ");
	strcpy(about[4], "                                                                             ");
	strcpy(about[5], "                 You will have 7 lives for guessing the word                 ");
	strcpy(about[6], "                        If you guessed the word right                        ");
	strcpy(about[7], "                       	you win the round!				               ");
	strcpy(about[8], "                                                                             ");
	strcpy(about[9], "                But if you're not able to guess the word and                 ");
	strcpy(about[10], "                   lives finish then you lose the round!                    ");
	strcpy(about[11], "                                                                            ");
	strcpy(about[12], "                     First, Player 1 must enter word to be                   ");
	strcpy(about[13], "                                                                             ");
	strcpy(about[14], "                          guessed, along with the hint                       ");
	strcpy(about[15], "                                                                             ");
	strcpy(about[16], "                         Player 2 will try to guess the word                 ");
	strcpy(about[17], "                                                                             ");
	strcpy(about[18], "                          Positions swap after each round                    ");
	for (int i = 0; i < 19; i++) {
	gotoXY(1, 5 + i); puts(about[i]);
	}
	gotoXY(0, 29);
	getch();
	hangmanGame();
	}	
	
	void storetheword(char *x)
	{
	response=x;
	}
	};
	
	int main()
	{
	Hangman Play; 
	system("mode 80,30");
	system("color 06");
	Play.hangmanGame();					
	return 0;
	}
