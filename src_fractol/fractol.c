/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsominsk <gsominsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 12:00:50 by gsominsk          #+#    #+#             */
/*   Updated: 2017/03/30 15:09:20 by gsominsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	show_list(void)
{
	ft_printf(KRED "Invalid number of arguments%s\n", KNRM);
	ft_printf(KGRN "=================================\n");
	ft_printf("1) Mandelbrot\n");
	ft_printf("2) Julia\n");
	ft_printf("3) Burning Ship\n");
	ft_printf("4) Bio Cells\n");
	ft_printf("5) Psychodellic\n");
	ft_printf("=================================%s\n", KNRM);
}

void	zero_fract(t_fract *cd)
{
	cd->depth = 60;
	cd->win_x = 1024;
	cd->win_y = 1024;
	cd->zoom = 1;
	cd->z_shx = 0;
	cd->z_shy = 0;
	cd->sh_x = 0;
	cd->j_x = 0.285;
	cd->j_y = 0.01;
	cd->sh_y = 0;
	cd->mouse_hooked = 0;
	cd->color = 10000;
	cd->size = 4;
	cd->mlx = mlx_init();
	cd->win = mlx_new_window(cd->mlx, cd->win_x, cd->win_x, "mlx 42");
}

int		hook_mouse(int x, int y, t_fract *cd)
{
	if (cd->mouse_hooked == 1 && (cd->flag == 2 || cd->flag == 4))
	{
		cd->j_x = ((x * cd->win_x) / cd->win_x + 0.685) / cd->win_x;
		cd->j_y = ((y * cd->win_y) / cd->win_y + 0.07) / cd->win_y;
		mlx_destroy_image(cd->mlx, cd->image);
		open_fractal(cd);
	}
	return (1);
}

int		zoom_fract(int keycode, int x, int y, t_fract *cd)
{
	if (keycode == 4)
	{
		cd->z_x = (x * 1. - cd->win_x / 2.) * 4. / (cd->win_x * cd->zoom);
		cd->z_y = (y * 1. - cd->win_y / 2.) * 4. / (cd->win_y * cd->zoom);
		cd->zoom *= 1.4;
		cd->z_dx = (x * 1. - cd->win_x / 2.) * 4. / cd->win_x;
		cd->z_dy = (y * 1. - cd->win_y / 2.) * 4. / cd->win_y;
		cd->z_shx -= cd->z_x - cd->z_dx / cd->zoom;
		cd->z_shy -= cd->z_y - cd->z_dy / cd->zoom;
		mlx_destroy_image(cd->mlx, cd->image);
	}
	else if (keycode == 5)
	{
		cd->z_x = (x * 1. - cd->win_x / 2.) * 4. / (cd->win_x * cd->zoom);
		cd->z_y = (y * 1. - cd->win_y / 2) * 4. / (cd->win_y * cd->zoom);
		cd->zoom /= 1.4;
		cd->zoom < 1 ? cd->zoom = 1 : 0;
		cd->z_dx = (x * 1. - cd->win_x / 2.) * 4. / cd->win_x;
		cd->z_dy = (y * 1. - cd->win_y / 2.) * 4. / cd->win_y;
		cd->z_shx -= cd->z_x - cd->z_dx / cd->zoom;
		cd->z_shy -= cd->z_y - cd->z_dy / cd->zoom;
		mlx_destroy_image(cd->mlx, cd->image);
	}
	open_fractal(cd);
	return (1);
}

int		key_func(int keycode, t_fract *cd)
{
	keycode == 53 ? exit(0) : 0;
	if (keycode == 65)
		cd->mouse_hooked = (cd->mouse_hooked == 0 ? 1 : 0);
	keycode == 123 ? cd->sh_x -= 10 : 0;
	keycode == 124 ? cd->sh_x += 10 : 0;
	keycode == 125 ? cd->sh_y += 10 : 0;
	keycode == 126 ? cd->sh_y -= 10 : 0;
	keycode == 67 ? cd->color += 1000 : 0;
	keycode == 69 ? cd->depth += 5 : 0;
	if (cd->depth > 0)
		keycode == 78 ? cd->depth -= 5 : 0;
	keycode == 18 ? cd->flag = 1 : 0;
	keycode == 19 ? cd->flag = 2 : 0;
	keycode == 20 ? cd->flag = 3 : 0;
	keycode == 21 ? cd->flag = 4 : 0;
	keycode == 23 ? cd->flag = 5 : 0;
	(keycode == 18 || keycode == 19 || keycode == 20 ||
	keycode == 21) ? cd->zoom = 1 : 0;
	(keycode == 18 || keycode == 19 || keycode == 20 ||
	keycode == 21) ? cd->z_shx = 0 : 0;
	(keycode == 18 || keycode == 19 || keycode == 20 ||
	keycode == 21) ? cd->z_shy = 0 : 0;
	open_fractal(cd);
	return (0);
}
