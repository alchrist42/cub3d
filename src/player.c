#include "cub3d.h"


void	inicialise_buttons(t_button *btn)
{
	btn->w = false;
	btn->a = false;
	btn->s = false;
	btn->d = false;
	btn->q = false;
	btn->e = false;
}

void	initialise_player(t_data *img, t_param *p, t_player *plr)
{
	img->plr = plr;
	plr->x = p->plr_x + 0.5;
	plr->y = p->plr_y + 0.5;
	plr->z = 0;
	plr->rotate_speed = p->cnt_v / 120;
	plr->speed = 0.08;

	if (p->map[p->plr_y][p->plr_x] == 'E')
		plr->ind_v = 0;
	else if (p->map[p->plr_y][p->plr_x] == 'S')
		plr->ind_v = p->cnt_v / 4;
	else if (p->map[p->plr_y][p->plr_x] == 'W')
		plr->ind_v = p->cnt_v / 2;
	else
		plr->ind_v = p->cnt_v * 3 / 4;
	// rotate_by_ange(&plr->vx, &plr->vy, sin(M_PI / 180), cos(M_PI / 180));
	plr->vx = img->v[plr->ind_v].x;
	plr->vy = img->v[plr->ind_v].y;
	printf("Start pos x=%f, y=%f, rotate_speed=%d\n ind=%d, char=%c\n", plr->vx, plr->vy, plr->rotate_speed, plr->ind_v, p->map[p->plr_y][p->plr_x]);
}


