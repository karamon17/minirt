/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:16:17 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/08/01 16:16:18 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	color_multiply(t_color color, float intecivity)
{
    t_color res;

    res.red = color.red * intecivity;
    res.green = color.green * intecivity;
    res.blue = color.blue * intecivity;
    res.red = res.red > 255 ? 255 : res.red;
    res.green = res.green > 255 ? 255 : res.green;
    res.blue = res.blue > 255 ? 255 : res.blue;
    return (res);
}

int color_to_int(t_color color)
{
	int r;
	int g;
	int b;
	int t;

	t = round(color.transparency);
	r = round(color.red);
	g = round(color.green);
	b = round(color.blue);
	return ((t << 24 | r << 16 | g << 8 | b));
}

t_color color_new(float r, float g, float b) {
	t_color color;

	color.transparency = 0;
	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

int get_color(t_data *data, t_vector ray)
{
    float 		closest_dist;
    t_figure 	*cl_fig;
	t_vectors	t;

    cl_fig = closest_inters(data->figures, data->camera->origin, ray, &closest_dist);
    if (cl_fig && closest_dist != INFINITY)
    {
		t.v1 = mult_vect2(closest_dist, ray);
		t.v2 = vector_subtract2(t.v1, cl_fig->center);
		if (cl_fig->type == CYLINDER)
			t.v2 = vector_subtract2(t.v1, vector_add2(mult_vect2(cl_fig->body.cyl.height / 2, cl_fig->body.cyl.normal), cl_fig->center));
        if (cl_fig->type == PLANE && cl_fig->body.plane.normal.z > 0)
			t.v2 = cl_fig->body.plane.normal;
		else if (cl_fig->type == PLANE && cl_fig->body.plane.normal.z <= 0)
			t.v2 = mult_vect2(-1, cl_fig->body.plane.normal);
		vector_normalize(t.v2);
		t.v4 = mult_vect2(data->camera->direction.z, ray);
		return(color_to_int(color_multiply(cl_fig->rgb_color, compute_lighting(data, &t, cl_fig->specular))));
    }
	else
    	return (color_to_int(color_new(0, 0, 0)));
}
