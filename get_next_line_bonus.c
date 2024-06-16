/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacvrlja <nacvrlja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:16:48 by nacvrlja          #+#    #+#             */
/*   Updated: 2024/06/16 15:26:45 by nacvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char **freed)
{
	if (*freed != NULL)
	{
		free(*freed);
		*freed = NULL;
	}
}

char	*ft_reset_buf(char **buffer, int fd)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = NULL;
	while (buffer[fd][i] && buffer[fd][i] != '\n')
		i++;
	if (!buffer[fd][i])
	{
		ft_free(&buffer[fd]);
		return (NULL);
	}
	temp = malloc(ft_strlen(buffer[fd]) - i + 1);
	if (!temp)
		return (ft_free(&buffer[fd]), NULL);
	i++;
	j = 0;
	while (buffer[fd][i])
		temp[j++] = buffer[fd][i++];
	temp[j] = '\0';
	ft_free(&buffer[fd]);
	return (temp);
}

char	*ft_line(char **buffer, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (buffer[fd][i] && buffer[fd][i] != '\n')
		i++;
	if (buffer[fd][i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[fd][i] && buffer[fd][i] != '\n')
	{
		line[i] = buffer[fd][i];
		i++;
	}
	if (buffer[fd][i] == '\n')
	{
		line[i] = buffer[fd][i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char **buffer)
{
	char	*temp;
	char	*read_buffer;
	int		bytes_read;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (ft_free(&buffer[fd]), NULL);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(&read_buffer), ft_free(&buffer[fd]), NULL);
		read_buffer[bytes_read] = '\0';
		temp = buffer[fd];
		buffer[fd] = ft_strjoin(buffer[fd], read_buffer);
		if (!buffer[fd])
			return (ft_free(&read_buffer), ft_free(&temp), NULL);
		ft_free(&temp);
		if (bytes_read < BUFFER_SIZE || ft_strchr(buffer[fd], '\n'))
			break ;
	}
	ft_free(&read_buffer);
	return (buffer[fd]);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	buffer[fd] = ft_read(fd, buffer);
	if (!buffer[fd])
		return (NULL);
	if (!*buffer[fd])
		return (ft_free(&buffer[fd]), NULL);
	line = ft_line(buffer, fd);
	if (!line || !*line)
		return (ft_free(&buffer[fd]), NULL);
	buffer[fd] = ft_reset_buf(buffer, fd);
	return (line);
}
/*
#include <fcntl.h>
int main(void)
{
    int fd = open("new.txt", O_RDONLY);
	int fd2 = open("text.txt", O_RDONLY);
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
	 while ((line = get_next_line(fd2)) != NULL)
    {
        printf("%s", line);
        free(line); // Free the allocated memory for the line
    }
    close(fd);
	close(fd2);
    return (0);
}
*/