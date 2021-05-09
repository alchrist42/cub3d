#include "cub3d.h"

void	change_position(t_params *p, t_player *plr, t_buttons *btn)
{
	float	row;
	float	col;

	row = plr->y;
	col = plr->x;
	if (btn->w)
	{
		row -= 0.02;
		if (p->map[(int)row][(int)col] != '1')
			plr->y = row;
		printf("player top top up\n");
	}
	// printf("x=%f, y=%f, W=%i, S=%i\n", plr->x, plr->y, btn->w, btn->s);
	if (btn->s)
	{
		row += 0.02;
		if (p->map[(int)row][(int)col] != '1')
			plr->y = row;
		printf("player top top down\n");
	}
}

void	rotate_view(t_params *p, t_player *plr, t_buttons *btn)
{	
	double	vector_x;

	vector_x = plr->vx;
	if (btn->q && !btn->e)
	{	
		plr->vx = vector_x * p->cos_a + plr->vy * p->sin_a;
		plr->vy = - vector_x * p->sin_a + plr->vy * p->cos_a;
	}
	if (btn->e && !btn->q)
	{	
		plr->vx = vector_x * p->cos_a - plr->vy * p->sin_a;
		plr->vy = vector_x * p->sin_a + plr->vy * p->cos_a;
	}
}