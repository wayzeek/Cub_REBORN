/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:50:56 by vcart             #+#    #+#             */
/*   Updated: 2023/06/08 11:09:13 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	mlx_pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (img == NULL || img->addr == NULL)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	put_tile(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * data->tile_size;
	while (i <= x * data->tile_size + data->tile_size)
	{
		j = y * data->tile_size;
		while (j < y * data->tile_size + data->tile_size)
		{
			mlx_pixel_put_img(&data->img_minimap, i, j, color);
			j++;
		}
		i++;
	}
}

void	print_square(t_data *data, int x, int y, int size)
{
	int	i;
	int	j;

	i = x;
	while (i <= x + size)
	{
		j = y;
		while (j <= y + size)
		{
			mlx_pixel_put_img(&data->img_minimap, i, j, 0x2133bf);
			j++;
		}
		i++;
	}
}
