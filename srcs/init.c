#include "mlx.h"
#include "vector2.h"
#include "data.h"
#include "events.h"
#include "draw.h"

int		on_update(t_data *data);
int		on_close(t_data *data);
void	keys_init(bool *key_pressed, bool *key_just_pressed);
int		on_keypressed(int keycode, t_data *data);
int		on_keyreleased(int keycode, t_data *data);

bool	init(t_data *data) // TODO how to name it?
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (false);
	data->img.size = (t_vector2){SCREEN_WIDTH, SCREEN_HEIGHT};
	data->win = mlx_new_window(data->mlx, data->img.size.x, data->img.size.y,
		"A fucking beautiful cub3D!");
	if (data->win == NULL)
		return (false);
	data->img.img = mlx_new_image(data->mlx, data->img.size.x, data->img.size.y);
	if (data->img.img == NULL)
		return (false);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
		&data->img.line_len, &data->img.endian);
	mlx_do_key_autorepeatoff(data->mlx);
	keys_init(data->key_pressed, data->key_just_pressed);
	mlx_hook(data->win, KeyPress, KeyPressMask, on_keypressed, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, on_keyreleased, data);
	data->mouse_pos = (t_vector2){0, 0};
	draw_background(&data->img, C_BLUE2); // TODO needed? (TODO test on linux)
	mlx_hook(data->win, DestroyNotify, NoEventMask, on_close, &data);
	mlx_loop_hook(data->mlx, on_update, data);
	return (true);
}
