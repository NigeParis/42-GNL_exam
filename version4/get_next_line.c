/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:11:12 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/24 14:52:42 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;
	
	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_strcpy(char *copy, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
}

int		ft_strlen(char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str && str[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(char *(str))
{
	char *copy;
	int	 len;

	copy = NULL;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	copy = malloc(sizeof(char) * len + 1);
	if (!copy)
		return (NULL);
	ft_strcpy(copy, str);
	return (copy);
}

char *ft_strchr(char *str, char c)
{
	int i;

	i = 0;
	if (!str || !c)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] && str[i] == c)
			return (&str[i]);
		i++;
	}


	return (NULL);	
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *join;
	int len_s1;
	int len_s2;

	join = NULL;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!s1)
		return (ft_strdup(s2));
	join = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join)
		return (NULL);
	join[0] = '\0';
	ft_strcpy(join, s1);
	ft_strcpy(join + len_s1, s2);
	if (s1)
		free(s1);
	return (join);	
}


char	*get_next_line(int fd)
{
	static char buff[BUFFER_SIZE + 1];
	char *line;
	char *newline_pos;
	int	 endline_pos;
	int nbytes;

	line = ft_strdup(buff);
	newline_pos = NULL;
	endline_pos = 0;
	nbytes = 1;

	while (!(newline_pos = ft_strchr(line, '\n')) && nbytes)
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(line), NULL);
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	if (newline_pos != NULL)
	{
		endline_pos = newline_pos - line + 1;
		ft_strcpy(buff, newline_pos + 1);
	}
	else
	{
		endline_pos = ft_strlen(line);
		buff[0] = '\0';
	}
	line[endline_pos] = '\0';
	return (line);
}









int main(void)
{
	int fd = open("./test.txt", R_OK);
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}