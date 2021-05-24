#include "cub3d_bonus.h"

void	collision_item(t_data *img, t_player *plr)
{
	int	row;
	int	col;

	col = (int)plr->x;
	row = (int)plr->y;
	if (char_in_str(img->p->map[row][col], "7"))
	{
		plr->i_torch = 600;
		img->p->map[row][col] = 0;
	}
	else if (char_in_str(img->p->map[row][col], "8"))
	{
		plr->hp--;
	}
}

void	check_player(t_data *img, t_player *plr)
{
	collision_item(img, plr);
	if (plr->hp <= 0)
	{
		sleep(1);
		initialise_player(img, img->p, plr);
	}
	plr->shadow_gl = PLR_VIEW + (float)plr->i_torch-- / 200;
	plr->i_torch = ft_max(1, plr->i_torch);
}
