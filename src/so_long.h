/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amc <amc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:08:36 by amc               #+#    #+#             */
/*   Updated: 2022/11/04 09:25:27 by amc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <fcntl.h>

enum CONSTS
{
    EMPTY,
    WALL,
    COLLECT='C',
    EXIT='E',
    PSTARPOS='P'
}   MAP;

typedef struct s_tile
{
    void    *tile_img;
    int     tile_width;
    int     tile_height;
}               t_tile;

typedef struct s_info
{
	void	*mlx;

    int     PIXELS;

    // can use t_tile for win
	void	*win;
	unsigned int	SIZE_X;
	unsigned int	SIZE_Y;

	// void			*img;

	unsigned int	ppos_x;
	unsigned int	ppos_y;

    char            **matrixmap;

    t_tile          player;
    
    t_tile          empspace;
    t_tile          wall;
    t_tile          collectible;
    t_tile          mapexit;

	size_t			n_moves;
}				t_info;


/*  MAP */
char    **matrix_maker(char *filename);

int draw_map(t_info *worldata);

void    matrixmap_printer(t_info *worldata);


/*  MOVEMENT    */
int move_player(int directionx, int directiony, size_t quant, t_info *worldata);


/*  COLOR   */
void	intbin_append(int *color, unsigned char fam);

int	rgbToColor(unsigned char r, unsigned char g, unsigned char b);
