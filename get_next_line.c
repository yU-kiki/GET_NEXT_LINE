/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikeda <yikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:06:39 by yikeda            #+#    #+#             */
/*   Updated: 2020/12/02 19:28:34 by yikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_cutncpy_save(char **save)
{
	int		i;
	char	*toto;

	i = 0;
	toto = *save;
	while (toto[i])
	{
		if (toto[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	if (!(*save = ft_substr(toto, i, ft_strlen(toto))))
		return (-1);
	free(toto);
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
			break;
	}
	return (ret);
}

int			get_next_line(int const fd, char **line)
{
	static char	*save;
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE <= 0)
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
	if (ft_cutncpy_save(&save) == -1)
		return (-1);
	return (1);
}
