/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:38:56 by amargy            #+#    #+#             */
/*   Updated: 2020/02/28 14:39:47 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	linebody_tail(char **fd_depot, char **line)
{
	int		i;
	char	*bag;

	i = 0;
	while ((*fd_depot)[i] != '\n' && (*fd_depot)[i] != '\0')
		i++;
	if ((*fd_depot)[i] == '\n')
	{
		*line = ft_strsub(*fd_depot, 0, i);
		bag = ft_strdup(&((*fd_depot)[i + 1]));
		free(*fd_depot);
		*fd_depot = bag;
		if ((*fd_depot)[0] == '\0')
			ft_strdel(&(*fd_depot));
	}
	else
	{
		*line = ft_strdup(*fd_depot);
		ft_strdel(&(*fd_depot));
	}
	return (1);
}

static int	return_value(char **fd_depot, char **line, int readvalue, int fd)
{
	if (readvalue < 0)
	{
		return (-1);
		close(fd);
	}
	else if (readvalue == 0 && fd_depot[fd] == NULL)
	{
		return (0);
		close(fd);
	}
	else
		return (linebody_tail(&fd_depot[fd], line));
}

int			get_next_line(const int fd, char **line)
{
	int			readvalue;
	static char	*fd_depot[10000];
	char		buff[BUFF_SIZE_GNL + 1];
	char		*bag;

	ft_bzero(buff, BUFF_SIZE_GNL + 1);
	if (fd < 0 || line == NULL || fd > 10000 || read(fd, buff, 0) < 0)
		return (-1);
	while ((readvalue = read(fd, buff, BUFF_SIZE_GNL)) > 0)
	{
		buff[readvalue] = '\0';
		if (fd_depot[fd] == NULL)
			fd_depot[fd] = ft_strdup(buff);
		else
		{
			bag = ft_strjoin(fd_depot[fd], buff);
			free(fd_depot[fd]);
			fd_depot[fd] = bag;
		}
		if (ft_strchr(fd_depot[fd], '\n'))
			break ;
	}
	return (return_value(fd_depot, line, readvalue, fd));
}
