#include "cub3d_bonus.h"

/**
 * @brief puts sprites and walls to img
 * 
 * @param p 	pointer to structure with parameters
 * @param img 	the mlx instance
 */
void	draw_walls(t_param *p, t_data *img)
{
	int		col;
	int		start_ind;
	float	k;
	int		i;

	col = 0;
	start_ind = img->plr->ind_v - p->res_x / 2;
	if (start_ind < 0)
		start_ind += p->cnt_v;
	while (col < p->res_x)
	{
		throw_ray(img, img->v[start_ind + col]);
		k = img->v[ft_abs(p->res_x / 2 - col)].x;
		i = img->plr->cnt_s;
		img->plr->sprite[i - 1].h /= k;
		while (i--)
			img->plr->sprite[i].shad_k = img->plr->shadow_gl * img->plr->sprite[i].h * img->plr->sprite[i].h / p->res_y / p->res_y;
		put_column(img, img->plr->sprite, col, img->plr->cnt_s);
		col++;
	}
}

/**
 * @brief fills in foolr and celling colors
 * 
 * @param p 	pointer to structure with parameters
 * @param img 	the mlx instance
 */
void	draw_floor_and_cel(t_param *p, t_data *img)
{
	int	i;

	i = 0;
	while (i < p->res_y / 2)
		my_mlx_row_put(img, i++, p->cel);
	while (i < p->res_y)
		my_mlx_row_put(img, i++, p->floor);
}

/**
 * @brief 	fills one column of image. 
 * 			draws sprites pixels sequentially starting from the farthest
 * 
 * @param img 	the mlx instance
 * @param spr 	sprite sequence
 * @param col 	сolumn index
 * @param i 	index last  sprite. just for nominette
 */
void	put_column(t_data *img, t_sprite *spr, int col, int i)
{
	int			row_sp;
	int			up;
	int			down;
	t_texture	*xpm;
	int			color;

	while (i--)
	{
		xpm = spr[i].xpm;
		down = (img->p->res_y - spr[i].h) / 2;
		row_sp = -1;
		while (++row_sp < xpm->h)
		{
			up = ft_max(0, down);
			down = ft_min(img->p->res_y, (img->p->res_y - spr[i].h) / 2
					+ (row_sp + 1) * spr[i].h / xpm->h);
			if (down >= 0 && up < img->p->res_y
				&& (i + 1 == img->plr->cnt_s
					|| spr[i].h / 3 < img->p->res_y)
				&& (color = get_pixel(xpm, row_sp, spr[i].diff)) != TRNS)
				while (up < down)
					my_mlx_pixel_put(img, up++, col, ft_shadow(img, color, i));
		}
	}
}

int	ft_shadow(t_data *img, int color, int ind)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	float			k;

	r = color >> 16;
	g = color >> 8;
	b = color;
	k = img->plr->sprite[ind].shad_k;
	return (create_trgb(0, ft_min(r, 1.3 * r * k), ft_min(g * 0.8, g * k), ft_min(b * 0.8, b * k)));
}
