/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:42:46 by moelalj           #+#    #+#             */
/*   Updated: 2023/01/19 18:06:35 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*copy_to_xyata(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc (ft_strlen (str) - i + 1);
	while (str[i] != '\0')
	{
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

char	*cut(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc (i + 1);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_read(char *xyata, int fd)
{
	int		n;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	n = 1;
	while (n != 0 && !(ft_strchr(xyata, '\n')))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n < 0)
		{
			free(buff);
			free(xyata);
			xyata = NULL;
			return (0);
		}
		buff[n] = '\0';
		xyata = ft_strjoin(xyata, buff);
	}
	free(buff);
	return (xyata);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*xyata;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	xyata = ft_read(xyata, fd);
	if (!xyata)
		return (0);
	if (xyata[0] == '\0')
	{
		free(xyata);
		xyata = NULL;
		return (NULL);
	}
	line = cut(xyata);
	xyata = copy_to_xyata(xyata);
	return (line);
}

//int main()
//{
//	int	fd;

//	fd = open("t", O_RDONLY);
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//	return(0);
//}
