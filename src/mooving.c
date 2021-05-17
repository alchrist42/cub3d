#include "cub3d.h"

void	change_pos(t_param *p, t_player *plr, t_button *btn, t_vector *vs)
{
	float		row;
	float		col;
	float		row2;
	float		col2;
	t_vector	v;

	row = plr->y;
	col = plr->x;
	row2 = row;
	col2 = col;
	v = vs[plr->ind_v];
	if (btn->w && !btn->s)
	{
		row += v.y * plr->speed;
		col += v.x * plr->speed;
		row2 += v.y * 2 * plr->speed;
		col2 += v.x * 2 * plr->speed;
		
	}
	if (btn->s && !btn->w)
	{
		row -= v.y * plr->speed;
		col -= v.x * plr->speed;
		row2 -= v.y * 2 * plr->speed;
		col2 -= v.x * 2 * plr->speed;
	}
	if (btn->a && !btn->d)
	{
		row -= v.x * plr->speed;
		col += v.y * plr->speed;
		row2 -= v.x * 2 * plr->speed;
		col2 += v.y * 2 * plr->speed;
	}

	if (btn->d && !btn->a)
	{
		row += v.x * plr->speed;
		col -= v.y * plr->speed;
		row2 += v.x * 2 * plr->speed;
		col2 -= v.y * 2 * plr->speed;
	}

	if (p->map[(int)row][(int)col] != '1' && p->map[(int)row2][(int)col2] != '1' && p->map[(int)plr->y][(int)col2] != '1' && p->map[(int)row2][(int)plr->x] != '1')
	{
		plr->y = row;
		plr->x = col;
	}
	else if (p->map[(int)row][(int)plr->x] != '1' && p->map[(int)row2][(int)plr->x] != '1')
		plr->y = row;
	else if (p->map[(int)plr->y][(int)col] != '1' && p->map[(int)plr->y][(int)col2] != '1')
		plr->x = col;
}

void	rotate_view(t_param *p, t_player *plr, t_button *btn, t_data *img) //del img
{	
	if (btn->q && !btn->e)
		plr->ind_v -= plr->rotate_speed;
		// rotate_by_ange(&plr->vx, &plr->vy, -p->sin_a, p->cos_a);

	if (btn->e && !btn->q)
		plr->ind_v += plr->rotate_speed;
		// rotate_by_ange(&plr->vx, &plr->vy, p->sin_a, p->cos_a);
		(void)img;
	if (plr->ind_v >= p->cnt_v)
		plr->ind_v -= p->cnt_v;
	else if (plr->ind_v < 0)
		plr->ind_v += p->cnt_v;
	// plr->vx = img->v[plr->ind_v].x;
	// plr->vy = img->v[plr->ind_v].y;
}

void	rotate_by_ange(double *x, double *y, double sin_a, double cos_a)
{
	double	copy_x;

	copy_x = *x;
	*x = copy_x * cos_a - *y * sin_a;
	*y = copy_x * sin_a + *y * cos_a;
}