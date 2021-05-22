#include "cub3d_bonus.h"

/*
 * @brief	gets len the nullterminated array of string
 * 
 * @param arr	pointer to array
 * @return int	count strings in array
 */
int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/*
**	@brief	tests strings consist only digits
**	
**	@param	s	pointer to string
**	@return	int	0 if test fail, else 1
*/
int	only_digits(char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

/*
**	@brief	free array, goten by split
**	
**	@param	arr	pointer to array of strings
*/
void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
**	@brief	checks if there is a character in the string
**	
**	@param	ch		character
**	@param	charset	pointer to set characters (string)
**	@return	int		0 if checks fail, else 1
*/
int	char_in_str(char ch, char *charset)
{
	while (*charset)
		if (*charset++ == ch)
			return (1);
	return (0);
}
