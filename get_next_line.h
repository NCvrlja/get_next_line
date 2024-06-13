/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxnotebook <maxnotebook@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:30:43 by nacvrlja          #+#    #+#             */
/*   Updated: 2024/06/12 10:07:36 by maxnotebook      ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 5

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_reset_buf(char *buffer);
char	*ft_line(char *buffer);
char	*ft_read(int fd, char *read_buffer);
char	*ft_free(char *buffer, char *read_buffer);
int	bufferhasnonewline(char *buffer);

#endif 
