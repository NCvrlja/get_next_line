/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacvrlja <nacvrlja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:31:51 by nacvrlja          #+#    #+#             */
/*   Updated: 2024/05/25 23:25:04 by nacvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// free the read_buffer
char	*ft_free(char *buffer, char *read_buffer)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, read_buffer);
	free(buffer);
	return (tmp);
}

// read the file
char	*ft_read(int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*read_buffer;

	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	read_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	read_buffer[bytes_read] = '\0';
	buffer = ft_free(buffer, read_buffer);
	return (buffer);
}

// put the line 
char	*ft_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

// reset the buffer to start after the \n
char	*ft_reset_buf(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_line(buffer);
	buffer = ft_reset_buf(buffer);
	return (line);
}
/*
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
	line[length] = '\0';
	// is there a new line in static buffer
	// if yes => break out of loop
	// if no => read again
	// get a the string to return with the new line
	// reset the buffer, so it will contain everything after the first new line
	// 
	return (line);
} */
#include <fcntl.h>
int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return (1);
    }

    char *line;
	/*line = get_next_line(0);
	printf("%s", line);
	free(line);
	*/
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Free the allocated memory for the line
    }
    close(fd);
    return (0);
}
