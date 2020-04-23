#include "../includes/wolf3d.h"

int		is_looking_up(float	*angle)
{
	return((*angle > 0.0f && *angle < (float)M_PI) ? 1 : 0);
}

int		is_looking_left(float *angle)
{
	return((*angle > 0.5f * (float)M_PI && *angle < 1.5f * (float)M_PI) ? 1 : 0);
}

float		angle_between_rays(float fov)
{
	return(fov / WIN_WIDTH);
}

void    calculate_rays_angles(t_wolfec *w, float angle_step)
{
    int     q;
    float   this_angle;
    
    q = -1;
    w->player.angle = normalize_angle(w->player.angle);
    this_angle = normalize_angle(w->player.angle - (w->player.fov / 2));
    while (++q < WIN_WIDTH)
    {
        w->rays[q] = this_angle;
        this_angle = normalize_angle(this_angle + angle_step);
    }
    return(void);
}

void    update(t_wolfec *w)
{
    int q;

    q = -1;
    calculate_rays_angles(w, angle_between_rays(w->player.fov));
    while(++q < WIN_WIDTH)
    {
        find_wall(&(w->ray[q]), &(w->player.pos_int), &(w->map));
    }
    return ;
}