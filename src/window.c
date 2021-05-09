#include "cub3d.h"

void	create_window(t_data *img, t_params *p, t_buttons *btn)
{

	
	img->mlx = mlx_init();
	correct_resolution(img, p);
	img->win = mlx_new_window(img->mlx, p->res_x, p->res_y, "Cub3D");
	img->img = mlx_new_image(img->mlx, p->res_x, p->res_y);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->llen, &img->end);
	img->params = p;
	img->btn = btn;
}


/*
**	@brief	closes window and stop program
**	
**	@param	img		the mlx instance
*/
int	close_win(t_data *img)
{
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	exit (0);
}


/*
**	@brief changes resolution if it's bigger than the display resolution 
**	
**	@param	img		the mlx instance
**	@param	p		pointer to structure of parameters
**	@return	int		has no return value
*/
void	correct_resolution(t_data *img, t_params *p)
{
	int	x;
	int	y;
	
	mlx_get_screen_size(img->mlx, &x, &y);
	p->res_x = ft_min(x, p->res_x);
	p->res_y = ft_min(y, p->res_y);
	p->sin_a = sin(M_PI / 60);
	p->cos_a = cos(M_PI / 60);
}