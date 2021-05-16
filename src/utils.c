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