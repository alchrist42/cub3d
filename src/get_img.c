#include "cub3d.h"

void	draw_walls(t_param *p, t_data *img) 
{
	int		col;
	int		start_ind;
	
	col = 0;
	start_ind = img->plr->ind_v - p->res_x / 2;
	if (start_ind < 0)
		start_ind += p->cnt_v;
	while(col < p->res_x)
	{
		throw_ray(img, img->v[start_ind + col]);
		put_column(p, img, img->plr->sprite, col, img->v[ft_abs(p->res_x / 2 - col)].x);
		col++;
	}
}

void	draw_floor_and_cel(t_param *p, t_data *img)
{
	int	i;

	i = 0;
	while (i < p->res_y / 2)
		my_mlx_row_put(img, i++, p->cel);
	while (i < p->res_y)
		my_mlx_row_put(img, i++, p->floor);

}

void	put_column(t_param *p, t_data *img, t_sprite *spr, int col, float k)
{
	int		row;
	int		color;
	int		up;
	t_texture	*xpm;
	int row_sp;
	(void)row_sp;

	int i = img->plr->n_spr;
	while (i--)
	{
		// xpm = spr[i].xpm;
		// w = (spr[i].xpm->bpp / 8) * (int)(spr[i].xpm->w * (spr[i].diff));
		// up = p->res_y / 2 - spr[i].h / k / 2;
		// down = p->res_y / 2 + spr[i].h / k / 2;
		// row = ft_max(up, 0);
		
		// while (row < down && row < p->res_y)
		// {
		// 	color = (int *)(spr[i].xpm->addr + spr[i].xpm->llen * (int)((row - up) * spr[i].xpm->h / (down - up)) + w);
		// 	if (*color != 0x980088)
		// 		my_mlx_pixel_put(img, row, col, *color);
		// 	row++;
		// }
		// (void)row_sp;

		xpm = spr[i].xpm;
		
		spr[i].h /= k;
		up = (p->res_y - spr[i].h) / 2;
		
		row_sp = ft_max(0, (xpm->h - xpm->h * p->res_y / spr[i].h) / 2);
		row = up + row_sp * spr[i].h / xpm->h;
		while (row_sp < xpm->h)
		{
			if (row  > p->res_y)
				break;
			color = my_mlx_pixel_get(xpm, row_sp, spr[i].diff);
			while (row < p->res_y  && row < up + row_sp * spr[i].h / xpm->h)
			{
				if (color != 0x980088 && row >= 0)
					my_mlx_pixel_put(img, row, col, color);
				row++;
			}
			row_sp++;
		}
	}
}

// void	put_column(t_param *p, t_data *img, int col, int up, int down)
// {
// 	int		row;
// 	int		*color;
// 	int		w;
// 	t_texture	xpm;

// 	xpm = img->xpm[img->plr->texture_ind];
// 	w = (xpm.bpp / 8) * (int)(xpm.w * (img->plr->diff));
// 	row = 0;
// 	// while (row <= up && row < p->res_y)
// 	// 	my_mlx_pixel_put(img, row++, col, p->cel);
// 	row = ft_max(up, 0); 
// 	while (row < down && row < p->res_y)
// 	{
// 		color = (int *)(xpm.addr + xpm.llen * (int)((row - up) * xpm.h / (down - up)) + w);
// 		my_mlx_pixel_put(img, row++, col, *color);
// 	}
// 	// while (row < p->res_y)
// 	// 	my_mlx_pixel_put(img, row++, col, p->floor);
// }
