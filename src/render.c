
#include "../includes/wolf3d.h"




int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};






float		distance_projected(t_v2d ray, t_player blazco)
{
	//t_v2d	projected_distance = {.x = 0, .y = 0};
	float	corrected_distance;

	corrected_distance = 0.0f;
	/* projected_distance.x = intersection.x - blazco.x;
	projected_distance.y = intersection.y - blazco.y;
	projected_distance.x *= cos(blazco.angle);
	projected_distance.y *= sin(blazco.angle); */
	corrected_distance = projected_distance.x - projected_distance.y;
	return();
}

int		calc_center(int	width, int height)
{
	return(t_v2d = {.x = width / 2, .y = height / 2});
}


float		angle_between_rays()
{
	return(FOV / WIN_WIDTH);
}


float       calc_distance(float x1, float y1, float x2, float y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float		calc_distance_projected(t_v2d start, t_v2d end, float angle)
{
	return(abs((start.x - end.x) * cos(angle) - (start.y - end.y) * sin(angle)))
}


float		distance_to_projection_plane()
{
	return((WIN_WIDTH / 2) / tan(FOV / 2));
}

float		cloumn_height(float ray_dist, float proj_dist)
{
	return((TILE_SIZE / ray_dist) * proj_dist);
}


float       norm_angle(float angle)
{
	andgle = angle % (2 * PI);
	if (angle < 0)
		angle = (2 * PI) + angle;
	return(angle);
}


float       degrees_to_rads(float degrees)
{
	return(degrees * (PI / 180));
}

float		normalize_angle(float angle)
{
	return(fabs(angle % (2 * M_PI)));
}


int		find_horizontal_intersection(float angle, t_v2d origin)
{
	t_v2d		check = {.x = 0, .y = 0};
	int			ray_is_up;
	t_v2d		step;
	t_v2d		intercept;
	t_v2d		adder;
	
	intercept.y = ((origin->y / TILE_SIZE) * TILE_SIZE);
	intercept.y += (ray_is_up ? 0 : TILE_SIZE);
	intercept.x = (origin->x + (origin->y - (intercept.y) / tan(angle));
	step.y = (ray_is_up ? -TILE_SIZE : TILE_SIZE);
	step.x = (TILE_SIZE / tan(angle));
	step.x *= ((ray_is_left && step.x > 0) ? -1 : 1);
	step.x *= ((!ray_is_left && step.x < 0) ? -1 : 1);
	intercept.y += (ray_is_up ? -1 : 0);
	
	while((intercept.y + step.y) > 0 && (intercept.y + step.y) < WIN_HEIGH && (intercept.x + step.x) > 0 && (intercept.x + step.x) < WIN_WIDTH)
	{
	check.y = (int)(intercept.y + step.y);
	check.x = (int)(intercept.x + step.x);
	if (find_an_obstacle(((int)check.x / TILE_SIZE),((int)check.y / TILE_SIZE)))
		break;
	intercept.x = check.x;
	intercept.y = check.y;
	}
}


int		find_vertical_intersection(float angle, t_v2d origin)
{
	t_v2d	check = {.x = 0, .y = 0};
	t_v2d	step;
	t_v2d	intercept;
	int		ray_is_left;
	int		ray_is_up;

	intercept.x = ((origin->x / TILE_SIZE) * TILE_SIZE);
	intercept.x += (ray_is_left ? 0 : TILE_SIZE);
	intercept.y = (origin->y + (origin->x - (intercept.x) / tan(angle)));
	step.x = (ray_is_left ? -TILE_SIZE : TILE_SIZE);
	step.y = (TILE_SIZE * tan(angle));
	step.y *= ((ray_is_up && step.y > 0) ? -1 : 1);
	step.y *= ((!ray_is_up && step.y < 0) ? -1 : 1);
	intercept.x += (ray_is_left ? -1 : 0);

	while((intercept.y + step.y) > 0 && (intercept.y + step.y) < WIN_HEIGH && (intercept.x + step.x) > 0 && (intercept.x + step.x) < WIN_WIDTH)
	{
		check.x = (int)(intercept.x + step.x);
		check.y = (int)(intercept.y + step.y);
		if (find_an_obstacle(((int)check.x / TILE_SIZE), (int)check.y / TILE_SIZE))
			break ;
		intercept.x = check.x;
		intercept.y = check.y;
	}
}

}


int		is_ray_up(t_ray	*ray)
{
	return(ray->ray_is_up = (ray->angle > 0 && ray->angle < M_PI) ? 1 : 0);
}

int		is_ray_left(t_ray *ray)
{
	return(ray->ray_is_left = (ray->angle > 0.5 * M_PI && ray->angle < 1.5 * M_PI) ? 1 : 0);
}



int		find_vertical_intersection(float angle, t_v2d	origin)
{
	t_v2d		check = {.x = 0, .y = 0};
	int			ray_is_up;
	t_v2d		start;
	t_v2d		intercept;
	t_v2d		step;

	ray_is_left = (find_ray_orientation);
	ray_is_up = (origin->ray_is_left ? -1 : TILE_SIZE);
	intercept.y = ((origin->y / TILE_SIZE) * TILE_SIZE + ray_is_up);
	intercept.x = (origin->x + (origin->y - (intercept.y) / tan(angle));
	step.x = (ray_is_up ? -TILE_SIZE : TILE_SIZE);
wes	step.y = step.x / tan(angle);
	while(1)
	{
	check.y = (int)(intercept.y + step.y);
	check.x = (int)(intercept.x + step.x);
	if (find_an_obstacle(((int)check.x / TILE_SIZE),((int)check.y / TILE_SIZE)))
		break;
	intercept.x = check.x;
	intercept.y = check.y;
	}
}



int		find_wall(t_player blazco)
{
	float	vertical_distance;
	float	horizontal_distance;
	t_v2d	hit;
	float	distance;
	int		column_num;

	column_num = 0;

	while (column_num < WIDTH)
	{
		if (!horizontal_distance = calc_distance(find_horizontal_intersection()))
			horizontal_distance = __INT_MAX__;
		if (!vertical_distance = calc_distance(find_vertical_intersection()))
			vertical_distance = __INT_MAX__;
		hit.x = ((horizontal_distance < vertical_distance) ? horz.x : vert.x);
		hit.y = ((horizontal_distance < vertical_distance) ? horz.y : vert.y);
		total_distance = ((horizontal_distance < vertical_distance) ? horizontal_distance : vertical_distance);
	}

}




void	cast_some_rays(t_ray )
{
	int	num_of_rays = FOV / WIN_WIDTH;
	t_ray banch_of_rays[num_of_rays] = {0};
	int	q;

	q = -1;
	while (++q < num_of_rays)
	{
		(bunch_of_rays[q]).distance = ()
	}

}






void	render_it(t_wolfec *w)
{
	
	
	SDL_RenderCopy(w->rend, w->back, NULL, NULL);
	SDL_RenderPresent(w->rend);
}



