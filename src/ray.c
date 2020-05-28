/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 01:20:52 by cspare            #+#    #+#             */
/*   Updated: 2020/05/28 01:20:53 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	sacrifice_to_norme(t_raycast *tmp)
{
	tmp->check.x = 0;
	tmp->check.y = 0;
	tmp->intercept.x = 0;
	tmp->intercept.y = 0;
	tmp->next.x = 0;
	tmp->next.y = 0;
	tmp->step.x = 0;
	tmp->step.y = 0;
}

void	vert_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_raycast vert;

	sacrifice_to_norme(&vert);
	calc_vert_step(blazko, this_ray, &vert);
	while (vert.next.x >= 0 && vert.next.x
	<= (blazko->map.columns * TILE_SIZE - 1)
		&& vert.next.y >= 0 && vert.next.y
	<= (blazko->map.rows * TILE_SIZE - 1))
	{
		vert.check.x = vert.next.x + (this_ray->ray_is_left ? -1 : 0);
		vert.check.y = vert.next.y;
		if ((this_ray->hit_side = (find_an_obstacle(vert.check.x,
									vert.check.y, &(blazko->map)))))
			break ;
		else
		{
			vert.next.x += vert.step.x;
			vert.next.y += vert.step.y;
		}
	}
	if (!vert.check.x && !vert.check.y)
		this_ray->hit_side = 1;
	this_ray->wall_hit.x = vert.next.x;
	this_ray->wall_hit.y = vert.next.y;
	this_ray->hit_is_vert = TRUE;
}

void	get_distance(t_wolf3d *blazko, t_ray *vert_ray, t_ray *hor_ray)
{
	float distance_hor;
	float distance_ver;

	distance_hor = (hor_ray->hit_is_horz
	? calc_distance(blazko->player.pos.x, blazko->player.pos.y,
			hor_ray->wall_hit.x, hor_ray->wall_hit.y) : INT_MAX);
	distance_ver = (vert_ray->hit_is_vert
	? calc_distance(blazko->player.pos.x, blazko->player.pos.y,
			vert_ray->wall_hit.x, vert_ray->wall_hit.y) : INT_MAX);
	if (distance_hor < distance_ver)
	{
		vert_ray->distance = distance_hor;
		vert_ray->wall_hit.x = hor_ray->wall_hit.x;
		vert_ray->wall_hit.y = hor_ray->wall_hit.y;
		vert_ray->hit_side = hor_ray->hit_side;
		vert_ray->hit_is_vert = FALSE;
	}
	else
		vert_ray->distance = distance_ver;
	if (vert_ray->distance <= 0)
		vert_ray->distance = 1;
}

void	cast_this_ray(t_wolf3d *blazko, t_ray *this_ray)
{
	t_ray save_hor;

	save_hor.wall_hit.x = 0;
	save_hor.wall_hit.y = 0;
	save_hor.hit_is_horz = 0;
	save_hor.hit_side = 0;
	horz_intersect(blazko, this_ray);
	save_hor.wall_hit.x = this_ray->wall_hit.x;
	save_hor.wall_hit.y = this_ray->wall_hit.y;
	save_hor.hit_is_horz = this_ray->hit_is_horz;
	save_hor.hit_side = this_ray->hit_side;
	vert_intersect(blazko, this_ray);
	get_distance(blazko, this_ray, &save_hor);
	find_wall_side(this_ray, &(blazko->map));
}

void	raycast(t_wolf3d *blazko)
{
	int		q;
	float	ray_angle;

	q = -1;
	ray_angle = blazko->player.rot_angle - (blazko->player.fov / 2);
	while (++q < WIN_WIDTH)
	{
		blazko->rays[q].angle = normalize_angle(ray_angle);
		blazko->rays[q].ray_is_down = is_looking_down(blazko->rays[q].angle);
		blazko->rays[q].ray_is_right = is_looking_right(blazko->rays[q].angle);
		blazko->rays[q].ray_is_up = !(blazko->rays[q].ray_is_down);
		blazko->rays[q].ray_is_left = !(blazko->rays[q].ray_is_right);
		cast_this_ray(blazko, &(blazko->rays[q]));
		ray_angle += (blazko->player.fov / WIN_WIDTH);
	}
}
