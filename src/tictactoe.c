#include "tictactoe.h"

Grid
ttt_new_grid (GridCells current, GridCells opponent, gboolean isO)
{
	Grid result;
	result.Current = current;
	result.Opponent = opponent;
	result.CurrentIsO = isO;

	return result;
}

Grid
ttt_new_grid_empty ()
{
	Grid result;
	result.Current = None;
	result.Opponent = None;
	result.CurrentIsO = FALSE;

	return result;
}

inline gboolean 
inline_ttt_check (GridCells state, GridCells target)
{
	return (state & target) == target;
}

gboolean 
ttt_check (GridCells state, GridCells target)
{
	return (state & target) == target;
}

gboolean 
ttt_can_move (const Grid *this, GridCells target)
{
	if (ttt_check (this->Current, target))
		return FALSE;

	if (ttt_check (this->Opponent, target))
		return FALSE;

	return TRUE;
}

gboolean 
ttt_make_move (Grid *this, GridCells target)
{
	if (!ttt_is_finished (this) && ttt_can_move (this, target))
	{	
		*this = ttt_new_grid (this->Opponent, this->Current | target, !this->CurrentIsO);
		return TRUE;		
	}
	return FALSE;
}

Grid
ttt_make_move_new_grid (Grid *this, GridCells target)
{
	return ttt_new_grid (this->Opponent, this->Current | target, !this->CurrentIsO);
}


gboolean
ttt_check_win (GridCells target)
{
	if (ttt_check (target, TopRow))
		return TRUE;

	if (ttt_check (target, MiddleRow))
		return TRUE;

	if (ttt_check (target, BottomRow))
		return TRUE;

	if (ttt_check (target, LeftColumn))
		return TRUE;

	if (ttt_check (target, CenterColumn))
		return TRUE;

	if (ttt_check (target, RightColumn))
		return TRUE;

	if (ttt_check (target, Diagonal1))
		return TRUE;

	if (ttt_check (target, Diagonal2))
		return TRUE;

	return FALSE;
}

gboolean
ttt_current_is_loser (const Grid *this)
{
	return ttt_check_win (this->Opponent);
}

// this function never return true
//gboolean
//ttt_current_is_winner (const Grid *this)
//{
//	return ttt_check_win (this->Current);
//}

gboolean
ttt_is_draw (const Grid *this)
{
	if (!ttt_check (this->Opponent | this->Current, All))
		return FALSE;

	return !ttt_current_is_loser (this); //(!ttt_current_is_winner (this)) && (!ttt_current_is_loser (this));
}

gboolean
ttt_is_finished (const Grid *this)
{
	return ttt_is_draw (this) || ttt_current_is_loser (this); //|| ttt_current_is_winner (this)
}

EnumerableGridCells 
ttt_get_moves (const Grid *this)
{
	EnumerableGridCells result;
	result.count = 0;

	if (ttt_current_is_loser (this))
		return result;

	GridCells occupation = this->Current | this->Opponent;

	if (!ttt_check (occupation, MC))
	{
		result.items[result.count] = MC;
		result.count++;
	}

	if (!ttt_check (occupation, TL))
	{
		result.items[result.count] = TL;
		result.count++;
	}

	if (!ttt_check (occupation, TR))
	{
		result.items[result.count] = TR;
		result.count++;
	}
	
	if (!ttt_check (occupation, BL))
	{
		result.items[result.count] = BL;
		result.count++;
	}

	if (!ttt_check (occupation, BR))
	{
		result.items[result.count] = BR;
		result.count++;
	}
		
	if (!ttt_check (occupation, ML))
	{
		result.items[result.count] = ML;
		result.count++;
	}

	if (!ttt_check (occupation, MR))
	{
		result.items[result.count] = MR;
		result.count++;
	}

	if (!ttt_check (occupation, TC))
	{
		result.items[result.count] = TC;
		result.count++;
	}

	if (!ttt_check (occupation, BC))
	{
		result.items[result.count] = BC;
		result.count++;
	}

	return result;
}