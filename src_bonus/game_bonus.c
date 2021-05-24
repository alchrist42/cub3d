#include "cub3d_bonus.h"

/*
**	@brief	registration game's hooks
**	
**	@param	img		the mlx instance
*/
void	run_game(t_data *img)
{
	mlx_hook(img->win, 2, 1L << 0, press_button, img);
	mlx_hook(img->win, 3, 1L << 1, release_button, img);
	mlx_hook(img->win, 4, 0, mouse_press, img);
	mlx_hook(img->win, 17, 1L << 1, close_win, img);
	mlx_loop_hook(img->mlx, main_game, img);
	mlx_loop(img->mlx);
}

/*
**	@brief	main loop game. change view and position player. then draw screen
**	
**	@param	img		the mlx instance
**	@return	int		0 if no error
*/
int	main_game(t_data *img)
{
	mouse_move(img, img->btn);
	rotate_view(img->p, img->plr, img->btn);
	change_pos(img->p->map, img->plr, img->btn, img->v);
	check_player(img, img->plr);
	draw_floor_and_cel(img->p, img);
	draw_walls(img->p, img);
	draw_hp_bar(img->p, img);
	draw_mmap(img->p, img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	mlx_do_sync(img->mlx);
	return (0);
}

/*
**	@brief	saves game screen to bpm file if --save in args
**	
**	@param	img		the mlx instance
**	@param	p		pointer to structure with parametrs
**	@param	plr		the player's stucture
*/
void	save_mode(t_data *img, t_param *p, t_player *plr)
{
	img->p = p;
	img->mlx = mlx_init();
	if (!img->mlx)
		ft_raise_error("Cannot initialize mlx\n");
	img->llen = p->res_x * 4;
	img->bpp = 32;
	img->addr = malloc(img->llen * p->res_y);
	if (!img->addr)
		ft_raise_error("Cannot allocate memory for img instance\n");
	get_textures(img, img->xpm, p);
	pe4em_vectora(img, p);
	initialise_player(img, p, plr);
	draw_floor_and_cel(p, img);
	draw_walls(img->p, img);
	ft_save_bmp(img);
	exit(0);
}
