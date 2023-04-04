#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096LU
#endif

enum	e_ret
{
	RETURN_THE_LINE,
	CONTINUE_TO_READ,
	ERROR_OCCURED,
};

inline static int	__append_to_line(
	char *line,
	size_t *const line_size,
	char *const buffer)
{
	char	*newline;
	char	*dent;

	dent = line;
	newline = strchr(buffer, '\n');
	if (newline)
	{
		size_t const	append_len = newline - buffer;

		line = malloc((*line_size + append_len + 1) * sizeof(char));
		if (!line)
		{
			line = dent;
			return ERROR_OCCURED;
		}
		memcpy(line, dent, *line_size);
		memcpy(line + *line_size, buffer, append_len);
		*line_size += append_len;
		line[*line_size] = 0;
		++*line_size;
		return (RETURN_THE_LINE);
	}
	
}

char	*get_next_line(int const fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	size_t		line_size;
	ssize_t		read_ret;
	char		*line;
	int			ret;


	line_size = 0LU;
	line = NULL;
	if (*buffer)
	{
		ret = __append_to_line(line, &line_size, buffer);
		if (ret == ERROR_OCCURED)
			return NULL;
		if (ret == RETURN_THE_LINE)
			return line;
	}
}
