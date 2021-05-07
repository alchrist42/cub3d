#include "cub3d.h"


void	run_loop_game(t_data *img)
{
	mlx_hook(img->win, 2, 1L<<0, press_button, img);
	mlx_hook(img->win, 3, 1L<<1, release_button, img);
	mlx_loop_hook(img->mlx, main_game, img);
	
	mlx_loop(img->mlx);


}

int	main_game(t_data *img)
{
	t_params	*p;

	p = img->params;
	
	change_position(img, p);
	draw_mmap(p, img);
	draw_player(p, img);
	return (0);
}

void	change_position(t_data *img, t_params *p)
{
	if (img->btn_w)
	{
		p->plr->x = 5;
		printf("player top top to up =)\n");
	}
}