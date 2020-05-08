/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:46:05 by llifeboa          #+#    #+#             */
/*   Updated: 2020/02/17 22:52:27 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include <math.h>

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

float			vec3_dot(t_vec3 v1, t_vec3 v2);
float			vec3_length(t_vec3 v);
t_vec3			vec3_div(t_vec3 v, float s);
t_vec3			vec3_normalize(t_vec3 v);
t_vec3			vec3_mult(t_vec3 v, float s);
t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);

#endif
