#include "cub3d.h"

int	check_cell(t_data *img, t_vector vray, t_dot *dot)
{
	char cell_x;
	char	cell_y;

	cell_x = img->p->map[(int)(dot->y)][(int)(dot->x + 0.0000001 * vray.cx)];
	cell_y = img->p->map[(int)(dot->y + 0.0000001 * vray.ry)][(int)(dot->x)];
	img->plr->sprite[img->plr->cnt_s].xpm = &img->xpm[4];

	if (cell_x == '2')
	{
		img->plr->sprite[img->plr->cnt_s].diff = 0.5 + (vray.cx * (dot->y - (int)dot->y - 0.5) - vray.cy * (dot->x - (int)(dot->x + 0.000001 * vray.cx) - 0.5)) / ft_dist(vray.cx, vray.cy);
		img->plr->sprite[img->plr->cnt_s].xpm = &img->xpm[4];
		if (img->plr->sprite[img->plr->cnt_s].diff > 0 && img->plr->sprite[img->plr->cnt_s].diff < 1)
			img->plr->sprite[img->plr->cnt_s++].h = img->p->res_x / (ft_dist((int)dot->y + 0.5 - img->plr->y , (int)(dot->x + 0.000001 * vray.cx ) + 0.5 - img->plr->x));
		return (img->plr->cnt_s > 198);
	}
	else if (cell_y == '2')	
	{
		img->plr->sprite[img->plr->cnt_s].diff = 0.5 + (vray.rx * (-(int)(dot->y + 0.000001 * vray.ry) + dot->y - 0.5) - vray.ry * (dot->x - (int)(dot->x) - 0.5)) / ft_dist(vray.rx, vray.ry);
		img->plr->sprite[img->plr->cnt_s].xpm = &img->xpm[4];
		if (img->plr->sprite[img->plr->cnt_s].diff > 0 && img->plr->sprite[img->plr->cnt_s].diff < 1)
			img->plr->sprite[img->plr->cnt_s++].h = img->p->res_x  / (ft_dist((int)(dot->y + 0.000001 * vray.ry) + 0.5 - img->plr->y, (int)dot->x  + 0.5 - img->plr->x));
		return (img->plr->cnt_s > 198);
	}
	else if (cell_x == '1' || cell_y == '1')
	{
		if (dot->x - (int)dot->x < dot->y - (int)dot->y)
		{
			img->plr->sprite[img->plr->cnt_s].diff = dot->y - (int)dot->y;
			img->plr->sprite[img->plr->cnt_s].xpm = &img->xpm[(vray.rx > 0)];
		}
		else
		{
			img->plr->sprite[img->plr->cnt_s].diff = dot->x - (int)dot->x;
			img->plr->sprite[img->plr->cnt_s].xpm = &img->xpm[2 + (vray.ry > 0)];
		}
		img->plr->sprite[img->plr->cnt_s++].h = img->p->res_x  / (ft_dist(dot->y - img->plr->y, dot->x - img->plr->x));
	}

	return (cell_x == '1' || cell_y == '1');
}


void	throw_ray(t_data *img, t_vector vray)
{
	t_dot	dot;
	t_dot	d1;
	t_dot	d2;
	int		i;

	get_first_cross(img, &vray, &dot, &d1, &d2);
	// my_mlx_pixel_put(img, dot.y * img->p->res_y / (img->p->h_map * 3), dot.x * img->p->res_x / (img->p->w_map * 2), 0x00BFF0FF);

	img->plr->cnt_s = 0;
	i = -1;
	while (++i < 300)
	{
		if (check_cell(img, vray, &dot))
			break ;
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
		// my_mlx_pixel_put(img, dot.y * img->p->res_y / (img->p->h_map * 3), dot.x * img->p->res_x / (img->p->w_map * 2), 0x00BFB0FF);
	}
	
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
