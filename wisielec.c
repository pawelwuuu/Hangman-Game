#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define maxWordLen 20

typedef struct
{
	char nickname[21];
	char gameResult[10];
	char guessWord[maxWordLen];
	int attempts;
	int guessesInRow;
}

TGame;

void readLine(const char *, int, char *);
int getRandomNum();
TGame initGame(const char *);

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
	game.attempts = 0;
	game.guessesInRow = 0;

	return game;
}