/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:20:13 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/02 18:28:51 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Moves player in specified direction.
// If cannot, returns 0 
int move_player(int directionx, int directiony, size_t quant, t_info *worldata)
{
    worldata->ppos_x += directionx * quant * worldata->PIXELS;
    worldata->ppos_y -= directiony * quant * worldata->PIXELS;
    return (1);
}