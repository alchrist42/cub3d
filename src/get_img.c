#include "cub3d.h"

void	draw_walls(t_param *p, t_data *img) 
{
	int		col;
	int		wall_h;
	int		start_ind;
	float	dst;
	
	col = 0;
	start_ind = img->plr->ind_v - p->res_x / 2;
	if (start_ind < 0)
		start_ind += p->cnt_v;
	while(col < p->res_x)
	{
		dst = get_dist_to_wall(img, img->v[start_ind + col]);
		// dst = log(start_ind);
		wall_h = p->res_x / 3 / dst / img->v[ft_abs(p->res_x / 2 - col)].x;
		// put_column(p, img, col, p->res_y / 2 - wall_h, p->res_y / 2 + wall_h);
		put_column2(p, img, img->plr->sprite, col, img->v[ft_abs(p->res_x / 2 - col)].x);
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

void	put_column2(t_param *p, t_data *img, t_sprite *spr, int col, float k)
{
	int		row;
	int		*color;
	int		w;
	int		up;
	int		down;
	t_texture	*xpm;

	int i = img->plr->n_spr;
	while (i--)
	{
		xpm = spr[i].xpm;
		w = (xpm->bpp / 8) * (int)(xpm->w * (spr[i].diff));
		up = p->res_y / 2 - spr[i].h / k;
		down = p->res_y / 2 + spr[i].h / k;
		row = ft_max(up, 0);
		
		while (row < down && row < p->res_y)
		{
			// color = (int *)(xpm->addr + xpm->llen * (int)((row - up) * xpm->h / (down - up)) + w);
			// color = (int *)(xpm->addr + xpm->llen * (int)((row - up) * xpm->h / (down - up)) + w);
			
			color = (int *)(xpm->addr + xpm->llen * (int)((row - up) * xpm->h / (down - up)) + w);
			if (*color != 0x980088)
				my_mlx_pixel_put(img, row, col, *color);
			// if (i == 1)
			// {
			// 		printf("color = %i, %x\n", *color, *color);
			// 		exit(1);
			// }
				
			row++;
		}
	}
}

void	put_column(t_param *p, t_data *img, int col, int up, int down)
{
	int		row;
	int		*color;
	int		w;
	t_texture	xpm;

	xpm = img->xpm[img->plr->texture_ind];
	w = (xpm.bpp / 8) * (int)(xpm.w * (img->plr->diff));
	row = 0;
	// while (row <= up && row < p->res_y)
	// 	my_mlx_pixel_put(img, row++, col, p->cel);
	row = ft_max(up, 0); 
	while (row < down && row < p->res_y)
	{
		color = (int *)(xpm.addr + xpm.llen * (int)((row - up) * xpm.h / (down - up)) + w);
		my_mlx_pixel_put(img, row++, col, *color);
	}
	// while (row < p->res_y)
	// 	my_mlx_pixel_put(img, row++, col, p->floor);
}
