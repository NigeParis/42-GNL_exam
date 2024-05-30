/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:26:24 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/30 10:09:02 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy(char *copy, char *str)
{
	int i;
	i = 0;
	if (!copy || !str)
		return ;
	while (str && str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
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

char	*ft_strdup(char *str)
{
	char *copy;
	int len;
	
	len = ft_strlen(str);
	copy = NULL;
	copy = (char *)malloc(sizeof(char) * len + 1);
	if (!copy)
		return (NULL);
	ft_strcpy(copy, str);
	return (copy);	
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *join;
	int	 len_s1;
	int	 len_s2;
	
	if (!s1)
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = NULL;
	join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);	
	ft_strcpy(join + len_s1, s2);	
	if (s1)
		free(s1);
	return (join);
}


char	*ft_strchr(char *str, char c)
{
	int	i;

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
