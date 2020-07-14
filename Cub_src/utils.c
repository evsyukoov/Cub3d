/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/10 17:56:06 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	normalize_deg(float deg)
{
	if (deg < 0)
		return (360 + deg);
	if (deg > 360)
		return (deg - 360);
	return (deg);
}

int		is_looking_up(float deg)
{
	if (deg > 180)
		return (1);
	else
		return (-1);
}

int		is_looking_right(float deg)
{
	if (deg < 90 || deg > 270)
		return (1);
	else
		return (-1);
}

double	degrees_to_rad(double degrees)
{
	return (degrees * (M_PI / 180));
}

double	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}
