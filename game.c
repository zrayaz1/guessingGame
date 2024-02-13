#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Player {
    int guesses;
    char name[30];  
} Player;



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
            fprintf(file, "%s %d", scores[i].name, scores[i].guesses);
        }
        fclose(file);
    }
    else {
        printf("Unable to get file handle (should never happen)");
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
    int guess;
    int tries;
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



