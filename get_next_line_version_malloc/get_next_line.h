/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:05:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/28 13:35:39 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_strcpy(char *copy, char *str);
int		ft_strlen(char *str);
char	*ft_strdup(char *(str));
char *ft_strchr(char *str, char c);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);


#endif