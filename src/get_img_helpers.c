#include "cub3d.h"

/*
**	@brief	Create a trgb object (encoding color)
**	
**	@param	t		transparency
**	@param	r		red
**	@param	g		green
**	@param	b		blue
**	@return	int		color in 0xTTRRGGBB format
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief put one pixel to img 
 * 
 * @param img 	the mlx instance
 * @param row 	row index
 * @param col 	column index
 * @param color	color in 0xTTRRGGBB format
 */
void	my_mlx_pixel_put(t_data *img, int row, int col, int color)
{
	char	*dst;

	dst = img->addr + (row * img->llen + col * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief 	put row pixels to img 
 * 
 * @param img 	the mlx instance
 * @param row 	row index
 * @param color	color in 0xTTRRGGBB format
 */
void	my_mlx_row_put(t_data *img, int row, int color)
{
	unsigned int	*dst;
	int				i;

	i = 0;
	dst = (unsigned int *)(img->addr + row * img->llen);
	while (i < img->p->res_x)
		dst[i++] = color;
}

/**
 * @brief Get the pixel object from sprite
 * 
 * @param xpm 		sprite
 * @param row_sp	row index
 * @param diff 		fractional column index
 * @return int 		color in 0xTTRRGGBB format
 */
int	get_pixel(t_texture *xpm, int row_sp, float diff)
{
	int	*color;

	color = (int *)(xpm->addr + xpm->llen * row_sp
			+ (xpm->bpp / 8) * (int)(xpm->w * diff));
	return (*color);
}

/**
 * @brief preprocessing of all possible vectors for turning and throwing rays
 * 
 * @param img 	the mlx instance
 * @param p 	the structure with parameters
 */
void	pe4em_vectora(t_data *img, t_param *p)
{
	int		i;
	double	sin_step;
	double	cos_step;

	p->cnt_v = ft_max(360, p->res_x * 6);
	sin_step = sin(M_PI * 2 / p->cnt_v);
	cos_step = cos(M_PI * 2 / p->cnt_v);
	img->v = malloc(sizeof(*img->v) * p->cnt_v * 1.21);
	if (!img->v)
		ft_raise_error("Allocation error\n");
	i = 0;
	img->v[i].x = 1;
	img->v[i].y = 0;
	while (++i < p->cnt_v * 1.2)
	{
		img->v[i].x = img->v[i - 1].x;
		img->v[i].y = img->v[i - 1].y;
		rotate_by_ange(&img->v[i].x, &img->v[i].y, sin_step, cos_step);
		img->v[i].cx = 1 - 2 * (img->v[i].x < 0);
		img->v[i].cy = img->v[i].y / img->v[i].x * img->v[i].cx;
		img->v[i].ry = 1 - 2 * (img->v[i].y < 0);
		img->v[i].rx = img->v[i].x / img->v[i].y * img->v[i].ry;
	}
}
