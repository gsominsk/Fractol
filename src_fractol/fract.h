/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsominsk <gsominsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:59:08 by gsominsk          #+#    #+#             */
/*   Updated: 2017/03/30 14:56:46 by gsominsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H

# include <stdarg.h>
# include <math.h>
# include "../lib/src_lib/libft.h"
# include "../lib/src_printf/ft_printf.h"
# include "../lib/src_gnl/get_next_line.h"
# include "mlx.h"

# define KNRM	"\x1B[0m"
# define KRED	"\x1B[91m"
# define KGRN	"\x1B[92m"
# define KYEL	"\x1B[93m"
# define KBLU	"\x1B[94m"
# define KMAG	"\x1B[95m"
# define KCYN	"\x1B[96m"
# define KWHT	"\x1B[97m"

typedef struct		s_fract
{
	double			depth;
	double			m_x;
	double			m_y;
	double			zoom;
	double			z_shx;
	double			z_shy;
	double			z_x;
	double			z_y;
	double			z_dx;
	double			z_dy;
	double			j_x;
	double			j_y;
	double			sh_x;
	double			sh_y;
	double			x_win;
	double			y_win;
	double			size;
	double			a;
	double			b;
	double			tmp;
	void			*mlx;
	void			*win;
	void			*image;
	int				mouse_hooked;
	int				win_x;
	int				win_y;
	int				color;
	int				flag;

}					t_fract;

int					hook_mouse(int x, int y, t_fract *cd);
void				open_fractal(t_fract *cd);
int					key_func(int keycode, t_fract *cd);
int					zoom_fract(int keycode, int x, int y, t_fract *cd);
int					hook_mouse(int x, int y, t_fract *cd);
void				zero_fract(t_fract *cd);
void				show_list(void);

#endif
