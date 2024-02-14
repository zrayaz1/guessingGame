#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Player {
    int guesses;
    char name[30];  
} Player;



void sort(Player scores[], int size) {
    for (int i = 0; i < size; i++) {
        int min = i;
        for (int j = i + 1; j < size-1; j++) {
            if (scores[j].guesses < scores[i].guesses) {
                min = j;
            }
        }
        Player temp = scores[min];
        scores[min] = scores[i];
        scores[i] = temp;

    }
}

void namePrompt(char* name) {
    printf("Please enter your name to start: ");
    scanf("%s", name);
}

// returns the count of scores and writes it to the scores array
int getCurrentScores(Player scores[]) {
    FILE* file = fopen("scores.txt","r");
    int count = 0;
    if (file) {
        fscanf(file, "%d", &count);
        for (int i = 0; i < count; i++) {
            fscanf(file, "%s %d", scores[i].name, &scores[i].guesses);
        }
        fclose(file);
    }
    return count;
}

void writeScoresToFile(Player scores[], int scoreCount) {
    FILE* file = fopen("scores.txt","w");
    if (file) { // probably not necessary since we should always get a file handle
        fprintf(file,"%d\n",scoreCount);
        for (int i = 0; i < scoreCount; i++) {
            fprintf(file, "%s %d\n", scores[i].name, scores[i].guesses);
        }
        fclose(file);
    }
    else {
        printf("Unable to get file handle (should never happen)");
    }

}

void displayScores(Player scores[], int scoresCount) {
    printf("Here are the current leaders: \n");
    for (int i = 0; i < scoresCount; i++) {
        printf("%s made %d guesses.\n", scores[i].name, scores[i].guesses);
    }
}


double getRandom() {
    return rand() % (100+1-10) + 10;
}
int getGuess() {
    int guess;
    printf("Guess a value between 10 and 100: ");
    scanf("%d", &guess);
    return guess;
}

void PlayGuessingGame() {
    char name[30];
    int scoresCount = 0;
    Player scores[5];
    scoresCount = getCurrentScores(scores);
    namePrompt(name);
    double squaredNum = getRandom();
    double num = sqrt(squaredNum);
    sort(scores, scoresCount);
    int guess;
    int tries = 0;
    printf("%f is the sqrt of which number?", num);
    while (guess != squaredNum) {
        guess = getGuess();
        tries++;
        if (guess < squaredNum) {
            printf("Too low, guess again: ");
        }
        else if (guess > squaredNum) {
            printf("Too high, guess again: ");
        }
    }
    printf("You Got it!\n");
    printf("You did it in %d guesses.\n",tries);
    Player currentPlayer;
    currentPlayer.guesses = tries;
    strcpy(currentPlayer.name, name);
    if (scoresCount != 5) {
        scores[scoresCount] = currentPlayer;
        scoresCount++;
    }
    sort(scores,scoresCount);
    displayScores(scores, scoresCount);
    writeScoresToFile(scores, scoresCount);
}

int main() {
    char choice;
    printf("Welcome!"); 
    while (1) {
        printf("Press 'q' to quit or any other key to continue");
        scanf(" %c", &choice);
        if (choice == 'q') {
            break;
        }
        PlayGuessingGame();
    }
}



