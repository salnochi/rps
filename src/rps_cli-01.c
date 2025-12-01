#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

int main() {

        int xMax, yMax; int main_winY; int main_winX; int paneY; int paneX; int right_offset; int left_offset; int bottom_offset; int bottomR_offset; int userChoice;
        FILE *fpt;

//generate timestamp for log
    time_t t ;                                                          //this sets up the time variables
    char MY_TIME[80];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(MY_TIME, sizeof(MY_TIME), "%m%d%Y, %H:%M:%S", info);       //this sets the output format of the time and date
    printf("%s", MY_TIME);
    srand(time(NULL));

//log new game timestamp
    fpt = fopen("logs/rps.csv", "a");
        fprintf(fpt, "\nNew GAME!!,"); fprintf(fpt, "%s", MY_TIME);
    fclose(fpt);

//this is to restart the game but not log a new session
    startProgram:
//initialize the ncurses screen
        initscr();
        //noecho(); this hides the user input
        cbreak();
        keypad(stdscr, TRUE);

//get the main terminal window dimensions
        getmaxyx(stdscr, yMax, xMax);
        refresh();

//create the main window to the dimensions of the terminal window
        WINDOW *main_win; main_winY = yMax; main_winX = xMax; main_win = newwin(main_winY, main_winX, 0, 0); box(main_win, 0, 0);
        wrefresh(main_win);

//create the right_pane window
        WINDOW *right_pane; paneY = yMax - 5; paneX = xMax/2 - 2; right_offset = xMax/2;right_pane = newwin(paneY, paneX, 1, right_offset); box(right_pane, 0, 0);
        wrefresh(right_pane);

//create the left_pane window
        WINDOW *left_pane; paneY = yMax - 5; paneX = xMax/2 - 2; left_offset = 2; left_pane = newwin(paneY, paneX, 1, left_offset); box(left_pane, 0, 0);
        wrefresh(left_pane);

//create the bottom_pane window
        WINDOW *bottom_pane; bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
        wrefresh(bottom_pane);

//Main window title
    mvwprintw(main_win, 0, 4, "> ROCK, PAPER, SCISSORS!!! <");
    wrefresh(main_win);

//Right pane menu items
    mvwprintw(right_pane, 1, 2, "Rules:");
        mvwprintw(right_pane, 3, 2, "1. Rock Beats Scissors");
        mvwprintw(right_pane, 4, 2, "2. Paper Beats Rock");
        mvwprintw(right_pane, 5, 2, "3. Scissors Beats Paper");
        mvwprintw(right_pane, 7, 5, "Enter 1 for Rock");
        mvwprintw(right_pane, 8, 5, "Enter 2 for Paper");
        mvwprintw(right_pane, 9, 5, "Enter 3 for Scissors");
        mvwprintw(right_pane, 11, 2, "Have Fun!");
    wrefresh(right_pane);

//Bottom pane initial entry text
    mvwprintw(bottom_pane, 1, 2,"Enter your choice (1, 2, or 3): ");
    wrefresh(bottom_pane);

userChoice = wgetch(bottom_pane); //gets the user input
   if(userChoice == '1'){
                    mvwprintw(left_pane, 2, 2, "You selected Rock!");
}
    else if(userChoice == '2'){
                    mvwprintw(left_pane, 2, 2, "You selected Paper!");
}
    else if(userChoice == '3'){
                    mvwprintw(left_pane, 2, 2, "You selected Scissors!");
}

int compSelect = (rand() % 3) + 1; //randomly selects the computer's choice
   if (compSelect == 1){
                    mvwprintw(left_pane, 3, 2, "The Computer Chose Rock!");
}
    else if(compSelect == 2){
                    mvwprintw(left_pane, 3, 2, "The Computer Chose Paper!");
}
    else if(compSelect == 3){
                    mvwprintw(left_pane, 3, 2, "The Computer Chose Scissors!");
}

getch();

if (userChoice == '1' && compSelect == 1){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                    wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "It's a tie!");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nIt's a tie!"); fprintf(fpt, ",1"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);

            }
            else if (userChoice == '2' && compSelect == 2){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "It's a tie!");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nIt's a tie!"); fprintf(fpt, ",2"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);

            }
            else if (userChoice == '3' && compSelect == 3){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "It's a tie!");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nIt's a tie!"); fprintf(fpt, ",3"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);

            }
            else if (userChoice == '1' && compSelect == 3){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "You Win!");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nYou win!"); fprintf(fpt, ",1"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);

            }
            else if (userChoice == '2' && compSelect == 1){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "You Win!");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nYou win!"); fprintf(fpt, ",2"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);
            }
            else if (userChoice == '3' && compSelect == 2){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "You Win!");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nYou win!"); fprintf(fpt, ",3"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);
            }

            else if (userChoice == '3' && compSelect == 1){
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                mvwprintw(bottom_pane, 1, 2, "You lose :(");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nYou lose!"); fprintf(fpt, ",3"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);

            }
            else if (userChoice == '1' && compSelect == 2){
                    wclear(bottom_pane);
                        bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                    wrefresh(bottom_pane);
                    mvwprintw(bottom_pane, 1, 2, "You lose :(");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nYou lose!"); fprintf(fpt, ",1"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);
            }
            else if (userChoice == '2' && compSelect == 3){
                    wclear(bottom_pane);
                        bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                    wrefresh(bottom_pane);
                    mvwprintw(bottom_pane, 1, 2, "You lose (");

            fpt = fopen("logs/rps.csv", "a");
                fprintf(fpt, "\nYou lose!"); fprintf(fpt, ",2"); fprintf(fpt, ",%d", compSelect);
            fclose(fpt);

                wrefresh(bottom_pane);
                wrefresh(left_pane);
            }
            else{
                wclear(bottom_pane);
                    bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
                wrefresh(bottom_pane);
                wattron(bottom_pane, A_STANDOUT);
                mvwprintw(bottom_pane, 1, 2, "***Invalid Entry***");
                wattroff(bottom_pane, A_STANDOUT);
                wrefresh(bottom_pane); wrefresh(left_pane);
}

getch();

    wrefresh(main_win);
        wclear(bottom_pane);
            bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
        wrefresh(bottom_pane);
        mvwprintw(bottom_pane, 1, 2, "Play again? Y/N: ");
        wrefresh(bottom_pane);

playAgain:
int yesNo = wgetch(bottom_pane);
if (yesNo == 'y' || yesNo == 'Y') {
    goto startProgram;
}
else if (yesNo == 'n' || yesNo == 'N'){
    fpt = fopen("logs/rps.csv", "a");
        fprintf(fpt, "\nEnd GAME!!,"); fprintf(fpt, "%s", MY_TIME);
    fclose(fpt);

    endwin();
return 0;
}
else{
        wclear(bottom_pane);
            bottom_offset = yMax - 1 - 3; bottomR_offset = xMax -5; bottom_pane = newwin(3, bottomR_offset, bottom_offset, 2); box(bottom_pane, 0, 0);
        wrefresh(bottom_pane);
        mvwprintw(bottom_pane, 1, 2, "Please enter one of the options Y/N: ");
        wrefresh(bottom_pane);
        goto playAgain;
}
}
