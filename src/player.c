#include "cub3d.h"

void	initialise_player(t_data *img, t_params *p, t_player *plr)
{
	img->plr = plr;
	plr->x = p->plr_x + 0.5;
	plr->y = p->plr_y + 0.5;
	plr->speed = 0.1;
	plr->angle = 0.4;
	if (p->map[p->plr_y][p->plr_x] == 'E')
		plr->vx = 1;
	else if (p->map[p->plr_y][p->plr_x] == 'W')
		plr->vx = -1;
	else if (p->map[p->plr_y][p->plr_x] == 'S')
		plr->vy = 1;
	else
		plr->vy = -1;
}

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
	printf("x=%f, y=%f, W=%i, S=%i\n", plr->x, plr->y, btn->w, btn->s);
	if (btn->s)
	{
		row += 0.02;
		if (p->map[(int)row][(int)col] != '1')
			plr->y = row;
		printf("player top top down\n");
	}
}