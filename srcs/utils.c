/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:15:51 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/22 14:11:08 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

size_t	ft_strlen_delim(char *str, char delim)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] && str[count] != delim)
		count++;
	return (count);
}

void	update_exit(t_map	*game, t_position e_pos)
{
	game->images->exit_closed->enabled = false;
	if (mlx_image_to_window(game->mlx, game->images->exit_open,
			e_pos.x * PIXELS, e_pos.y * PIXELS) < 0)
		error_exit_array("Error: image: closed exit\n", game, game->map);
}

void	time_to_exit(t_map	*game)
{
	if (game->collected >= game->tokens)
	{
		ft_printf("You win!");
		mlx_close_window(game->mlx);
	}
}

void	remove_token(t_map	*game, int y, int x)
{
	int		i;
	int		j;
	t_ani	*temp;

	i = 0;
	game->collected++;
	while (i < game->tokens)
	{
		temp = game->tokens_ani[i];
		if (temp->pos.x == x && temp->pos.y == y)
		{
			j = 0;
			while (j < temp->len)
			{
				temp->animes[j]->instances[temp->ids[j]].enabled = false;
				j++;
			}
			temp->enabled = false;
		}
		i++;
	}
	if (game->collected >= game->tokens)
		update_exit(game, game->e_position);
}
