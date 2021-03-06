#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_param		p;
	t_data		img;
	t_player	plr;
	t_button	btn;

	parcer(argc, argv, &p);
	if (p.save)
		save_mode(&img, &p, &plr);
	inicialise_buttons(&btn);
	create_window(&img, &p, &btn);
	pe4em_vectora(&img, &p);
	initialise_player(&img, &p, &plr);
	run_game(&img);
}
