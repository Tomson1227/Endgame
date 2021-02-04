#ifndef MAIN_H
#define MAIN_H //#include "main.h"



//includes
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <time.h> // Time lib
#include <sys/time.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//defines
#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L
#define STDOUT 1
#define ERROR 2
#define ERROR1_1 "error\n"
#define BUF_SIZE 1


//define functions
#define RAND(min,max) (min + rand()%(max + 1 - min))


//structures
typedef struct s_word {
    unsigned int xCord;
    unsigned int yCord;
    int length;
    int speed;
    int interval;
    char *word;
    unsigned int color;
}t_word;

typedef struct s_game {
    int lives;
    int score;
    double time;
} t_game;

enum Screen {
    Play = 0, Rules = 2, Menu = -1, Exit = 4
};

//functions
WINDOW *create_menu(void);
WINDOW *create_play_win(void);
WINDOW *create_rules_screen(int max_y, int max_x); //Rules menu page
void init_ncurses(void);
void destroy_win(WINDOW *local_win);
int exit_rules_code(WINDOW *win);
long get_nanos(void); //Return time in nanoseconds
long currentTimeMillis(void); //Return time in miliseconds
void play_screen(WINDOW *menu_window);
void print_str(WINDOW *win, t_word *pWord, int lett); //Word painting
void init_word(t_word *pWord, char *str);
unsigned int count_right(t_word *pWord);
void play_screen_print(WINDOW *menu_window);

//mark functions
int get_character(int *quit, WINDOW *win, t_word *pWord);
int mx_strcmp(const char *s1, const char *s2);
int getRandomNumber(int min, int max);

//File functions
void file_close(int name);
int file_open(char *name);
char *mx_file_to_str(const char *filename);
void write_to_stream(int stream, char * massage);
char **readWordsFromFile(const char *filename);

//Usefull string functions
char *gennstr(int n);
int mx_strlen(const char *s);
char *mx_strnew(const int size);
char *mx_strdup(const char *str);
char *mx_strcat(char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
char *mx_strjoin(char const *s1, char const *s2);
int mx_strcmp(const char *s1, const char *s2);

//menue.c functions
void select_item_menue(WINDOW *win, int choice, int x_max, int y_max);
void print_menu(WINDOW *win, int x_max, int y_max);
void handle_choice(int key, int *choice, bool *is_true);
void switch_screen(int choice, int y_max, int x_max);
int get_selected_item(WINDOW *win);

//GAME functions
void init_game(void);
void quite_condition(WINDOW *menu_window, int *quit);
void create_new_str(t_word *pWord, WINDOW *win, unsigned int *lett, char **str);
void clean_afret_str(WINDOW *win, t_word *pWord);

//Variables
extern t_game *game;
extern const char game_over1[];
extern const char game_over2[];
extern const char heart[];
extern int delay_for_halfdelay;
extern char **arr;
extern time_t start, end;

#endif /* MAIN_H */
