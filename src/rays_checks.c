#include "cub3d.h"
/*
**	@brief	checks the cell of map and get dist(height) to cell
**			if it's a sprite or a wall
**	
**	@param	img		the mlx instance
**	@param	vray	current ray vector
**	@param	dot		the point of cross vertical border between cells
**	@param	i		the index of sprite
**	@return	int		1 if it's wall, else 0
*/
int	check_cell_x(t_data *img, t_vector *vray, t_dot *dot, int *i)
{
	char	cell;

	cell = img->p->map[(int)(dot->y)][(int)(dot->x + 0.0001 * vray->cx)];
	check_sprite_x(img, vray, dot, cell);
	if (cell == '1')
	{
		if (vray->cx > 0)
			img->plr->sprite[*i].diff = dot->y - (int)dot->y;
		else
			img->plr->sprite[*i].diff = 1 - (dot->y - (int)dot->y);
		img->plr->sprite[*i].xpm = &img->xpm[(vray->rx > 0)];
		img->plr->sprite[(*i)++].h = img->p->res_x
			/ (ft_dist(dot->y - img->plr->y, dot->x - img->plr->x));
	}
	return (cell == '1');
}

/*
**	@brief	checks the cell of map and get dist(height) to cell
**			if it's a sprite
**	
**	@param	img		the mlx instance
**	@param	vray	current ray vector
**	@param	dot		the point of cross horizontal border between cells
**	@param	cell	the cell of the map
*/
void	check_sprite_x(t_data *img, t_vector *vray, t_dot *dot, char cell)
{
	int	*i;

	i = &img->plr->cnt_s;
	if (cell == '2')
	{
		img->plr->sprite[*i].diff = (vray->cx * (dot->y - (int)dot->y - 0.5)
				- (dot->x - (int)(dot->x + 0.00001 * vray->cx) - 0.5)
				* vray->cy) / ft_dist(vray->cx, vray->cy) + 0.5;
		img->plr->sprite[*i].xpm = &img->xpm[4];
		if (img->plr->sprite[*i].diff > 0 && img->plr->sprite[*i].diff < 1)
			img->plr->sprite[(*i)++].h = img->p->res_x
				/ (ft_dist((int)dot->y + 0.5 - img->plr->y, (int)(dot->x
							+ 0.000001 * vray->cx) + 0.5 - img->plr->x));
	}
}

/*
**	@brief	checks the cell of map and get dist(height) to cell
**			if it's a sprite or a wall
**	
**	@param	img		the mlx instance
**	@param	vray	current ray vector
**	@param	dot		the point of cross veticals border between cells
**	@param	i		the index of sprite
**	@return	int		1 if it's wall, else 0
*/
int	check_cell_y(t_data *img, t_vector *vray, t_dot *dot, int *i)
{
	char	cell;

	cell = img->p->map[(int)(dot->y + 0.0001 * vray->ry)][(int)(dot->x)];
	check_sprite_y(img, vray, dot, cell);
	if (cell == '1')
	{
		if (vray->ry > 0)
			img->plr->sprite[*i].diff = 1 - (dot->x - (int)dot->x);
		else
			img->plr->sprite[*i].diff = dot->x - (int)dot->x;
		img->plr->sprite[*i].xpm = &img->xpm[2 + (vray->ry > 0)];
		img->plr->sprite[(*i)++].h = img->p->res_x
			/ (ft_dist(dot->y - img->plr->y, dot->x - img->plr->x));
	}
	return (cell == '1');
}

/*
**	@brief	checks the cell of map and get dist(height) to cell
**			if it's a sprite
**	
**	@param	img		the mlx instance
**	@param	vray	current ray vector
**	@param	dot		the point of cross horizontal border between cells
**	@param	cell	the cell of the map
*/
void	check_sprite_y(t_data *img, t_vector *vray, t_dot *dot, char cell)
{
	int	*i;

	i = &img->plr->cnt_s;
	if (cell == '2')
	{
		img->plr->sprite[*i].diff = -(vray->ry * (dot->x - (int)(dot->x) - 0.5)
				- (dot->y - (int)(dot->y + 0.000001 * vray->ry) - 0.5)
				* vray->rx) / ft_dist(vray->rx, vray->ry) + 0.5;
		img->plr->sprite[*i].xpm = &img->xpm[4];
		if (img->plr->sprite[*i].diff > 0 && img->plr->sprite[*i].diff < 1)
			img->plr->sprite[(*i)++].h = img->p->res_x
				/ (ft_dist((int)(dot->y + 0.000001 * vray->ry)
						+ 0.5 - img->plr->y, (int)dot->x + 0.5 - img->plr->x));
	}
}
