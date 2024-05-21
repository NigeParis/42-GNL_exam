/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:47:03 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/21 22:04:47 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    char c;
    int  i;

    i = 0;
    while (str && str[i])
    {
        c = str[i];
        ft_putchar(c);
        i++;
    }
    
}

void    ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while (src && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int ft_strlen(char *str)
{
    int len;

    len = 0;
    if (!str)
        return (0);
    while (str && str[len])
        len++;
    return (len);
}


char *ft_strdup(char *str)
{
    int len;
    char *copy;
    
    copy = NULL;
    if (!str)
        return (0);
    len = ft_strlen(str);
    copy = malloc(sizeof(char) * len + 1);   
    if (!copy)
        return (0);
    ft_strcpy(copy, str);
    return (copy);    
}

char *ft_strjoin(char *s1, char *s2)
{
    char *join;
    int  s1_len = ft_strlen(s1);
    int  s2_len = ft_strlen(s2);
    int i = 0;
    int j = 0;

    if (!s1)
        return (ft_strdup(s2));
    join = NULL;    
    join = malloc(sizeof(char) * (s1_len + s2_len + 1));
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
    free (s1);
    return (join);
}

char    *ft_strchr(char *str)
{
    int i = 0;

    while (str && str[i])
    {
        if (str[i] == '\n')
            return (&str[i]);
        i++;
    }
    return (NULL);    
}




char *get_next_line(int fd)
{
    static char buff[BUFFER + 1];
    char *line;
    char *newline;
    int nbytes = 1;
    int tocopy = 0;

    line = ft_strdup(buff);
    while (!(newline = ft_strchr(line)) && (nbytes))
	{
        nbytes = read(fd, buff, BUFFER);
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);
	}
    if (newline != NULL)
    {
        tocopy = newline - line + 1;
        ft_strcpy(buff, newline + 1);
        
    }
    else
	{
		tocopy = ft_strlen(line);
		buff[0] = '\0';
	}
    line[tocopy] = '\0';
    return (line);    
}


int main(void)
{
    char *line;

    line = NULL;
    line = get_next_line(0);
  
    ft_putstr(line);
    free (line);
    return (0);
}