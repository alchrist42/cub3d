#include "cub3d.h"

/*
**	@brief	changes player position
**	
**	@param	map		pointer to map
**	@param	plr		player structure
**	@param	btn		button structure
**	@param	vs		vectors massive
*/
void	change_pos(char **map, t_player *plr, t_button *btn, t_vector *vs)
{
	float	row;
	float	col;

	row = plr->y;
	col = plr->x;
	if (btn->w && !btn->s)
		forward_mov(&vs[plr->ind_v], plr->speed, &row, &col);
	if (btn->s && !btn->w)
		forward_mov(&vs[plr->ind_v], -plr->speed, &row, &col);
	if (btn->a && !btn->d)
		sideways_mov(&vs[plr->ind_v], plr->speed, &row, &col);
	if (btn->d && !btn->a)
		sideways_mov(&vs[plr->ind_v], -plr->speed, &row, &col);
	check_and_change(map, plr, row, col);
}

/*
**	@brief	rotates player's view
**	
**	@param	p		the structure with parametrs
**	@param	plr		the player structure
**	@param	btn		the buttons structure
*/
void	rotate_view(t_param *p, t_player *plr, t_button *btn)
{	
	if (btn->q && !btn->e)
		plr->ind_v -= plr->rotate_speed;
	if (btn->e && !btn->q)
		plr->ind_v += plr->rotate_speed;
	if (plr->ind_v >= p->cnt_v)
		plr->ind_v -= p->cnt_v;
	else if (plr->ind_v < 0)
		plr->ind_v += p->cnt_v;
}

/*
**	@brief	movings player  forward or backward
**	
**	@param	v		player sight vector
**	@param	speed	player speed
**	@param	row		new player y position
**	@param	col		new player x position
*/
void	forward_mov(t_vector *v, float speed, float *row, float *col)
{
	*row += v->y * speed;
	*col += v->x * speed;
}

/*
**	@brief	movings player  left or right
**	
**	@param	v		player sight vector
**	@param	speed	player speed
**	@param	row		new player y position
**	@param	col		new player x position
*/
void	sideways_mov(t_vector *v, float speed, float *row, float *col)
{
	*row -= v->x * speed;
	*col += v->y * speed;
}

/*
**	@brief	checks and moovings player to new position if its correct
**	
**	@param	map		pointer to map
**	@param	plr		the player structure
**	@param	row		new player y position
**	@param	col		new player x position
*/
void	check_and_change(char **map, t_player *plr, float row, float col)
{
	int	row2;
	int	col2;

	row2 = (int)(plr->y + 2 * (row - plr->y));
	col2 = (int)(plr->x + 2 * (col - plr->x));
	if (map[(int)row][(int)col] != '1' && map[row2][col2] != '1'
		&& map[(int)plr->y][col2] != '1' && map[row2][(int)plr->x] != '1')
	{
		plr->y = row;
		plr->x = col;
	}
	else if (map[(int)row][(int)plr->x] != '1'
			&& map[row2][(int)plr->x] != '1')
		plr->y = row;
	else if (map[(int)plr->y][(int)col] != '1'
			&& map[(int)plr->y][col2] != '1')
		plr->x = col;
}
