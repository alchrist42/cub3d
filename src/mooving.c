#include "cub3d.h"

void	change_position(t_params *p, t_player *plr, t_buttons *btn)
{
	float	row;
	float	col;

	row = plr->y;
	col = plr->x;
	if (btn->w && !btn->s)
	{
		row += plr->vy * plr->speed;
		col += plr->vx * plr->speed;
		
	}
	if (btn->s && !btn->w)
	{
		row -= plr->vy * plr->speed;
		col -= plr->vx * plr->speed;
	}
	if (btn->a && !btn->d)
	{
		row -= plr->vx * plr->speed;
		col += plr->vy * plr->speed;
	}

	if (btn->d && !btn->a)
	{
		row += plr->vx * plr->speed;
		col -= plr->vy * plr->speed;
	}

	if (p->map[(int)row][(int)col] != '1')
	{
		plr->y = row;
		plr->x = col;
	}
	else if (p->map[(int)row][(int)plr->x] != '1')
		plr->y = row;
	else if (p->map[(int)plr->y][(int)col] != '1')
		plr->x = col;
}

void	rotate_view(t_params *p, t_player *plr, t_buttons *btn)
{	
	if (btn->q && !btn->e)
		rotate_by_ange(&plr->vx, &plr->vy, -p->sin_a, p->cos_a);
	if (btn->e && !btn->q)
		rotate_by_ange(&plr->vx, &plr->vy, p->sin_a, p->cos_a);
}

void	rotate_by_ange(double *x, double *y, double sin_a, double cos_a)
{
	double	copy_x;

	copy_x = *x;
	*x = copy_x * cos_a - *y * sin_a;
	*y = copy_x * sin_a + *y * cos_a;
}