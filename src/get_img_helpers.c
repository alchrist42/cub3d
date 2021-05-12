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

void	my_mlx_pixel_put(t_data *data, int row, int col, int color)
{
	char	*dst;

	dst = data->addr + (row * data->llen + col * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

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

int	prepare_frame(t_data *img)
{
	(void)img;
	return (0);
}

void	pe4em_vectora(t_data *img, t_param *p)
{


	int i;
	double	sin_step;
	double	cos_step;

	p->cnt_v = p->res_x * 5;
	if (p->cnt_v < 360)
		p->cnt_v = 360;
	
	sin_step = sin(M_PI * 2 / p->cnt_v);
	cos_step = cos(M_PI * 2 / p->cnt_v);

	img->v = malloc(sizeof(*img->v) * p->cnt_v * 1.21);
	i = 0;
	img->v[i].x = 1;
	img->v[i].y = 0;
	while (++i < p->cnt_v * 1.21)
	{
		img->v[i].x = img->v[i - 1].x;
		img->v[i].y = img->v[i - 1].y;
		rotate_by_ange(&img->v[i].x, &img->v[i].y, sin_step, cos_step);
		img->v[i].cx = 1;
		if (img->v[i].x < 0)
			img->v[i].cx = -1;
		img->v[i].cy = img->v[i].y / img->v[i].x * img->v[i].cx;
		img->v[i].ry = 1;
		if (img->v[i].y < 0)
			img->v[i].ry = -1;
		img->v[i].rx = img->v[i].x / img->v[i].y * img->v[i].ry;
	}
	printf("zapekli vectorov: %d, first: %f %f\n", i, img->v[1].x, img->v[1].y);
	i--;
	rotate_by_ange(&img->v[i].x, &img->v[i].y, sin_step, cos_step);
	printf("zapekli vectorov: %d, last: %f %f\n", p->cnt_v, img->v[i].x, img->v[i].y);


}