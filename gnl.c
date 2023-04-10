#include "gnl.h"

void *ft_memcpy(char *dest, char *src, int dest_len)
{
	int i = 0;
	while (i < dest_len && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char *ft_strjoin(char *a, char *b, size_t len_a, size_t len_b)
{
	char *ret;

	ret = malloc(sizeof(char) * (len_a + len_b));
	if (!ret)
		return (free(a), NULL);
	ft_memcpy(ret, a, len_a);
	ft_memcpy(ret + len_a, b, len_b);
	free(a);
	return (ret);
}

size_t ft_strnchr(char *str, char c, int n)
{
	int i = 0;

	while (str[i] && i < n && str[i] != c)
		i++;
	if (i < n && str[i] == c)
		return (i);
	return (-1);
}

static inline void __clean_buffer(char *buffer, size_t *size_buffer, size_t newline)
{
	*size_buffer -= newline + 1;
	ft_memcpy(buffer, buffer + newline + 1, *size_buffer);
}

static inline int __append_to_line(char *buffer, size_t *size_buffer, char **line, ssize_t size_read)
{
	size_t newline = ft_strnchr(buffer, '\n', *size_buffer);
	static int size_line = 0;

	if (newline == -1)
	{
		if (!*line)
		{
			*line = malloc(sizeof(char) * *size_buffer);
			if (!*line)
				return (*line = NULL, ERROR_OCCURED);
			ft_memcpy(*line, buffer, *size_buffer);
			size_line = *size_buffer;
		}
		else
		{
			*line = ft_strjoin(*line, buffer, size_line, *size_buffer);
			if (!*line)
				return (*line = NULL, ERROR_OCCURED);
			size_line += *size_buffer;
		}
		if (size_read != BUFFER_SIZE)
		{
			*line = ft_strjoin(*line, "\0", size_line, 1);
			if (!*line)
				return (*line = NULL, ERROR_OCCURED);
			size_line = 0;
			return (RETURN_THE_LINE);
		}
		return (CONTINUE_TO_READ);
	}
	else
	{
		if (!*line)
		{
			*line = malloc(sizeof(char) * (newline + 2));
			if (!*line)
				return (*line = NULL, ERROR_OCCURED);
			ft_memcpy(*line, buffer, newline + 1);
			(*line)[newline + 1] = '\0';
		}
		else
		{
			*line = ft_strjoin(*line, buffer, size_line, newline + 2);
			if (!*line)
				return (*line = NULL, ERROR_OCCURED);
			(*line)[size_line + newline + 1] = '\0';
		}
		size_line = 0;
		__clean_buffer(buffer, size_buffer, newline);
		return (RETURN_THE_LINE);
	}
	return (CONTINUE_TO_READ);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE] = {0};
	static size_t size_buffer = 0;
	ssize_t size_read = BUFFER_SIZE;
	char *line = NULL;
	int return_status = CONTINUE_TO_READ;

	while (return_status == CONTINUE_TO_READ)
	{
		if (size_buffer != 0)
		{
			return_status = __append_to_line(buffer, &size_buffer, &line, size_read);
			if (return_status == ERROR_OCCURED)
				return (free(line), NULL);
		}
		if (return_status == CONTINUE_TO_READ)
		{
			size_read = read(fd, buffer, BUFFER_SIZE);
			if (size_read < 0)
				return (free(line), NULL);
			size_buffer += size_read;
		}
		if (size_read == 0)
			return (line);
	}
	return (line);
}

int main(int ac, char **av)
{
	int fd = open(av[1], O_RDWR);
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
