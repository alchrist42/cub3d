#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define CONTENT_MIN_SIZE 4096
# define BUFFER_SIZE 4096

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_gnlst
{
	int				fd;
	size_t			lenght;
	size_t			start;
	size_t			end;
	size_t			buffer_size;
	char			*content;
	struct s_gnlst	*flow;
	struct s_gnlst	*next;
}					t_gnlst;

int		get_next_line(int fd, char **line);

t_gnlst		*ft_find_or_create_elem(t_gnlst **begin, int fd);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_create_line(t_gnlst **begin_flow, t_gnlst *flow, char **line);
int			ft_check_buf(t_gnlst **begin_flow, t_gnlst **flow,
			int lenght, char **line);

t_gnlst		*ft_glstnew(int fd);
void		ft_glstadd_front(t_gnlst **lst, t_gnlst *new);
t_gnlst		*ft_lstfind(t_gnlst *begin_list, int fd);
int			ft_glstclear(t_gnlst **lst);
int			ft_lst_delflow(t_gnlst **begin, t_gnlst *begin_flow);

#endif