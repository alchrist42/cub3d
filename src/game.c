#include "cub3d.h"

void	run_game(t_data *img)
{
	mlx_hook(img->win, 2, 1L<<0, press_button, img);
	mlx_hook(img->win, 3, 1L<<1, release_button, img);
	mlx_hook(img->win, 17, 1L<<1, close_win, img);
	mlx_loop_hook(img->mlx, main_game, img);
	mlx_loop(img->mlx);
}


// void	test_texture(t_data *img)
// {
// 	// int w;
// 	// int pos;
// 	unsigned int color;


	
// 	for (int row = 0; row < 64; row++)
// 	{
// 		for (int col = 0; col < 64; col++)
// 		{
// 			color = *(unsigned int *)(img->t_no_addr + img->t_no_llen * row + col * (img->t_no_bpp / 8));
// 			my_mlx_pixel_put(img, row, col, color);
// 		}
// 	}
// }

int	main_game(t_data *img)
{
	img->img = mlx_new_image(img->mlx, img->param->res_x, img->param->res_y);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->llen, &img->end);

	rotate_view(img->param, img->plr, img->btn, img);
	change_pos(img->param, img->plr, img->btn, img->v);
	// draw_mmap(img->param, img);
	// draw_player(img->param, img);
	// draw_ray_of_sight(img->param,  img);
	get_img(img->param, img);
	// test_texture(img);
	
	
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}
