#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drawing.h"
#include <string.h>
#include <stdbool.h>
#define maxWordLen 20

typedef struct
{
	char nickname[21];
	char gameResult[9];
	char guessWord[maxWordLen];
	char usedChars[60];
	bool isOn;
	int attempts;
	int badAnswers;
	char userProgress[maxWordLen];
}TGame;


void readLine(const char *, int, char *);
int getRandomNum();
void gameplay(TGame*);
void checkGuess(TGame*, char);
TGame initGame(const char *);
bool isUsed(TGame*, char c);
void printRevealed(TGame*);
void updateGameSt(TGame*);
void saveStat(TGame*);
void printStat();
void winKeeper();


int main(int argc, char **argv)
{
	int lineToRead = getRandomNum();
	char *guessWord;
	readLine("words.txt", lineToRead, guessWord);
	if (guessWord[0] == 0)
	{
		printf("Blad, nie udalo sie odczytac pliku.\n");
		winKeeper();
		return 1;
	}

	TGame game = initGame(guessWord);
	gameplay(&game);

	printf("Aby wywietlic statystki wpisz 's' lub inny znak aby wyjsc.\n");
	char userChc;

	fflush(stdin);
	scanf("%c", &userChc);
	if (userChc == 's'){
		printStat();
	}else{
		saveStat(&game);
		return 0;
	}

	saveStat(&game);
	winKeeper();


	return 0;
}

void readLine(const char *filename, int n, char *toSave)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		toSave[0] = 0;
		return;
	}

	char word[maxWordLen];

	for (int i = 0; i < n; i++)
	{
		if (fgets(word, maxWordLen, file) == NULL)
		{
			fclose(file);
			toSave[0] = 0;
			return;
		}
	}
  
	word[strlen(word) - 1] = 0;
	fclose(file);
	strcpy(toSave, word);
}

int getRandomNum()
{
	srand(time(NULL));

	return rand() % 176;
}

TGame initGame(const char *guessWord)
{
	char nickname[21];
	printf("Podaj swoj nick, moze miec maksymalnie 20 znakow oraz tylko polskie znaki: \n");
	scanf("%20s", &nickname);

	TGame game = {};

	strcpy(game.nickname, nickname);
	strcpy(game.gameResult, "Brak");
	strcpy(game.guessWord, guessWord);
	game.isOn = true;
	game.attempts = 0;
	game.badAnswers = 0;
	for (int i = 0; guessWord[i] != 0; i++)
	{
		game.userProgress[i] = '_';
	}
	
	return game;
}

void checkGuess(TGame *game, char userGuess){
	game -> attempts++;

	bool isPresent = false;
	for (int i = 0; game -> guessWord[i] != 0; i++){
		if ((game -> guessWord[i] == userGuess) && (game -> userProgress[i] == '_')){
			game -> userProgress[i] = userGuess;
			isPresent = true;
		}
	}
	if (! isPresent)
		game -> badAnswers++;
}

bool isUsed(TGame *game, char c){
	for (int i=0; i < sizeof(game -> usedChars); i++){
		if (game -> usedChars[i] == c)
			return true;
	}

	for (int i=0; i < sizeof(game -> usedChars); i++){
		if (game -> usedChars[i] == 0){
			game -> usedChars[i] = c;
			return false;
		}
	}
}

void printRevealed(TGame *game){
	printf("\nSTATUS: ");
	for (int i = 0; game -> userProgress[i]; i++){
		printf("%c", game -> userProgress[i]);
	}
	printf("\n");
}

void updateGameSt(TGame *game){
	if (strcmp(game -> userProgress, game -> guessWord) == 0){
		game -> isOn = false;
		strcpy(game -> gameResult, "Wygrana");
		system("cls");
		draw(game -> badAnswers);
		printf("WYGRALES! :D\n");
	} else if (game -> badAnswers > 10){
		game -> isOn = false;
		strcpy(game -> gameResult, "Przegrana");
		system("cls");
		draw(game -> badAnswers);
		printf("Przegrana :(\nTwoje slowo to '%s'.\n", game -> guessWord);

	}
}

void gameplay(TGame *game){
	printf("Twoje slowo ma %d liter, sprobuj je odgadnac:\n", strlen(game -> guessWord));

	bool wasChrUsed = false;
	while(game -> isOn){
		system("cls");

		if (game -> badAnswers > 0)
			draw(game -> badAnswers);

		printRevealed(game);
		if (wasChrUsed){
			printf("Uzyles juz tego znaku.\n");
		}

		char userGuess;
		printf("Podaj znak: ");
		fflush(stdin);
		scanf("%c", &userGuess);
		if (userGuess == 10){
			printf("Niedozwolony znak.");
			continue;
		}
			
		wasChrUsed = isUsed(game, userGuess);
		if (wasChrUsed)
			continue;

		checkGuess(game, userGuess);
		updateGameSt(game);
	}
}

void saveStat(TGame *game){
    FILE *file = fopen("statistics.txt", "a");
    fprintf(file, "%s %s %s %s %d %d %s\n", 
    game -> nickname, game -> gameResult, game -> guessWord,
    game -> usedChars, game-> attempts,
    game -> badAnswers, game -> userProgress);

	fclose(file);
}

void printStat(){
	FILE *file = fopen("statistics.txt", "r");
	if (file == NULL){
		printf("Plik ze statystykami jeszcze nie istnieje, rozegraj wiecej rozgrywek.");
		fclose(file);
		return;
	}

	printf("Statystyki wygladaja nastepujaco:\n");

	char nickname[21];
	char gameResult[10];
	char guessWord[maxWordLen];
	char usedChars[60];
	int attempts;
	int badAnswers;
	char userProgress[maxWordLen];
	while (fscanf(file, "%s %s %s %s %d %d %s", nickname, gameResult, guessWord, usedChars, &attempts, &badAnswers, userProgress) == 7)
	{
		printf("------------------------\n");
		printf("Pseudonim: %s\nWynik gry: %s\nSlowo do odgadniecia: %s\nUzyte znaki: %s\nWszystkich odpowiedzi: %d\nBlednych odpowiedzi: %d\nPlansza gracza: %s\n", 
		nickname, gameResult, guessWord, usedChars, attempts, badAnswers, userProgress);
		printf("------------------------\n");
	}

	fclose(file);
}

void winKeeper(){
	printf("\nAby wyjsc wpisz jakis przycisk: ");
	scanf("%s");
}