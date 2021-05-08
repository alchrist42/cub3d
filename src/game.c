#include "cub3d.h"

void	run_game(t_data *img)
{
	mlx_hook(img->win, 2, 1L<<0, press_button, img);
	mlx_hook(img->win, 3, 1L<<1, release_button, img);
	mlx_hook(img->win, 17, 1L<<0, close_win, img);
	mlx_loop_hook(img->mlx, main_game, img);
	mlx_loop(img->mlx);
}

int	main_game(t_data *img)
{

	change_position(img->params, img->plr, img->btn);
	draw_mmap(img->params, img);
	draw_player(img->params, img);
	draw_ray_of_sight(img->params,  img);
	
	
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}
