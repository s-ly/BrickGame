#ifndef S21_C7_BRICKGAME_V1_1_GUI_CLI_TETRIS_H_
#define S21_C7_BRICKGAME_V1_1_GUI_CLI_TETRIS_H_

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 10
#define TIMEOUT 1
#define TIMER_TIC 500000
#define TIMER_L01 500000
#define TIMER_L02 480000
#define TIMER_L03 460000
#define TIMER_L04 440000
#define TIMER_L05 420000
#define TIMER_L06 400000
#define TIMER_L07 380000
#define TIMER_L08 360000
#define TIMER_L09 340000
#define TIMER_L10 320000
#define TIMER_TIC_DOWN 25000

typedef struct {
  clock_t time_start;
  clock_t time_current;
} Time_t;

typedef enum {
  Start = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  No_signal
} UserAction_t;

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  DOWN_SHIFT,
  GAME_OWER
} state;

typedef struct {
  int **field;
  int **current_figure;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int game_true;
  Time_t timer;
  state state;
  char message[20];
  int shift;
  int draw;
} GameInfo_t;

typedef struct {
  int field_matrix[FIELD_SIZE_Y][FIELD_SIZE_X];
} field;

typedef void (*action_fsm)(GameInfo_t *GameInfo);

void SPaw(GameInfo_t *GameInfo);
void PAus(GameInfo_t *GameInfo);
void EXit(GameInfo_t *GameInfo);
void LEft(GameInfo_t *GameInfo);
void RIgh(GameInfo_t *GameInfo);
void DOwn(GameInfo_t *GameInfo);
void ROta(GameInfo_t *GameInfo);
void CTim(GameInfo_t *GameInfo);
void ATta(GameInfo_t *GameInfo);
void Shif(GameInfo_t *GameInfo);
void ReSt(GameInfo_t *GameInfo);

void init_GameInfo(GameInfo_t *GameInfo);
void init_Figure(GameInfo_t *GameInfo);
void gameLoop(WINDOW *game_win, GameInfo_t *GameInfo);

/**
 * Проверяет есть ли собранная строка в поле.
 * Если есть, возвращает номер строки, иначе 0.
 */
int check_lines(GameInfo_t *GameInfo);

/**
 * Удаляет собранную линию и матрицы поля.
 * @param field_buff Матрица поля
 * @param line Строка для удаления
 */
void del_line(GameInfo_t *GameInfo, int line);

/**
 * Сдвигает слетки вниз после удаления собранной строки.
 * @param field_buff Матрица поля
 * @param line  Удаленная строка
 */
void shift_down(GameInfo_t *GameInfo, int line);

void draw_Field(WINDOW *game_win, GameInfo_t *GameInfo);
void draw_Figure(WINDOW *game_win, GameInfo_t *GameInfo);
int downCollisionFigure(GameInfo_t *GameInfo);
void saveFigureField(GameInfo_t *GameInfo);

/**
 * Создает фигуру в матрице в зависимости от ее типа.
 * @param GameInfo главная структура игры.
 * @param figure_cur Какую фигуру нужно заполнить, 1 - текущую, 0 - следующую.
 */
void getFigureData(GameInfo_t *GameInfo, int figure_cur);

void rotFigure(GameInfo_t *GameInfo);
void copyFigureData(GameInfo_t *GameInfo);
void initNextFigure(GameInfo_t *GameInfo);
void drawNextFigure(WINDOW *game_win, GameInfo_t *GameInfo);
void drawScore(WINDOW *game_win, GameInfo_t *GameInfo);
int checkTimerShifting(GameInfo_t *GameInfo, int time);

UserAction_t get_signal(int user_input);
void userInput(UserAction_t action, bool hold);
int leftCollisionFigure(GameInfo_t *GameInfo);
int rightCollisionFigure(GameInfo_t *GameInfo);
void addScore(GameInfo_t *GameInfo, int line_sum);
void gameStart(WINDOW *game_win, GameInfo_t *GameInfo);
void rest_GameInfo(GameInfo_t *GameInfo);
void drawRecord(WINDOW *game_win, GameInfo_t *GameInfo);
void drawLevel(WINDOW *game_win, GameInfo_t *GameInfo);

void getRecordFile(GameInfo_t *GameInfo);
void setRecordFile(GameInfo_t *GameInfo);
void checkRecord(GameInfo_t *GameInfo);
void checkLevel(GameInfo_t *GameInfo);
int rotCollisionFigure(GameInfo_t *GameInfo);
GameInfo_t updateCurrentState();

/**
 * Создаёт статическую переенную (СнглТон).
 */
GameInfo_t *getInstance_GameInfo();
void draw(WINDOW *game_win, GameInfo_t *GameInfo);
void drawMessage(WINDOW *game_win, GameInfo_t *GameInfo);
void free_GameInfo(GameInfo_t *GameInfo);
#endif