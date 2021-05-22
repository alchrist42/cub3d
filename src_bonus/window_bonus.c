#include "cub3d_bonus.h"

/*
**	@brief	Create a window and img objects and load textures
**	
**	@param	img		the mlx instance
**	@param	p		the structure with parameters
**	@param	btn		the structure with buttons
*/
void	create_window(t_data *img, t_param *p, t_button *btn)
{
	img->p = p;
	img->btn = btn;
	img->mlx = mlx_init();
	if (!img->mlx)
		ft_raise_error("Cannot initialize mlx\n");
	get_textures(img, img->xpm, p);
	correct_resolution(p);
	img->win = mlx_new_window(img->mlx, p->res_x, p->res_y, "Cub3D");
	if (!img->win)
		ft_raise_error("Cannot create game windows\n");
	img->img = mlx_new_image(img->mlx, p->res_x, p->res_y);
	if (!img->img)
		ft_raise_error("Cannot create new mlx_img\n");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->llen, &img->end);
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
void	correct_resolution(t_param *p)
{
	int	x;
	int	y;

	if (!p->save)
	{
		mlx_get_screen_size(&x, &y);
		p->res_x = ft_min(x, p->res_x);
		p->res_y = ft_min(y, p->res_y);
	}
}

/*
**	@brief	Get the textures object
**	
**	@param	img		the mlx instance
**	@param	xpm		array for textures
**	@param	p		the structure with parameters
*/
void	get_textures(t_data *img, t_texture *xpm, t_param *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < i)
		{
			if (!ft_strncmp(p->xpm[i], p->xpm[j], ft_strlen(p->xpm[i]) + 1))
			{
				xpm[i] = xpm[j];
				continue ;
			}
		}
		if (!ft_strncmp(p->xpm[i] + ft_strlen(p->xpm[i]) - 4, ".png", 4))
			ft_raise_error("png textures not supported\n");
		xpm[i].img = mlx_xpm_file_to_image(img->mlx, p->xpm[i],
				&xpm[i].w, &xpm[i].h);
		if (!xpm[i].img)
			ft_raise_error("Cannot read texture file\n");
		xpm[i].addr = mlx_get_data_addr(xpm[i].img, &xpm[i].bpp,
				&xpm[i].llen, &xpm[i].end);
	}
}
