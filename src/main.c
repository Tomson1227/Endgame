#include "main.h"

//Garbage
t_game *game;
time_t start, end;
const char game_over1[] = "¯\\_(ツ)_/¯";
const char game_over2[] = "GAME OVER";
const char heart[] = "♡";
int delay_for_halfdelay = 1;


int main() {
    WINDOW *custom_win;
    init_game();
    init_ncurses();
    srand(time(NULL)); 
    // int pressed_key;
    custom_win = create_menu();
    int selected_screen = get_selected_item(custom_win);
    bool exit = false;

    while (!exit) {
        switch (selected_screen) {
            case Play:
                destroy_win(custom_win);
                custom_win = create_play_win();
                play_screen(custom_win);
                selected_screen = Menu;
                break;
            case Menu:
                clear();
                refresh();
                destroy_win(custom_win);
                custom_win = create_menu();
                selected_screen = get_selected_item(custom_win);
                break;
            case Rules:
                destroy_win(custom_win);
                custom_win = create_rules_screen(LINES, COLS);
                selected_screen = exit_rules_code(custom_win);
                break;
            case Exit:
                exit = true;
                break;
            default:
                selected_screen = Menu;
        }
    }
    endwin();
    return 0;
}

void init_game(void) {
    game = (t_game*) malloc(sizeof(t_game));
    game->lives = 3;
    game->score = 0;
    game->time = 0;
}

void init_ncurses(void) {
    setlocale(LC_CTYPE, "");
    initscr();
    start_color();
    init_pair(1,  COLOR_RED,     COLOR_BLACK); 
    init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
    init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4,  COLOR_WHITE,  COLOR_BLACK);
    init_pair(5,  COLOR_BLUE,  COLOR_BLACK);

    noecho();
    curs_set(FALSE); //Cursor off
}

void destroy_win(WINDOW *local_win) {	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
