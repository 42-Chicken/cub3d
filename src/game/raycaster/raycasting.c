/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:43:43 by efranco           #+#    #+#             */
/*   Updated: 2025/05/19 23:09:36 by rguigneb         ###   ########.fr       */
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
	float	next_x;
	float	next_y;

	angle = normalizeangle(ray->rayangle);
	ray->found_horizontal_wall = false;
	y_intercept = floor(data->player.location.y * TILESIZE / TILESIZE)
		* TILESIZE;
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
	next_x = x_intercept;
	next_y = y_intercept;
	while (next_x >= 0 && next_x <= data->map.width * TILESIZE && next_y >= 0
		&& next_y <= data->map.height * TILESIZE)
	{
		if (angle > 0 && angle < M_PI)
			check_y = next_y;
		else
			check_y = next_y - 1;
		if (map_is_wall(data, next_x / TILESIZE, check_y / TILESIZE))
		{
			ray->horizontal_hit_x = next_x;
			ray->horizontal_hit_y = check_y;
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
	float	next_x;
	float	next_y;

	angle = normalizeangle(ray->rayangle);
	ray->found_vertical_wall = false;
	x_intercept = floor(data->player.location.x * TILESIZE / TILESIZE)
		* TILESIZE;
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
	if (angle > M_PI && y_step > 0)
		y_step *= -1;
	if (angle < M_PI && y_step < 0)
		y_step *= -1;
	next_x = x_intercept;
	next_y = y_intercept;
	while (next_x >= 0 && next_x <= data->map.width * TILESIZE && next_y >= 0
		&& next_y <= data->map.height * TILESIZE)
	{
		if (angle < M_PI_2 || angle > 3 * M_PI_2) // angle vers la droite
			check_x = next_x;
		else
			check_x = next_x - 1;
		if (map_is_wall(data, check_x / TILESIZE, next_y / TILESIZE))
		{
			ray->vertical_hit_x = check_x;
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
		vert_dist = fdistance_between(data->player.location.x * TILESIZE,
				data->player.location.y * TILESIZE, ray->vertical_hit_x,
				ray->vertical_hit_y);
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
	ray->wall = map_get_wall(data, ray->wall_hit_x / TILESIZE, ray->wall_hit_y
			/ TILESIZE);
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
	// ((unsigned int *)data->rendering_buffer->data)[(y
		// * data->rendering_buffer->size_line / 4
	// 		+ x)] = color;
}
void	fdraw_line(t_cub3d *data, int x0, int y0, int x1, int y1, int color)
{
	double	dx;
	double	dy;
	double	step;
	double	x;
	double	y;

	dx = x1 - x0;
	dy = y1 - y0;
	step = fmax(fabs(dx), fabs(dy));
	if (step == 0)
	{
		put_pixel(data, x0, y0, color);
		return ;
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

void	draw_wall(t_cub3d *data, t_ray *ray, int i)
{
	double			height;
	double			distanceFromTop;
	t_texture		*wall_texture;
	unsigned int	color;
	t_uvec2			textureLoc;
	t_color			dcolor;
	int				y;
	double			darkness_weight;
	double			draw_begin;

	height = ((double)(64 / ray->distance) * DISTANCE_FROM_CAMERA);
	draw_begin = (SCREEN_H - height) / 2;

	if (height > SCREEN_H)
		height = SCREEN_H;
	if (draw_begin < 0)
		draw_begin = 0;

	wall_texture = get_linked_texture(data, ray->wall);
	igmlx_simple_copy_to_dest(wall_texture, data->rendering_buffer, (t_uvec2){0, 0});
	if (ray->was_hit_vertical)
	{
		textureLoc.x = (int)floor(ray->wall_hit_y) % wall_texture->width;
		color = 0x008888;
	}
	else
	{
		textureLoc.x = (int)floor(ray->wall_hit_x) % wall_texture->width;
		color = 0x008800;
	}
	if (ray->wall == 'M')
		wall_texture = get_texture(data, TEXTURE_WALL);
	darkness_weight = (215 / ray->distance);
	if (darkness_weight < 0)
		darkness_weight = 0;
	if (darkness_weight > 1)
		darkness_weight = 1;
	textureLoc.x = (textureLoc.x * wall_texture->width)
		/ wall_texture->width;
	for (size_t y = 0; y < draw_begin; y++)
	{
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){i, y}, 0x0000F0);
	}
	y = draw_begin;
	double h = ((double)(64 / ray->distance) * DISTANCE_FROM_CAMERA) / 2;
	while (y < SCREEN_H - draw_begin)
	{
		distanceFromTop = y + (h) - (SCREEN_H / 2);
		textureLoc.y = (1LL * distanceFromTop * wall_texture->height
				+ h) / (h *2) ;
		textureLoc.y = textureLoc.y % wall_texture->height;
		dcolor = get_pixel_color(wall_texture, textureLoc);
		dcolor = igmlx_melt_colors_weigthed(0x000000, dcolor, darkness_weight);
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){i, y}, (int)dcolor);
		y++;
	}
	for (size_t d = (int)height + draw_begin; d < SCREEN_H; d++)
	{
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){i, d}, 0xFF0000);
	}
}
void	render_raycasting(t_cub3d *data)
{
	t_ray	ray;
	double	angle;
	int		i;

	i = 0;
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
