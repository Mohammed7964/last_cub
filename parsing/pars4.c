/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:25:18 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/25 15:27:36 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*clean_newline_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	return (str);
}

static void	set_texture_or_color(t_cub *cub, char *key, char *value)
{
	if (!cub || !key || !value)
		return ;
	if (strcmp(key, "NO") == 0)
		(free(cub->north_texture), cub->north_texture = value);
	else if (strcmp(key, "SO") == 0)
		(free(cub->south_texture), cub->south_texture = value);
	else if (strcmp(key, "WE") == 0)
		(free(cub->west_texture), cub->west_texture = value);
	else if (strcmp(key, "EA") == 0)
		(free(cub->east_texture), cub->east_texture = value);
	else if (strcmp(key, "F") == 0)
		(free(cub->_f), cub->_f = value);
	else if (strcmp(key, "C") == 0)
		(free(cub->_c), cub->_c = value);
	else
		free(value);
}

void	join(t_cub *cub, char **path)
{
	int		i;
	char	*joined;
	char	*tmp;

	if (!cub || !path || !path[0])
		return ;
	i = 1;
	while (path[i] && path[i][0] == '\0')
		i++;
	if (!path[i])
		return ;
	joined = ft_strdup(path[i++]);
	if (!joined)
		return ;
	while (path[i])
	{
		tmp = joined;
		joined = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = joined;
		joined = ft_strjoin(tmp, path[i++]);
		free(tmp);
	}
	joined = clean_newline_str(joined);
	set_texture_or_color(cub, path[0], joined);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	clean_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}
