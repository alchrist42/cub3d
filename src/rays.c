#include "cub3d.h"

int	check_cell(t_data *img, t_vector vray, t_dot *dot)
{
	t_cell	cell;
	int		*i;

	cell.x = img->p->map[(int)(dot->y)][(int)(dot->x + 0.0000001 * vray.cx)];
	cell.y = img->p->map[(int)(dot->y + 0.0000001 * vray.ry)][(int)(dot->x)];
	if (cell.x == '2' || cell.y == '2')
		sprite_cell(img, &vray, dot, &cell);
	i = &img->plr->cnt_s;
	if (cell.x == '1' || cell.y == '1')
	{
		if (dot->x - (int)dot->x < dot->y - (int)dot->y)
		{
			img->plr->sprite[*i].diff = dot->y - (int)dot->y;
			img->plr->sprite[*i].xpm = &img->xpm[(vray.rx > 0)];
		}
		else
		{
			img->plr->sprite[*i].diff = dot->x - (int)dot->x;
			img->plr->sprite[*i].xpm = &img->xpm[2 + (vray.ry > 0)];
		}
		img->plr->sprite[(*i)++].h = img->p->res_x
			/ (ft_dist(dot->y - img->plr->y, dot->x - img->plr->x));
	}
	return (cell.x == '1' || cell.y == '1');
}

void	sprite_cell(t_data *img, t_vector *vray, t_dot *dot, t_cell *cell)
{
	int	*i;

	i = &img->plr->cnt_s;
	if (cell->x == '2')
	{
		img->plr->sprite[*i].diff = (vray->cx * (dot->y - (int)dot->y - 0.5)
				- (dot->x - (int)(dot->x + 0.000001 * vray->cx) - 0.5)
				* vray->cy) / ft_dist(vray->cx, vray->cy) + 0.5;
		img->plr->sprite[*i].xpm = &img->xpm[4];
		if (img->plr->sprite[*i].diff > 0 && img->plr->sprite[*i].diff < 1)
			img->plr->sprite[(*i)++].h = img->p->res_x
				/ (ft_dist((int)dot->y + 0.5 - img->plr->y, (int)(dot->x
							+ 0.000001 * vray->cx) + 0.5 - img->plr->x));
	}
	else if (cell->y == '2')
	{
		img->plr->sprite[*i].diff = 0.5 - vray->ry * (dot->x - (int)(dot->x)
				+ (vray->rx * (dot->y - (int)(dot->y + 0.000001 * vray->ry)
						- 0.5) - 0.5)) / ft_dist(vray->rx, vray->ry);
		img->plr->sprite[*i].xpm = &img->xpm[4];
		if (img->plr->sprite[*i].diff > 0 && img->plr->sprite[*i].diff < 1)
			img->plr->sprite[(*i)++].h = img->p->res_x
				/ (ft_dist((int)(dot->y + 0.000001 * vray->ry)
						+ 0.5 - img->plr->y, (int)dot->x + 0.5 - img->plr->x));
	}
}

void	throw_ray(t_data *img, t_vector vray)
{
	t_dot	dot;
	t_dot	d1;
	t_dot	d2;
	int		i;

	img->plr->cnt_s = 0;
	d1.x = (int)img->plr->x + (vray.cx > 0);
	d1.y = img->plr->y + (d1.x - img->plr->x) * vray.cy * vray.cx;
	d2.y = (int)img->plr->y + (vray.ry > 0);
	d2.x = img->plr->x + (d2.y - img->plr->y) * vray.rx * vray.ry;
	i = -1;
	while (++i < 512 && img->plr->cnt_s < 200)
	{
		if (ft_dist(d1.x - img->plr->x, d1.y - img->plr->y)
			< ft_dist(d2.x - img->plr->x, d2.y - img->plr->y))
			get_next_cross(&vray, &dot, &d1, 1);
		else
			get_next_cross(&vray, &dot, &d2, 0);
		if (check_cell(img, vray, &dot))
			break ;
	}
}

void	get_next_cross(t_vector *vray, t_dot *dot, t_dot *d, int is_row)
{
	dot->y = d->y;
	dot->x = d->x;
	if (is_row)
	{
		d->x = (int)dot->x + vray->cx;
		d->y = dot->y + (d->x - dot->x) * vray->cy * vray->cx;
	}
	else
	{
		d->y = (int)dot->y + vray->ry;
		d->x = dot->x + (d->y - dot->y) * vray->rx * vray->ry;
	}
}
