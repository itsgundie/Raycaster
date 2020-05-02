
#include "../includes/wolf3d.h"


int		is_looking_up(float	*angle)
{
	return((*angle > 0.0f && *angle < (float)M_PI) ? 1 : 0);
}

int		is_looking_left(float *angle)
{
	return((*angle > 0.5f * (float)M_PI && *angle < 1.5f * (float)M_PI) ? 1 : 0);
}


float		drawing_height(float ray_dist, float proj_dist)
{
	return((TILE_SIZE / ray_dist) * proj_dist);
}

t_v2_int		calc_center(int	width, int height)
{
	t_v2_int	centr = {0};
	centr.x = width / 2;
	centr.y = height / 2;
	return(centr);
}

int     find_an_obstacle(t_v2_int coords, int **map, t_ray *this_ray)
{
	int x;
	int y;
	int x_offset;
	int y_offset;
	
	if ((coords.x < 0 || coords.x > WIN_WIDTH) || (coords.y < 0 || coords.x > WIN_HEIGHT))
		return(0);
	x_offset = ((this_ray->look_left) ? -1 : 1);
	y_offset = ((this_ray->look_up) ? -1 : 1);
	x = (coords.x + x_offset) / TILE_SIZE ;
	y = (coords.y + y_offset) / TILE_SIZE;

	this_ray->hit_index = map[x / TILE_SIZE][y / TILE_SIZE];
	return(map[x][y]);
}

int		calc_distance(t_v2_int *start, t_v2_int *end, float *angle)
{
	t_v2_float	begin;
	t_v2_float	finish;
	int			distance;

	distance = 0;
	begin.x = (float)(start->x);
	finish.x = (float)(end->x);
	begin.y = (float)(start->y);
	finish.y = (float)(end->y);
	distance = (int)(fabs((begin.x - finish.x) * cos(*angle) - (begin.y - finish.y) * sin(*angle)));
	return(distance);
}

void		find_vertical_intersection(t_ray *this_ray, t_v2_int *player_pos, int **map)
{
	t_v2_int	check = {.x = 0, .y = 0};
	t_v2_int	step;
	t_v2_int	intercept;

	intercept.x = ((player_pos->x / TILE_SIZE) * TILE_SIZE);
	intercept.x += ((this_ray->look_left) ? 0 : TILE_SIZE);
	intercept.y = (player_pos->y + (player_pos->x - (int)(((float)intercept.x) / tan(this_ray->angle))));
	step.x = ((this_ray->look_left) ? -TILE_SIZE : TILE_SIZE);
	step.y = (int)((float)TILE_SIZE * tan(this_ray->angle));
	step.y *= (((this_ray->look_up) && step.y > 0) ? -1 : 1);
	step.y *= ((!(this_ray->look_up) && step.y < 0) ? -1 : 1);
	//intercept.x += (this_ray->look_left ? -1 : 0);
	while((intercept.y + step.y) > 0 && (intercept.y + step.y) < WIN_HEIGHT
		&& (intercept.x + step.x) > 0 && (intercept.x + step.x) < WIN_WIDTH)
	{
		check.x = (intercept.x + step.x);
		check.y = (intercept.y + step.y);
		if (find_an_obstacle(check, map, this_ray))
			break ;
		intercept = check;
	//	intercept.y = check.y;
	}
	this_ray->pos = check;
//	this_ray->pos.y = check.y;
	return ;
}



void	find_horizontal_intersection(t_ray *this_ray, t_v2_int *player_pos, int **map)
{
	t_v2_int		check = {.x = 0, .y = 0};
	t_v2_int		step;
	t_v2_int		intercept;
	
	intercept.y = ((player_pos->y / TILE_SIZE) * TILE_SIZE);
	intercept.y += ((this_ray->look_up) ? -1 : TILE_SIZE);
	intercept.x = (player_pos->x + (player_pos->y - ((int)(((float)intercept.y) / tan(this_ray->angle)))));
	step.y = ((this_ray->look_up) ? -TILE_SIZE : TILE_SIZE);
	step.x = (int)((float)TILE_SIZE / tan(this_ray->angle));
	step.x *= ((this_ray->look_left && step.x > 0) ? -1 : 1);
	step.x *= ((!(this_ray->look_left) && step.x < 0) ? -1 : 1);
	//intercept.y += ((this_ray->look_up) ? -1 : 0);
	while((intercept.y + step.y) > 0 && (intercept.y + step.y) < WIN_HEIGHT 
		&& (intercept.x + step.x) > 0 && (intercept.x + step.x) < WIN_WIDTH)
	{
	check.y = (intercept.y + step.y);
	check.x = (intercept.x + step.x);
	if (find_an_obstacle(check, map, this_ray))
		break ;
	intercept = check;
	//intercept.y = check.y;
	}
	this_ray->pos = check;
	//this_ray->pos.y = check.y;
	return ;
}



void		find_wall(t_ray *this_ray, t_v2_int *player_pos, int **map)
{
	int		    vertical_distance;
	int	    	horizontal_distance;
	int			hit_index;
	t_v2_int	hor_hit = {0};

	hit_index = 0;
    vertical_distance = horizontal_distance = INT_MAX;
	this_ray->look_up = is_looking_up(&(this_ray->angle));
	this_ray->look_left = is_looking_left(&(this_ray->angle));
	find_horizontal_intersection(this_ray, player_pos, map);
	hor_hit = this_ray->pos;
	hit_index = this_ray->hit_index;
	horizontal_distance = calc_distance(player_pos , &(this_ray->pos), &(this_ray->angle));
    find_vertical_intersection(this_ray, player_pos, map);
	vertical_distance = calc_distance(player_pos ,&(this_ray->pos), &(this_ray->angle));
    this_ray->distance = ((horizontal_distance < vertical_distance) 
                        ? horizontal_distance : vertical_distance);
	this_ray->pos = ((horizontal_distance < vertical_distance) 
                        ? hor_hit : this_ray->pos);
	//this_ray->pos.y = ((horizontal_distance < vertical_distance) 
    //                    ? hor_hit.y : 0);
	this_ray->hit_index = ((horizontal_distance < vertical_distance) 
                        ? hit_index : 0);
	this_ray->hit_is_hor = ((horizontal_distance < vertical_distance) 
                        ? 1 : 0);
	return ;
}
