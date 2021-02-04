#include "main.h"

void game_screen() {
    initscr();
    curs_set(0);
    
    //start_color();
    halfdelay(5);
    int x = 0 ,y = 10, max_x, max_y;
    int interval = 10, count = 0, count2 = 0;
    int i = 0;
    int score = 0;
    unsigned int lett = 0;
   
    
     init_pair(1, COLOR_GREEN, COLOR_BLACK);
    // init_pair(2, COLOR_RED, COLOR_BLACK);
    getmaxyx(stdscr ,max_y, max_x);

    while(true) {
        char *word = "slovo";
        
        while(x != max_x) {
            clear();
            
            if (y >= 10 && count < interval) {
                y++;
                count++;
            }
            else if (y <= 20 && count2 < interval) {
                y--;
                count2++;
            }
            if (count == interval && count2 == interval) {
                count = 0;
                count2 = 0; 
            }
            mvaddstr(y, x, word);
            if (getch() == word[lett]) {
                attron(COLOR_PAIR(1));
                mvaddch(30, 30, word[lett]);
                refresh();
                score++;
                lett++;
            }
            refresh();
            if (lett == 5) {
                endwin();
                return 0;
            }
            
            x++;
            i++;
            //usleep(100000);
            
        }
        
        // for ( ; j < 100; j++) {
        //     if (x == max_x) {
        //         x = 0;
        //         y++;
        //     }
        //     dictionary[j] = getRandomNumber(33, 127);
        //     mvaddch(y, x, dictionary[j]);
        //     x++;
        //     refresh();
        // }
        // x = 0;
        // y = 0;
        // for ( ; i < j; i++) {
        //     usleep(400000);
        //     int ch = getch();
            
        //     if (ch == dictionary[i]) {
        //         attron(COLOR_PAIR(1));
        //         mvaddch(y, x, dictionary[i]);
        //         score++;
        //         x++;
        //         continue;
        //     }
        //     else {
        //         attron(COLOR_PAIR(2));
        //         mvaddch(y, x, '>');
        //         x++;
        //         refresh();
        //     }
        // }
        // printw("%d",score);
        // refresh();
        // usleep(100000000);
        // endwin();
        // int randNum = getRandomNumber(0,2);

        // for (i = 0; i < max_x; i++) {
        //     usleep(10000);
        //     mvprintw(max_y / 2, x, dictionary[randNum]);
        //     refresh();
        //     x += 2;
        //     printw("\n");
        //     refresh();
            
        //     scanw("%s", userWord);
        //     clear();
        //     if (mx_strcmp(userWord, dictionary[randNum]) == 0) {
        //         endwin();
        //         return 0;
        //     }
        //     else {
        //         printw("Error");
        //         usleep(10000);
        //     }
        // }
    }
    endwin();
}
