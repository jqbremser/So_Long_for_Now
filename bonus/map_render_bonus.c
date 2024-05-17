/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:27:38 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 14:58:12 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	anime_picker(t_map *game, int y, int x, t_ani *ani)
{
	mlx_image_t	*img;
	int			i;
	int			id;

	i = 0;
	ani->pos.y = y;
	ani->pos.x = x;
	while (i < ani->len)
	{
		img = ani->animes[i];
		if (img)
			id = mlx_image_to_window(game->mlx, ani->animes[i],
					x * PIXELS, y * PIXELS);
		else
			return (0);
		ani->ids[i] = id;
		img->instances[id].enabled = true;
		i++;
	}
	ani->enabled = true;
	return (1);
}

static void	floorfill(t_map	*game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			if (mlx_image_to_window(game->mlx, game->images->floor,
					x * PIXELS, y * PIXELS) < 0)
				error_exit_array("Error: floorfill\n", game, game->map);
			x++;
		}
		y++;
	}
}

static void	wall_exit_add(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			if (game->map[y][x] == 'E')
			{
				if (mlx_image_to_window(game->mlx,
						game->images->exit_closed, x * PIXELS, y * PIXELS) < 0)
					error_exit_array("Error: c_exit_img\n", game, game->map);
			}
			else if (game->map[y][x] == '1')
			{
				if (mlx_image_to_window(game->mlx,
						game->images->wall, x * PIXELS, y * PIXELS) < 0)
					error_exit_array("Error: wall_img\n", game, game->map);
			}
			x++;
		}
		y++;
	}
}

static void	player_tokens_add(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			if (game->map[y][x] == 'P')
			{
				if (anime_picker(game, y, x, game->p_ani) == 0)
					error_msg("Error: p_ani add fail\n");
			}
			else if (game->map[y][x] == 'C')
			{
				if (anime_picker(game, y, x,
						game->tokens_ani[game->token_index++]) == 0)
					error_msg("Error: tokens_ani add fail\n");
			}
			x++;
		}
		y++;
	}
}

void	map_render(t_map *game)
{
	floorfill(game);
	wall_exit_add(game);
	player_tokens_add(game);
}
