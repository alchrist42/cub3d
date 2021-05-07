#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/errno.h>

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"

// # define DEBUG 1

// # define KEY_S 1
// # define KEY_A 0
// # define KEY_D 2
// # define KEY_W 13

// # define KEY_UP 126
// # define KEY_DW 125
// # define KEY_L 123
// # define KEY_R 124

// # define KEY_ESC 53

typedef struct	s_krd
{
	int	x;
	int	y;
	int	z;
}	t_krd;

typedef struct s_params
{
	int		res_x;
	int		res_y;
	char	*t_no;
	char	*t_so;
	char	*t_we;
	char	*t_ea;
	char	*t_sp;
	int		floor[3];
	int		cel[3];
	bool	got_res;
	bool	got_floor;
	bool	got_cel;
	bool	got_params;

	bool	end_map;
	int		h_map;
	int		w_map;
	t_list	*lst_map;
	char	**map;

	t_krd	*plr;
	bool	save;
}	t_params;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		end;
}				t_data;

void	ft_raise_error(char *s);

int		ft_arrlen(char **arr);
int		ft_min(int a, int b);
int		only_digits(char *s);
void	ft_free_split(char **arr);
int		char_in_str(char ch, char *charset);

void	inicialise_params(t_params *p);
int		parcer(int argc, char **argv, t_params *p);
int		parsing_args(int argc, char **argv, t_params *p);
void	parsing_params(int fd, t_params *p);
void	parsing_line(char *s, t_params *p);

void	get_resolution(char *s, t_params *p);
void	get_colors(char *s, bool is_floor, t_params *p);
void	get_texture(char *s, t_params *p);

void	check_line_map(char *s, t_params *p);
void	create_map(t_params *p);
void	check_field(t_params *p);

void	create_window(t_params *p);
int		close_win(int keycode, t_data *img);

int		create_trgb(int t, int r, int g, int b);
void	correct_resolution(t_data *img, t_params *p);

#endif
