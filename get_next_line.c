/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacvrlja <nacvrlja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:16:48 by nacvrlja          #+#    #+#             */
/*   Updated: 2024/06/16 15:23:26 by nacvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **freed)
{
	if (*freed != NULL)
	{
		free(*freed);
		*freed = NULL;
	}
}

char	*ft_reset_buf(char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		ft_free(&buffer);
		return (NULL);
	}
	temp = malloc(ft_strlen(buffer) - i + 1);
	if (!temp)
		return (ft_free(&buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		temp[j++] = buffer[i++];
	temp[j] = '\0';
	ft_free(&buffer);
	return (temp);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *buffer)
{
	char	*temp;
	char	*read_buffer;
	int		bytes_read;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (ft_free(&buffer), NULL);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(&read_buffer), ft_free(&buffer), NULL);
		read_buffer[bytes_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, read_buffer);
		if (!buffer)
			return (ft_free(&read_buffer), ft_free(&temp), NULL);
		ft_free(&temp);
		if (bytes_read < BUFFER_SIZE || ft_strchr(buffer, '\n'))
			break ;
	}
	ft_free(&read_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
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
	if (!*buffer)
		return (ft_free(&buffer), NULL);
	line = ft_line(buffer);
	if (!line || !*line)
		return (ft_free(&buffer), NULL);
	buffer = ft_reset_buf(buffer);
	return (line);
}
/*
#include <fcntl.h>
int main(void)
{
    int fd = open("new.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return (1);
    }

    char *line;
	//line = get_next_line(0);
	//printf("%s", line);
	//free(line);
	
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Free the allocated memory for the line
    }
    close(fd);
    return (0);
}
*/