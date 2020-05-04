#include "../includes/wolf3d.h"

float		angle_between_rays(float fov)
{
	return(fov / WIN_WIDTH);
}

void    calculate_rays_angles(t_wolfec *w, float angle_step)
{
    int     q;
    float   this_angle;
    
    q = 0;
    // w->player.angle = normalize_angle(w->player.angle);
    this_angle = normalize_angle(w->ray[0].angle - angle_step);
    while (++q < WIN_WIDTH)
    {
        w->ray[q].angle = this_angle;
        this_angle = normalize_angle(this_angle - angle_step);
    }
    return ;
}

void    update(t_wolfec *w)
{
    int q;

    q = -1;

    // w->player.pos.x = TILE_SIZE * (int)w->player.pos_float.x;
    // w->player.pos.y = TILE_SIZE * (int)w->player.pos_float.y;
     w->player.angle = normalize_angle(w->player.angle);
    w->ray[0].angle = normalize_angle(w->player.angle + (w->player.fov / 2));
    calculate_rays_angles(w, normalize_angle(angle_between_rays(w->player.fov)));
    while(++q < WIN_WIDTH)
    {
        find_wall(&(w->ray[q]), &(w->player.pos), (w->map));
    }
    return ;
}