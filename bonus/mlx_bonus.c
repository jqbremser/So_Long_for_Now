/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:17:17 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 14:58:29 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		mlx_close_window(game->mlx);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& keydata.action == MLX_PRESS)
		move_up(game);
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& keydata.action == MLX_PRESS)
		move_down(game);
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& keydata.action == MLX_PRESS)
		move_left(game);
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& keydata.action == MLX_PRESS)
		move_right(game);
}

static void	window_init(t_map *game)
{
	t_img	*images;
	t_ani	*p_ani;
	t_ani	**tokens;

	game->mlx = mlx_init((game->columns) * PIXELS,
			game->rows * PIXELS, "So_Long", false);
	if (!game->mlx)
		error_exit_array("Error: mlx_init\n", game, game->map);
	images = images_init(game);
	if (!images)
		error_exit_array("Error: images_init\n", game, game->map);
	p_ani = p_animes_init(game);
	if (!p_ani)
		error_exit_array("Error: p_ani_init\n", game, game->map);
	tokens = malloc(sizeof(t_ani) * game->tokens);
	while (game->token_index < game->tokens)
		tokens[game->token_index++] = t_animes_init(game);
	game->token_index = 0;
	if (!tokens)
		error_exit_array("Error: tokens_ani malloc", game, game->map);
	game->p_ani = p_ani;
	game->images = images;
	game->tokens_ani = tokens;
}

void	mlx_starter(t_map *game)
{
	window_init(game);
	map_render(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, animation_loop, game);
	step_counter_init(game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->images->floor);
	mlx_delete_image(game->mlx, game->images->token);
	mlx_delete_image(game->mlx, game->images->exit_closed);
	mlx_delete_image(game->mlx, game->images->exit_open);
	free_animes(game->mlx, game->p_ani);
	while (game->token_index-- > 0)
		free_animes(game->mlx, game->tokens_ani[game->token_index]);
	mlx_terminate(game->mlx);
}
