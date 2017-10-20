/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsominsk <gsominsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 12:11:30 by gsominsk          #+#    #+#             */
/*   Updated: 2017/03/30 15:17:25 by gsominsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	ft_ipp(t_fract *cd, int x, int y, int rgb)
{
	int				bpp;
	int				sl;
	int				en;
	char			*image;
	unsigned int	tmp;

	image = mlx_get_data_addr(cd->image, &bpp, &sl, &en);
	tmp = (mlx_get_color_value(cd->mlx, rgb));
	if (x > 0 && x < cd->win_x && y > 0 && y < cd->win_y)
		ft_memcpy((void *)(image + y * cd->win_x *
				(bpp / 8)) + x * (bpp / 8), (void *)&tmp, 4);
}

void	choose_fractal(t_fract *cd, double *x, double *y)
{
	if (cd->flag == 3)
	{
		cd->tmp = *x * *x - *y * *y + cd->x_win;
		*y = 2 * fabs(*x * *y) + cd->y_win;
		*x = cd->tmp;
	}
	else if (cd->flag == 4)
	{
		cd->tmp = sin(*x * *x - *y * *y) + cd->a;
		*y = 1 * cos(*x * *y) + cd->b;
		*x = cd->tmp;
	}
	else if (cd->flag == 5)
	{
		cd->tmp = sin(*x * *x) - tan(*y * *y) + cd->a;
		*y = 2 * *x * *y + cd->b;
		*x = cd->tmp;
	}
	else
	{
		cd->tmp = *x * *x - *y * *y + cd->a;
		*y = 2 * *x * *y + cd->b;
		*x = cd->tmp;
	}
}

void	open_fract(t_fract *cd, double i, double j)
{
	double	x;
	double	y;
	int		z;

	x = 0;
	y = 0;
	(cd->flag == 2 || cd->flag == 4 || cd->flag == 5) ? x = cd->x_win : 0;
	(cd->flag == 2 || cd->flag == 4 || cd->flag == 5) ? y = cd->y_win : 0;
	z = 0;
	while ((x * x + y * y) < 4 && z < cd->depth)
	{
		cd->flag == 1 ? cd->a = cd->x_win : 0;
		cd->flag == 1 ? cd->b = cd->y_win : 0;
		cd->flag == 2 ? cd->a = cd->j_x : 0;
		cd->flag == 2 ? cd->b = cd->j_y : 0;
		cd->flag == 4 || cd->flag == 5 ? cd->a = 1.177 : 0;
		cd->flag == 4 || cd->flag == 5 ? cd->b = 0.915 : 0;
		choose_fractal(cd, &x, &y);
		z++;
	}
	(z < cd->depth / 2) ? ft_ipp(cd, j, i, cd->color * z) : ft_ipp(cd, j, i, 0);
}

void	open_fractal(t_fract *cd)
{
	double i;
	double j;

	cd->x_win = 0;
	cd->y_win = 0;
	cd->image = mlx_new_image(cd->mlx, cd->win_x, cd->win_y);
	i = -1;
	while (++i <= cd->win_y)
	{
		j = -1;
		cd->y_win = ((i - cd->sh_y - cd->win_y / 2.) * cd->size - cd->win_y *
		1. * cd->z_shy * cd->zoom) / (cd->win_y * cd->zoom);
		while (++j < cd->win_x)
		{
			cd->x_win = ((j - cd->sh_x - cd->win_x / 2.) * cd->size - cd->win_x
			* 1. * cd->z_shx * cd->zoom) / (cd->win_x * cd->zoom);
			open_fract(cd, i, j);
		}
	}
	mlx_put_image_to_window(cd->mlx, cd->win, cd->image, 0, 0);
	mlx_key_hook(cd->win, key_func, cd);
	mlx_hook(cd->win, 6, 0, hook_mouse, cd);
	mlx_mouse_hook(cd->win, zoom_fract, cd);
	mlx_loop(cd->mlx);
}

int		main(int argc, char const *argv[])
{
	t_fract cd;

	if (argc != 2)
		show_list();
	else
	{
		cd.flag = 0;
		ft_strcmp(argv[1], "1") == 0 ? cd.flag = 1 : 0;
		ft_strcmp(argv[1], "2") == 0 ? cd.flag = 2 : 0;
		ft_strcmp(argv[1], "3") == 0 ? cd.flag = 3 : 0;
		ft_strcmp(argv[1], "4") == 0 ? cd.flag = 4 : 0;
		ft_strcmp(argv[1], "5") == 0 ? cd.flag = 5 : 0;
		zero_fract(&cd);
		cd.flag != 0 ? open_fractal(&cd) : show_list();
	}
	return (0);
}
