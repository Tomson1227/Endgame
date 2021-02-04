#include "main.h"

const char menue_items[5][10] = {
    "Play", 
    "Mode",
    "Rules", 
    "Settings",
    "Exit"
};

WINDOW *create_menu(void) {
    WINDOW *win = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);
    
    int x_max = 0;
    int y_max = 0;
    

    keypad(win, true);
    getmaxyx(win, y_max, x_max);
    wattron(win, COLOR_PAIR(3));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(3));

    print_menu(win, x_max, y_max);
    mvwprintw(win,  1, 3, "Count: ");
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 1, 10, "%d", game->score);
    wattroff(win, COLOR_PAIR(3));
    mvwprintw(win, 2, 3, "Time: ");
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 2, 10, "%ld", end - start);

    return win;
}

void print_menu(WINDOW *win, int x_max, int y_max) {
    int i;
    wattron(win, COLOR_PAIR(2));
    wattron(win, A_BOLD);
    for(i = 0; i < 5; ++i)
        mvwaddstr(win, (y_max / 2) - 2 + i, (x_max / 2) - 3, menue_items[i]);
    wattroff(win, COLOR_PAIR(2));
    wattroff(win, A_BOLD);
    wrefresh(win);
}

void select_item_menue(WINDOW *win, int choice, int x_max, int y_max) {
    int x_coord = (x_max / 2) - 4;
    int y_coord = (y_max / 2) - 2;
    for (int i = 0; i < 5; ++i) {
        if (i == choice) {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, y_coord + i, x_coord, ">");
            wattroff(win, COLOR_PAIR(1));
        }
        else      
            mvwprintw(win, y_coord + i, x_coord, " ");
    }
    wrefresh(win);
}

int get_selected_item(WINDOW *win) {
    int choice = 0;
    bool is_true = true;
    int pressed_key;
    int x_max = 0;
    int y_max = 0;
    getmaxyx(win, y_max, x_max);
    while (is_true) {
        select_item_menue(win, choice, x_max, y_max);
        pressed_key = wgetch(win);
        handle_choice(pressed_key, &choice, &is_true);
    }
    return choice;
}

void handle_choice(int key, int *choice, bool *is_true) {
    switch (key) {
        case KEY_UP:
            if (*choice)
                *choice -= 1;  
            else
                *choice = 4;
            break;

        case KEY_DOWN:
            if (*choice != 4)
                *choice += 1;
            else
                *choice = 0;
            break;

        case ' ':
            *is_true = false;
            break;

        default : 
            break;   
    }
}

WINDOW *create_rules_screen(int max_y, int max_x)
{
    char *title = "GAME RULES";
    char *main_text = "\tThe rules are simple)\n\n"
    "\tYou need to fill up the symbols/words that appear on the\n"
    "\tscreen until it ruins the wall. With time the speed will\n"
    "\tslowly increase.\n\n"
    "\tLIVES\n"
    "\tYou have three lives if the box reaches the end of the line\n"
    "\tyou lose one. So be attentive and try to avoid it. If you\n"
    "\tlose all your lives the GAME OVER and you get your score.\n\n"
    "\tSCORE\n"
    "\tThe main idea is to get as greater a score as you can. For\n"
    "\teach correct symbol, you get points. If you fill in all sets\n"
    "\tof symbols the point for it doubles. The number of points\n"
    "\tyou get depends on the game mode and time of the session.\n\n"
    "\tTIME\n"
    "\tTime is one of the vital parameters of the game. The longer\n"
    "\tgame continues, the greater speed of text and the greater\n"
    "\tscore you can achieve. So keep it in mind.\n\n\n\n"
    "\t For quit press ESC\n";
    WINDOW *menu_window = newwin(max_y - 2, max_x - 2, 0, 1);
    box(menu_window, 0, 0);
    mvwaddstr(menu_window, 2, (max_x - strlen(title)) / 2, title);
    mvwaddstr(menu_window, 4, 0, main_text);
    wrefresh(menu_window);
    return menu_window;
}

int exit_rules_code(WINDOW *win) {
    while(wgetch(win) != 27);
    wclear(win);
    return -1;
}

