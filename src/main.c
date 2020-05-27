#include "../includes/wolf3d.h"

void	make_a_move(t_wolf3d *blazko, float delta_time)
{
	float move_step;
	t_v2	new_pos;

	printf( "player angle before move is %f\n",blazko->player.rot_angle);
	printf( "player before move x - %f and y - %f\n", blazko->player.pos.x, blazko->player.pos.y);
	blazko->player.rot_angle += (((blazko->player.turn_direction)
			* (blazko->player.rotate_speed)));
	blazko->player.rot_angle = normalize_angle(blazko->player.rot_angle);
	move_step = blazko->player.walk_direction * blazko->player.move_speed;
	new_pos.x = (blazko->player.pos.x + cos(blazko->player.rot_angle) * move_step);
	new_pos.y = (blazko->player.pos.y + sin(blazko->player.rot_angle) * move_step);
	printf("this is a move_step - %f\n", move_step);
	printf("this is a new_pos.x - %f\n", new_pos.x);
	printf("this is a new_pos.y - %f\n", new_pos.y);
	if (!(find_an_obstacle(floor(new_pos.x) ,floor(new_pos.y), &(blazko->map))))
	{
		blazko->player.pos.x = new_pos.x;
		blazko->player.pos.y = new_pos.y;
	}
	printf( "player angle after move is %f\n",blazko->player.rot_angle);
	printf( "player after move x - %f and y - %f\n", blazko->player.pos.x, blazko->player.pos.y);
}

void	update(t_wolf3d *blazko, long long *ticks_last_frame)
{
	int time_to_wait;
	time_to_wait = blazko->frame_time - (SDL_GetTicks() - *ticks_last_frame);

	if (time_to_wait > 0 && time_to_wait <= blazko->frame_time)
		SDL_Delay(time_to_wait);

	while(!(SDL_TICKS_PASSED(SDL_GetTicks(), (*ticks_last_frame + blazko->frame_time))));

	float delta_time = (SDL_GetTicks() - *ticks_last_frame) * 1000.0f;
	*ticks_last_frame = SDL_GetTicks();
	//make_a_move(blazko, delta_time);
	raycast(blazko); //?
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
	t_wolf3d *blazko;
	int fd;
	long long ticks_last_frame;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("usage: ./wolf3d map");
	ticks_last_frame = SDL_GetTicks();
	if (!(blazko = init()))
		return (1);
	if (file_parser(blazko, fd))
		create_map(blazko);
	setup(blazko);
	music_on(blazko);
	int i = 0;
	int i2 = 0;
	while(1)
	{
		if (!(put_in(blazko)))
			break ;
		update(blazko, &ticks_last_frame);
		make_a_move(blazko, ticks_last_frame);
		render(blazko);
	}
	destroy(blazko);
	return(0);
}