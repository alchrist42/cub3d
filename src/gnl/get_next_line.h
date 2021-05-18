#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define CONTENT_MIN_SIZE 1
# define BUFFER_SIZE = 4096

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

int		get_next_line(int fd, char **line);

#endif