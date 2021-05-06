#include "get_next_line.h"

/*
**	@brief	creates new list element
**	
**	@param	fd		file descriptor
**	@return	t_gnlst*	pointer to new element or NULL if allocation fail
*/
t_gnlst	*ft_glstnew(int fd)
{
	t_gnlst	*elem;

	elem = (t_gnlst *)malloc(sizeof(*elem));
	if (elem)
	{
		elem->fd = fd;
		elem->lenght = 0;
		elem->start = 0;
		elem->end = 0;
		elem->flow = NULL;
		elem->next = NULL;
		if (BUFFER_SIZE < CONTENT_MIN_SIZE / 4)
			elem->buffer_size = CONTENT_MIN_SIZE;
		else
			elem->buffer_size = BUFFER_SIZE;
		elem->content = malloc(sizeof(*elem->content)
				* (elem->buffer_size + 1));
		if (!elem->content)
		{
			free(elem);
			return (NULL);
		}
		elem->content[elem->buffer_size] = 0;
	}
	return (elem);
}

/*
**	@brief	adds the element ’new’ at the beginning of the list
**	
**	@param	lst		pointer to list
**	@param	new		pointer to new element
*/
void	ft_glstadd_front(t_gnlst **lst, t_gnlst *new)
{
	new->next = *lst;
	*lst = new;
}

/*
**	@brief	find element in list by fd
**	
**	@param	begin_list	pointer to list begin
**	@param	fd			file descriptor
**	@return	t_gnlst*		pointer to found element
*/
t_gnlst	*ft_lstfind(t_gnlst *begin_list, int fd)
{
	while (begin_list)
	{
		if (begin_list->fd == fd)
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (NULL);
}

/*
**	@brief	removes one element from the list 
**	
**	@param	lst		addres to pointer the element
**	@return	int		0
*/
int	ft_glstclear(t_gnlst **lst)
{
	t_gnlst	*next;

	while (*lst)
	{
		next = (*lst)->flow;
		free((*lst)->content);
		free(*lst);
		*lst = next;
	}
	return (0);
}

/*
**	@brief	searches and deletes sublist int the list
**	
**	@param	begin		address to pointer the begin list
**	@param	begin_flow	pointer to the element - begin of sublist
**	@return	int			0 if delete succes, else -1
*/
int	ft_lst_delflow(t_gnlst **begin, t_gnlst *begin_flow)
{
	t_gnlst	*previous;
	t_gnlst	*current;

	previous = NULL;
	current = *begin;
	while (current)
	{
		if (current == begin_flow)
		{
			if (previous)
				previous->next = current->next;
			else
				*begin = current->next;
			ft_glstclear(&current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (-1);
}
