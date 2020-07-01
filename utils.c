/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/06/04 15:37:35 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float 	negative_cast(float a)
{
	if (a < 0)
		return (0.f);
	return (a);
}

float 	check_deg_round(float player_deg, float deg_to_add)
{
	if (player_deg + deg_to_add > 360)
		return (deg_to_add - (360 - player_deg));
	if (player_deg + deg_to_add < 0)
		return (360 - fabs(player_deg - deg_to_add));
	return player_deg + deg_to_add;
}

float 	normalize_deg(float deg)
{
	if (deg < 0)
		return (360 + deg);
	if (deg > 360)
		return (deg - 360);
	return (deg);
}

int 	is_looking_up(float deg)
{
	if (deg > 180)
		return (1);
	else
		return (-1);
}

int 	is_looking_right(float deg)
{
	if (deg < 90 || deg > 270)
		return (1);
	else
		return (-1);
}

int 	check_sect(float coord)
{
	//printf("ccord = %f\n", coord);
	if (fabs(coord - (int)coord) < 0.001)
		return (1);
	return (0);
}


int 	find_x_sign(float deg)
{
	if (deg < 90 || deg > 270)
		return (1);
	else
		return (-1);
}

float 	get_accute_angle(float deg)
{
	if (deg >=90 && deg <= 180)
		return (deg - 90);
	if (deg > 180 && deg <= 270)
		return (270 -deg);
	if (deg > 270)
		return (360 - deg);
	return (deg);
}

int 	find_cos_sign(float deg)
{
	if (deg >= 0 && deg <= 90)
		return (1);
	else if (deg > 90 && deg <= 180)
		return (-1);
	else if (deg > 180 && deg <=270)
		return (-1);
	else
		return (1);
}

int 	find_sin_sign(float deg)
{
	if(deg >= 0 && deg <= 180)
		return (1);
	else
		return (-1);
}

int 	my_round(double a)
{
	int res;
	double a_fractional;

	a_fractional = modf(a, &a_fractional);
	printf("a_fract = %.5f\n", a_fractional);
	if ((int)round(a_fractional * 10)  < (int)round(step * 10))
		res = (int)a;
	else {
		res = (int) a + 1;
	}
	return (res);
}

double	degrees_to_rad(double degrees)
{
	return (degrees * (M_PI / 180));
}

double 	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

