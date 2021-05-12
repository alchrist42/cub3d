#include "cub3d.h"

/*
**	@brief	checks line of map for bad charaters and puts it to list structure
**	
**	@param	s		pointer to string
**	@param	p		pointer to structure with parametrs
*/
void	check_line_map(char *s, t_param *p)
{
	int	i;

	if ((int)ft_strlen(s) > p->w_map)
		p->w_map = ft_strlen(s);
	printf("map |%s\n", s);
	i = 0;
	while (s[i])
	{
		if (!char_in_str(s[i], " 012NEWS"))
			ft_raise_error("Bad character in the map\n");
		if (char_in_str(s[i], "NEWS"))
		{
			if (p->plr_x)
				ft_raise_error("Double player position in the map");
			p->plr_y = p->h_map + 1;
			p->plr_x = i + 1;
		}
		i++;
	}
	p->h_map++;
	ft_lstadd_back(&p->lst_map, ft_lstnew(ft_strdup(s)));
	printf("lst |%s\n", ft_lstlast(p->lst_map)->content);
}

/*
**	@brief	Create a map object from list structure
**	
**	@param	p		pointer to structure with parametrs
*/
void	create_map(t_param *p)
{
	int	i;
	t_list	*list_elem;
	
	p->w_map += 2;
	p->h_map += 2;
	p->map = malloc(sizeof(*p->map) * p->h_map);
	// printf("allocate. w:%i, h:%i, mem( %zu ** )\n", p->w_map, p->h_map, sizeof(*p->map));
	if (!p->map)
		ft_raise_error("Cannot allocate\n");
	i = 0;
	list_elem = p->lst_map;
	while (i < p->h_map)
	{
		p->map[i] = ft_calloc(p->w_map, sizeof(**p->map));
		if (!p->map[i])
			ft_raise_error("Cannot allocate\n");
		if (i != 0 && i != (p->h_map - 1))
		{
			ft_strlcpy(p->map[i] + 1, list_elem->content, p->w_map);
			list_elem = list_elem->next;
		}
		i++;
	}
	ft_lstclear(&p->lst_map, free);
}

/*
**	@brief	searches for unenclosed areas on the map
**	
**	@param	p		pointer to structure with parametrs
*/
void	check_field(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	while (++i < p->h_map - 1)
	{
		j = 0;
		while (++j < p->w_map - 1)
		{
			if (char_in_str(p->map[i][j], "02NEWS")
					&& (!p->map[i + 1][j] || p->map[i + 1][j] == ' '
					|| !p->map[i - 1][j] || p->map[i - 1][j] == ' '
					|| !p->map[i][j + 1] || p->map[i][j + 1] == ' '
					|| !p->map[i][j - 1] || p->map[i][j - 1] == ' '))
			{
				// for (int z = 0; z < p->w_map; z++)
				// {
				// 	printf("|%i|", z % 10);
				// }
				// printf("\n");
				// for (int z = 0; z < p->w_map; z++)
				// {
				// 	printf("|%c|", p->map[i - 1][z]);
				// }
				// printf("\n");
				// for (int z = 0; z < p->w_map; z++)
				// {
				// 	printf("|%c|", p->map[i][z]);
				// }
				// printf("\n");
				// for (int z = 0; z < p->w_map; z++)
				// {
				// 	printf("|%c|", p->map[i + 1][z]);
				// }
				// printf("\n");
				// printf("4 cells: |%c,%c,%c,%c|\n", p->map[i + 1][j], p->map[i - 1][j], p->map[i][j + 1], p->map[i][j - 1]);
				printf("[%d,%d] %s \n", i, j, p->map[i] + 2);	
				ft_raise_error("Hole in the field\n");
			}
		}
	}
}