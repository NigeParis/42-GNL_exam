/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:11:12 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/29 15:45:06 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	if ((BUFFER_SIZE < 1) || (fd < 0))
		return (NULL);
		
	static char *buff;
	static int is_buff = 0;
	char *line;
	char *newline_pos;
	int	 endline_pos;
	int nbytes;
	
	newline_pos = NULL;
	endline_pos = 0;
	nbytes = 1;
	
	if (!is_buff)
	{
		buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		line = ft_strdup("");
		if (!line)
			return (free(buff), NULL);
	} 
	else 
	{
		line = ft_strdup(buff);
		if (!line)
			return (free(buff), free(line), NULL);
	}
	
	is_buff = 1;

	while (!(newline_pos = ft_strchr(line, '\n')) && nbytes)
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(buff);
			return (free(line), NULL);
		}
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);
	}
	
	if (ft_strlen(line) == 0)
		return (free(buff), free(line), NULL);
	
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
	int fd = 0;
	char *str;
	//int i = 0;

	fd = open("./test.txt", R_OK);
	str = get_next_line(fd);
	printf("%s", str);
	free (str);
	
// 	// str = get_next_line(fd);
// 	// printf("%s", str);
// 	// free (str);

// 	// str = get_next_line(fd);
// 	// printf("%s", str);
// 	// free (str);
	
// 	fd = open("./test.txt", R_OK);
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		if (!str)
// 			break ;	
// 		printf("%s", str);
// 		free (str);
// 	}
// 	free (str);

	return (0);
}

