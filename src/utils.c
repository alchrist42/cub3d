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

int		ft_abs(int a)
{
	if (a > 0)
		return (a);
	return (-a);
}