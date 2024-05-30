/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:26:24 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/30 10:23:10 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
		
	static char *buff;
	static int is_buff = 0;
	char *newline_pos;
	int nbytes = 1;
	int endline_pos;
	int	lenline = 0;
	int lennewline = 0;
	char *line;

	if (!is_buff)
	{
		buff = NULL;
		buff = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return (is_buff = 0, NULL);
		line = NULL;
		line = ft_strdup("");
		if (!line)
			return (is_buff = 0, free(buff), NULL);
	}
	else
	{
		line = ft_strdup(buff);
		if (!line)
			return (is_buff = 0, free(buff), free(line), NULL);		
	}
	is_buff = 1;
	
	while (!(newline_pos = ft_strchr(line, '\n')) && nbytes)
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes == -1)
			return (is_buff = 0, free(buff), free(line), NULL);		
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);	
	}
	lenline = ft_strlen(line);
	lennewline = ft_strlen(newline_pos);
	if (lenline == 0)
		return (is_buff = 0, free(buff), free(line), NULL);
	if (lennewline != 0)
	{
		endline_pos = lenline + 1 - lennewline;
		ft_strcpy(buff, newline_pos + 1);
	}
	else
	{
		endline_pos = lenline;
		buff[0] = '\0';
	}
	line[endline_pos] = '\0';
	return (line);	
}




// int	main(void)
// {
// 	char *copy;
// 	int fd = 0;

// 	fd = open("./test.txt", R_OK);

// 	copy = get_next_line(fd);
// 	printf("%s",copy);
// 	free(copy);
// 	copy = get_next_line(fd);
// 	printf("%s",copy);
// 	free(copy);
// 	copy = get_next_line(fd);
// 	printf("%s",copy);
// 	free(copy);


// 	// while (1)
// 	// {
// 	// copy = get_next_line(fd);
// 	// if (!copy)
// 	// 	break ;
// 	// printf("%s",copy);


// 	// free(copy);
// 	// }
// 	return (0);
// }