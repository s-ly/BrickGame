#include "../../gui/cli/tetris.h"

action_fsm fsm_matrix[7][9] = {
    // Star Paus Termi Left  Right Up    Down  Acti  No_sig
    {SPaw, NULL, EXit, NULL, NULL, NULL, NULL, NULL, NULL},   // START
    {NULL, NULL, EXit, NULL, NULL, NULL, NULL, NULL, SPaw},   // SPAWN
    {NULL, PAus, EXit, LEft, RIgh, NULL, DOwn, ROta, CTim},   // MOV
    {NULL, NULL, EXit, NULL, NULL, NULL, NULL, NULL, Shif},   // SHIFTING
    {NULL, PAus, EXit, ATta, ATta, ATta, ATta, ATta, ATta},   // ATTACH
    {NULL, PAus, EXit, NULL, NULL, NULL, NULL, NULL, DOwn},   // DOWN_SHIFT
    {ReSt, NULL, EXit, NULL, NULL, NULL, NULL, NULL, NULL}};  // GAME_OWER

void SPaw(GameInfo_t *GameInfo) {
  init_Figure(GameInfo);
  int collision = downCollisionFigure(GameInfo);
  if (collision == 1) {
    GameInfo->state = ATTACHING;
    strcpy(GameInfo->message, "Playing");
  } else {
    GameInfo->timer.time_start = clock();
    GameInfo->state = MOVING;
    strcpy(GameInfo->message, "Playing");
    GameInfo->draw = 1;
  }
};

void ReSt(GameInfo_t *GameInfo) {
  rest_GameInfo(GameInfo);
  SPaw(GameInfo);
};

void PAus(GameInfo_t *GameInfo) {
  if (GameInfo->pause == 0) {
    GameInfo->pause = 1;
    strcpy(GameInfo->message, "Pause");
    GameInfo->timer.time_start = clock();
    GameInfo->draw = 1;
  } else
    GameInfo->pause = 0;
};

void EXit(GameInfo_t *GameInfo) { GameInfo->game_true = 0; };

void LEft(GameInfo_t *GameInfo) {
  if (!leftCollisionFigure(GameInfo) && !GameInfo->pause) {
    (GameInfo->current_figure[4][1])--;
    GameInfo->draw = 1;
  }
};

void RIgh(GameInfo_t *GameInfo) {
  if (!rightCollisionFigure(GameInfo) && !GameInfo->pause) {
    (GameInfo->current_figure[4][1])++;
    GameInfo->draw = 1;
  }
};

void DOwn(GameInfo_t *GameInfo) {
  int first_down = 0;
  if (!GameInfo->pause) {
    if (GameInfo->state == MOVING) {
      GameInfo->state = DOWN_SHIFT;
      strcpy(GameInfo->message, "Playing");
      first_down = 1;  // первое нажатие вниз (надо сразу падать)
    }

    int collision = downCollisionFigure(GameInfo);

    if (collision == 0) {
      if (first_down) {
        (GameInfo->current_figure[4][0])++;
        GameInfo->shift = 1;
        GameInfo->draw = 1;
      }

      int time_out = checkTimerShifting(GameInfo, TIMER_TIC_DOWN);
      if (time_out) {
        (GameInfo->current_figure[4][0])++;
        GameInfo->draw = 1;
      }
    } else {
      GameInfo->state = ATTACHING;
      strcpy(GameInfo->message, "Playing");
    }
  }
};

void ROta(GameInfo_t *GameInfo) {
  if (!GameInfo->pause) {
    rotFigure(GameInfo);
    GameInfo->draw = 1;
  }
};

void CTim(GameInfo_t *GameInfo) {
  int time_out;
  time_out = checkTimerShifting(GameInfo, GameInfo->speed);
  if (time_out == 1 && !GameInfo->pause) {
    strcpy(GameInfo->message, "Playing!");
    GameInfo->state = SHIFTING;
  }
};

void ATta(GameInfo_t *GameInfo) {
  int flag = 1;
  int line_sum = 0;
  int first_shift = GameInfo->shift;
  saveFigureField(GameInfo);

  while (flag) {
    int line_full = check_lines(GameInfo);
    if (line_full) {
      del_line(GameInfo, line_full);
      shift_down(GameInfo, line_full);
      line_sum++;
    } else {
      flag = 0;
    }
  }
  if (line_sum) {
    addScore(GameInfo, line_sum);
    checkRecord(GameInfo);
    checkLevel(GameInfo);
  }

  if (line_sum == 0 && first_shift == 0) {
    GameInfo->state = GAME_OWER;
    strcpy(GameInfo->message, "Game Over");
    GameInfo->draw = 1;
  } else {
    GameInfo->state = SPAWN;
    strcpy(GameInfo->message, "Playing");
    GameInfo->draw = 1;
  }
};

void Shif(GameInfo_t *GameInfo) {
  int collision = downCollisionFigure(GameInfo);

  if (collision == 1) {
    GameInfo->state = ATTACHING;
    strcpy(GameInfo->message, "Playing");
  } else {
    (GameInfo->current_figure[4][0])++;
    GameInfo->shift = 1;  //  фигура упала
    GameInfo->draw = 1;
    GameInfo->state = MOVING;
    strcpy(GameInfo->message, "Playing");
  }
};

void userInput(UserAction_t action, bool hold) {
  action_fsm act;
  GameInfo_t *GameInfo = getInstance_GameInfo();
  state state = GameInfo->state;

  act = fsm_matrix[state][action];
  if (act && hold) {
    act(GameInfo);
  }
}

UserAction_t get_signal(int user_input) {
  UserAction_t user_act = No_signal;

  if (user_input == 10)
    user_act = Start;
  else if (user_input == 'p' || user_input == 'P')
    user_act = Pause;
  else if (user_input == 27)
    user_act = Terminate;
  else if (user_input == KEY_LEFT)
    user_act = Left;
  else if (user_input == KEY_RIGHT)
    user_act = Right;
  else if (user_input == KEY_UP)
    user_act = Up;
  else if (user_input == KEY_DOWN)
    user_act = Down;
  else if (user_input == ' ')
    user_act = Action;

  return user_act;
}