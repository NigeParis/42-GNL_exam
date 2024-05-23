/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:52:42 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/23 12:25:57 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		ft_putchar(str[i]);
		i++;
	}		
}

int	ft_strlen(char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str && str[len])
		len++;
	return (len);
}

char *ft_strchr(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (&str[i]);
		i++;
	}
return (0);
}

void	ft_strcpy(char *copy, const char *str)
{
	int	i;
	
	i = 0;
	if (!str || !copy)
		return ;
	while (str && str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
}

char	*ft_strdup(char *str)
{
	char *copy;
	int	 len;
	
	len = ft_strlen(str);
	copy = NULL;
	copy = malloc(sizeof(char) * len + 1);
	if (!copy)
		return (0);
	ft_strcpy(copy, str);
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *join;
	int len_s1;
	int len_s2;
	int i;
	int j;

	join = NULL;
	i = 0;
	j = 0;
	if (!s1)
		return(ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join)
		return (0);	
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '\0';
	while (s2 && s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;		
	}
	join[i] = '\0';
	free(s1);
	return (join);	
}


char	*get_next_line(int fd)
{
	static char buff[BUFFER];
	char *line;
	char *newline_pos;
	int line_end;
	int nbytes;


	nbytes = 1;
	newline_pos = NULL;
	line_end = 0;
	line = ft_strdup(buff);
	while (!(newline_pos = ft_strchr(line)) && nbytes)
	{
		nbytes = read(fd, buff, BUFFER);
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);	
	}
	if ((ft_strlen(line) == 0))
		return (free(line), NULL);
	if (newline_pos != NULL)
	{
		line_end = newline_pos - line + 1;
		ft_strcpy(buff, newline_pos + 1);

		
	}
	else
	{
		line_end = ft_strlen(line);
		buff[0] = '\0';
		
	}
	line[line_end] = '\0';	
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
