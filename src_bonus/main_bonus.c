#include "cub3d_bonus.h"

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
	initialise_bonuses(&img);
	run_game(&img);
}
