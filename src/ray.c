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

int		find_an_obstacle(float x, float y, t_2dmap *kapta)
{
	t_v2int check;

	if (x <= 0 || x >= (kapta->columns * TILE_SIZE - 1)
		|| y <= 0 || y >= (kapta->rows * TILE_SIZE - 1))
		return (TRUE);
	check.x = (int)(x / TILE_SIZE);
	check.y = (int)(y / TILE_SIZE);
	return(kapta->map[check.y][check.x] == 1);
}

void	find_wall_side(t_ray *this_ray, t_2dmap *kapta)
{
	if (this_ray->hit_side)
	{
		if (this_ray->hit_is_vert)
		{
			(this_ray->ray_is_up && this_ray->ray_is_left) ? this_ray->hit_side = 1 : 0;
			(this_ray->ray_is_up && this_ray->ray_is_right) ? this_ray->hit_side = 3 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_right) ? this_ray->hit_side = 3 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_left) ? this_ray->hit_side = 1 : 0;
		}
		else
		{
			(this_ray->ray_is_up && this_ray->ray_is_left) ? this_ray->hit_side = 2 : 0;
			(this_ray->ray_is_up && this_ray->ray_is_right) ? this_ray->hit_side = 2 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_right) ? this_ray->hit_side = 0 : 0;
			(this_ray->ray_is_down && this_ray->ray_is_left) ? this_ray->hit_side = 0 : 0;
		}	
	}
	return ;
}

void	calc_horz_step(t_wolf3d *blazko, t_ray *this_ray, t_raycast *hor)
{
	hor->intercept.y = floor(blazko->player.pos.y / TILE_SIZE) * TILE_SIZE;
	hor->intercept.y += (this_ray->ray_is_down) ? TILE_SIZE : 0;
	hor->intercept.x = blazko->player.pos.x + 
		(hor->intercept.y - blazko->player.pos.y) / tan(this_ray->angle);
	hor->step.y = ((this_ray->ray_is_up) ? -1 : 1) * TILE_SIZE;
	hor->step.x = TILE_SIZE / tan(this_ray->angle);
	hor->step.x *= (this_ray->ray_is_left && hor->step.x > 0) ? -1 : 1;
	hor->step.x *= (this_ray->ray_is_right && hor->step.x < 0) ? -1 : 1;
	hor->next.x = hor->intercept.x;
	hor->next.y = hor->intercept.y;

}

void	horz_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_raycast hor = {0};

	calc_horz_step(blazko, this_ray, &hor);
	while (hor.next.x >= 0 && hor.next.x <= (blazko->map.columns * TILE_SIZE - 1)
			&& hor.next.y >= 0 && hor.next.y <= (blazko->map.rows * TILE_SIZE - 1))
	{
		hor.check.x = hor.next.x;
		hor.check.y = hor.next.y + (this_ray->ray_is_up ? -1 : 0);

		if ((this_ray->hit_side = (find_an_obstacle(hor.check.x,
									hor.check.y, &(blazko->map)))))
			break;
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

void	calc_vert_step(t_wolf3d *blazko, t_ray *this_ray, t_raycast *vert)
{
	vert->intercept.x = floor(blazko->player.pos.x / TILE_SIZE) * TILE_SIZE;
	vert->intercept.x += (this_ray->ray_is_right ? TILE_SIZE : 0);
	vert->intercept.y = blazko->player.pos.y + (vert->intercept.x - blazko->player.pos.x) * tan(this_ray->angle);
	vert->step.x = TILE_SIZE;
	vert->step.x *= (this_ray->ray_is_left ? -1 : 1);
	vert->step.y = TILE_SIZE * tan(this_ray->angle);
	vert->step.y *= (this_ray->ray_is_up && vert->step.y > 0) ? -1 : 1;
	vert->step.y *= (this_ray->ray_is_down && vert->step.y < 0) ? -1 : 1;
	vert->next.x = vert->intercept.x;
	vert->next.y = vert->intercept.y;
}

void	vert_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_raycast vert = {0};

	calc_vert_step(blazko, this_ray, &vert);
	while (vert.next.x >= 0 && vert.next.x <= (blazko->map.columns * TILE_SIZE - 1) 
		&& vert.next.y >= 0 && vert.next.y <= (blazko->map.rows * TILE_SIZE - 1))
	{
		vert.check.x = vert.next.x + (this_ray->ray_is_left ? -1 : 0);
		vert.check.y = vert.next.y;

		if ((this_ray->hit_side = (find_an_obstacle(vert.check.x,
									vert.check.y, &(blazko->map)))))
			 break;
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

	distance_hor = (hor_ray->hit_is_horz ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y,
			 hor_ray->wall_hit.x, hor_ray->wall_hit.y) : INT_MAX);
	distance_ver = (vert_ray->hit_is_vert ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y,
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
	t_ray save_hor = {.wall_hit.x = 0, .wall_hit.y = 0,
						.hit_is_horz = 0, .hit_side = 0};

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
	int q;

	q = -1;
	float ray_angle = blazko->player.rot_angle - (blazko->player.fov / 2);
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
