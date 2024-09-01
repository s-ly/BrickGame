#include "../../gui/cli/tetris.h"

void f_LINE(int **figure, int rotFigure);
void f_CORNER_L(int **figure, int rotFigure);
void f_CORNER_R(int **figure, int rotFigure);
void f_SQUARE(int **figure, int rotFigure);
void f_LIGHTNING_L(int **figure, int rotFigure);
void f_LIGHTNING_R(int **figure, int rotFigure);
void f_PYRAMID(int **figure, int rotFigure);

void getFigureData(GameInfo_t *GameInfo, int figure_cur) {
  int **figure;
  int typeFigure;
  int rotFigure;

  if (figure_cur) {
    figure = GameInfo->current_figure;
    typeFigure = GameInfo->current_figure[4][3];
    rotFigure = GameInfo->current_figure[4][2];
  } else {
    figure = GameInfo->next;
    typeFigure = GameInfo->next[4][3];
    rotFigure = GameInfo->next[4][2];
  }

  // обнуление формы
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure[i][j] = 0;
    }
  }

  switch (typeFigure) {
    case 0:
      f_LINE(figure, rotFigure);
      break;
    case 1:
      f_CORNER_L(figure, rotFigure);
      break;
    case 2:
      f_CORNER_R(figure, rotFigure);
      break;
    case 3:
      f_SQUARE(figure, rotFigure);
      break;
    case 4:
      f_LIGHTNING_L(figure, rotFigure);
      break;
    case 5:
      f_LIGHTNING_R(figure, rotFigure);
      break;
    case 6:
      f_PYRAMID(figure, rotFigure);
      break;
  }
}

void f_LINE(int **figure, int rotFigure) {
  if (rotFigure == 0 || rotFigure == 2) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[0][3] = 1;
  } else if (rotFigure == 1 || rotFigure == 3) {
    figure[0][2] = 1;
    figure[1][2] = 1;
    figure[2][2] = 1;
    figure[3][2] = 1;
  }
}

void f_CORNER_L(int **figure, int rotFigure) {
  if (rotFigure == 0) {
    figure[0][0] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (rotFigure == 1) {
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][1] = 1;
    figure[2][1] = 1;
  } else if (rotFigure == 2) {
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][2] = 1;
  } else if (rotFigure == 3) {
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[2][0] = 1;
    figure[2][1] = 1;
  }
}

void f_CORNER_R(int **figure, int rotFigure) {
  if (rotFigure == 0) {
    figure[0][2] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (rotFigure == 1) {
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[2][1] = 1;
    figure[2][2] = 1;
  } else if (rotFigure == 2) {
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][0] = 1;
  } else if (rotFigure == 3) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[2][1] = 1;
  }
}

void f_SQUARE(int **figure, int rotFigure) {
  figure[0][0] = 1;
  figure[0][1] = 1;
  figure[1][0] = 1;
  figure[1][1] = 1;
}

void f_LIGHTNING_L(int **figure, int rotFigure) {
  if (rotFigure == 0) {
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
  } else if (rotFigure == 1) {
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][2] = 1;
  } else if (rotFigure == 2) {
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][0] = 1;
    figure[2][1] = 1;
  } else if (rotFigure == 3) {
    figure[0][0] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[2][1] = 1;
  }
}

void f_LIGHTNING_R(int **figure, int rotFigure) {
  if (rotFigure == 0) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (rotFigure == 1) {
    figure[0][2] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][1] = 1;
  } else if (rotFigure == 2) {
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[2][1] = 1;
    figure[2][2] = 1;
  } else if (rotFigure == 3) {
    figure[0][1] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[2][0] = 1;
  }
}

void f_PYRAMID(int **figure, int rotFigure) {
  if (rotFigure == 0) {
    figure[0][1] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (rotFigure == 1) {
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][1] = 1;
  } else if (rotFigure == 2) {
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[2][1] = 1;
  } else if (rotFigure == 3) {
    figure[0][1] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[2][1] = 1;
  }
}