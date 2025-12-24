/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:23:46 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/23 23:35:43 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	handle_empty_line(t_cub *cub, char *line)
{
	if (!is_empty_line(line))
	{
		if (cub->map_ended)
			return (0);
		return (2);
	}
	if (cub->map_started)
		cub->map_ended = 1;
	return (1);
}

int	handle_colors2(char **split, t_cub *cub)
{
	if (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
	{
		if (!split[1])
			return (0);
		init_texture(split[0], cub);
		return (1);
	}
	return (2);
}

int	handle_textures2(char **split, t_cub *cub)
{
	if (!ft_strcmp(split[0], "NO") || !ft_strcmp(split[0], "SO")
		|| !ft_strcmp(split[0], "WE") || !ft_strcmp(split[0], "EA"))
	{
		if (!split[1] || !check_path(split[1]))
			return (0);
		init_texture(split[0], cub);
		return (1);
	}
	return (2);
}

int	can_start_map(t_cub *cub)
{
	if (cub->no == 1 && cub->so == 1 && cub->we == 1
		&& cub->ea == 1 && cub->f == 1 && cub->c == 1)
		return (1);
	return (0);
}

int	is_path(char **split, t_cub *cub, char *line)
{
	int		status;
	char	*tmp;

	status = handle_empty_line(cub, line);
	if (status != 2)
		return (status);
	if (!split || !split[0])
		return (1);
	status = handle_colors2(split, cub);
	if (status != 2)
		return (status);
	status = handle_textures2(split, cub);
	if (status != 2)
		return (status);
	if (!can_start_map(cub))
		return (0);
	if (cub->map_ended)
		return (0);
	cub->map_started = 1;
	tmp = cub->map;
	cub->map = ft_strjoin(tmp, line);
	free(tmp);
	return (1);
}
