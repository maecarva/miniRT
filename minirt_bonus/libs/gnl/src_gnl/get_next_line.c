/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:56:21 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/02 22:23:50 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_all(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (NULL);
}

static char	*ft_read_save(int fd, char **buffer)
{
	char	*tmp;
	char	*new_buffer;
	ssize_t	r;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (ft_free_all(buffer, NULL));
	r = 1;
	while (r > 0 && ft_isline(*buffer) == 0)
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r == -1)
			return (ft_free_all(buffer, &tmp));
		tmp[r] = '\0';
		new_buffer = ft_strjoin(*buffer, tmp);
		if (!new_buffer)
			return (ft_free_all(buffer, &tmp));
		free(*buffer);
		*buffer = new_buffer;
	}
	free(tmp);
	return (*buffer);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i-- > 0)
		line[i] = buffer[i];
	return (line);
}

static char	*ft_modify_buffer(char **buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	j = 0;
	while ((*buffer)[i + j])
		j++;
	new_buffer = malloc(sizeof(char) * (j + 1));
	if (!new_buffer)
		return (ft_free_all(buffer, NULL));
	j = 0;
	while ((*buffer)[i + j])
	{
		new_buffer[j] = (*buffer)[i + j];
		j++;
	}
	new_buffer[j] = '\0';
	ft_free_all(buffer, NULL);
	*buffer = new_buffer;
	return (*buffer);
}
/*
This new gnl does the same as before.
But instead of returning line, it takes line in argument and returns
an int telling if the alloction worked or not.
42 = malloc issue.
0 = everything works.
1 = issue with the fd or the line or with the buffer's size.
*/

int	get_next_line(int fd, char **line)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (ft_free_all(&buffer, NULL), EXIT_FAILURE);
	if (line && (*line))
		ft_free_all(NULL, line);
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * 1);
		if (!buffer)
			return (ERROR_CODE);
		buffer[0] = '\0';
	}
	if (!ft_read_save(fd, &buffer))
		return (ft_free_all(&buffer, NULL), ERROR_CODE);
	(*line) = ft_get_line(buffer);
	if (!(*line))
		return (ft_free_all(&buffer, line), ERROR_CODE);
	if (*(*line) == '\0')
		return (ft_free_all(&buffer, line), EXIT_FAILURE);
	if (!ft_modify_buffer(&buffer))
		return (ft_free_all(NULL, line), ERROR_CODE);
	if (buffer[0] == '\0')
		ft_free_all(&buffer, NULL);
	return (0);
}
