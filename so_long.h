/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:58:52 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 15:03:45 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define PIXELS 64	

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_img
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*token;
	mlx_image_t	*exit_closed;
	mlx_image_t	*exit_open;
}	t_img;

typedef struct s_ani
{
	t_position	pos;
	mlx_image_t	**animes;
	int			*ids;
	int			len;
	int			enabled;
}	t_ani;

typedef struct s_map
{
	char		**map;
	char		**copy;
	int			columns;
	int			rows;
	int			tokens;
	int			exit;
	int			player;
	int			steps;
	int			collected;
	t_position	p_position;
	t_position	e_position;
	mlx_t		*mlx;
	t_img		*images;
	t_ani		*p_ani;
	t_ani		**tokens_ani;
	double		emote_time;
	int			cur_frame;
	int			token_index;
	mlx_image_t	*step_counter;
}	t_map;

/* ************************************************************************** */
/*                                   so_long								  */
/* ************************************************************************** */
int			main(int argc, char **argv);
/* ************************************************************************** */
/*                                   utils									  */
/* ************************************************************************** */
size_t		ft_strlen_delim(char *str, char delim);
void		remove_token(t_map	*game, int y, int x);
void		time_to_exit(t_map	*game);
void		update_exit(t_map	*game, t_position e_pos);
/* ************************************************************************** */
/*                                   map_init								  */
/* ************************************************************************** */
void		map_init(t_map *game, char *arg);
/* ************************************************************************** */
/*                                   map_parse								  */
/* ************************************************************************** */
int			map_parse(t_map *game);
/* ************************************************************************** */
/*                                   fill									  */
/* ************************************************************************** */
int			floodfill(t_map *game);
/* ************************************************************************** */
/*                                   error_time								  */
/* ************************************************************************** */
int			error_msg_exit(char *msg, t_map *game);
void		error_exit_array(char *msg, t_map	*game, char **array);
void		free_array(char **str);
void		error_msg(char *msg);
void		free_animes(mlx_t *mlx, t_ani *ani);
/* ************************************************************************** */
/*                                   mlx									  */
/* ************************************************************************** */
void		mlx_starter(t_map *game);
/* ************************************************************************** */
/*                                   assets									  */
/* ************************************************************************** */
void		load_all_assets(t_map *game, t_img **assets);
/* ************************************************************************** */
/*                                   map_render								  */
/* ************************************************************************** */
void		map_render(t_map *game);
/* ************************************************************************** */
/*                                   animations								  */
/* ************************************************************************** */
void		animate(t_map *game, t_ani *ani);
mlx_image_t	*png_to_img(mlx_t *mlx, char *file);
void		animation_loop(void *param);
/* ************************************************************************** */
/*                                   im_an_init								  */
/* ************************************************************************** */
t_img		*images_init(t_map *game);
t_ani		*p_animes_init(t_map *game);
t_ani		*t_animes_init(t_map *game);
void		step_counter_init(t_map *game);
/* ************************************************************************** */
/*                                   moves									  */
/* ************************************************************************** */
void		move_up(t_map *game);
void		move_down(t_map *game);
void		move_left(t_map *game);
void		move_right(t_map *game);

#endif // SO_LONG_H
