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
	char gameResult[10];
	char guessWord[maxWordLen];
	char usedChars[60];
	bool isOn;
	int attempts;
	int badAnswers;
	int guessesInRow;
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

int main(int argc, char **argv)
{
	int lineToRead = getRandomNum();
	char *guessWord;
	readLine("words.txt", lineToRead, guessWord);
	if (guessWord == NULL)
	{
		printf("Blad, nie udalo sie odczytac pliku.\n");
		return 1;
	}

	TGame game = initGame(guessWord);
	gameplay(&game);

	// printf("nick:%s zgadywanie:%s proby:%d jak:%s ciag:%d to dane", game.nickname, game.guessWord, game.attempts, game.gameResult, game.guessesInRow);

	return 0;
}

void readLine(const char *filename, int n, char *toSave)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		*toSave = NULL;
		return;
	}

	char word[maxWordLen];

	for (int i = 0; i < n; i++)
	{
		if (fgets(word, maxWordLen, file) == NULL)
		{
			fclose(file);
			*toSave = NULL;
			return;
		}
	}
  
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
	printf("Podaj swoj nick, moze miec maksymalnie 21 znakow oraz tylko polskie znaki: \n");
	scanf("%s", &nickname);

	TGame game = {};

	strcpy(game.nickname, nickname);
	strcpy(game.gameResult, "Undefined");
	strcpy(game.guessWord, guessWord);
	game.isOn = true;
	game.attempts = 0;
	game.guessesInRow = 0;
	game.badAnswers = 0;
	for (int i = 0; guessWord[i] != 0; i++)
	{
		game.userProgress[i] = '_';
	}
	
	return game;
}

void checkGuess(TGame *game, char userGuess){
	bool isPresent = false;
	for (int i = 0; game -> guessWord[i] != 0; i++){
		// char a = game -> guessWord[i];
		// char c = game -> userProgress[i];

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
		strcpy(game -> gameResult, "WIN");
		printf("WYGRALES! :D");
	} else if (game -> badAnswers > 10){
		game -> isOn = false;
		strcpy(game -> gameResult, "LOSE");
		printf("PRZEGRALES :(");
	}
}

void gameplay(TGame *game){
	printf("Twoje slowo ma %d liter, sprobuj je odgadnac:\n", strlen(game -> guessWord));
	while(game -> isOn){
		char userGuess;
		printf("Podaj znak:\n");
		fflush(stdin);
		scanf("%c", &userGuess);
		if (isUsed(game, userGuess)){
			printf("Uzyles juz znaku '%c'.\n", userGuess);
			continue;
		}

		checkGuess(game, userGuess);

		if (game -> badAnswers > 0)
			draw(game -> badAnswers);
		
		printRevealed(game);

		updateGameSt(game);

		
	}
}