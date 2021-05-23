#include "cub3d_bonus.h"

void	draw_mmap(t_param *p, t_data	*img)
{
	int x;
	int	y;
	char ch;

	x = 0;
	while (x*3 < p->res_y)
	{
		y = 0;
		while (y * 2 < p->res_x)
		{
			ch = p->map[x*3 * p->h_map / p->res_y][y * 2 * p->w_map / p->res_x];
			if (ch == '1')
				my_mlx_pixel_put(img, x, y, 0x004F204F);
			// else if (char_in_str(ch, "NEWS"))
			// 	my_mlx_pixel_put(img, y, x, 0x0F009F00);
			else if (char_in_str(ch, "2"))
				my_mlx_pixel_put(img, x, y, 0x00008000);
			else
				my_mlx_pixel_put(img, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	
}

void	draw_player(t_param *p, t_data *img)
{
	int	row;
	int	col;
	int	i;
	int j;
	int delta;

	delta = p->res_y / (p->h_map * 3 * 3);	
	row = img->plr->y * p->res_y / (p->h_map * 3);
	col = img->plr->x * p->res_x / (p->w_map * 2);
	i = -delta;
	while (++i < delta)
	{
		j = -delta;
		while (++j < delta)
			my_mlx_pixel_put(img, row + j, col + i, 0x00FF303F);
	}
}

void	draw_ray_of_sight(t_param *p, t_data *img)
{
	int i = 0;
	float	row;
	float	col;

	row = img->plr->y * p->res_y / (p->h_map * 3);
	col = img->plr->x * p->res_x / (p->w_map * 2);
	// printf("row=%f, col=%f\n", row, col);
	while (i < 100 && col > 1 && col < p->res_x && row > 1 && row < p->res_y)
	{
		my_mlx_pixel_put(img, row, col, 0x00BB305F);
		col += img->plr->vx;
		row += img->plr->vy;
		
		i++;
	}
}
