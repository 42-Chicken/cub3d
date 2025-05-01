/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:49:16 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 14:49:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H

# define VECTORS_H

typedef struct s_vec_2
{
	int					x;
	int					y;
}						t_vec2;

typedef struct s_uvec_2
{
	unsigned int		x;
	unsigned int		y;
}						t_uvec2;

typedef struct s_dvec_2
{
	double				x;
	double				y;
}						t_dvec2;

typedef struct s_fvec2
{
	float				x;
	float				y;
}						t_fvec2;

#endif
