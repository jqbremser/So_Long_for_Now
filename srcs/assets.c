/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:52:54 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/22 13:19:19 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	load_asset(t_map *game, mlx_image_t **img, char *img_path)
{
	mlx_texture_t	*txt;

	txt = NULL;
	txt = mlx_load_png(img_path);
	if (!txt)
	{
		error_msg("Error: Texture load fail\n");
		return ;
	}
	*img = mlx_texture_to_image(game->mlx, txt);
	mlx_delete_texture(txt);
	if (!*img)
	{
		mlx_close_window(game->mlx);
		error_msg("Error: Texture_to_image load fail\n");
		return ;
	}
	mlx_resize_image(*img, PIXELS, PIXELS);
}

void	load_all_assets(t_map *game, t_img *assets)
{
	load_asset(game, &assets->wall, "./assets/wall.png");
	load_asset(game, &assets->floor, "./assets/floor.png");
	load_asset(game, &assets->exit_open, "./assets/exit_open.png");
	load_asset(game, &assets->exit_closed, "./assets/exit_closed.png");
}
