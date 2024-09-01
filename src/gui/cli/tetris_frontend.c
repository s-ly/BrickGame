#include "tetris.h"

void draw_Field(WINDOW *game_win, GameInfo_t *GameInfo) {
  wclear(game_win);
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (GameInfo->field[i][j] == 0) {
        mvwprintw(game_win, i, j, ".");
      } else {
        mvwprintw(game_win, i, j, "#");
      }
    }
  }
  wrefresh(game_win);
}

void drawRecord(WINDOW *game_win, GameInfo_t *GameInfo) {
  mvwprintw(game_win, 7, 12, "record:");
  if (GameInfo->high_score >= 0) {
    mvwprintw(game_win, 8, 12, "%d", GameInfo->high_score);
  } else {
    mvwprintw(game_win, 8, 12, "---");
  }
  wrefresh(game_win);
}

void drawLevel(WINDOW *game_win, GameInfo_t *GameInfo) {
  mvwprintw(game_win, 10, 12, "level:");
  mvwprintw(game_win, 11, 12, "%d", GameInfo->level);
  wrefresh(game_win);
}

void drawScore(WINDOW *game_win, GameInfo_t *GameInfo) {
  int score = GameInfo->score;
  mvwprintw(game_win, 4, 12, "score:");
  mvwprintw(game_win, 5, 12, "%d", score);
}

void drawMessage(WINDOW *game_win, GameInfo_t *GameInfo) {
  mvwprintw(game_win, 19, 12, "%s", GameInfo->message);
  wrefresh(game_win);
}

void draw_Figure(WINDOW *game_win, GameInfo_t *GameInfo) {
  // опортая точка
  int loc_y = GameInfo->current_figure[4][0];
  int loc_x = GameInfo->current_figure[4][1];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (GameInfo->current_figure[i][j] == 1) {
        mvwprintw(game_win, i + loc_y, j + loc_x, "#");
      }
    }
  }
  wrefresh(game_win);
}

void drawNextFigure(WINDOW *game_win, GameInfo_t *GameInfo) {
  if (GameInfo->state == START) return;

  int loc_y = 1;
  int loc_x = 12;

  mvwprintw(game_win, 0, 12, "next figure:");

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (GameInfo->next[i][j] == 1) {
        mvwprintw(game_win, i + loc_y, j + loc_x, "#");
      }
    }
  }
  wrefresh(game_win);
}

void draw(WINDOW *game_win, GameInfo_t *GameInfo) {
  draw_Field(game_win, GameInfo);
  draw_Figure(game_win, GameInfo);
  drawNextFigure(game_win, GameInfo);
  drawScore(game_win, GameInfo);
  drawRecord(game_win, GameInfo);
  drawLevel(game_win, GameInfo);
  drawMessage(game_win, GameInfo);
}

void gameStart(WINDOW *game_win, GameInfo_t *GameInfo) {
  draw_Field(game_win, GameInfo);
  mvwprintw(game_win, 19, 12, "%s", GameInfo->message);
  wrefresh(game_win);
}