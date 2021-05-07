#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_params	p;
	t_data		img;
	
	parcer(argc, argv, &p);
	create_window(&img, &p);
	run_loop_game(&img);


}