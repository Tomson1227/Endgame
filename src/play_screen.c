#include "main.h"

void play_screen(WINDOW *menu_window) 
{   
    int quit = 1;
    long first_time_point;
    char **array;
    array = readWordsFromFile("resource/text.txt");
    unsigned int lett = 0;
    t_word *pWord = NULL;
    
    pWord = (t_word*)malloc(sizeof(t_word));
    pWord->word = array[RAND(0, 200)];
    init_word(pWord, array[RAND(0,200)]); 
    time(&start);  /* start the timer */ 
    halfdelay(delay_for_halfdelay);
    init_game();

    while(quit) {
        first_time_point = currentTimeMillis();
        play_screen_print(menu_window);  
        print_str(menu_window, pWord, lett); 
        wrefresh(menu_window);

        if ((unsigned)COLS - 4 <= (pWord->length) + (pWord->xCord)) {
            create_new_str(pWord, menu_window, &lett, array);

            --(game->lives);
            pWord->color = 0x00000000;

            quite_condition(menu_window, &quit);
        }
        else {
            pWord->xCord += pWord->speed;
            pWord->speed = LINES/24 + (end - start)/ 60;
        }
        
        while(currentTimeMillis() - first_time_point < 200) {
            int temp = get_character(&quit, menu_window, pWord);

            if(lett == strlen(pWord->word)) {
                unsigned int right = count_right(pWord);
                
                if(right == strlen(pWord->word))
                    game->score += strlen(pWord->word);
                else if(right < strlen(pWord->word)/2)
                    --(game->lives);

                create_new_str(pWord, menu_window, &lett, array);
            }

            quite_condition(menu_window, &quit);

            if(temp == pWord->word[lett]) {
                pWord->color |= (0x00000001 << lett);
                ++(game->score);
                lett++;
            }
            else if(-1 == temp || ' ' == temp) {
                continue;
            }
            else {
                pWord->color |= (0x00000000 << lett);
                lett++;
            }
        }
        wclear(menu_window);
    }
}

int get_character(int *quit, WINDOW *win, t_word *pWord)
{
    extern time_t start;
    time_t pause_delay_begin = 0;
    time_t pause_delay_end = 0;
    int character = wgetch(win);

    switch (character) {
        case 27:
            *quit = 0;
            break;
        case ' ':
            time(&pause_delay_begin);
            clean_afret_str(win, pWord);
            mvwaddstr(win, LINES / 2, (COLS - strlen("PAUSE")) / 2, "PAUSE");
            mvwaddstr(win, LINES / 2 + 1, (COLS - strlen("Press SPASE to continue")) / 2, "Press SPASE to continue");
            wrefresh(win);
            while(getch() != ' ');
            time(&pause_delay_end);
            start += difftime(pause_delay_end, pause_delay_begin);
            break;
        default:
            break;
    }
    return character;
}

void clean_afret_str(WINDOW *win, t_word *pWord)
{
    for(unsigned int i = 0; i <= strlen(pWord->word); ++i) {
        mvwaddch(win, pWord->yCord, pWord->xCord + i - pWord->speed , ' ');
    }
}

void create_new_str(t_word *pWord, WINDOW *win, unsigned int *lett, char **str) {
    clean_afret_str(win, pWord);
    pWord->xCord = 2;
    pWord->word = str[RAND(0, 200)];
    pWord->color = 0x00000000;

    *lett = 0;
}

void print_str(WINDOW *win, t_word *pWord, int lett)
{
    unsigned int i = 0;
    for(; i < (unsigned) lett; ++i) {
        if(pWord->color & (0x00000001 << i)) {
            wattron(win, COLOR_PAIR(2));
            mvwaddch(win, pWord->yCord, pWord->xCord + i, pWord->word[i]);
            wattroff(win, COLOR_PAIR(2));
        }
        else {
            wattron(win, COLOR_PAIR(1));
            mvwaddch(win, pWord->yCord, pWord->xCord + i, pWord->word[i]);
            wattroff(win, COLOR_PAIR(1));
        }
    }
    for(; i < strlen(pWord->word); ++i) {
        mvwaddch(win, pWord->yCord, pWord->xCord + i, pWord->word[i]);
    }
    mvwprintw(win, pWord->yCord, pWord->xCord - 1, " ");
}

unsigned int count_right(t_word *pWord)
{
    int count = 0;
    for(unsigned int i = 0; i < strlen(pWord->word); ++i) {
        if(pWord->color & (0x00000001 << i))
            ++count;
    }
    return count;
}

void init_word(t_word *pWord, char *str)
{
    pWord->word = str; //gennstr(word, RAND(4,8)); 
    pWord->xCord = 2;
    pWord->yCord = LINES/2;
    pWord->interval = RAND(0, 4);
    pWord->speed = LINES/24;
    pWord->length = sizeof(pWord->word);
    pWord->color = 0x00000000;
}

WINDOW *create_play_win(void)
{
    WINDOW *menu_window = newwin(LINES, COLS - 2, 0, 1);
    return menu_window;
}

void play_screen_print(WINDOW *menu_window)
{
    time(&end);
    box(menu_window, 0, 0);
    mvwprintw(menu_window, 2, 3, "Count: ");
    wattron(menu_window, COLOR_PAIR(3));
    mvwprintw(menu_window, 2, 10, "%d", game->score);
    wattroff(menu_window, COLOR_PAIR(3));
    mvwprintw(menu_window, 2, 24, "Time: ");
    wattron(menu_window, COLOR_PAIR(2));
    mvwprintw(menu_window, 2, 30, "%ld", end -start);
    wattroff(menu_window, COLOR_PAIR(2));
    mvwprintw(menu_window, 2, COLS - 20, "Lives: ");

    for(int i = 0; i < game->lives; ++i) {
        wattron(menu_window, COLOR_PAIR(1));
        mvwprintw(menu_window, 2, COLS - 20 + strlen("Lives: ") + i*strlen(heart), heart);
        wattroff(menu_window, COLOR_PAIR(1));
    }

    for(int i = 1; i < 40; ++i) {
        mvwaddch(menu_window, 4, i, '_');
    }
    for(int i = COLS - 23; i < COLS - 3; ++i) {
        mvwaddch(menu_window, 4, i, '_');
    }
    for(int i = 1; i < 4; ++i) {
        mvwaddch(menu_window, i, 20, '|');
        mvwaddch(menu_window, i, 40, '|');
        mvwaddch(menu_window, i, COLS - 24, '|');
    }
}

void quite_condition(WINDOW *menu_window, int *quit)
{
    if (game->lives <= 0) {
        wclear(menu_window);
        mvwprintw(menu_window, LINES / 2, (COLS - strlen(game_over1)) / 2, game_over1);
        wrefresh(menu_window);
        sleep(1);
        mvwprintw(menu_window, LINES / 2, (COLS - strlen(game_over2)) / 2 - 1, game_over2);
        wrefresh(menu_window);
        sleep(2);
        *quit = 0;
    }
}
