#include "cub3d_bonus.h"

void	draw_hp_bar(t_param *p, t_data	*img)
{
	int	row;
	int	col;
	int current_hp;

	current_hp = p->res_x * img->plr->hp / 400;
	col = p->res_x / 4 + 1;
	row = p->res_y * 0.96;
	while (row < p->res_y * 0.97 )
	{
		my_mlx_pixel_put(img, row, p->res_x / 2 + col, 0x60020000);
		my_mlx_pixel_put(img, row++, p->res_x / 2 - col, 0x60020000);
	}
	while (col--)
	{
		row = p->res_y * 0.96;
		my_mlx_pixel_put(img, row, p->res_x / 2 + col, 0x6002000);
		my_mlx_pixel_put(img, row, p->res_x / 2 - col, 0x6002000);
		while (col <= current_hp && row++ < p->res_y * 0.97 - 1)
		{
			my_mlx_pixel_put(img, row, p->res_x / 2 + col, 0x60053008);
			my_mlx_pixel_put(img, row, p->res_x / 2 - col, 0x60053008);
		}
		my_mlx_pixel_put(img, p->res_y * 0.97, p->res_x / 2 + col, 0x60002000);
		my_mlx_pixel_put(img, p->res_y * 0.97, p->res_x / 2 - col, 0x60002000);
	}
}