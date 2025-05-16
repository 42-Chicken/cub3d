/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:43:43 by efranco           #+#    #+#             */
/*   Updated: 2025/05/16 17:31:14 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalizeangle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

bool	isWall(t_cub3d *data, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return (true);
	map_x = (int)(x / TILESIZE);
	map_y = (int)(y / TILESIZE);
	return (data->map.buffer[map_y][map_x] == '1');
}

void	get_horizontal_intersection(t_cub3d *data, t_ray *ray)
{
	float	angle;
	float	y_intercept;
	float	x_intercept;
	float	y_step;
	float	x_step;
	float	check_y;

	angle = normalizeangle(ray->rayangle);
	ray->found_horizontal_wall = false;
	y_intercept = floor(data->player.location.y * TILESIZE / TILESIZE) * TILESIZE;
	if (angle > 0 && angle < M_PI)
		y_intercept += TILESIZE;
	x_intercept = data->player.location.x * TILESIZE + (y_intercept
			- data->player.location.y * TILESIZE) / tan(angle);
	if (angle > 0 && angle < M_PI)
		y_step = TILESIZE;
	else
		y_step = -TILESIZE;
	x_step = TILESIZE / tan(angle);
	if ((angle > M_PI_2 && angle < 3 * M_PI_2) && x_step > 0)
		x_step *= -1;
	if (!(angle > M_PI_2 && angle < 3 * M_PI_2) && x_step < 0)
		x_step *= -1;
	float next_x = x_intercept;
	float next_y = y_intercept;
	while (next_x >= 0 && next_x <= SCREEN_W && next_y >= 0
		&& next_y <= SCREEN_H)
	{
		if (angle > 0 && angle < M_PI)
			check_y = next_y;
		else
			check_y = next_y - 1;
		if (map_is_wall(data, next_x / TILESIZE, check_y/ TILESIZE))
		{
			ray->horizontal_hit_x = next_x;
			ray->horizontal_hit_y = next_y;
			ray->found_horizontal_wall = true;
			break ;
		}
		next_x += x_step;
		next_y += y_step;
	}
}
void	get_vertical_intersection(t_cub3d *data, t_ray *ray)
{
	double	angle;
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float	check_x;

	angle = normalizeangle(ray->rayangle);
	ray->found_vertical_wall = false;
	x_intercept = floor(data->player.location.x * TILESIZE / TILESIZE) * TILESIZE;
		// aligner le rayon sur la première ligne verticale devant lui
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		// viser le bord a droite
		x_intercept += TILESIZE;
	y_intercept = data->player.location.y * TILESIZE + (x_intercept
			- data->player.location.x * TILESIZE) * tan(angle);
		// y pour trouver la hauteur donc opp = adj * tan(a)
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		// si x va a droite positif si va vers la gauche negatif
		x_step = TILESIZE;
	else
		x_step = -TILESIZE;
	y_step = TILESIZE * tan(angle); // on monte suivant la tan
	if (angle > M_PI && y_step > 0) // on inverse , si il va vers le bas positif si il va vers le haut negatif
		y_step *= -1;
	if (angle < M_PI && y_step < 0)
		y_step *= -1;
	float next_x = x_intercept;
	float next_y = y_intercept;
	while (next_x >= 0 && next_x <= SCREEN_W && next_y >= 0
		&& next_y <= SCREEN_H)
	{
		if (angle < M_PI_2 || angle > 3 * M_PI_2) // angle vers la droite
			check_x = next_x;
		else
			check_x = next_x - 1;
		if (map_is_wall(data, check_x/ TILESIZE, next_y/ TILESIZE))
		{
			ray->vertical_hit_x = next_x;
			ray->vertical_hit_y = next_y;
			ray->found_vertical_wall = true;
			break ;
		}
		next_x += x_step;
		next_y += y_step;
	}
}
float	fdistance_between(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void	get_wall_hit(t_cub3d *data, t_ray *ray)
{
	float	hor_dist;
	float	vert_dist;
	float	angle_diff;

	get_horizontal_intersection(data, ray);
	get_vertical_intersection(data, ray);
	if (ray->found_horizontal_wall)
	{
		hor_dist = fdistance_between(data->player.location.x * TILESIZE,
				data->player.location.y * TILESIZE, ray->horizontal_hit_x,
				ray->horizontal_hit_y);
	}
	else
	{
		hor_dist = 99999;
	}
	if (ray->found_vertical_wall)
	{
		vert_dist = fdistance_between(data->player.location.x * TILESIZE, data->player.location.y * TILESIZE,
				ray->vertical_hit_x, ray->vertical_hit_y);
	}
	else
	{
		vert_dist = 99999;
	}
	angle_diff = ray->rayangle - data->player.rotation_angle;
	hor_dist *= cos(angle_diff);
	vert_dist *= cos(angle_diff);
	if (vert_dist < hor_dist)
	{
		ray->distance = vert_dist;
		ray->was_hit_vertical = true;
		ray->wall_hit_x = ray->vertical_hit_x;
		ray->wall_hit_y = ray->vertical_hit_y;
	}
	else
	{
		ray->distance = hor_dist;
		ray->was_hit_vertical = false;
		ray->wall_hit_x = ray->horizontal_hit_x;
		ray->wall_hit_y = ray->horizontal_hit_y;
	}
}
void	put_pixel(t_cub3d *data, int x, int y, unsigned int color)
{
	// if (x < 0)
	// 	x = 0;
	// if (x > SCREEN_W)
	// 	x = SCREEN_W;
	// if (y < 0)
	// 	y = 0;
	// if (y > SCREEN_W)
	// 	y = SCREEN_W;
	put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){x, y}, color);
	// ((unsigned int *)data->rendering_buffer->data)[(y * data->rendering_buffer->size_line / 4
	// 		+ x)] = color;
}
void	fdraw_line(t_cub3d *data, int x0, int y0, int x1, int y1, int color)
{
	double	dx = x1 - x0;
	double	dy = y1 - y0;
	double	step;
	double	x;
	double	y;

	step = fmax(fabs(dx), fabs(dy));
	if (step == 0)
	{
		put_pixel(data, x0, y0, color);
		return;
	}
	dx /= step;
	dy /= step;
	x = x0;
	y = y0;
	while (step > 0)
	{
		put_pixel(data, (int)x, (int)y, color);
		x += dx;
		y += dy;
		step--;
	}
}

void draw_wall(t_cub3d *data, t_ray *ray, int i)
{
	double height = ((double)(64 / ray->distance) * DISTANCE_FROM_CAMERA);
	unsigned int color;

	double draw_begin = (SCREEN_H - height) / 2;

	if (ray->was_hit_vertical)
		color = 0x008000;
	else
		color = 0x008800;

	// draw_line(data, i , 0, i, draw_begin, 0x000080);
	for (size_t y = 0; y < draw_begin; y++)
	{
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){i, y}, 0x0000F0);
	}
	// if (draw_begin >= INT_MAX || draw_begin <= INT_MIN)
	// 	draw_begin = 10;
	// if (height >= INT_MAX || height <= INT_MIN)
	// 	height = 10;
	// printf("%d %f %f\n", i, height, draw_begin);
	// fdraw_line(data, i, 0, i, (int)draw_begin, 0x000040);

	fdraw_line(data, i , draw_begin, i, height + draw_begin, color);

	for (size_t d = (int)height + draw_begin; d < SCREEN_H; d++)
	{
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){i, d}, 0xFF0000);
	}
	// fdraw_line(data, i , draw_end + draw_begin, i, SCREEN_H - 1, 0x880080);
}
void render_raycasting(t_cub3d *data)
{
	t_ray ray;
	double angle;
	int i;

	i = 0;
	// printf("%f, %f\n", data->player.location.x * TILESIZE, data->player.location.y * TILESIZE);
	angle = data->player.rotation_angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		ft_bzero(&ray, sizeof(t_ray));
		ray.rayangle = normalizeangle(angle);
		angle += FOV / NUM_RAYS;
		get_wall_hit(data, &ray);
		draw_wall(data, &ray, i);
		i++;
	}
}
