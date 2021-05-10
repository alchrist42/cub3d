#include "cub3d.h"


void	inicialise_buttons(t_buttons *btn)
{
	btn->w = false;
	btn->a = false;
	btn->s = false;
	btn->d = false;
	btn->q = false;
	btn->e = false;
}

void	initialise_player(t_data *img, t_params *p, t_player *plr)
{
	img->plr = plr;
	plr->x = p->plr_x + 0.5;
	plr->y = p->plr_y + 0.5;
	plr->z = 1;
	plr->speed = 0.05;
	plr->vx = 0;
	plr->vy = 0;
	plr->vz = 0;
	if (p->map[p->plr_y][p->plr_x] == 'E')
		plr->vx = 1;
	else if (p->map[p->plr_y][p->plr_x] == 'W')
		plr->vx = -1;
	else if (p->map[p->plr_y][p->plr_x] == 'S')
		plr->vy = 1;
	else
		plr->vy = -1;
	rotate_by_ange(&plr->vx, &plr->vy, sin(M_PI / 180), cos(M_PI / 180));
}



