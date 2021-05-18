#include "cub3d.h"

/*
**	@brief	just return minimal from two elements
**	
**	@param	a		DOC
**	@param	b		DOC
**	@return	int	first or second element
*/
int		ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int		ft_abs(int a)
{
	if (a > 0)
		return (a);
	return (-a);
}

float	ft_dist(float a, float b)
{
	return (sqrt(a * a + b * b));
}

void	rotate_by_ange(double *x, double *y, double sin_a, double cos_a)
{
	double	copy_x;

	copy_x = *x;
	*x = copy_x * cos_a - *y * sin_a;
	*y = copy_x * sin_a + *y * cos_a;
}