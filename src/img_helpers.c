#include "cub3d.h"

/*
**	@brief	Create a trgb object (encoding color)
**	
**	@param	t		transparency
**	@param	r		red
**	@param	g		green
**	@param	b		blue
**	@return	int		color in 0xTTRRGGBB format
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw_mmap(t_params *p, t_data	*img)
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
				my_mlx_pixel_put(img, y, x, 0x00AF80FF);
			// else if (char_in_str(ch, "NEWS"))
			// 	my_mlx_pixel_put(img, y, x, 0x0F009F00);
			else if (char_in_str(ch, "2"))
				my_mlx_pixel_put(img, y, x, 0x00008000);
			y++;
		}
		x++;
	}
	
}

void	draw_player(t_params *p, t_data *img)
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
			my_mlx_pixel_put(img, col + i, row + j, 0x00FF303F);
	}
}

void	draw_ray_of_sight(t_params *p, t_data *img)
{
	int i = 0;
	float	row;
	float	col;

	row = img->plr->y * p->res_y / (p->h_map * 3);
	col = img->plr->x * p->res_x / (p->w_map * 2);
	printf("row=%f, col=%f\n", row, col);
	while (i < 100 && col > 1 && col < p->res_x && row > 1 && row < p->res_y)
	{
		my_mlx_pixel_put(img, col, row, 0x00BB305F);
		col += img->plr->vx;
		row += img->plr->vy;
		
		i++;
	}
}

int	prepare_frame(t_data *img)
{
	(void)img;
	return (0);
}