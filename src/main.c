#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_param		p;
	t_data		img;
	t_player	plr;
	t_button	btn;

	parcer(argc, argv, &p);
	inicialise_buttons(&btn);
	create_window(&img, &p, &btn);
	pe4em_vectora(&img, &p);
	initialise_player(&img, &p, &plr);
	run_game(&img);
}
