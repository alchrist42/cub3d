#include "cub3d_bonus.h"

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

void	mouse_move(t_data *img, t_button *btn)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(img->win, &x, &y);
	if (!btn->ctrl && x > 0 && x < img->p->res_x && y > 0 && y < img->p->res_y)
	{
		mlx_mouse_hide();
		printf("mouse move x=%d y=%d\n", x, y);
		mlx_mouse_move(img->win, img->p->res_x / 2, img->p->res_y / 2);

	}
	else
	{
		mlx_mouse_show();

	}
}
