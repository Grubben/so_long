/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:40:09 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/03 16:40:19 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	intbin_append(int *color, unsigned char fam)
{
	*color = *color << 8;
	*color = *color | fam;
}

int	rgbToColor(unsigned char r, unsigned char g, unsigned char b)
{
	int		color;

	color = 127; // This is the hard-coded alpha value
	// Tried changing it and nothing happened so leaving it
	intbin_append(&color, r);
	intbin_append(&color, g);
	intbin_append(&color, b);
	return (color);

}
