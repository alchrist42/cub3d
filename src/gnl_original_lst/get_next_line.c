#include "get_next_line.h"

/*
**	@brief	finds or create new list for specific file descriptor
**	
**	@param	begin		address pointer to begin list_fds
**	@param	fd			file descriptor
**	@return	t_gnlst*		pointer to list
*/
t_gnlst	*ft_find_or_create_elem(t_gnlst **begin, int fd)
{
	t_gnlst	*current;

	current = ft_lstfind(*begin, fd);
	if (current)
		return (current);
	current = ft_glstnew(fd);
	if (!current)
		return (NULL);
	ft_glstadd_front(begin, current);
	return (current);
}

/*
**	@brief	copy source string to dest string, not more than dstsize - 1.
**			than null terminate dest.
**	
**	@param	dst		pointer to string
**	@param	src		pointer to string
**	@param	dstsize		count bytes to copy + 1 for null terminate
**	@return	size_t	lenght src string
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (dst && i + 1 < dstsize)
			dst[i] = src[i];
		i++;
	}
	if (dstsize && dst)
	{
		if (dstsize - 1 < i)
			dst[dstsize - 1] = 0;
		else
			dst[i] = 0;
	}
	return (i);
}

/*
**	@brief	contactenates the string from lists content
**	
**	@param	begin_flow		address the pointer to begin list
**	@param	flow		pointer to begin list
**	@param	line		address the pointer to string
**	@return	int	1 if create the string succes, else -1
*/
int	ft_create_line(t_gnlst **begin_flow, t_gnlst *flow, char **line)
{
	char	*temp;
	char	*dst;

	*line = malloc(sizeof(**line) * ((*begin_flow)->lenght + 1));
	if (!*line)
		return (ft_glstclear(&(*begin_flow)->flow) - 1);
	dst = *line;
	while (flow->flow)
	{
		dst += ft_strlcpy(dst, flow->content + flow->start,
				flow->end - flow->start + 1);
		flow = flow->flow;
	}
	(*begin_flow)->start = flow->start + 1 + ft_strlcpy(dst,
			flow->content + flow->start, flow->end - flow->start + 1);
	(*begin_flow)->end = flow->end;
	(*begin_flow)->lenght = 0;
	if (*begin_flow != flow)
	{
		temp = (*begin_flow)->content;
		(*begin_flow)->content = flow->content;
		flow->content = temp;
	}
	return (ft_glstclear(&(*begin_flow)->flow) + 1);
}

/*
**	@brief	finds first occurense '\n' in list
**	
**	@param	begin_flow		address the pointer to begin list
**	@param	flow		address the pointer to begin list
**	@param	lenght		address the pointer to current list
**	@param	line		address the pointer to string
**	@return	int	1 if new line found and created new string,
**				0 if new line not found,
**				-1 of allocation memory error
*/
int	ft_check_buf(t_gnlst **begin_flow, t_gnlst **flow, int lenght, char **line)
{
	if (lenght > 0)
		(*flow)->end += lenght;
	while ((*flow)->start + (*flow)->lenght < (*flow)->end)
	{
		if ((*flow)->content[(*flow)->start + (*flow)->lenght] == '\n')
		{
			(*flow)->content[(*flow)->start + (*flow)->lenght] = 0;
			return (ft_create_line(begin_flow, *begin_flow, line));
		}
		(*flow)->lenght++;
		(*begin_flow)->lenght += (*begin_flow != *flow);
	}
	if ((*flow)->buffer_size - (*flow)->end < BUFFER_SIZE)
	{
		(*flow)->flow = ft_glstnew((*flow)->fd);
		*flow = (*flow)->flow;
	}
	return (0);
}

/*
**	@brief	Get the next line from file by file descriptor
**	
**	@param	fd		file descriptor
**	@param	line	address to pointer string
**	@return	int		1 if file read and string found,
**					0 if file ended,
**					-1 if any error.
*/
int	get_next_line(int fd, char **line)
{
	static t_gnlst	*begin_fds;
	t_gnlst			*begin_flow;
	t_gnlst			*flow;
	int				readen;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	begin_flow = ft_find_or_create_elem(&begin_fds, fd);
	flow = begin_flow;
	if (!begin_fds || !flow)
		return (-1);
	readen = -1;
	while (true)
	{
		readen = ft_check_buf(&begin_flow, &flow, readen, line);
		if (readen == -1 || readen == 1)
			return (readen);
		readen = (read(fd, flow->content + flow->end, BUFFER_SIZE));
		if (!readen && (flow != begin_flow || flow->start <= flow->end))
			ft_create_line(&begin_flow, begin_flow, line);
		if (!readen || readen < 0)
			return (ft_lst_delflow(&begin_fds, begin_flow) + readen);
	}
}
