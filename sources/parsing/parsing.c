/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:54:37 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 15:27:29 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_parsing(t_data *data, char *map_name)
{
	int		map_fd;
	int		map_size;
	char	*line;

	init_parsing(data);
	map_size = get_map_size(map_name);
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		return (printf("Error\nCan't open map file\n"), -1);
	line = get_next_line(map_fd);
	while (line)
	{
		while (line[0] == '\n')
		{
			free(line);
			line = get_next_line(map_fd);
			if (!line)
				return (0);
		}
		if (line[get_index_first_char(line)] == 'F' && ft_contains(" \t\n\r\v\f", line[get_index_first_char(line) + 1]))
		{
			if (data->parsing.color_floor != -1)
				return (free(line), printf("Error\nFloor color already filled !\n"), -1);
			if (fill_floor_ceiling(data, line, 'F') == -1)
				return (free(line), -1);
		}
		else if (line[get_index_first_char(line)] == 'C' && ft_contains(" \t\n\r\v\f", line[get_index_first_char(line) + 1]))
		{
			if (data->parsing.color_ceiling != -1)
				return (free(line), printf("Error\nCeiling color already filled !\n"), -1);
			if (fill_floor_ceiling(data, line, 'C') == -1)
				return (free(line), -1);
		}
		else if (line[get_index_first_char(line)] == 'N' && line[get_index_first_char(line) + 1] == 'O')
		{
			if (data->parsing.path_texture_north != NULL)
				return (free(line), printf("Error\nNorth texture already filled !\n"), -1);
			if (fill_directions(data, line, 'N') == -1)
				return (free(line), -1);
		}
		else if (line[get_index_first_char(line)] == 'S' && line[get_index_first_char(line) + 1] == 'O')
		{
			if (data->parsing.path_texture_south != NULL)
				return (free(line), printf("Error\nSouth texture already filled !\n"), -1);
			if (fill_directions(data, line, 'S') == -1)
				return (free(line), -1);
		}
		else if (line[get_index_first_char(line)] == 'W' && line[get_index_first_char(line) + 1] == 'E')
		{
			if (data->parsing.path_texture_west != NULL)
				return (free(line), printf("Error\nWest texture already filled !\n"), -1);
			if (fill_directions(data, line, 'W') == -1)
				return (free(line), -1);
		}
		else if (line[get_index_first_char(line)] == 'E' && line[get_index_first_char(line) + 1] == 'A')
		{
			if (data->parsing.path_texture_east != NULL)
				return (free(line), printf("Error\nEast texture already filled !\n"), -1);
			if (fill_directions(data, line, 'E') == -1)
				return (free(line), -1);
		}
		else if (line[get_index_first_char(line)] == '1' || line[get_index_first_char(line)] == '0')
		{
			if (parsing_is_filled(data) && data->parsing.map == NULL)
			{
				if (fill_map(data, line, map_size, map_fd) == -1)
					return (free(line), -1);
				return (free(line), 0);
			}
			else
				return (free(line), printf("Error\nMap is not in last position or is already filled!\n"), -1);
		}
		else
			return (free(line), printf("Error\nInvalid identifier !\n"), -1);
		free(line);
		line = get_next_line(map_fd);
	}
	free(line);
	return (0);
}