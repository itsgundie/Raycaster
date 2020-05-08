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
    t_v2_int map_size;
    q = -1;

    // float forward_x = cos(w->player.angle);
    // float forward_y = -sin(w->player.angle);
    // float right_x = -forward_x;
    // float right_y = forward_x;
    

    map_size.x = (w->params_vars.line_width * (TILE_SIZE - 1));
    map_size.y = (w->params_vars.number_of_lines * (TILE_SIZE - 1));

    w->player.angle = normalize_angle(w->player.angle);
    w->ray[0].angle = normalize_angle(w->player.angle + (w->player.fov / 2));
    calculate_rays_angles(w, normalize_angle(angle_between_rays(w->player.fov)));
    while(++q < WIN_WIDTH)
    {
        if (q > 62)
            write(1, "\n", 1);
        find_wall(&(w->ray[q]), &(w->player.pos), (w->map), map_size);
    }
    return ;
}