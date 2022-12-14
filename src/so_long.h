/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:08:36 by amc               #+#    #+#             */
/*   Updated: 2022/11/16 17:06:16 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

enum e_CONSTS
{
	EMPTY = '0',
	WALL = '1',
	COLLECT = 'C',
	EXIT = 'E',
	PSTARTPOS = 'P'
};

typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
}				t_img;

// Could make another struct for level_init
// To separate it from the window construction and mlx initing
typedef struct s_info
{
	void			*mlx;

	int				pixels;

	t_img			win;

	unsigned int	ppos_x;
	unsigned int	ppos_y;

	char			**matrixmap;

	t_img			imgplyr;

	t_img			imgempty;
	t_img			imgwall;

	t_img			imgcoll;
	size_t			n_collectibles;
	size_t			n_collected;

	t_img			imgexit;

	size_t			n_moves;
	int				move_printb;
	char			*smvs;
}				t_info;

/*  MAP */
char	**matrix_maker(char *filename);

void	matrixmap_printer(char **matrixmap);

void	mtrx_free(char **mtrxmap);

/*	CHECKS	*/
int		mtrx_checkwallsp(char **mtrxmap);

int		mtrx_checkmp(t_info *worldata);

/*	PATH	*/
int		vldpath_checkerp(t_info *worldata);

/*  MOVEMENT    */
int		move_player(int directx, int directy, size_t quant, t_info *worldata);

int		keyboardprinter(int keycode, t_info *worldata);

/*  COLOR   */
int		rgbtocolor(unsigned char r, unsigned char g, unsigned char b);

int		draw_map(t_info *worldata);

/*	MAIN	*/
int		destroy(t_info *worldata);

/*	UTILS	*/
int		mtrxdo(char **mtrx, void *data,
			int (*func)(char, void *, size_t, size_t));

char	**mtrxmap_cpy(char **matrixmap);

#endif
