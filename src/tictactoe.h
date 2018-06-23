#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <glib.h>

typedef enum
{
	None = 0,
	TL = 1,  TC = 2,  TR = 4,
	ML = 8,  MC = 16, MR = 32,
	BL = 64, BC =128, BR = 256,
	TopRow = TL | TC | TR,
	MiddleRow = ML | MC | MR,
	BottomRow = BL | BC | BR,
	LeftColumn = TL | ML | BL,
	CenterColumn = TC | MC | BC,
	RightColumn = TR | MR | BR,
	Diagonal1 = TL | MC | BR,
	Diagonal2 = TR | MC | BL,
	All = TopRow | MiddleRow | BottomRow
} GridCells;

typedef struct {
	GridCells Current;
	GridCells Opponent;
	gboolean CurrentIsO;
} Grid;

typedef struct {
	int count;
	GridCells items[9];
} EnumerableGridCells;

extern Grid      ttt_new_grid            (GridCells current, GridCells opponent, gboolean isO);
extern Grid      ttt_new_grid_empty      (void);
extern gboolean  ttt_check               (GridCells state, GridCells target);
extern gboolean  ttt_can_move            (const Grid *this, GridCells target);
extern gboolean  ttt_make_move           (Grid *this, GridCells target);
extern gboolean  ttt_check_win           (GridCells target);
extern gboolean  ttt_current_is_loser    (const Grid *this);
extern gboolean  ttt_is_draw             (const Grid *this);
extern gboolean  ttt_is_finished         (const Grid *this);

extern Grid      ttt_make_move_new_grid  (Grid *this, GridCells target);
extern EnumerableGridCells ttt_get_moves (const Grid *this);

#endif