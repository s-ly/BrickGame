#include "test.h"

START_TEST(test_checkLevel) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);

  GameInfo->score = 0;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 1);

  GameInfo->score = 800;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 2);

  GameInfo->score = 1500;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 3);

  GameInfo->score = 2000;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 4);

  GameInfo->score = 2800;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 5);

  GameInfo->score = 3300;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 6);

  GameInfo->score = 4000;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 7);

  GameInfo->score = 4500;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 8);

  GameInfo->score = 5000;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 9);

  GameInfo->score = 5500;
  checkLevel(GameInfo);
  ck_assert_int_eq(GameInfo->level, 10);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_addScore) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);

  GameInfo->score = 0;
  addScore(GameInfo, 1);
  ck_assert_int_eq(GameInfo->score, 100);

  GameInfo->score = 0;
  addScore(GameInfo, 2);
  ck_assert_int_eq(GameInfo->score, 300);

  GameInfo->score = 0;
  addScore(GameInfo, 3);
  ck_assert_int_eq(GameInfo->score, 700);

  GameInfo->score = 0;
  addScore(GameInfo, 4);
  ck_assert_int_eq(GameInfo->score, 1500);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_saveFigureField) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  saveFigureField(GameInfo);

  int flag = 0;
  for (int i = 0; i < FIELD_SIZE_Y && !flag; i++) {
    for (int j = 0; j < FIELD_SIZE_X && !flag; j++) {
      if (GameInfo->field[i][j] == 1) {
        flag = 1;
      }
    }
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_downCollisionFigure) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 19;  // y
  GameInfo->current_figure[4][1] = 1;   // x
  GameInfo->current_figure[4][2] = 0;   // поворот (горизонт)
  GameInfo->current_figure[4][3] = 0;   // тип LINE
  getFigureData(GameInfo, 1);
  flag = downCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 18;  // y
  GameInfo->current_figure[4][1] = 1;   // x
  GameInfo->current_figure[4][2] = 0;   // поворот
  GameInfo->current_figure[4][3] = 3;   // тип SQUARE
  getFigureData(GameInfo, 1);
  flag = downCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 17;  // y
  GameInfo->current_figure[4][1] = 1;   // x
  GameInfo->current_figure[4][2] = 1;  // поворот (вертикально)
  GameInfo->current_figure[4][3] = 6;  // тип PYRAMID
  getFigureData(GameInfo, 1);
  flag = downCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 16;  // y
  GameInfo->current_figure[4][1] = 1;   // x
  GameInfo->current_figure[4][2] = 1;  // поворот (вертикально)
  GameInfo->current_figure[4][3] = 0;  // тип LINE
  getFigureData(GameInfo, 1);
  flag = downCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 17;  // y
  GameInfo->current_figure[4][1] = 1;   // x
  GameInfo->current_figure[4][2] = 0;   // поворот
  GameInfo->current_figure[4][3] = 3;   // тип SQUARE
  getFigureData(GameInfo, 1);
  GameInfo->field[19][1] = 1;
  flag = downCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_leftCollisionFigure) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 1;  // y
  GameInfo->current_figure[4][1] = 0;  // x
  GameInfo->current_figure[4][3] = 3;  // тип SQUARE
  getFigureData(GameInfo, 1);
  flag = leftCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 1;  // y
  GameInfo->current_figure[4][1] = 1;  // x
  GameInfo->current_figure[4][3] = 3;  // тип SQUARE
  getFigureData(GameInfo, 1);
  GameInfo->field[1][0] = 1;
  flag = leftCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_rightCollisionFigure) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 1;  // y
  GameInfo->current_figure[4][1] = 8;  // x
  GameInfo->current_figure[4][3] = 3;  // тип SQUARE
  getFigureData(GameInfo, 1);
  flag = rightCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 1;  // y
  GameInfo->current_figure[4][1] = 7;  // x
  GameInfo->current_figure[4][3] = 3;  // тип SQUARE
  getFigureData(GameInfo, 1);
  GameInfo->field[1][9] = 1;
  flag = rightCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_rotCollisionFigure) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 0;   // y
  GameInfo->current_figure[4][1] = -2;  // x
  GameInfo->current_figure[4][2] = 1;  // поворот (вертикально)
  GameInfo->current_figure[4][3] = 6;  // тип PYRAMID
  getFigureData(GameInfo, 1);
  flag = rotCollisionFigure(GameInfo);
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_check_lines) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  int str = 15;

  for (int x = 0; x < FIELD_SIZE_X; x++) {
    GameInfo->field[str][x] = 1;
  }
  flag = check_lines(GameInfo);
  ck_assert_int_eq(flag, str);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_del_line) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  int str = 7;
  for (int x = 0; x < FIELD_SIZE_X; x++) {
    GameInfo->field[str][x] = 1;
  }
  del_line(GameInfo, str);
  if (GameInfo->field[str][0] == 0) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_shift_down) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  int str = 17;
  GameInfo->field[16][1] = 1;
  GameInfo->field[18][1] = 1;
  GameInfo->field[19][1] = 1;
  shift_down(GameInfo, str);
  if (GameInfo->field[str][1] == 1) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_rotFigure) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 1;  // y
  GameInfo->current_figure[4][1] = 1;  // x
  GameInfo->current_figure[4][2] = 0;  // поворот (горизонт)
  GameInfo->current_figure[4][3] = 6;  // тип PYRAMID
  getFigureData(GameInfo, 1);
  rotFigure(GameInfo);
  if (GameInfo->current_figure[2][1] == 1) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  if (GameInfo->current_figure[4][2] == 1) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  rotFigure(GameInfo);
  if (GameInfo->current_figure[4][2] == 2) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  rotFigure(GameInfo);
  if (GameInfo->current_figure[4][2] == 3) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  rotFigure(GameInfo);
  if (GameInfo->current_figure[4][2] == 0) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_checkRecord) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  //   init_Figure(GameInfo);
  int flag = 0;
  GameInfo->score = 25;
  GameInfo->high_score = 10;
  checkRecord(GameInfo);
  if (GameInfo->high_score == 25) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_checkTimerShifting) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = -1;
  int time = 90000000;
  GameInfo->timer.time_start = clock();
  flag = checkTimerShifting(GameInfo, time);
  ck_assert_int_eq(flag, 0);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_updateCurrentState) {
  GameInfo_t Info = updateCurrentState();
  ck_assert_ptr_nonnull(&Info);
}
END_TEST

START_TEST(test_getFigureData) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 0;  // тип f_LINE
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][0] == 1) &&
      (GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[0][2] == 1) &&
      (GameInfo->current_figure[0][3] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 1;  // тип f_CORNER_L
  GameInfo->current_figure[4][2] = 0;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][0] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 1;  // тип f_CORNER_L
  GameInfo->current_figure[4][2] = 1;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[0][2] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 1;  // тип f_CORNER_L
  GameInfo->current_figure[4][2] = 2;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1) &&
      (GameInfo->current_figure[2][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 1;  // тип f_CORNER_L
  GameInfo->current_figure[4][2] = 3;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][0] == 1) &&
      (GameInfo->current_figure[2][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 2;  // тип f_CORNER_R
  GameInfo->current_figure[4][2] = 0;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][2] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 2;  // тип f_CORNER_R
  GameInfo->current_figure[4][2] = 1;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][1] == 1) &&
      (GameInfo->current_figure[2][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 2;  // тип f_CORNER_R
  GameInfo->current_figure[4][2] = 2;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1) &&
      (GameInfo->current_figure[2][0] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 2;  // тип f_CORNER_R
  GameInfo->current_figure[4][2] = 3;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][0] == 1) &&
      (GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 3;  // тип f_SQUARE
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][0] == 1) &&
      (GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 4;  // тип f_LIGHTNING_L
  GameInfo->current_figure[4][2] = 0;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[0][2] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 4;  // тип f_LIGHTNING_L
  GameInfo->current_figure[4][2] = 1;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1) &&
      (GameInfo->current_figure[2][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 4;  // тип f_LIGHTNING_L
  GameInfo->current_figure[4][2] = 2;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1) &&
      (GameInfo->current_figure[2][0] == 1) &&
      (GameInfo->current_figure[2][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 4;  // тип f_LIGHTNING_L
  GameInfo->current_figure[4][2] = 3;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][0] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 5;  // тип f_LIGHTNING_R
  GameInfo->current_figure[4][2] = 0;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][0] == 1) &&
      (GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 5;  // тип f_LIGHTNING_R
  GameInfo->current_figure[4][2] = 1;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][2] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1) &&
      (GameInfo->current_figure[2][1] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 5;  // тип f_LIGHTNING_R
  GameInfo->current_figure[4][2] = 2;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][1] == 1) &&
      (GameInfo->current_figure[2][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 5;  // тип f_LIGHTNING_R
  GameInfo->current_figure[4][2] = 3;  // поворот
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[2][0] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  clear_figure(GameInfo);
  GameInfo->current_figure[4][3] = 6;  // тип f_PYRAMID
  getFigureData(GameInfo, 1);
  if ((GameInfo->current_figure[0][1] == 1) &&
      (GameInfo->current_figure[1][0] == 1) &&
      (GameInfo->current_figure[1][1] == 1) &&
      (GameInfo->current_figure[1][2] == 1)) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_SPaw) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  SPaw(GameInfo);
  if (GameInfo->state == MOVING) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_ReSt) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  ReSt(GameInfo);
  if (GameInfo->state == MOVING) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_PAus) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;

  GameInfo->pause = 0;
  PAus(GameInfo);
  if (GameInfo->pause == 1) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);

  flag = 0;
  GameInfo->pause = 1;
  PAus(GameInfo);
  if (GameInfo->pause == 0) {
    flag = 1;
  }
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_EXit) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  EXit(GameInfo);
  flag = (GameInfo->game_true == 0) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_LEft) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag, x_before, x_after = 0;
  x_before = GameInfo->current_figure[4][1];
  LEft(GameInfo);
  x_after = GameInfo->current_figure[4][1];
  flag = (x_before == x_after + 1) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_RIgh) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag, x_before, x_after = 0;
  x_before = GameInfo->current_figure[4][1];
  RIgh(GameInfo);
  x_after = GameInfo->current_figure[4][1];
  flag = (x_before == x_after - 1) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_DOwn) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag, y_before, y_after = 0;
  y_before = GameInfo->current_figure[4][0];
  DOwn(GameInfo);
  y_after = GameInfo->current_figure[4][0];
  flag = (y_before == y_after - 1) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_ROta) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag, rot_before, rot_after = 0;

  rot_before = GameInfo->current_figure[4][2];
  ROta(GameInfo);
  rot_after = GameInfo->current_figure[4][2];
  flag = (rot_before != rot_after) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_CTim) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag = 0;
  GameInfo->state = MOVING;
  GameInfo->speed = 1;
  CTim(GameInfo);
  flag = (GameInfo->state == SHIFTING) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_ATta) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag = 0;

  clear_figure(GameInfo);
  GameInfo->current_figure[4][0] = 18;  // y
  GameInfo->current_figure[4][1] = 0;   // x
  GameInfo->current_figure[4][2] = 0;   // поворот (горизонт)
  GameInfo->current_figure[4][3] = 3;   // тип f_SQUARE
  getFigureData(GameInfo, 1);

  // заполнил часть поля (для квадрата)
  for (int y = 18; y < FIELD_SIZE_Y; y++) {
    for (int x = 2; x < FIELD_SIZE_X; x++) {
      GameInfo->field[y][x] = 1;
    }
  }
  ATta(GameInfo);
  flag = ((GameInfo->score == 300) && (GameInfo->state == SPAWN)) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_Shif) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag, y_before, y_after = 0;
  y_before = GameInfo->current_figure[4][0];
  Shif(GameInfo);
  y_after = GameInfo->current_figure[4][0];
  flag = ((y_before == y_after - 1) && (GameInfo->state == MOVING)) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_userInput) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  init_Figure(GameInfo);
  int flag, x_before, x_after = 0;
  x_before = GameInfo->current_figure[4][1];
  userInput(Left, 1);
  x_after = GameInfo->current_figure[4][1];

  flag = (x_before == x_after + 1) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

START_TEST(test_get_signal) {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);
  int flag;
  UserAction_t user_act;

  user_act = No_signal;
  user_act = get_signal(10);
  flag = (user_act == Start) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal('p');
  flag = (user_act == Pause) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal(27);
  flag = (user_act == Terminate) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal(KEY_LEFT);
  flag = (user_act == Left) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal(KEY_RIGHT);
  flag = (user_act == Right) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal(KEY_UP);
  flag = (user_act == Up) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal(KEY_DOWN);
  flag = (user_act == Down) ? 1 : 0;
  ck_assert_int_eq(flag, 1);

  user_act = No_signal;
  user_act = get_signal(' ');
  flag = (user_act == Action) ? 1 : 0;
  ck_assert_int_eq(flag, 1);
  free_GameInfo(GameInfo);
}
END_TEST

Suite *tetris_tests(void) {
  Suite *s = suite_create("tetris");
  TCase *tc = tcase_create("tetris_tc");
  tcase_add_test(tc, test_checkLevel);
  tcase_add_test(tc, test_addScore);
  tcase_add_test(tc, test_saveFigureField);
  tcase_add_test(tc, test_downCollisionFigure);
  tcase_add_test(tc, test_leftCollisionFigure);
  tcase_add_test(tc, test_rightCollisionFigure);
  tcase_add_test(tc, test_rotCollisionFigure);
  tcase_add_test(tc, test_check_lines);
  tcase_add_test(tc, test_del_line);
  tcase_add_test(tc, test_shift_down);
  tcase_add_test(tc, test_rotFigure);
  tcase_add_test(tc, test_checkRecord);
  tcase_add_test(tc, test_checkTimerShifting);
  tcase_add_test(tc, test_updateCurrentState);
  tcase_add_test(tc, test_getFigureData);
  tcase_add_test(tc, test_SPaw);
  tcase_add_test(tc, test_ReSt);
  tcase_add_test(tc, test_PAus);
  tcase_add_test(tc, test_EXit);
  tcase_add_test(tc, test_LEft);
  tcase_add_test(tc, test_RIgh);
  tcase_add_test(tc, test_DOwn);
  tcase_add_test(tc, test_ROta);
  tcase_add_test(tc, test_CTim);
  tcase_add_test(tc, test_ATta);
  tcase_add_test(tc, test_Shif);
  tcase_add_test(tc, test_userInput);
  tcase_add_test(tc, test_get_signal);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int fail = 0;
  int flag = 0;
  Suite *sum_tests[] = {tetris_tests(), NULL};

  for (int i = 0; sum_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(sum_tests[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    fail += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  if (fail == 0) {
    flag = 0;
  } else {
    flag = 1;
    printf("FAILED: %d", fail);
  }
  return flag;
}

void clear_figure(GameInfo_t *GameInfo) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      GameInfo->current_figure[i][j] = 0;
    }
  }
}
