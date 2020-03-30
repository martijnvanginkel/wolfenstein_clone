/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shoot_3d_rays.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 09:51:19 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/03/12 16:37:37 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static float get_right_ray_dist(t_ray_info *ray, int side)
{
    if (side == 0)
    {
        (ray->ray_x_dir < 0) ? (ray->side_hit = 3) : (ray->side_hit = 1);
        return (ray->side_dist_x);
    }
    else
    {
        (ray->ray_y_dir < 0) ? (ray->side_hit = 2) : (ray->side_hit = 0);
        return (ray->side_dist_y);
    } 
}

static t_sprite_hit_data    collect_sprite_hit_data(t_game_tile tile, t_ray_info *ray, float increment, t_game_manager *gm, int side)
{
    t_sprite_hit_data  hit_data;

    hit_data.angle = ray->ray_dir + (M_PI / 2);
    hit_data.angle_x_dir = sin(hit_data.angle);
    hit_data.angle_y_dir = cos(hit_data.angle);

    hit_data.ray_hit_point = gm->player_x + (get_right_ray_dist(ray, side) * ray->ray_x_dir);
    hit_data.ray_point_incr = ((ray->ray_x_dir / ray->ray_y_dir) * increment);
    hit_data.perp_point_incr = ((hit_data.angle_x_dir / hit_data.angle_y_dir) * increment);

    hit_data.tile_middle_x = (float)tile.x + 0.5;
    hit_data.tile_middle_y = (float)tile.y + 0.5;

    return (hit_data);
}

static void     set_sprite_distance_to_ray(t_sprite_hit_data hd, t_ray_info *ray, t_game_manager *gm)
{
    float start_point;

    if (hd.ray_point_incr > 0)
    {
        while (hd.ray_hit_point > hd.perp_hit_point)
        {
            hd.ray_hit_point -= hd.ray_point_incr;
            hd.perp_hit_point -= hd.perp_point_incr;
        }
    }
    else if (hd.ray_point_incr < 0)
    {
        while (hd.ray_hit_point < hd.perp_hit_point)
        {
            hd.ray_hit_point -= hd.ray_point_incr;
            hd.perp_hit_point -= hd.perp_point_incr;
        }
    }
    start_point = hd.tile_middle_x - (fabs(hd.angle_x_dir) / 2);
    if (hd.ray_hit_point < start_point || hd.ray_hit_point > (start_point + fabs(hd.angle_x_dir)))
        return ;
    ray->sprite.eucl_dist = sqrt(pow(hd.tile_middle_x - gm->player_x, 2) + pow(hd.tile_middle_y - gm->player_y, 2));
    ray->sprite.percentage = fabs((hd.ray_hit_point - start_point) / hd.angle_x_dir);
    ray->has_sprite = 1;  
}

static void     add_sprite_to_ray_south(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm, double (*f)(double), float increment)
{ 
    t_sprite_hit_data hd;

    hd = collect_sprite_hit_data(tile, ray, increment, gm, side);
    hd.perp_hit_point = hd.tile_middle_x - ((0.5 / f(hd.angle)) * hd.angle_x_dir);
    set_sprite_distance_to_ray(hd, ray, gm);
}

static void     add_sprite_to_ray_north(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm, double (*f)(double), float increment)
{
    t_sprite_hit_data hd;

    hd = collect_sprite_hit_data(tile, ray, increment, gm, side);
    hd.perp_hit_point = hd.tile_middle_x + ((0.5 / f(hd.angle)) * hd.angle_x_dir);
    set_sprite_distance_to_ray(hd, ray, gm);
}

static void     add_sprite_to_ray_west(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm, double (*f)(double), float increment)
{
    float   angle;
    float   angle_x_dir;
    float   angle_y_dir;
    float   ray_hit_point;
    float   perp_hit_point;
    float   perp_point_incr;
    float   ray_point_incr;
    float tile_middle_x;
    float tile_middle_y;

    tile_middle_x = (float)tile.x + 0.5;
    tile_middle_y = (float)tile.y + 0.5;
    ray_hit_point = gm->player_y + (get_right_ray_dist(ray, side) * ray->ray_y_dir);
    angle = ray->ray_dir + (M_PI / 2);
    angle_x_dir = sin(angle);
    angle_y_dir = cos(angle);
    ray_point_incr = ((ray->ray_y_dir / ray->ray_x_dir) * increment);
    perp_point_incr = ((angle_y_dir / angle_x_dir) * increment);


    perp_hit_point = tile_middle_y + ((0.5 / f(angle)) * angle_y_dir);


    if (ray_point_incr > 0)
    {
        while (ray_hit_point > perp_hit_point)
        {
            ray_hit_point -= ray_point_incr;
            perp_hit_point -= perp_point_incr;
        }
    }
    else if (ray_point_incr < 0)
    {
        while (ray_hit_point < perp_hit_point)
        {
            ray_hit_point -= ray_point_incr;
            perp_hit_point -= perp_point_incr;
        }
    }
    
    float start_point_y;

    start_point_y = tile_middle_y - (fabs(angle_y_dir) / 2);
    if (ray_hit_point < start_point_y || ray_hit_point > (start_point_y + fabs(angle_y_dir)))
        return ;

    ray->sprite.eucl_dist = sqrt(pow(tile_middle_x - gm->player_x, 2) + pow(tile_middle_y - gm->player_y, 2));
    ray->sprite.percentage = fabs((ray_hit_point - start_point_y) / angle_y_dir);
    ray->has_sprite = 1;
}

static void     add_sprite_to_ray_east(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm, double (*f)(double), float increment)
{
    float   angle;
    float   angle_x_dir;
    float   angle_y_dir;

    float   ray_point_hit;
    float   perp_hit_point;
    float   perp_point_incr;
    float   ray_point_incr;

    float   tile_middle_x;
    float   tile_middle_y;

    tile_middle_x = (float)tile.x + 0.5;
    tile_middle_y = (float)tile.y + 0.5;
    ray_point_hit = gm->player_y + (get_right_ray_dist(ray, side) * ray->ray_y_dir);
    angle = ray->ray_dir + (M_PI / 2);
    angle_x_dir = sin(angle);
    angle_y_dir = cos(angle);
    ray_point_incr = ((ray->ray_y_dir / ray->ray_x_dir) * increment); 
    perp_point_incr = ((angle_y_dir / angle_x_dir) * increment);


    perp_hit_point = tile_middle_y - ((0.5 / f(angle)) * angle_y_dir);


    if (ray_point_incr > 0)
    {
        while (ray_point_hit > perp_hit_point)
        {
            ray_point_hit -= ray_point_incr;
            perp_hit_point -= perp_point_incr;
        }
    }
    else if (ray_point_incr < 0)
    {
        while (ray_point_hit < perp_hit_point)
        {
            ray_point_hit -= ray_point_incr;
            perp_hit_point -= perp_point_incr;
        }
    }
    
    float start_point_y;

    start_point_y = tile_middle_y - (fabs(angle_y_dir) / 2);
    if (ray_point_hit < start_point_y || ray_point_hit > (start_point_y + fabs(angle_y_dir)))
        return ;

    ray->sprite.eucl_dist = sqrt(pow(tile_middle_x - gm->player_x, 2) + pow(tile_middle_y - gm->player_y, 2));
    ray->sprite.percentage = fabs((ray_point_hit - start_point_y) / angle_y_dir);
    ray->has_sprite = 1;
}

static void     find_right_ray(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm)
{



    if (side == 1 && ray->ray_y_dir < 0)
    {
        add_sprite_to_ray_north(tile, ray, side, gm, &cos, 0.001);
    }
    else if (side == 1 && ray->ray_y_dir > 0)
    {
        add_sprite_to_ray_south(tile, ray, side, gm, &cos, -0.001);
    }
    else if (side == 0 && ray->ray_x_dir > 0)
    {
        add_sprite_to_ray_east(tile, ray, side, gm, &sin, -0.001); // -0.001
    }
    else if (side == 0 && ray->ray_x_dir < 0)
    {
        add_sprite_to_ray_west(tile, ray, side, gm, &sin, 0.001); // 0.001
    }
}

static int      increase_ray_distance(t_game_tile tile, t_ray_info *ray, int side, t_game_manager *gm)
{
    if (tile.value == 2)
    {
        /*
            Soort van tussenstop maken om te kijken of er een object wordt geraakt
            Als dit zo is, stop de afstand van de speler naar het middelste punt van de tile in de ray op
        */
        //write(1, "yes\n", 4);

        find_right_ray(tile, ray, side, gm);
        //add_sprite_to_ray(tile, ray, side, gm);
    }
    if (tile.value == 1)
    {
        ray->final_dist = get_right_ray_dist(ray, side);
        ray->tile_hit = &tile;
        return (0);
    }
    if (side == 0)
        ray->side_dist_x += ray->delta_dist_x;
    else
        ray->side_dist_y += ray->delta_dist_y;
    return (1);
}

static float calculate_ray_distance(t_game_manager *gm, t_ray_info *ray_info)
{
    int side;
    int map_y;
    int map_x;
    int step_x;
    int step_y;

    map_x = gm->player_tile->x;
    map_y = gm->player_tile->y;
    calculate_steps(ray_info, &step_x, &step_y);
    while (1)
    {
        if (ray_info->side_dist_x < ray_info->side_dist_y)
        {
            side = 0;
            map_x += step_x;
        }
        else
        {
            side = 1;
            map_y += step_y;
        }
        if (!increase_ray_distance(gm->map[map_y][map_x], ray_info, side, gm))
            return (ray_info->final_dist);       
    }
}

static float   get_texture_start_percentage(t_game_manager *gm, t_ray_info ray)
{
    float x_cord;
    float y_cord;
    float perc;

    x_cord = gm->player_x + (ray.eucl_dist * ray.ray_x_dir);
    y_cord = gm->player_y + (ray.eucl_dist * ray.ray_y_dir);
    if (ray.side_hit == 0 || ray.side_hit == 2)
        perc = (x_cord - (int)x_cord);    
    else if (ray.side_hit == 1 || ray.side_hit == 3)
        perc = y_cord - (int)y_cord;
    return (perc);
}

static t_ray_info calculate_ray(t_game_manager *gm, float ray_dir)
{
    t_ray_info  ray;

    ray.ray_dir = ray_dir;
    ray.ray_x_dir = sin(ray_dir);
    ray.ray_y_dir = cos(ray_dir);
    ray.has_sprite = 0;
    calculate_side_distances(gm, &ray);
    calculate_deltas(gm, &ray);
    ray.eucl_dist = calculate_ray_distance(gm, &ray);
    ray.perp_dist = cos(gm->player_dir - ray_dir) * ray.eucl_dist;
    return (ray);
}

static t_data  *find_wall_texture(t_game_manager *gm, t_ray_info *ray)
{
    t_data  *texture;

    texture = 0;
    if (ray->side_hit == 0)
        texture = gm->textures->north_tex;
    else if (ray->side_hit == 1)
        texture = gm->textures->east_tex;
    else if (ray->side_hit == 2)
        texture = gm->textures->south_tex;
    else if (ray->side_hit == 3)
        texture = gm->textures->west_tex;
    return (texture);
}

static void draw_sprite_line(t_game_manager *gm, int world_img_x, t_ray_info *ray)
{
    t_data *sprite_texture;
    int line_height;
    t_coordinates tex_cords;
    t_coordinates world_cords;
    float y_incr;

    sprite_texture = gm->textures->sprite_tex;
    tex_cords.x = ((float)sprite_texture->width * ray->sprite.percentage);
    world_cords.x = (float)world_img_x;
    line_height = ((float)(gm->file_data->resolution[0][1]) / ray->sprite.eucl_dist);
    world_cords.y = ((float)(gm->file_data->resolution[0][1]) / 2) + ((float)line_height / 2);
    y_incr = (float)sprite_texture->height / (float)line_height;
    tex_cords.y = ((float)line_height * y_incr) - 1;   
    while (line_height > 0)
    {
        my_image_put(sprite_texture, tex_cords, gm->world_image, world_cords, gm);
        tex_cords.y -= y_incr;
        world_cords.y -= 1;
        line_height--;
    }
}

static void draw_wall_line(t_game_manager *gm , int world_img_x, float ray_dir)
{
    t_ray_info ray;
    float y_incr;
    int line_height;
    t_coordinates tex_cords;
    t_coordinates world_cords;
    t_data *texture;

    ray = calculate_ray(gm, ray_dir);
    texture = find_wall_texture(gm, &ray);
    line_height = (int)(gm->file_data->resolution[0][1]) / ray.perp_dist;
    y_incr = (float)texture->height / (float)line_height;
    tex_cords.x = (float)texture->width * get_texture_start_percentage(gm, ray);
    tex_cords.y = 0;
    world_cords.x = world_img_x;
    world_cords.y = ((int)(gm->file_data->resolution[0][1]) / 2) + (line_height / 2);
    while (line_height > 0)
    {
        my_image_put(texture, tex_cords, gm->world_image, world_cords, gm);
        tex_cords.y += y_incr;
        world_cords.y -= 1;
        line_height--;
    }

    if (ray.has_sprite == 1)
    {
        draw_sprite_line(gm, world_img_x, &ray);
    }
    else
    {
        //write(1, "no\n", 3);
    }
    

}

/* Container function for shooting all the rays in the player's view */
void shoot_rays(t_game_manager *gm, float player_dir, int color)
{
    float   ray_dir;
    int     cur_px;
    float   start_incr;
    float   start;
    float   player_length;

    start = 1;
    start_incr = 2.0 / (float)(gm->file_data->resolution[0][0]);
    player_length = fabs(start) / tan(M_PI / 6);
    cur_px = gm->file_data->resolution[0][0];
    while (start > -1)
    {
        draw_2d_vision_line(gm, ray_dir, 0xFF0000);
        ray_dir = gm->player_dir + atan(start / player_length);
        draw_2d_vision_line(gm, ray_dir, 0x000000);
        start -= start_incr;  
        cur_px--;    
        draw_wall_line(gm, cur_px, ray_dir);
    }
    mlx_put_image_to_window(gm->map_image->mlx, gm->map_image->mlx_win, gm->map_image->img, 0, 0);
    mlx_put_image_to_window(gm->world_image->mlx, gm->world_image->mlx_win, gm->world_image->img, 0, 0);
}