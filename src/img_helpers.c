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
		while (y*2 < p->res_x)
		{
			ch = p->map[x*3 * p->h_map / p->res_y][y*2 * p->w_map / p->res_x];
			if (ch == '1')
				my_mlx_pixel_put(img, y, x, 0x00AF80FF);
			// else if (char_in_str(ch, "NEWS"))
			// 	my_mlx_pixel_put(img, y, x, 0x0F009F00);
			else if (char_in_str(ch, "2"))
				my_mlx_pixel_put(img, y, x, 0x0F800000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void	draw_player(t_params *p, t_data *img)
{
	int	x = img->x * p->res_y / p->h_map * 3;
	int	y = img->y * p->res_x / p->w_map * 2;
	my_mlx_pixel_put(img, y, x, 0x007070FF);
	x = img->x * p->res_y / p->h_map * 3 + 1;
	y = img->y * p->res_x / p->w_map * 2 + 1;
	my_mlx_pixel_put(img, y, x, 0x007070FF);
	x = img->x * p->res_y / p->h_map * 3 + 1;
	y = img->y * p->res_x / p->w_map * 2;
	my_mlx_pixel_put(img, y, x, 0x007070FF);
	x = img->x * p->res_y / p->h_map * 3;
	y = img->y * p->res_x / p->w_map * 2 + 1;
	my_mlx_pixel_put(img, y, x, 0x007070FF);
	x = img->x * p->res_y / p->h_map * 3 + 1;
	y = img->y * p->res_x / p->w_map * 2 + 2;
	my_mlx_pixel_put(img, y, x, 0x007070FF);
}

int	prepare_frame(t_data *img)
{
	(void)img;
	return (0);
}