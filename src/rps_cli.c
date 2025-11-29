#include <stdio.h>                                      //imports the standard input output functions from the file stdio.h which comes with the compiler
#include <stdlib.h>
#include <time.h>

int getComputerChoice();
int getUserChoice();
char yesNo;
void checkWinner(int UserChoice, int ComputerChoice);
FILE *fpt;

int getComputerChoice(){
    return (rand() % 3)+1;
}
int getUserChoice(){
    int choice = 0;
    do{
        printf("\nChoose and option:");
        printf("\n 1. Rock");
        printf("\n 2. Paper");
        printf("\n 3. Scissors");
        printf("\n Enter your choice 1-3: ");
        scanf("%d", &choice);

    }while(choice < 1 || choice > 3);

    return choice;
}
void checkWinner(int userChoice, int computerChoice){
    if(userChoice == computerChoice){
            printf("It's a Tie!\n");

            fpt = fopen("logs/rps.csv", "a");
            fprintf(fpt, "\nIt's a tie!");
            fprintf(fpt, ",%d", userChoice);
            fprintf(fpt, ",%d", computerChoice);
            fclose(fpt);

            }
            else if (userChoice == 1 && computerChoice == 3){
                printf("You Win!\n");

            fpt = fopen("logs/rps.csv", "a");
            fprintf(fpt, "\nYou Win!");
            fprintf(fpt, ",%d", userChoice);
            fprintf(fpt, ",%d", computerChoice);
            fclose(fpt);

            }
            else if (userChoice == 2 && computerChoice == 1){
                printf("\nYou Win!\n");

            fpt = fopen("logs/rps.csv", "a");
            fprintf(fpt, "\nYou Win!");
            fprintf(fpt, ",%d", userChoice);
            fprintf(fpt, ",%d", computerChoice);
            fclose(fpt);

            }
            else if (userChoice == 3 && computerChoice == 2){
                printf("You Win!\n");

            fpt = fopen("logs/rps.csv", "a");
            fprintf(fpt, "\nYou Win!");
            fprintf(fpt, ",%d", userChoice);
            fprintf(fpt, ",%d", computerChoice);
            fclose(fpt);

            }
            else{
                printf("You Lose :( \n");

            fpt = fopen("logs/rps.csv", "a");
            fprintf(fpt, "\nYou Lose!");
            fprintf(fpt, ",%d", userChoice);
            fprintf(fpt, ",%d", computerChoice);
            fclose(fpt);

            }
}

int main(){                                             //this establishes the main function of the program, all subroutines will fall within the main brackets {}


time_t t ;                                                              //this sets up the time variables
    char MY_TIME[80];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);                                                     // Get current time
    info = localtime(&rawtime);                                         // Convert to local time
    strftime(MY_TIME, sizeof(MY_TIME), "%m%d%Y, %H:%M:%S", info);       //this sets the output format of the time and date
    printf("%s", MY_TIME);

  srand(time(NULL));


fpt = fopen("logs/rps.csv", "a");
    fprintf(fpt, "\nNew GAME!!,");
    fprintf(fpt, "%s", MY_TIME);
fclose(fpt);

startProgram:  //this is just a label for the goto function
printf("\n*** Rock Paper Scissors ***\n");

int userChoice = getUserChoice();
int computerChoice = getComputerChoice();

switch(userChoice){
    case 1:
        printf("\nYou chose Rock!\n");
        break;

    case 2:
        printf("\nYou chose Paper!\n");
        break;

    case 3:
        printf("\nYou chose Scissors!\n");
        break;
}

switch(computerChoice){
    case 1:
        printf("The Computer chose Rock!\n");
        break;

    case 2:
        printf("The Computer chose Paper!\n");
        break;

    case 3:
        printf("The Computer chose Scissors!\n");
        break;
}

checkWinner(userChoice, computerChoice);
playAgain:
printf("Play again? Y/N: ");
scanf(" %c", &yesNo);
if (yesNo == 'y' || yesNo == 'Y') {
    goto startProgram;
}
else if (yesNo == 'n' || yesNo == 'N'){
    fpt = fopen("logs/rps.csv", "a");
    fprintf(fpt, "\nEnd GAME!!,");
    fprintf(fpt, "%s", MY_TIME);
    fclose(fpt);
    return 0;
}
else{
    printf("Please enter another option\n");
    goto playAgain;
}
}//this indicates that the program completed with no errors


