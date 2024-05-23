/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacvrlja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:31:51 by nacvrlja          #+#    #+#             */
/*   Updated: 2024/05/23 18:12:26 by nacvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

// free the read_buffer
char	*ft_free(char *buffer, char *read_buffer)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, read_buffer);
	free(read_buffer);
	return (tmp);
}

// read the file
char	*ft_read(int fd, char *read_buffer)
{
	int	bytes_read;

	read_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1;
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	read_buffer[bytes_read] = '\0';
}

// put the line 
char	*ft_line(char *buffer)
{
	int	i;
	char	*line;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	i = 0;
	while (buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

// reset the buffer to start after the \n
char	*ft_reset(char *buffer)
{
	int	i;
	int	j;
	char	*new_line

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_line = malloc(sizeof(char) * ft_strlen(buffer) - i + 1);
	i++;
	while (buffer[i])
	{
		new_line[j++] = buffer[i++];
		free(buffer);
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;


}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_buffer;
	char		*line;
	ssize_t		bytes_read;
	size_t		length;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return NULL;
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(read_buffer);
		return NULL;
	}
	ft_strjoin(buffer, read_buffer);
	while ((line = strchr(buffer, '\n')) != NULL)
	{
		length = line - read_buffer + 1;
		line = malloc(length + 1);
		if (!line)
		{
			free(buffer);
			return NULL;
		}
	}
	strncpy(line, buffer, length);
	line[length] = '\0';
	// is there a new line in static buffer
	// if yes => break out of loop
	// if no => read again
	// get a the string to return with the new line
	// reset the buffer, so it will contain everything after the first new line
	// 
	return (line);
}

int	main(void)
{
	char *line = get_next_line(open("text.txt", O_RDONLY));
	close (open("text.txt", O_RDONLY));
}
