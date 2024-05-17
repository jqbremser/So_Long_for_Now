/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:54:52 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 14:58:46 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	update_ani_pos(t_ani *ani)
{
	int	i;

	i = 0;
	if (ani == NULL)
		return ;
	while (i < ani->len)
	{
		ani->animes[i]->instances[ani->ids[i]].x = ani->pos.x * PIXELS;
		ani->animes[i]->instances[ani->ids[i]].y = ani->pos.y * PIXELS;
		i++;
	}
}

void	move_up(t_map *game)
{
	if (game->p_ani == NULL)
		return ;
	if (game->map[game->p_ani->pos.y - 1][game->p_ani->pos.x] != '1')
	{
		if (game->map[game->p_ani->pos.y - 1][game->p_ani->pos.x] == 'C')
		{
			remove_token(game, game->p_ani->pos.y - 1, game->p_ani->pos.x);
			game->map[game->p_ani->pos.y - 1][game->p_ani->pos.x] = '0';
		}
		if (game->map[game->p_ani->pos.y - 1][game->p_ani->pos.x] == 'E')
		{
			time_to_exit(game);
		}
		game->p_ani->pos.y -= 1;
		update_ani_pos(game->p_ani);
		step_counter_init(game);
		ft_printf("\nSteps: %i\n", game->steps);
	}
}

void	move_down(t_map *game)
{
	if (game->p_ani == NULL)
		return ;
	if (game->map[game->p_ani->pos.y + 1][game->p_ani->pos.x] != '1')
	{
		if (game->map[game->p_ani->pos.y + 1][game->p_ani->pos.x] == 'C')
		{
			remove_token(game, game->p_ani->pos.y + 1, game->p_ani->pos.x);
			game->map[game->p_ani->pos.y + 1][game->p_ani->pos.x] = '0';
		}
		if (game->map[game->p_ani->pos.y + 1][game->p_ani->pos.x] == 'E')
		{
			time_to_exit(game);
		}
		game->p_ani->pos.y += 1;
		update_ani_pos(game->p_ani);
		step_counter_init(game);
		ft_printf("\nSteps: %i\n", game->steps);
	}
}

void	move_left(t_map *game)
{
	if (game->p_ani == NULL)
		return ;
	if (game->map[game->p_ani->pos.y][game->p_ani->pos.x - 1] != '1')
	{
		if (game->map[game->p_ani->pos.y][game->p_ani->pos.x - 1] == 'C')
		{
			remove_token(game, game->p_ani->pos.y, game->p_ani->pos.x - 1);
			game->map[game->p_ani->pos.y][game->p_ani->pos.x - 1] = '0';
		}
		if (game->map[game->p_ani->pos.y][game->p_ani->pos.x - 1] == 'E')
		{
			time_to_exit(game);
		}
		game->p_ani->pos.x -= 1;
		update_ani_pos(game->p_ani);
		step_counter_init(game);
		ft_printf("\nSteps: %i\n", game->steps);
	}
}

void	move_right(t_map *game)
{
	if (game->p_ani == NULL)
		return ;
	if (game->map[game->p_ani->pos.y][game->p_ani->pos.x + 1] != '1')
	{
		if (game->map[game->p_ani->pos.y][game->p_ani->pos.x + 1] == 'C')
		{
			remove_token(game, game->p_ani->pos.y, game->p_ani->pos.x + 1);
			game->map[game->p_ani->pos.y][game->p_ani->pos.x + 1] = '0';
		}
		if (game->map[game->p_ani->pos.y][game->p_ani->pos.x + 1] == 'E')
		{
			time_to_exit(game);
		}
		game->p_ani->pos.x += 1;
		update_ani_pos(game->p_ani);
		step_counter_init(game);
		ft_printf("\nSteps: %i\n", game->steps);
	}
}
