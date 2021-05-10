#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	int result;
	int i;

	i = 0;
	*line = malloc(4 * 1024 * 1024);
	while ((result = read(fd, *line + i, CONTENT_MIN_SIZE)))
	{
		if (result == -1)
			return (-1);
		if ((*line)[i] == '\n')
			break;
		i++;
	}
	(*line)[i] = 0;
	return ((result != 0));
}