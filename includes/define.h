/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:55:54 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/08 14:25:15 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define RESET "\e[0m"
# define RED "\e[1;91m"
# define GREEN "\e[1;92m"
# define BLUE "\e[1;94m"
# define YELLOW "\e[1;93m"
# define MAGENTA "\e[1;95m"
# define CYAN "\e[1;96m"
# define WHITE "\e[1;97m"
# define BLACK "\e[1;90m"
# define GRAY "\e[1;37m"
# define MALLOC "Error\nMalloc failed\n"
# define NO_PATH_NO "Error\nInvalid path to NO texture.\n"
# define NO_PATH_SO "Error\nInvalid path to SO texture.\n"
# define NO_PATH_WE "Error\nInvalid path to WE texture.\n"
# define NO_PATH_EA "Error\nInvalid path to EA texture.\n"
# define MISS_WALL "Error\nThe map isn't surrounded by walls\n"
# define WRONG_CHAR "Error\nThere is at least one wrong character in map\n"
# define STRAIGHT "textures/handlebars/handlebars_straight.xpm"
# define LEFT0 "textures/handlebars/handlebars_left_0.xpm"
# define LEFT1 "textures/handlebars/handlebars_left_1.xpm"
# define RIGHT0 "textures/handlebars/handlebars_right_0.xpm"
# define RIGHT1 "textures/handlebars/handlebars_right_1.xpm"
# define MAX_MAP_WIDTH 100
# define MAX_MAP_HEIGHT 100
# define PX 10 //nb de pixels d'une case de mini map
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923 /* pi/2 */
# define SPEED 0.1 //0.03

#endif