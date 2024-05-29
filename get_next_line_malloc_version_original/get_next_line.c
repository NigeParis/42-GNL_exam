/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:11:12 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/29 13:38:27 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd, char *buffer)
{
	char	*line;
	int		nbytes;

	nbytes = 1;
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && nbytes)
	{
		nbytes = read(fd, line, BUFFER_SIZE);
		if (nbytes == -1)
		{
			return (free(line), NULL);
		}
		line[nbytes] = 0;
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	return (buffer);
}

char	*get_line_trim(char *buffer)
{
	char	*trimmed_read;
	int		i;
	int		len;

	len = 0;
	i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	trimmed_read = malloc(ft_strlen(buffer) + 2 * sizeof(char));
	if (!trimmed_read)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		trimmed_read[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		trimmed_read[i] = buffer[i];
		i++;
	}
	trimmed_read[i] = '\0';
	return (trimmed_read);
}

char	*get_leftover(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!buffer[i])
		return (free(buffer), NULL);
		
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	len = ft_strlen(&buffer[i]);	
	if (len == 0)
		return (free(buffer), NULL);
		
	new_buffer = malloc(sizeof(char) * len + 1);
	if (!new_buffer)
		return (NULL);

	ft_strcpy(new_buffer, &buffer[i]);
	return (free(buffer), new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*output;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer = get_line(fd, buffer);
	if (!buffer)
		return (NULL);
	output = get_line_trim(buffer);
	buffer = get_leftover(buffer);
	return (output);
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
	
	str = get_next_line(fd);
	printf("%s", str);
	free (str);

	str = get_next_line(fd);
	printf("%s", str);
	free (str);
	
	// fd = open("./test.txt", R_OK);
	// while (1)
	// {
	// 	str = get_next_line(fd);
	// 	if (!str)
	// 		break ;	
	// 	printf("%s", str);
	// 	free (str);
	// }
	// free (str);

	return (0);
}
// int main(void)
// {
// 	int fd = 0;
// 	char *str;
// 	fd = open("./test.txt", R_OK);
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		if (!str)
// 			break ;
// 		printf("%s", str);
// 		free (str);
// 	}
// 	return (0);
// }