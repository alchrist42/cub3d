#include "cub3d.h"

/*
**	@brief	runs different check for file with parametrs and map. 
**			Create map from file
**	
**	@param	argc	number of arguments
**	@param	argv	array of arguments
**	@param	p		pointer to structure to save different parametrs from file
**	@return	int		always zero now
*/
int		parcer(int argc, char **argv, t_param *p)
{
	int	fd;
	
	fd = parsing_args(argc, argv, p);
	inicialise_params(p);
	parsing_params(fd ,p);
	if (!p->got_param || !p->h_map)
		ft_raise_error("Missing params or map");
	printf("GOOD PARSING\n");
	create_map(p);
	check_field(p);
	printf("GOOD MAP\n");
	close (fd);
	// sleep(20);
	return (0);
}

/*
**	@brief	checks right number of arguments and their format
**	
**	@param	argc		number of arguments
**	@param	argv		array of arguments
**	@param	p			pointer to structure to save different parametrs
**	@return	int			file desciptor
*/
int		parsing_args(int argc, char **argv, t_param *p)
{
	int	fd;
	int	len_fname;

	if (argc != 2 && argc != 3)
		ft_raise_error("Incorrect arguments. use 'cub3d filename [--save]'\n");
	len_fname = ft_strlen(argv[1]);
	if (len_fname < 4 || ft_strncmp(argv[1] + (len_fname -  4), ".cub", 5))
		ft_raise_error("File map should be by mask *.cub\n");

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_raise_error(NULL);
	
	p->save = false;
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			ft_raise_error("Second parametr should be '--save'\n");
		p->save = true;
	}
	return (fd);
}

/*
**	@brief	inicialise structure for parametrs
**	
**	@param	p	pointer to structure to save different parametrs from file
*/
void	inicialise_params(t_param *p)
{
	p->got_cel = false;
	p->got_floor = false;
	p->got_res = false;
	p->got_param = false;
	p->save = false;
	p->end_map = 0;
	p->lst_map = NULL;
	p->h_map = 0;
	p->w_map = 0;
	p->plr_x = 0;
	p->plr_y = 0;
}

/*
**	@brief	reads line by line from file and runs parsing for each
**	
**	@param	fd		file descriptor
**	@param	p		pointer to structure to save different parametrs
*/
void	parsing_params(int fd, t_param *p)
{
	char	*line;
	int		res;

	res = 1;
	line = NULL;
	while (res)
	{
		res = get_next_line(fd, &line);
		if (res < 0)
			ft_raise_error(NULL);
		if (!ft_strlen(line) && p->h_map && !p->end_map)
				p->end_map = true;			
		if (ft_strlen(line))
		{
			if (p->end_map)
				ft_raise_error("Empty line in map structure\n");
			if (p->got_param)
				check_line_map(line, p);
			else
				parsing_line(line, p);
		}
		free(line);
	}
}

/*
**	@brief	check first few symbols in line and runs hundlers
**	
**	@param	s		pointer to string
**	@param	p		pointer to structure to save different parametrs
*/
void	parsing_line(char *s, t_param *p)
{
	if (!ft_strncmp(s, "R ", 2))
		get_resolution(s + 2, p);
	else if (!ft_strncmp(s, "F ", 2) || !ft_strncmp(s, "C ", 2))
		get_colors(s + 2, !ft_strncmp(s, "F ", 2), p);
	else if (!(ft_strncmp(s, "NO ", 3) && ft_strncmp(s, "SO ", 3) && ft_strncmp(s, "EA ", 3) && ft_strncmp(s, "WE ", 3) && ft_strncmp(s, "S ", 2)))
		get_texture(s, p);
	else
	{
		printf("cel %d , floor %d, res %d , %s + %s + %s + %s + %s\n", p->got_cel, p->got_floor,p->got_res , p->t_so ,p->t_we ,p->t_no , p->t_ea , p->t_sp);
		ft_raise_error(ft_strjoin("Cannot parse string: ", s));
	}
	p->got_param = (p->got_cel && p->got_floor && p->got_res && p->t_so && p->t_we && p->t_no && p->t_ea && p->t_sp);
}	
