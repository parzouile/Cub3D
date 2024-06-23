/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:34:13 by aschmitt          #+#    #+#             */
/*   Updated: 2024/06/24 01:11:21 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ml/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>

#ifndef WIDTH
# define WIDTH 1900
#endif

#ifndef HEIGHT
# define HEIGHT 1000
#endif

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_data;

typedef struct s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}				t_player;

typedef struct s_key
{
	int		z;
	int		q;
	int		s;
	int		d;
	int		left;
	int		right;
}				t_key;

typedef struct s_image
{
	void	*img;
	int		*addr;
	int 	bpp;
    int 	size_line;
   	int 	endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_ray
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX; //length of ray from current position to next x or y-side
	double	sideDistY;
	double	deltaDistX; //longueur du rayon depuis la position actuelle jusqu'au prochain côté x ou y
	double	deltaDistY;
	double	perpWallDist;
	int		mapX;
	int		mapY;
	int		stepX; //dans quelle direction avancer dans la direction x ou y (soit +1 ou -1)
	int		stepY;
	int		hit; //Y a-t-il eu un coup de mur ?
	int		side; //un mur NS ou EW a-t-il été touché ?
	int		h;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		x;
}				t_ray;

typedef struct s_minimap
{
	int		enable;
	int		i;
	int		width;
	int		height;
	int		max;
	int		min;
	int		pos;
	t_image	img;
}		t_minimap;

typedef struct s_game
{
	int			width;
	int			height;
	double		moveSpeed;
	double		rotSpeed;
	char		**map;
	char		**p_map;
	int			map_y_scale;
	int			frame;
	t_image		NO;
	t_image		SO;
	t_image		WE;
	t_image		EA;
	int			F;
	int			C;
	t_data		mlibx;
	t_player	player;
	t_key		key;
	t_image		img;
	t_image		img2;
	t_ray		ray;
	t_minimap	minimap;
}				t_game;

// construct
void	game_construct(t_game *game);

// free
void	free_map(t_game *game, int line);
void 	free_game(t_game *game, int error_code);

// init map
void	get_y_scale_map(t_game *game);
void	create_color_FC(t_game *game, int line, int j, int i);
void	open_texture(t_game *game, size_t line);
void 	del_newline(char *line);
int		still_header(t_game *game, size_t line);
int		check_extention(char *file);
char	**ft_malloc_map(t_game *game, char *file);
void	print_map(char **map);
void	init_map(char *file, t_game *game);
char	*get_next_line(int fd);

// init mlx
void	init_mlx(t_game *game);
int		close_win(t_game *game);

// game
void	cub3d(t_game *game);


void	mini_map(t_game *game);
int		render_next_frame(t_game *game);
size_t	ft_strlen(const char *str);
int		is_wspace(char c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_iswspace(char c);
int		ft_isdigit(int c);
int		create_rgb(unsigned char r, unsigned char g, unsigned char b);

// key hook
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
int		play(t_game *game);

void    draw(t_game *game);
void	performe_dda(t_game *game);
void	init_vecteur(t_game *game);
void	display(t_game *game);
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);

#endif