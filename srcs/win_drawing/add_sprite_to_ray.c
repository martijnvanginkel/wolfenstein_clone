/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_sprite_to_ray.c                              :+:    :+:              */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 10:02:51 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/28 15:31:33 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void     loop_to_find_texture_percentage(t_sprite *sprite)
{
    if (sprite->ray_point_incr > 0)
    {
        while (sprite->ray_hit_point > sprite->perp_hit_point)
        {
            sprite->ray_hit_point -= sprite->ray_point_incr;
            sprite->perp_hit_point -= sprite->perp_point_incr;
        }
    }
    else if (sprite->ray_point_incr < 0)
    {
        while (sprite->ray_hit_point < sprite->perp_hit_point)
        {
            sprite->ray_hit_point -= sprite->ray_point_incr;
            sprite->perp_hit_point -= sprite->perp_point_incr;
        }
    }
}

static void     set_basic_sprite_values(t_sprite *sprite, t_ray_info *ray, t_game_tile tile)
{
    sprite->angle = ray->ray_dir + (M_PI / 2);
    sprite->angle_x_dir = sin(sprite->angle);
    sprite->angle_y_dir = cos(sprite->angle);
    sprite->tile_middle_x = (float)tile.x + 0.5;
    sprite->tile_middle_y = (float)tile.y + 0.5;
}

static void     north_or_south_hit(t_sprite *sprite, t_ray_info *ray, t_game_manager *gm, float increment)
{
    float start_point;

    sprite->ray_hit_point = gm->player_x + (get_right_ray_dist(ray, sprite->side_hit) * ray->ray_x_dir);
    sprite->ray_point_incr = ((ray->ray_x_dir / ray->ray_y_dir) * increment);
    sprite->perp_point_incr = ((sprite->angle_x_dir / sprite->angle_y_dir) * increment);
    if (increment > 0)
        sprite->perp_hit_point = sprite->tile_middle_x + ((0.5 / cos(sprite->angle)) * sprite->angle_x_dir);
    else
        sprite->perp_hit_point = sprite->tile_middle_x - ((0.5 / cos(sprite->angle)) * sprite->angle_x_dir);
    loop_to_find_texture_percentage(sprite);
    start_point = sprite->tile_middle_x - (fabs(sprite->angle_x_dir) / 2);
    if (sprite->ray_hit_point < start_point || sprite->ray_hit_point > (start_point + fabs(sprite->angle_x_dir)))
        return ;
    sprite->percentage = fabs((sprite->ray_hit_point - start_point) / sprite->angle_x_dir);
    sprite->eucl_dist = sqrt(pow(sprite->tile_middle_x - gm->player_x, 2) + pow(sprite->tile_middle_y - gm->player_y, 2));
}

static void     west_or_east_hit(t_sprite *sprite, t_ray_info *ray, t_game_manager *gm, float increment)
{
    float start_point;

    sprite->ray_hit_point = gm->player_y + (get_right_ray_dist(ray, sprite->side_hit) * ray->ray_y_dir);
    sprite->ray_point_incr = ((ray->ray_y_dir / ray->ray_x_dir) * increment);
    if (increment > 0)
        sprite->perp_hit_point = sprite->tile_middle_y + ((0.5 / sin(sprite->angle)) * sprite->angle_y_dir);
    else
        sprite->perp_hit_point = sprite->tile_middle_y - ((0.5 / sin(sprite->angle)) * sprite->angle_y_dir);
    sprite->perp_point_incr = ((sprite->angle_y_dir / sprite->angle_x_dir) * increment);
    loop_to_find_texture_percentage(sprite);
    start_point = sprite->tile_middle_y - (fabs(sprite->angle_y_dir) / 2);
    if (sprite->ray_hit_point < start_point || sprite->ray_hit_point > (start_point + fabs(sprite->angle_y_dir)))
        return ;
    sprite->percentage = fabs((sprite->ray_hit_point - start_point) / sprite->angle_y_dir);
    sprite->eucl_dist = sqrt(pow(sprite->tile_middle_x - gm->player_x, 2) + pow(sprite->tile_middle_y - gm->player_y, 2));
}

void     calculate_sprite_distance(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm)
{
    t_sprite *sprite;
    t_sprite *temp;
    float increment;

    sprite = malloc(sizeof(t_sprite) * 1);
    if (!sprite)
        return ;

    sprite->side_hit = side;
    sprite->next_sprite = NULL;
    set_basic_sprite_values(sprite, ray, tile);
    if (side == 1)
    {
        (ray->ray_y_dir > 0) ? (increment = -0.001) : (increment = 0.001);
        north_or_south_hit(sprite, ray, gm, increment);
    }
    else if (side == 0)
    {
        (ray->ray_x_dir > 0) ? (increment = -0.001) : (increment = 0.001);
        west_or_east_hit(sprite, ray, gm, increment);
    }
    if (ray->sprite == NULL)
    {
        ray->sprite = sprite;
    }
    else
    {
        temp = ray->sprite;
        ray->sprite = sprite;
        ray->sprite->next_sprite = temp;
    }
}