/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_safe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:27:36 by tfreydie          #+#    #+#             */
/*   Updated: 2024/09/16 17:59:50 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*secure_init(int *line_status, int fd, int *status);
static char	*check(char *line, char *buffer, int *line_status, int *status);
static int	safe_read(char *line, char *buffer, int fd);
static char	*join_and_free(char *line, char *buffer, int *status);

char	*get_next_line_safe(int fd, int *status)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;
	int			line_status;

	line = secure_init(&line_status, fd, status);
	if (!line)
		return (free_and_null(line));
	if (buffer[0])
	{
		line = check(line, buffer, &line_status, status);
		if (line_status)
			return (line);
	}
	bytes_read = safe_read(line, buffer, fd);
	while (bytes_read)
	{
		if (bytes_read < 0)
			return (NULL);
		line = check(line, buffer, &line_status, status);
		if (line_status)
			return (line);
		bytes_read = safe_read(line, buffer, fd);
	}
	return (final_check(line));
}

static void	*secure_init(int *line_status, int fd, int *status)
{
	char	*line;

	if (fd < 0)
		return (NULL);
	*line_status = 1;
	if (BUFFER_SIZE + 1 <= 0)
		return (NULL);
	line = malloc(1);
	if (!line)
	{
		*status = 1;
		return (NULL);
	}
	line[0] = '\0';
	return (line);
}

static char	*check(char *line, char *buffer, int *line_status, int *status)
{
	int	i;

	line = join_and_free(line, buffer, status);
	i = 0;
	*line_status = 1;
	if (!line)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		ft_memmove(buffer, &buffer[i], ft_strlen(&buffer[i]) + 1);
		return (line);
	}
	*line_status = 0;
	return (line);
}

static int	safe_read(char *line, char *buffer, int fd)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		ft_memset(buffer, 0, BUFFER_SIZE);
		free(line);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*join_and_free(char *line, char *buffer, int *status)
{
	char	*new_line;
	int		linelen;
	int		effective_bufferlen;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	effective_bufferlen = i + (buffer[i] == '\n');
	linelen = ft_strlen(line);
	new_line = malloc(sizeof(char) * (linelen + effective_bufferlen + 1));
	if (!new_line)
	{
		*status = 1;
		return (free_and_null(line));
	}
	new_line[linelen + effective_bufferlen] = '\0';
	i = -1;
	while (++i < linelen)
		new_line[i] = line[i];
	j = 0;
	while (j < effective_bufferlen)
		new_line[i++] = buffer[j++];
	return (free(line), new_line);
}
