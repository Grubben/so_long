/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:20:13 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/03 16:37:38 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Moves player in specified direction.
// If cannot, returns 0 
int move_player(int directionx, int directiony, size_t quant, t_info *worldata)
{
    int    newx;
    int    newy;
    
    newx = worldata->ppos_x + directionx * quant;
    newy = worldata->ppos_y - directiony * quant;
    // if ((newx < 0) || (newy < 0))
    //     return (0);
    if (worldata->matrixmap[newy][newx] == '1')
        return (0);
    worldata->ppos_x = newx;
    worldata->ppos_y = newy;
    worldata->n_moves++;
    return (1);
}