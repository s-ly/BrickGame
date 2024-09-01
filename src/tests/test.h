#ifndef S21_C7_BRICKGAME_V1_1_TESTS_TEST_H_
#define S21_C7_BRICKGAME_V1_1_TESTS_TEST_H_
#include <check.h>

#include "../gui/cli/tetris.h"
Suite *tetris_tests(void);

void clear_figure(GameInfo_t *GameInfo);
#endif