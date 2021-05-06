#include "cub3d.h"

void	ft_raise_error(char *s)
{
	ft_putstr_fd("Error\n", 2);
	if (s)
		ft_putstr_fd(s, 2);
	else
		perror(NULL);
	exit (1);
}

int		ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}

int		ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int		only_digits(char *s)
{
	while(*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		free(arr[i++]);
	free(arr);
}

int	char_in_str(char ch, char *charset)
{
	while (*charset)
		if (*charset++ == ch)
			return (1);
	return (0);
}