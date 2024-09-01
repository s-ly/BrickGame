#include "tetris.h"

int main() {
  GameInfo_t *GameInfo = getInstance_GameInfo();
  init_GameInfo(GameInfo);

  initscr();
  curs_set(0);
  cbreak();
  noecho();
  refresh();

  WINDOW *game_win = newwin(22, 32, 0, 0);
  keypad(game_win, true);
  nodelay(game_win, true);
  gameStart(game_win, GameInfo);
  gameLoop(game_win, GameInfo);
  wgetch(game_win);
  endwin();
  free_GameInfo(GameInfo);
  return 0;
}

void gameLoop(WINDOW *game_win, GameInfo_t *GameInfo) {
  while (GameInfo->game_true) {
    UserAction_t action = get_signal(wgetch(game_win));
    userInput(action, 1);
    if (GameInfo->draw) {
      GameInfo_t Info = updateCurrentState();
      draw(game_win, &Info);
      GameInfo->draw = 0;
    }
  }
}
