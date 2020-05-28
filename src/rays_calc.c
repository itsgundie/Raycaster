/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 23:59:21 by cspare            #+#    #+#             */
/*   Updated: 2020/05/28 23:59:24 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	calc_vert_step(t_wolf3d *blazko, t_ray *this_ray, t_raycast *vert)
{
	vert->intercept.x = floor(blazko->player.pos.x / TILE_SIZE) * TILE_SIZE;
	vert->intercept.x += (this_ray->ray_is_right ? TILE_SIZE : 0);
	vert->intercept.y = blazko->player.pos.y
	+ (vert->intercept.x - blazko->player.pos.x) * tan(this_ray->angle);
	vert->step.x = TILE_SIZE;
	vert->step.x *= (this_ray->ray_is_left ? -1 : 1);
	vert->step.y = TILE_SIZE * tan(this_ray->angle);
	vert->step.y *= (this_ray->ray_is_up && vert->step.y > 0) ? -1 : 1;
	vert->step.y *= (this_ray->ray_is_down && vert->step.y < 0) ? -1 : 1;
	vert->next.x = vert->intercept.x;
	vert->next.y = vert->intercept.y;
}

int		find_an_obstacle(float x, float y, t_2dmap *kapta)
{
	t_v2int check;

	if (x <= 0 || x >= (kapta->columns * TILE_SIZE - 1)
		|| y <= 0 || y >= (kapta->rows * TILE_SIZE - 1))
		return (TRUE);
	check.x = (int)(x / TILE_SIZE);
	check.y = (int)(y / TILE_SIZE);
	return (kapta->map[check.y][check.x] == 1);
}

void	find_wall_side(t_ray *this_ray, t_2dmap *kapta)
{
	if (this_ray->hit_side)
	{
		if (this_ray->hit_is_vert)
		{
			(this_ray->ray_is_up && this_ray->ray_is_left)
			? this_ray->hit_side = 1 : 0;
			(this_ray->ray_is_up && this_ray->ray_is_right)
			? this_ray->hit_side = 3 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_right)
			? this_ray->hit_side = 3 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_left)
			? this_ray->hit_side = 1 : 0;
		}
		else
		{
			(this_ray->ray_is_up && this_ray->ray_is_left)
			? this_ray->hit_side = 2 : 0;
			(this_ray->ray_is_up && this_ray->ray_is_right)
			? this_ray->hit_side = 2 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_right)
			? this_ray->hit_side = 0 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_left)
			? this_ray->hit_side = 0 : 0;
		}
	}
}

void	calc_horz_step(t_wolf3d *blazko, t_ray *this_ray, t_raycast *hor)
{
	hor->intercept.y = floor(blazko->player.pos.y / TILE_SIZE) * TILE_SIZE;
	hor->intercept.y += (this_ray->ray_is_down) ? TILE_SIZE : 0;
	hor->intercept.x = blazko->player.pos.x
	+ (hor->intercept.y - blazko->player.pos.y) / tan(this_ray->angle);
	hor->step.y = ((this_ray->ray_is_up) ? -1 : 1) * TILE_SIZE;
	hor->step.x = TILE_SIZE / tan(this_ray->angle);
	hor->step.x *= (this_ray->ray_is_left && hor->step.x > 0) ? -1 : 1;
	hor->step.x *= (this_ray->ray_is_right && hor->step.x < 0) ? -1 : 1;
	hor->next.x = hor->intercept.x;
	hor->next.y = hor->intercept.y;
}

void	horz_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_raycast hor;

	sacrifice_to_norme(&hor);
	calc_horz_step(blazko, this_ray, &hor);
	while (hor.next.x >= 0 && hor.next.x
	<= (blazko->map.columns * TILE_SIZE - 1)
	&& hor.next.y >= 0 && hor.next.y <= (blazko->map.rows * TILE_SIZE - 1))
	{
		hor.check.x = hor.next.x;
		hor.check.y = hor.next.y + (this_ray->ray_is_up ? -1 : 0);
		if ((this_ray->hit_side = (find_an_obstacle(hor.check.x,
									hor.check.y, &(blazko->map)))))
			break ;
		else
		{
			hor.next.x += hor.step.x;
			hor.next.y += hor.step.y;
		}
	}
	if (!hor.check.x && !hor.check.y)
		this_ray->hit_side = 1;
	this_ray->wall_hit.x = hor.next.x;
	this_ray->wall_hit.y = hor.next.y;
	this_ray->hit_is_horz = TRUE;
}
