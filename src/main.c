#include <gtk/gtk.h>
#include <sys/time.h>

#include "tictactoe.h"
#include "minimax.h"

const GridCells GRIDCELL_TL = TL;
const GridCells GRIDCELL_TC = TC;
const GridCells GRIDCELL_TR = TR;
const GridCells GRIDCELL_ML = ML;
const GridCells GRIDCELL_MC = MC;
const GridCells GRIDCELL_MR = MR;
const GridCells GRIDCELL_BL = BL;
const GridCells GRIDCELL_BC = BC;
const GridCells GRIDCELL_BR = BR;

GtkWidget *window;
GtkWidget *header_bar;
GtkWidget *btn_new_game;

GtkWidget *box;

GtkWidget *grid;
GtkWidget *btnTL, *btnTC, *btnTR,
          *btnML, *btnMC, *btnMR,
          *btnBL, *btnBC, *btnBR;

GtkWidget *lbl_status;

Grid grid_game;

const gchar*
get_cell (const Grid *grid, GridCells target)
{
	if ((grid->Current & target) != None)
		return (grid->CurrentIsO ? "ο" : "×");

	if ((grid->Opponent & target) != None)
		return (grid->CurrentIsO ? "×" : "ο");

	return "";
}

const gchar*
get_game_status (void)
{
	if (!ttt_is_finished (&grid_game))
		return grid_game.CurrentIsO ? "Current is O" : "Current is X";
	
	if (ttt_is_draw (&grid_game))
		return "Draw";

	if (grid_game.CurrentIsO && ttt_current_is_loser (&grid_game))
		return "X is Winner";
	if (!grid_game.CurrentIsO && ttt_current_is_loser (&grid_game))
		return "O is Winner";
}

double
elapsed_ms (clock_t start, clock_t end)
{
	return (double)(end - start) / (double)1000.0;
}

const gchar* 
get_gridcell (GridCells target)
{
	return target == TL ? "TL" :
		   target == TC ? "TC" :
		   target == TR ? "TR" :
		   target == ML ? "ML" :
		   target == MC ? "MC" :
		   target == MR ? "MR" :
		   target == BL ? "BL" :
		   target == BC ? "BC" :
		   target == BR ? "BR" :
		   "Invalid";
}

void
update_grid (void)
{
	GridCells bestMove = 0;

    clock_t start, end;
	start = clock();
	minimax (grid_game, &bestMove);
    end = clock();
	g_print("Best MiniMax: %s\n", get_gridcell (bestMove));
	g_print("time: %f\n", elapsed_ms (start, end));

	start = clock();
	alphabeta_minimax (grid_game, &bestMove);
    end = clock();
	g_print("Best AlphaBetaMinimax: %s\n", get_gridcell (bestMove));
	g_print("time: %f\n", elapsed_ms (start, end));
	
	gtk_button_set_label (GTK_BUTTON (btnTL), get_cell (&grid_game, TL));
	gtk_button_set_label (GTK_BUTTON (btnTC), get_cell (&grid_game, TC));
	gtk_button_set_label (GTK_BUTTON (btnTR), get_cell (&grid_game, TR));

	gtk_button_set_label (GTK_BUTTON (btnML), get_cell (&grid_game, ML));
	gtk_button_set_label (GTK_BUTTON (btnMC), get_cell (&grid_game, MC));
	gtk_button_set_label (GTK_BUTTON (btnMR), get_cell (&grid_game, MR));

	gtk_button_set_label (GTK_BUTTON (btnBL), get_cell (&grid_game, BL));
	gtk_button_set_label (GTK_BUTTON (btnBC), get_cell (&grid_game, BC));
	gtk_button_set_label (GTK_BUTTON (btnBR), get_cell (&grid_game, BR));

	gtk_label_set_text (GTK_LABEL (lbl_status), get_game_status ());
}


void
on_btn_new_game_clicked (void)
{
	grid_game = ttt_new_grid_empty (); 
	update_grid ();
}

void 
on_btn_gridcell_clicked (GtkWidget *widget, gpointer data)
{
	GridCells target = GPOINTER_TO_INT (data);

	if (ttt_make_move (&grid_game, target))
		update_grid ();
}

GtkWidget*
gtk_button_for_gridcell (GridCells gridcell)
{
	GtkWidget* result = gtk_button_new_with_label ("");
	gtk_widget_set_size_request (result, 100, 100);
	g_signal_connect (result, "clicked", G_CALLBACK (on_btn_gridcell_clicked), GINT_TO_POINTER (gridcell));

	return result;
}

void
initialize_widgets (void)
{
	// Main Window
	//
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 20);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

	// Header Bar
	//
	header_bar = gtk_header_bar_new ();
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header_bar), TRUE);

	// Button New Game
	//
	btn_new_game = gtk_button_new_with_label ("New Game");
	g_signal_connect (btn_new_game, "clicked", G_CALLBACK (on_btn_new_game_clicked), NULL);

	// Main Box
	//
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);

	// Status Label
	//
	lbl_status = gtk_label_new ("");

	// Grid
	//
	grid = gtk_grid_new ();
	gtk_widget_set_size_request (grid, 300, 350);

	// Grid Buttons
	//
	btnTL = gtk_button_for_gridcell (GRIDCELL_TL);       
	btnTC = gtk_button_for_gridcell (GRIDCELL_TC);    
	btnTR = gtk_button_for_gridcell (GRIDCELL_TR);

	btnML = gtk_button_for_gridcell (GRIDCELL_ML);
	btnMC = gtk_button_for_gridcell (GRIDCELL_MC);
	btnMR = gtk_button_for_gridcell (GRIDCELL_MR);

	btnBL = gtk_button_for_gridcell (GRIDCELL_BL);
	btnBC = gtk_button_for_gridcell (GRIDCELL_BC);
	btnBR = gtk_button_for_gridcell (GRIDCELL_BR);
}

void
pack_widgets_and_show (void)
{
	gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), GTK_WIDGET (btn_new_game));

	gtk_window_set_titlebar (GTK_WINDOW (window), header_bar);

	gtk_grid_attach (GTK_GRID (grid), btnTL, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), btnTC, 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), btnTR, 2, 0, 1, 1);

	gtk_grid_attach (GTK_GRID (grid), btnML, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), btnMC, 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), btnMR, 2, 1, 1, 1);

	gtk_grid_attach (GTK_GRID (grid), btnBL, 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), btnBC, 1, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), btnBR, 2, 2, 1, 1);

	gtk_container_add (GTK_CONTAINER (box), GTK_WIDGET (grid));
	gtk_container_add (GTK_CONTAINER (box), GTK_WIDGET (lbl_status));
	gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (box));

	gtk_widget_show_all (window);

	gtk_window_set_focus (GTK_WINDOW (window), GTK_WIDGET (btn_new_game));
}

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);

	initialize_widgets ();
	pack_widgets_and_show ();

	update_grid ();

	gtk_main ();

	return 0;
}