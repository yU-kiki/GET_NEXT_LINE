/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikeda <yikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:06:39 by yikeda            #+#    #+#             */
/*   Updated: 2021/03/03 18:49:28 by yikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_cut_save(char **save)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *save;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (!(*save = ft_substr(tmp, i, ft_strlen(tmp))))
		return (-1);
	free(tmp);
	return (0);
}

static int	ft_readnsave(int fd, char *buff, char **save)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buff, BUFFER_SIZE)))
	{
		buff[ret] = '\0';
		tmp = *save;
		if (!(*save = ft_strjoin(tmp, buff)))
			return (-1);
		free(tmp);
		if (ft_strnchr(buff, '\n', BUFFER_SIZE))
			break ;
	}
	free(buff);
	return (ret);
}

int			get_next_line(int const fd, char **line)
{
	static char	*save;
	char		*buff;
	int			ret;

	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE <= 0 ||
			!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!save)
	{
		if (!(save = malloc(sizeof(char))))
			return (-1);
		save[0] = '\0';
	}
	if ((ret = ft_readnsave(fd, buff, &save)) == -1)
		return (-1);
	*line = ft_strndup(save);
	if (!ft_strnchr(save, '\n', ft_strlen(save)))
	{
		free(save);
		save = NULL;
		return (0);
	}
	if (ft_cut_save(&save) == -1)
		return (-1);
	return (1);
}
