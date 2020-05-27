#include "../includes/wolf3d.h"

float	normalize_angle(float angle)
{
	float norm_angle;

	norm_angle = angle;
	if (norm_angle > TWO_PI)
		norm_angle = remainderf(angle, TWO_PI);
	if (norm_angle < 0)
		norm_angle = TWO_PI + norm_angle;
	return (norm_angle);
}

float	calc_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int		is_looking_down(float angle)
{
	return (angle >= 0 && angle <= PI);
}

int		is_looking_right(float angle)
{
	return ((angle <= (0.5 * PI)) || (angle >= (1.5 * PI)));
}
