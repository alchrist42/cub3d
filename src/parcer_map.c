#include "cub3d.h"

void	check_line_map(char *s, t_params *p)
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
			if (p->plr->x != -1)
				ft_raise_error("Double player position in the map");
			p->plr->x = p->h_map + 1;
			p->plr->y = i + 1;
		}
		i++;
	}
	p->h_map++;
	ft_lstadd_back(&p->lst_map, ft_lstnew(ft_strdup(s)));
}

void	create_map(t_params *p)
{
	int	i;
	t_list	*list_elem;
	
	printf("Create map...\n");
	p->w_map += 2;
	p->h_map += 2;
	p->map = malloc(sizeof(*p->map) * p->h_map);
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

void	check_field(t_params *p)
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
				printf("[%d,%d] %s \n", i, j, p->map[i] + 2);	
				ft_raise_error("Hole in the field\n");
			}
		}
	}
}