#include "cub3d.h"

int	check_cell(t_data *img, t_vector vray, t_dot *dot)
{
	char cell_x;
	char	cell_y;

	cell_x = img->param->map[(int)(dot->y)][(int)(dot->x + 0.000001 * vray.cx)];
	cell_y = img->param->map[(int)(dot->y + 0.000001 * vray.ry)][(int)(dot->x)];
	img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[4];
	// if (cell_x == '2' || cell_y == '2')
	// {
	if (cell_x == '2')
	{
		img->plr->sprite[img->plr->n_spr].diff = 0.5 + (vray.cx * (dot->y - (int)dot->y - 0.5) - vray.cy * (dot->x - (int)(dot->x + 0.000001 * vray.cx) - 0.5)) / ft_dist(vray.cx, vray.cy);
		img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[4];
		if (img->plr->sprite[img->plr->n_spr].diff > 0 && img->plr->sprite[img->plr->n_spr].diff < 1)
			img->plr->sprite[img->plr->n_spr++].h = img->param->res_x / 2 / (ft_dist((int)dot->y + 0.5 - img->plr->y , (int)(dot->x + 0.000001 * vray.cx ) + 0.5 - img->plr->x));
		return (0);
	}
	else if (cell_y == '2')	
	{
		img->plr->sprite[img->plr->n_spr].diff = 0.5 + (vray.rx * (-(int)(dot->y + 0.000001 * vray.ry) + dot->y - 0.5) - vray.ry * (dot->x - (int)(dot->x) - 0.5)) / ft_dist(vray.rx, vray.ry);
		img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[4];
		if (img->plr->sprite[img->plr->n_spr].diff > 0 && img->plr->sprite[img->plr->n_spr].diff < 1)
			img->plr->sprite[img->plr->n_spr++].h = img->param->res_x / 2 / (ft_dist((int)(dot->y + 0.000001 * vray.ry) + 0.5 - img->plr->y, (int)dot->x  + 0.5 - img->plr->x));
		return (0);
	}
		// 
			
		// return (0);
	// }
	else if (cell_x == '1' || cell_y == '1')
	{
		if (dot->x - (int)dot->x < dot->y - (int)dot->y)
		{
			img->plr->sprite[img->plr->n_spr].diff = dot->y - (int)dot->y;
			img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[(vray.rx > 0)];
		}
		else
		{
			img->plr->sprite[img->plr->n_spr].diff = dot->x - (int)dot->x;
			img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[2 + (vray.ry > 0)];
		}
		img->plr->sprite[img->plr->n_spr++].h = img->param->res_x / 2 / (ft_dist(dot->y - img->plr->y, dot->x - img->plr->x));
	}
	// else if (cell_y == '1')
	// {
	// 	img->plr->sprite[img->plr->n_spr].diff = fabs(dot->x - (int)dot->x);
	// 	img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[2 + (vray.ry > 0)];
	// }
	// else
	// 	return (0);
	// if (cell_x == '2' || cell_y == '2')
	// 	img->plr->sprite[img->plr->n_spr].xpm = &img->xpm[4];
	// img->plr->sprite[img->plr->n_spr].h = img->param->res_x / 3 / (ft_dist(dot->y - img->plr->y, dot->x - img->plr->x));
	// img->plr->n_spr++;
	// printf("sp=%i\n", img->plr->n_spr);
	return (cell_x == '1' || cell_y == '1');
}


float	get_dist_to_wall(t_data *img, t_vector vray)
{
	t_dot	dot;
	t_dot	d1;
	t_dot	d2;
	int		i;

	get_first_cross(img, &vray, &dot, &d1, &d2);
	my_mlx_pixel_put(img, dot.y * img->param->res_y / (img->param->h_map * 3), dot.x * img->param->res_x / (img->param->w_map * 2), 0x00BFF0FF);

	img->plr->n_spr = 0;
	i = -1;
	while (++i < 300)
	{
		
		if (check_cell(img, vray, &dot))
			return (1);
		// if (img->param->map[(int)(dot.y + 0.000001 * vray.ry)][(int)(dot.x)] == '1'
		// || img->param->map[(int)(dot.y)][(int)(dot.x + 0.000001 * vray.cx )] == '1')
		// {
		// 	if (dot.x - (int)dot.x < dot.y - (int)dot.y)
		// 	{
		// 		img->plr->diff = dot.y - (int)dot.y;
		// 		img->plr->texture_ind = (vray.rx > 0);

		// 		img->plr->sprite[0].diff = dot.y - (int)dot.y;
		// 		img->plr->sprite[0].xpm = &img->xpm[(vray.rx > 0)];
				
		// 	}
		// 	else
		// 	{
		// 		img->plr->diff = dot.x - (int)dot.x;
		// 		img->plr->texture_ind = 2 + (vray.ry > 0);

		// 		img->plr->sprite[0].diff = dot.x - (int)dot.x;
		// 		img->plr->sprite[0].xpm = &img->xpm[2 + (vray.ry > 0)];
		// 	}
		// 	img->plr->n_spr = 1;
		// 	img->plr->sprite[0].h = img->param->res_x / 3 / ft_dist(dot.y - img->plr->y, dot.x - img->plr->x);
		// 	return (ft_dist(dot.y - img->plr->y, dot.x - img->plr->x));
		// }

		if (ft_dist(d1.x - img->plr->x, d1.y - img->plr->y) < ft_dist(d2.x - img->plr->x, d2.y - img->plr->y))
		{
			dot.y = d1.y;
			dot.x = d1.x;
			d1.x = (int)dot.x + vray.cx;
			d1.y = dot.y + (d1.x - dot.x) * vray.cy * vray.cx;
		}
		else
		{
			dot.y = d2.y;
			dot.x = d2.x;
			d2.y = (int)dot.y + vray.ry;
			d2.x = dot.x + (d2.y - dot.y) * vray.rx * vray.ry;
		}
		// printf("-----------\nplayer (%f %f)\npoint(%i): %f %f \n", img->plr->y, img->plr->x, i, dot.y, dot.x);
		my_mlx_pixel_put(img, dot.y * img->param->res_y / (img->param->h_map * 3), dot.x * img->param->res_x / (img->param->w_map * 2), 0x00BFB0FF);
	}
	return (300);
	
}

void	get_first_cross(t_data *img, t_vector *vray, t_dot *dot, t_dot *d1, t_dot *d2)
{
	d1->x = (int)img->plr->x + (vray->cx > 0);
	d1->y = img->plr->y + (d1->x - img->plr->x) * vray->cy * vray->cx;
	d2->y = (int)img->plr->y + (vray->ry > 0);
	d2->x = img->plr->x + (d2->y - img->plr->y) * vray->rx * vray->ry;

	if (fabs(d1->x - img->plr->x) + fabs(d1->y - img->plr->y) < fabs(d2->x - img->plr->x) + fabs(d2->y - img->plr->y))
	{
		dot->y = d1->y;
		dot->x = d1->x;
		d1->x = (int)dot->x + (vray->cx > 0);
		d1->y = dot->y + (d1->x - dot->x) * vray->cy * vray->cx;
	}
	else
	{
		dot->y = d2->y;
		dot->x = d2->x;
		d2->y = (int)dot->y + (vray->ry > 0);
		d2->x = dot->x + (d2->y - dot->y) * vray->rx * vray->ry;
	}
}
