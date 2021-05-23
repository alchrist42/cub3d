#include "cub3d_bonus.h"

/*
**	@brief	'trows' ray of sight and get distance (and height)
**			to cell with sprite and walls
**	
**	@param	img		the mlx instance
**	@param	vray	current ray vector
*/
void	throw_ray(t_data *img, t_vector vray)
{
	t_dot	dot;
	t_dot	dot_row;
	t_dot	dot_col;
	int		max_cross;

	inicialise_first_dots(img, &vray, &dot_row, &dot_col);
	max_cross = 256;
	while (--max_cross && img->plr->cnt_s < 200)
	{
		draw_ray_mmap(img, &dot);
		if (ft_dist(dot_row.x - img->plr->x, dot_row.y - img->plr->y)
			< ft_dist(dot_col.x - img->plr->x, dot_col.y - img->plr->y))
		{
			get_next_cross(&vray, &dot, &dot_row, 1);
			if (check_cell_x(img, &vray, &dot, &img->plr->cnt_s))
				break ;
		}
		else
		{
			get_next_cross(&vray, &dot, &dot_col, 0);
			if (check_cell_y(img, &vray, &dot, &img->plr->cnt_s))
				break ;
		}
	}
}

/*
**	@brief	initialises first intersection ray
**	
**	@param	img			the mlx instance
**	@param	vray		current ray vector
**	@param	dot_row		intersection by vertical border
**	@param	dot_col		intersection by horisontal border
*/
void	inicialise_first_dots(t_data *img, t_vector *vray,
		t_dot *dot_row, t_dot *dot_col)
{
	img->plr->cnt_s = 0;
	dot_row->x = (int)img->plr->x + (vray->cx > 0);
	dot_row->y = img->plr->y + (dot_row->x - img->plr->x)
		* vray->cy * vray->cx;
	dot_col->y = (int)img->plr->y + (vray->ry > 0);
	dot_col->x = img->plr->x + (dot_col->y - img->plr->y)
		* vray->rx * vray->ry;
}

/*
**	@brief	Get the next ray and cell intersection
**	
**	@param	vray	current ray vector
**	@param	dot		the old point of cross borders between cells
**	@param	d		the new point of cross borders between cells
**	@param	is_row		1 if it's vertical border, else 0
*/
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
