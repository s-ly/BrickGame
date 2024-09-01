#include "../../gui/cli/tetris.h"

void addScore(GameInfo_t *GameInfo, int line_sum) {
  int sum = 0;
  switch (line_sum) {
    case 1:
      sum = 100;
      break;
    case 2:
      sum = 300;
      break;
    case 3:
      sum = 700;
      break;
    case 4:
      sum = 1500;
      break;
  }
  GameInfo->score = GameInfo->score + sum;
}

void saveFigureField(GameInfo_t *GameInfo) {
  int pivot_y = GameInfo->current_figure[4][0];
  int pivot_x = GameInfo->current_figure[4][1];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (GameInfo->current_figure[i][j] == 1) {
        GameInfo->field[pivot_y + i][pivot_x + j] = 1;
      }
    }
  }
}

int downCollisionFigure(GameInfo_t *GameInfo) {
  int flag = 0;
  int loc_y = GameInfo->current_figure[4][0];
  int loc_x = GameInfo->current_figure[4][1];

  // проверка на "пол"
  for (int j = 0; j < 4; j++) {
    if (GameInfo->current_figure[3][j] == 1 && loc_y == 16) {
      flag = 1;
    } else if ((GameInfo->current_figure[2][j] == 1 && loc_y == 17)) {
      flag = 1;
    } else if ((GameInfo->current_figure[1][j] == 1 && loc_y == 18)) {
      flag = 1;
    } else if ((GameInfo->current_figure[0][j] == 1 && loc_y == 19)) {
      flag = 1;
    }
  }

  // проверка на точку
  for (int i = 0; i < 4 && !flag; i++) {
    for (int j = 0; j < 4 && !flag; j++) {
      if (GameInfo->current_figure[i][j]) {
        if (GameInfo->field[loc_y + i + 1][loc_x + j]) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

int leftCollisionFigure(GameInfo_t *GameInfo) {
  int flag = 0;
  int loc_y = GameInfo->current_figure[4][0];
  int loc_x = GameInfo->current_figure[4][1];

  // проверка на "стену слева"
  for (int i = 0; i < 4 && flag != 1; i++) {
    if ((GameInfo->current_figure[i][0] == 1 && loc_x == 0) ||
        (GameInfo->current_figure[i][1] == 1 && loc_x == -1) ||
        (GameInfo->current_figure[i][2] == 1 && loc_x == -2) ||
        (GameInfo->current_figure[i][3] == 1 && loc_x == -3)) {
      flag = 1;
    }
  }

  // проверка на точку
  for (int y = 0; y < 4 && !flag; y++) {
    for (int x = 0; x < 4 && !flag; x++) {
      if (GameInfo->current_figure[y][x]) {
        if (GameInfo->field[loc_y + y][loc_x + x - 1]) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

int rightCollisionFigure(GameInfo_t *GameInfo) {
  int flag = 0;
  int loc_y = GameInfo->current_figure[4][0];
  int loc_x = GameInfo->current_figure[4][1];

  // проверка на "стену справа"
  for (int i = 0; i < 4 && flag != 1; i++) {
    if ((GameInfo->current_figure[i][3] == 1 && loc_x == 6) ||
        (GameInfo->current_figure[i][2] == 1 && loc_x == 7) ||
        (GameInfo->current_figure[i][1] == 1 && loc_x == 8) ||
        (GameInfo->current_figure[i][0] == 1 && loc_x == 9)) {
      flag = 1;
    }
  }

  // проверка на точку
  for (int y = 0; y < 4 && !flag; y++) {
    for (int x = 0; x < 4 && !flag; x++) {
      if (GameInfo->current_figure[y][x]) {
        if (GameInfo->field[loc_y + y][loc_x + x + 1]) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

int rotCollisionFigure(GameInfo_t *GameInfo) {
  int flag = 0;
  int loc_y = GameInfo->current_figure[4][0];
  int loc_x = GameInfo->current_figure[4][1];

  for (int y = 0; y < 4 && flag != 1; y++) {
    for (int x = 0; x < 4 && flag != 1; x++) {
      if ((GameInfo->current_figure[y][x] && loc_x + x < 0) ||
          (GameInfo->current_figure[y][x] && loc_x + x > 9) ||
          (GameInfo->current_figure[y][x] && loc_y + y > 19) ||
          (GameInfo->current_figure[y][x] &&
           GameInfo->field[loc_y + y][loc_x + x])) {
        flag = 1;
      };
    }
  }
  return flag;
}

int check_lines(GameInfo_t *GameInfo) {
  int flag = 1;
  int line_full = 0;
  for (int i = 0; i < FIELD_SIZE_Y && flag; i++) {
    int cell_true_sum = 0;
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      cell_true_sum = cell_true_sum + GameInfo->field[i][j];
    }
    if (cell_true_sum == 10) {
      // все ячейки в строке заполненны
      flag = 0;
      line_full = i;
    }
  }
  return line_full;
}

void del_line(GameInfo_t *GameInfo, int line) {
  for (int j = 0; j < FIELD_SIZE_X; j++) {
    GameInfo->field[line][j] = 0;
  }
}

void shift_down(GameInfo_t *GameInfo, int line) {
  field temp_field_buff = {0};

  // спуск клеток вниз до очищенной строки
  // во временной матрице поля
  for (int i = 0; i < line; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (GameInfo->field[i][j]) {
        temp_field_buff.field_matrix[i + 1][j] = 1;
      }
    }
  }
  // копирование оставшихся ячеек
  // во временную матрицу поля
  for (int i = line + 1; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (GameInfo->field[i][j]) {
        temp_field_buff.field_matrix[i][j] = 1;
      }
    }
  }
  // Перенос данных из временной матрицы в основную
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      GameInfo->field[i][j] = temp_field_buff.field_matrix[i][j];
    }
  }
}

void init_Figure(GameInfo_t *GameInfo) {
  GameInfo->shift = 0;  // фигура еще не падала
  if (GameInfo->next[4][3] == -1) {
    initNextFigure(GameInfo);
  }
  copyFigureData(GameInfo);
  initNextFigure(GameInfo);
}

void initNextFigure(GameInfo_t *GameInfo) {
  int typeFigure = 0;
  typeFigure = rand() % 7;

  // обнуление
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      GameInfo->next[i][j] = 0;
    }
  }

  GameInfo->next[4][0] = 0;           // y
  GameInfo->next[4][1] = 4;           // x
  GameInfo->next[4][2] = 0;           // поворот
  GameInfo->next[4][3] = typeFigure;  // тип
  getFigureData(GameInfo, 0);
}

void copyFigureData(GameInfo_t *GameInfo) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      GameInfo->current_figure[i][j] = GameInfo->next[i][j];
    }
  }
}

void rotFigure(GameInfo_t *GameInfo) {
  int temp_figure_y = GameInfo->current_figure[4][0];
  int temp_figure_x = GameInfo->current_figure[4][1];
  int temp_figure_r = GameInfo->current_figure[4][2];
  int temp_figure_t = GameInfo->current_figure[4][3];

  int rotFigure = GameInfo->current_figure[4][2];
  if (rotFigure == 0) {
    rotFigure = 1;
  } else if (rotFigure == 1) {
    rotFigure = 2;
  } else if (rotFigure == 2) {
    rotFigure = 3;
  } else if (rotFigure == 3) {
    rotFigure = 0;
  }

  GameInfo->current_figure[4][2] = rotFigure;
  getFigureData(GameInfo, 1);

  if (rotCollisionFigure(GameInfo)) {
    // нельзя крутить
    GameInfo->current_figure[4][2] = temp_figure_r;
    getFigureData(GameInfo, 1);
  }
}

void init_GameInfo(GameInfo_t *GameInfo) {
  srand(time(NULL));
  // текущая фигура
  // матрица фигуры 5х4, 5я строка для дополнительных данных
  GameInfo->current_figure = malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    GameInfo->current_figure[i] = malloc(4 * sizeof(int));
    for (int j = 0; j < 4; j++) {
      GameInfo->current_figure[i][j] = 0;
    }
  }

  // следующая фигура
  // матрица фигуры 5х4, 5я строка для дополнительных данных
  GameInfo->next = malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++) {
    GameInfo->next[i] = malloc(4 * sizeof(int));
    for (int j = 0; j < 4; j++) {
      GameInfo->next[i][j] = 0;
    }
  }

  // матрица игрового поля 20х10
  GameInfo->field = malloc(FIELD_SIZE_Y * sizeof(int *));
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    GameInfo->field[i] = malloc(FIELD_SIZE_X * sizeof(int));
  }
  rest_GameInfo(GameInfo);
}

void rest_GameInfo(GameInfo_t *GameInfo) {
  // Сброс полля
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      GameInfo->field[i][j] = 0;
    }
  }

  GameInfo->game_true = 1;
  strcpy(GameInfo->message, "press Enter");
  GameInfo->draw = 0;
  GameInfo->next[4][3] = -1;  // нужна инициация next
  GameInfo->score = 0;
  GameInfo->pause = 0;
  GameInfo->level = 1;
  GameInfo->speed = TIMER_L01;
  getRecordFile(GameInfo);
}

int checkTimerShifting(GameInfo_t *GameInfo, int time) {
  int flag = 0;
  double t_current = clock();
  double t_start = GameInfo->timer.time_start;
  double t_diff = 0;
  t_diff = t_current - t_start;

  if (t_diff >= time) {
    GameInfo->timer.time_start = clock();
    flag = 1;
  }
  return flag;
}

void getRecordFile(GameInfo_t *GameInfo) {
  FILE *record = fopen("./record", "r");
  if (record != NULL) {
    fscanf(record, "%d", &GameInfo->high_score);
    fclose(record);
  } else {
    GameInfo->high_score = -1;
  }
}

void setRecordFile(GameInfo_t *GameInfo) {
  FILE *record = fopen("./record", "w");
  if (record != NULL) {
    fprintf(record, "%d", GameInfo->high_score);
    fclose(record);
  }
}

void checkRecord(GameInfo_t *GameInfo) {
  if (GameInfo->score > GameInfo->high_score) {
    GameInfo->high_score = GameInfo->score;
    setRecordFile(GameInfo);
  }
}

void checkLevel(GameInfo_t *GameInfo) {
  int level = GameInfo->level;
  int score = GameInfo->score;

  if (score < 600) {
    level = 1;
    GameInfo->speed = TIMER_L01;
  } else if (score >= 600 && score < 1200) {
    level = 2;
    GameInfo->speed = TIMER_L02;
  } else if (score >= 1200 && score < 1800) {
    level = 3;
    GameInfo->speed = TIMER_L03;
  } else if (score >= 1800 && score < 2400) {
    level = 4;
    GameInfo->speed = TIMER_L04;
  } else if (score >= 2400 && score < 3000) {
    level = 5;
    GameInfo->speed = TIMER_L05;
  } else if (score >= 3000 && score < 3600) {
    level = 6;
    GameInfo->speed = TIMER_L06;
  } else if (score >= 3600 && score < 4200) {
    level = 7;
    GameInfo->speed = TIMER_L07;
  } else if (score >= 4200 && score < 4800) {
    level = 8;
    GameInfo->speed = TIMER_L08;
  } else if (score >= 4800 && score < 5400) {
    level = 9;
    GameInfo->speed = TIMER_L09;
  } else if (score >= 5400) {
    level = 10;
    GameInfo->speed = TIMER_L10;
  }

  GameInfo->level = level;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *InfP = getInstance_GameInfo();
  GameInfo_t Info = *InfP;

  return Info;
}

GameInfo_t *getInstance_GameInfo() {
  static GameInfo_t GameInfo;
  return &GameInfo;
}

void free_GameInfo(GameInfo_t *GameInfo) {
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    free(GameInfo->field[i]);
  }
  free(GameInfo->field);

  for (int i = 0; i < 5; i++) {
    free(GameInfo->current_figure[i]);
  }
  free(GameInfo->current_figure);

  for (int i = 0; i < 5; i++) {
    free(GameInfo->next[i]);
  }
  free(GameInfo->next);
}
