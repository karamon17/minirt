#include "../../includes/miniRT.h"

void init_mlx_data(t_data *data);

void init_move_data(t_data *data);

t_data *init_data(char *input) {

	t_data *rt_data;

	rt_data = malloc(sizeof(t_data));
	rt_data->filename = input;
	rt_data->lights = NULL;
	rt_data->figures = NULL;
	init_checker(rt_data);
	init_mlx_data(rt_data);
	init_move_data(rt_data);
	return (rt_data);
}

void init_move_data(t_data *data) {

	t_movement *move;

	move = malloc(sizeof(t_movement));
	move->up = vector_new(0, 1, 0);
	move->down = vector_new(0, -1, 0);
	move->left = vector_new(-1, 0, 0);
	move->right = vector_new(1, 0, 0);
	move->forward = vector_new(0, 0, 1);
	move->backward = vector_new(0, 0, -1);
			
	data->movement = move;

}

void init_mlx_data(t_data *data) {
	t_mlx_data *mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	mlx_data->mlx = mlx_init();
	mlx_data->win = mlx_new_window(mlx_data->mlx, 800, 600, "miniRT");
	mlx_data->img = mlx_new_image(mlx_data->mlx, 800, 600);
	mlx_data->width = 800;
	mlx_data->height = 600;
	mlx_data->bpp = 32;
	mlx_data->size_line = 800 * 4;
	mlx_data->endian = 0;
	data->mlx_data = mlx_data;

}

void init_checker(t_data *data) {
	data->checker.camera_init = 0;
	data->checker.has_ambient = 0;
	data->checker.has_spot = 0;
	data->checker.has_object = 0;

}

t_light *new_ambient_light(t_data *data) {
	t_light *light;

	light = malloc(sizeof(t_light));
	light->type = 'A';
	if (data->lights == NULL)
		data->lights = light;
	else
		data->lights->next = light;
	light->next = NULL;
	return (light);
}

t_light *new_spot_light(t_data *data) {
	t_light *light;

	light = malloc(sizeof(t_light));
	light->type = 'L';
	if (data->lights == NULL)
		data->lights = light;
	else
		data->lights->next = light;
	light->next = NULL;
	data->checker.has_spot++;
	return (light);
}

t_camera *new_camera(t_data *data) {
	t_camera *camera;

	camera = malloc(sizeof(t_camera));
	camera->next = NULL;
	data->checker.camera_init++;
	return (camera);
}


