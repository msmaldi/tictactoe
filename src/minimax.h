#ifndef MINIMAX_H
#define MINIMAX_H

#include "tictactoe.h"

extern int    minimax           (Grid g, GridCells *best);
extern int    alphabeta_minimax (Grid g, GridCells *best);

#endif