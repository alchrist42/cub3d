#include "cub3d.h"

void	run_game(t_data *img)
{
	mlx_hook(img->win, 2, 1L << 0, press_button, img);
	mlx_hook(img->win, 3, 1L << 1, release_button, img);
	mlx_hook(img->win, 17, 1L << 1, close_win, img);
	mlx_loop_hook(img->mlx, main_game, img);
	mlx_loop(img->mlx);
}

int	main_game(t_data *img)
{
	rotate_view(img->p, img->plr, img->btn);
	change_pos(img->p->map, img->plr, img->btn, img->v);
	draw_floor_and_cel(img->p, img);
	draw_walls(img->p, img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}
