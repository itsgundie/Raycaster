#include "../includes/wolf3d.h"

void	make_a_move(t_wolf3d *blazko, float delta_time)
{
	float	move_step;
	t_v2	new_pos;

	blazko->player.rot_angle += (((blazko->player.turn_direction)
			* (blazko->player.rotate_speed)));
<<<<<<< HEAD
	blazko->player.rot_angle = normalize_angle(blazko->player.rot_angle);
=======
	blazko->player.
	rot_angle = normalize_angle(blazko->player.rot_angle);
>>>>>>> 8e688ce27f0910279bd62fbc66583871641c10e6
	move_step = blazko->player.walk_direction * blazko->player.move_speed;
	new_pos.x = (blazko->player.pos.x
	+ cos(blazko->player.rot_angle) * move_step);
	new_pos.y = (blazko->player.pos.y
	+ sin(blazko->player.rot_angle) * move_step);
	if (!(find_an_obstacle(floor(new_pos.x), floor(new_pos.y), &(blazko->map))))
	{
		blazko->player.pos.x = new_pos.x;
		blazko->player.pos.y = new_pos.y;
	}
}

void	update(t_wolf3d *blazko, long long *ticks_last_frame)
{
	int		time_to_wait;
	float	delta_time;
	Uint32	ticks;

	time_to_wait = blazko->frame_time - (SDL_GetTicks() - *ticks_last_frame);
	if (time_to_wait > 0 && time_to_wait <= blazko->frame_time)
		SDL_Delay(time_to_wait);
	ticks = SDL_GetTicks();
	while (!(SDL_TICKS_PASSED(ticks, (*ticks_last_frame + blazko->frame_time))))
		ticks = SDL_GetTicks();
	delta_time = (SDL_GetTicks() - *ticks_last_frame) * 1000.0f;
	*ticks_last_frame = SDL_GetTicks();
	raycast(blazko);
}

void	clear_color_buf(uint32_t *color_buf, uint32_t color)
{
	int x;
	int y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			color_buf[(WIN_WIDTH * y) + x] = color;
	}
}

int		main(int argc, char **argv)
{
	t_wolf3d	*blazko;
	int			fd;
	long long	ticks_last_frame;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("usage: ./wolf3d map");
	ticks_last_frame = SDL_GetTicks();
	if (!(blazko = init()))
		return (1);
	if (file_parser(blazko, fd))
		create_map(blazko);
	setup(blazko);
	music_on(blazko);
	while (1)
	{
		if (!(put_in(blazko)))
			break ;
		update(blazko, &ticks_last_frame);
		make_a_move(blazko, ticks_last_frame);
		render(blazko);
	}
	destroy(blazko);
	return (0);
}
