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

void horz_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_v2 intercept_hor;
	t_v2 step_hor;
	t_v2 next_hor;
	t_v2 check_hor = {0};

	intercept_hor.y = floor(blazko->player.pos.y / TILE_SIZE) * TILE_SIZE;
	intercept_hor.y += (this_ray->ray_is_down) ? TILE_SIZE : 0;
	intercept_hor.x = blazko->player.pos.x + 
		(intercept_hor.y - blazko->player.pos.y) / tan(this_ray->angle);
	step_hor.y = ((this_ray->ray_is_up) ? -1 : 1) * TILE_SIZE;
	step_hor.x = TILE_SIZE / tan(this_ray->angle);
	step_hor.x *= (this_ray->ray_is_left && step_hor.x > 0) ? -1 : 1;
	step_hor.x *= (this_ray->ray_is_right && step_hor.x < 0) ? -1 : 1;
	next_hor.x = intercept_hor.x;
	next_hor.y = intercept_hor.y;
	while (next_hor.x >= 0 && next_hor.x <= (blazko->map.columns * TILE_SIZE)
			&& next_hor.y >= 0 && next_hor.y <= (blazko->map.rows * TILE_SIZE))
	{
		check_hor.x = next_hor.x;
		check_hor.y = next_hor.y + (this_ray->ray_is_up ? -1 : 0);

		if ((find_an_obstacle(check_hor.x, check_hor.y, &(blazko->map))))
			break;
		else
		{
			next_hor.x += step_hor.x;
			next_hor.y += step_hor.y;
		}
	}
	if (!check_hor.x && !check_hor.y)
	    this_ray->hit_side = 1;
	this_ray->wall_hit.x = next_hor.x;
	this_ray->wall_hit.y = next_hor.y;
	this_ray->hit_is_horz = TRUE;
}

void	cast_this_ray(t_wolf3d *blazko, t_ray *this_ray)
{
	t_v2 intercept_hor;
	t_v2 step_hor;
	t_v2 next_hor;
	t_v2 check_hor;
	t_v2 hit_point_hor = {0};
	int	 was_hit_horizont = FALSE;
	int side_index_hor = 0;
	t_ray save_ray = *this_ray;

	horz_intersect(blazko, this_ray);
	hit_point_hor.x = this_ray->wall_hit.x;
	hit_point_hor.y = this_ray->wall_hit.y;
	was_hit_horizont = this_ray->hit_is_horz;
	side_index_hor = this_ray->hit_side;
	
	/// VERTICAL INTERSECTION ///

	t_v2 intercept_ver;
	t_v2 step_ver;
	t_v2 next_ver;
	t_v2 check_ver = {0};
	t_v2 hit_point_ver = {0};
	int	 was_hit_vert = FALSE;
	int side_index_ver = 0;

	intercept_ver.x = floor(blazko->player.pos.x / TILE_SIZE) * TILE_SIZE;
	intercept_ver.x += (this_ray->ray_is_right ? TILE_SIZE : 0);

	intercept_ver.y = blazko->player.pos.y + (intercept_ver.x - blazko->player.pos.x) * tan(this_ray->angle);

	step_ver.x = TILE_SIZE;
	step_ver.x *= (this_ray->ray_is_left ? -1 : 1);

	step_ver.y = TILE_SIZE * tan(this_ray->angle);
	step_ver.y *= (this_ray->ray_is_up && step_ver.y > 0) ? -1 : 1;
	step_ver.y *= (this_ray->ray_is_down && step_ver.y < 0) ? -1 : 1;

	next_ver.x = intercept_ver.x;
	next_ver.y = intercept_ver.y;

	while (next_ver.x >= 0 && next_ver.x <= (blazko->map.columns * TILE_SIZE) 
		&& next_ver.y >= 0 && next_ver.y <= (blazko->map.rows * TILE_SIZE))
	{
		check_ver.x = next_ver.x + (this_ray->ray_is_left ? -1 : 0);
		check_ver.y = next_ver.y;

		if ((find_an_obstacle(check_ver.x, check_ver.y, &(blazko->map))))
		{
			 hit_point_ver.x = next_ver.x;
			 hit_point_ver.y = next_ver.y;
			 was_hit_vert = TRUE;
			 break;
		}
		else
		{
			next_ver.x += step_ver.x;
			next_ver.y += step_ver.y;
		}
	}
	if (!check_ver.x && !check_ver.y)
	{
		check_ver.x = next_ver.x + (this_ray->ray_is_left ? -1 : 0);
		check_ver.y = next_ver.y;	
	}
	side_index_ver = find_an_obstacle(check_ver.x, check_ver.y, &(blazko->map));

	//// DISTANCE ///

	float distance_hor = (was_hit_horizont ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y, hit_point_hor.x, hit_point_hor.y) : INT_MAX);
	
	float distance_ver = (was_hit_vert ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y, hit_point_ver.x, hit_point_ver.y) : INT_MAX);
	
	if (distance_ver <= distance_hor)
	{
		this_ray->distance = (distance_ver <= 0 ? 1 : distance_ver);
		this_ray->wall_hit.x = hit_point_ver.x;
		this_ray->wall_hit.y = hit_point_ver.y;
		this_ray->hit_side = side_index_ver;
		this_ray->hit_is_vert = TRUE;
	}
	else
	{
		{
		this_ray->distance = (distance_hor <= 0 ? 1 : distance_hor);
		this_ray->wall_hit.x = hit_point_hor.x;
		this_ray->wall_hit.y = hit_point_hor.y;
		this_ray->hit_side = side_index_hor;
		this_ray->hit_is_vert = FALSE;
	}
	find_wall_side(this_ray, &(blazko->map));
	}
}

void	raycast(t_wolf3d *blazko)
{
	int q;

	q = -1;
	float ray_angle = blazko->player.rotation_angle - (blazko->player.fov / 2);
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