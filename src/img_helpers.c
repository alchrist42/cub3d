#include "cub3d.h"
#include	"mlx.h"

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
}

