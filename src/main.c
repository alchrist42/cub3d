#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_params	p;
	t_data		img;
	t_player	plr;
	t_buttons	btn;
	
	parcer(argc, argv, &p);
	create_window(&img, &p, &btn);
	initialise_player(&img, &p, &plr);
	run_game(&img);

}
