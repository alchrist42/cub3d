#include "cub3d.h"

/*
**	@brief	Get the resolution object from the string
**	
**	@param	s		pointer to string
**	@param	p		pointer to structure to save different parametrs
*/
void	get_resolution(char *s, t_param *p)
{
	char **arr;

	if (p->got_res)
		ft_raise_error("Dublicate resolution string\n");
	arr = ft_split_set(s, ", ");
	if (ft_arrlen(arr) != 2 || !only_digits(arr[0]) || !only_digits(arr[1]))
		ft_raise_error("Incorrect string of parameters in resolution\n");
	arr[0][ft_min(ft_strlen(arr[0]), 9)] = 0;
	arr[1][ft_min(ft_strlen(arr[1]), 9)] = 0;
	p->res_x = ft_atoi(arr[0]);
	p->res_y = ft_atoi(arr[1]);
	if (!p->res_x || !p->res_y)
		ft_raise_error("Zero resolution in parametrs\n");
	if (DEBUG)
		printf("get R from %s.... got: x = %d, y = %d\n", s, p->res_x, p->res_y);
	p->got_res = true;
	ft_free_split(arr);
}

/*
**	@brief	saves color to structure
**	
**	@param	color		array[3] for RGB
**	@param	is_floor	
**	@param	p		pointer to structure to save different parametrs
*/
void	put_colors_to_params(int *color, bool is_floor, t_param *p)
{
	int	i;
	
	i = -1;
	if (is_floor)
	{
		if (p->got_floor)
			ft_raise_error("Dublicate floor color string\n");
		while (++i < 3)
			p->floor[i] = color[i];
		p->got_floor = true;
	}
	else
	{
		if (p->got_cel)
			ft_raise_error("Dublicate celling color string\n");
		while (++i < 3)
			p->cel[i] = color[i];
		p->got_cel = true;
	}
}

/*
**	@brief	Get the colors object from the string
**	
**	@param	s			pointer to string
**	@param	is_floor		DOC
**	@param	p		pointer to structure to save different parametrs
*/
void	get_colors(char *s, bool is_floor, t_param *p)
{
	char	**arr;
	int		color[3];
	int		i;

	arr = ft_split_set(s, ", ");
	if (ft_arrlen(arr) != 3 || !only_digits(arr[0]) || !only_digits(arr[1])
			|| !only_digits(arr[2]) || ft_strlen(arr[0]) > 3
			|| ft_strlen(arr[1]) > 3 || ft_strlen(arr[2]) > 3)
		ft_raise_error("Incorrect parameters in color\n");
	i = -1;
	while (++i < 3)
		color[i] = ft_atoi(arr[i]);
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		ft_raise_error("Incorrect color code\n");
	put_colors_to_params(color, is_floor, p);
	if (DEBUG)
		printf("get colors from %s\n", s);
	ft_free_split(arr);
}

/*
**	@brief	Get texture objects from the string
**	
**	@param	s		pointer to string
**	@param	p		pointer to structure to save different parametrs
*/
void	get_texture(char *s, t_param *p)
{
	int	fd;

	fd = open(s + 2, O_RDONLY);
	// if (fd < 0)
	// 	ft_raise_error("Missing texture file\n");
	if (!ft_strncmp(s, "NO ", 3))
		p->t_no = ft_strdup(s + 3); //todo del strdup
	else if (!ft_strncmp(s, "SO ", 3))
		p->t_so = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "WE ", 3))
		p->t_we = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "EA ", 3))
		p->t_ea = ft_strdup(s + 3);
	else if (!ft_strncmp(s, "S ", 2))
		p->t_sp = ft_strdup(s + 2);
	else
		ft_raise_error("Impossible error!\n");
	s[2] = 0;
	if (DEBUG)
		printf("get TEXTURE %i for %s from %s\n", fd, s, s + 3);
}