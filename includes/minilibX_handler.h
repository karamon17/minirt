#ifndef MINIRT_MINILIBX_HANDLER_H
#define MINIRT_MINILIBX_HANDLER_H

#include "miniRT.h"

# define KEY_S		1
# define KEY_D		2
# define KEY_W		13
# define KEY_Q		12
# define KEY_E		14
# define KEY_A		0
# define KEY_ESC	53
#define KEY_UP_ARROW     126
#define KEY_DOWN_ARROW   125
#define KEY_LEFT_ARROW   123
#define KEY_RIGHT_ARROW  124

#define KEY_0            82
#define KEY_1            83
#define KEY_2            84
#define KEY_3            85
#define KEY_4            86
#define KEY_5            87
#define KEY_6            88
#define KEY_7            89
#define KEY_8            91
#define KEY_9            92
#define KEY_MINUS        78
#define KEY_PLUS         69
#define LEFT_CLICK       1

void	mlx_hooks_handler(t_data *data);
int	ft_exit(int keycode, void *f);
int	press_keys(int keycode, t_data *data);
int	mouse_handle(int button, int x, int y, t_data *data);
int	press_object_movement_keys(int keycode, t_data *data);
void press_camera_rotation_keys(int keycode, t_data *data);
int is_object_key(int keycode);
int is_camera_movement_key(int keycode);
void press_camera_movement_keys(int keycode, t_data *data);
int is_camera_rotation_key(int keycode);
void rotate_cam(t_data *data);

void move_cam(t_data *data, t_vector *direction);
void get_object(t_data *data, int x, int y);
t_figure *get_closest_intersection(t_figure *figure, t_vector *vector, t_vector *ray, float *closest_dist);
void move_object(t_data *data, t_vector *direction);
void move_sphere(t_figure *sphere, t_vector *direction);
t_quaternion multiply_quaternion(t_quaternion q1, t_quaternion q2);
#endif //MINIRT_MINILIBX_HANDLER_H
