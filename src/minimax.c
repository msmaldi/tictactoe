#include "minimax.h"

int 
minimax (Grid g, GridCells *best)
{
	*best = None;
	int bestResult = -10;
	GridCells garbage;

	if (ttt_current_is_loser (&g))
		return -1;

	if (ttt_is_draw (&g))
		return 0;

	EnumerableGridCells moves = ttt_get_moves (&g);
	int i;
	for (i = 0; i < moves.count; i++)
	{
		int move = moves.items[i];

		Grid other = ttt_make_move_new_grid (&g, move);

		int result = -minimax (other, &garbage);
		
		if (result > bestResult)
		{
			*best = move;
            bestResult = result;
		}
	}
	return bestResult;
}

int 
alphabeta_minimax_depth (Grid g, GridCells *best, int alpha, int beta, int depth)
{
	*best = None;
	float bestResult = -10;
	GridCells garbage;

	if (ttt_current_is_loser (&g))
		return -10 + depth;
	
	if (ttt_is_draw (&g))
		return 0;


	EnumerableGridCells moves = ttt_get_moves (&g);
	int i;
	for (i = 0; i < moves.count; i++)
	{
		int move = moves.items[i];

		Grid other = ttt_make_move_new_grid (&g, move);
		alpha = -alphabeta_minimax_depth (other, &garbage, -beta, -alpha, depth + 1);

		if (beta <= alpha)
			return alpha;

		if (alpha > bestResult)
		{
			*best = move;
			bestResult = alpha;
		}
	}
	return bestResult;
}

int 
alphabeta_minimax (Grid g, GridCells *best)
{
    return alphabeta_minimax_depth (g, best, -10, +10, 1);
}