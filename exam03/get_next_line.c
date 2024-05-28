/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:41:31 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/28 18:45:11 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_line(int fd, char *buffer)
{
	char *line;
	int nbytes = 1;
	
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	
	while(!(ft_strchr(buffer, '\n')) && nbytes)
	{
		nbytes = read(fd, line, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(line),NULL);
		line[nbytes] = 0;
		buffer = ft_strjoin(buffer, line);
	}	
	free(line);
	return (buffer);
}

char *getleftover(char *buffer)
{
	char *line;
	int len;	
	int	i;

	i = 0;
	len = 0;
	if (!buffer[0])
		return (free(buffer), NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		i++;
	}
	if (buffer[i] == '\n')
		i++;
	len = ft_strlen(&buffer[i]);
	if (len == 0)
		return (free(buffer), NULL);
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	ft_strcpy(line, &buffer[i]);
	return (free(buffer),line);
}

char *gettrim(char *buffer)
{
	char *line;
	int	  len;
	int	  i;
	
	len = 0;
	i = 0;
	if (!buffer[0])
		return (NULL);
	
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * ft_strlen(buffer) + 2); 
	if (!line)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}


char	*get_next_line(int fd)
{
	char *output;
	static char *buffer;
	
	
	if ((fd < 0) || BUFFER_SIZE < 1)
		return (NULL);

	buffer = get_line(fd, buffer);
	if (!buffer)
		return (NULL);
	output = gettrim(buffer);
	buffer = getleftover(buffer);
	return (output);	
}


int	main(void)
{
	char *str;
	int	fd = 0;
	fd = open("./test.txt", R_OK);
	while (1)
	{
		
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("%s", str);
		free(str);
	
	}
	return (0);
}