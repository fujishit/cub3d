/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 07:52:12 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	input_error_exit(char *s, int errornum)
{
	if (errornum == READ_ERROR)
		printf("read error : %s\n", s);
	else if (errornum == FILE_ERROR)
		printf("file error : %s\n", s);
	else if (errornum == FORMAT_ERROR)
		printf("format error : %s\n", s);
	else if (errornum == MAP_ERROR)
		printf("map error : %s\n", s);
	else if (errornum == RESOLUTION_ERROR)
		printf("resolution error : %s\n", s);
	else if (errornum == TEXTURE_ERROR)
		printf("texture error : %s\n", s);
	else if (errornum == COLOR_ERROR)
		printf("color error : %s\n", s);
	else if (errornum == EXTENSION_ERROR)
		printf("extension error : %s\n", s);
	else if (errornum == DUPLICATE_ERROR)
		printf("element error : %s\n", s);
	else if (errornum == ELEMENT_ERROR)
		printf("invalid element : %s\n", s);
	else
		printf("unknown error : input//error:%d\n", errornum);
	exit(1);
}

void	game_error_exit(t_game *game, char *s, int errornum)
{
	if (errornum == SUCCESS)
		exit (0);
	else if (errornum == TEXTURE_ERROR)
		printf("texture error : %s\n", s);
	else if (errornum != SUCCESS)
		printf("unknown error : game\n");
	exit(1);
}

void	error_exit(char *s, int errornum)
{
	if (errornum == READ_ERROR)
		printf("read error : %s\n", s);
	else if (errornum == FILE_ERROR)
		printf("file error : %s\n", s);
	else if (errornum == ARG_ERROR)
		printf("argument error : %s\n", s);
	else
		printf("unknown error : system\n");
	exit(1);
}
