#include "../../includes/miniRT.h"

void	press_camera_rotation_keys(int keycode, t_data *data)
{
	if (keycode == KEY_1)
		rotate_camera(data, data->movement->rotate_y_right);
	else if (keycode == KEY_3)
		rotate_camera(data, data->movement->rotate_y_left);
	else if (keycode == KEY_5)
		rotate_camera(data, data->movement->rotate_x_right);
	else if (keycode == KEY_2)
		rotate_camera(data, data->movement->rotate_x_left);
}

void	rotate_camera(t_data *data, t_quaternion direction)
{
	t_figure	*figure;
	t_vector	temp_h;
	t_vector	c;

	figure = data->figures;
	while (figure)
	{
		if (figure->type == SPHERE)
			rotate_figure_for_camera(data, &figure->center, direction);
		else if (figure->type == PLANE)
			rotate_figure_for_camera(data,
				&figure->body.plane.normal, direction);
		else if (figure->type == CYLINDER)
		{
			temp_h = mult_vect2(figure->body.cyl.height,
					figure->body.cyl.normal);
			c = vector_add2(figure->center, temp_h);
			rotate_figure_for_camera(data, &c, direction);
			figure->center = vector_subtract2(c, temp_h);
		}
		figure = figure->next;
	}
	rotate_light_for_camera(data, direction);
}

void	rotate_light_for_camera(t_data *data, t_quaternion direction)
{
	if (data->lights->type != 'L')
		rotate_figure_for_camera(data, &data->lights->next->vector, direction);
	else
		rotate_figure_for_camera(data, &data->lights->vector, direction);
}

void	rotate_figure_for_camera(t_data *data,
			t_vector *figure_center, t_quaternion direction)
{
	t_vector	rotation_point;

	rotation_point = data->camera->origin;
	vector_subtract2(*figure_center, rotation_point);
	rotate_quaternion(figure_center, direction);
	vector_add2(*figure_center, rotation_point);
}

void	press_camera_movement_keys(int keycode, t_data *data)
{
	if (keycode == KEY_UP_ARROW)
		move_camera(data, data->camera->up_vector, 1);
	else if (keycode == KEY_DOWN_ARROW)
		move_camera(data, data->camera->up_vector, 0);
	else if (keycode == KEY_LEFT_ARROW)
		move_camera(data, data->camera->right_vector, 0);
	else if (keycode == KEY_RIGHT_ARROW)
		move_camera(data, data->camera->right_vector, 1);
	else if (keycode == KEY_PLUS)
		move_camera(data, data->camera->direction, 0);
	else if (keycode == KEY_MINUS)
		move_camera(data, data->camera->direction, 1);
}
