/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:37 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/04 21:54:04 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	input_n_file_checks(int argc, char **argv, char ***map);
int		check_format(char **map);

//  ./cub3d <file>
int	main(int argc, char **argv)
{
	t_map	map;

	input_n_file_checks(argc, argv, &map.board);
	if (check_format(map.board) == 1)
	{
		free_double_char(map.board);
		write(2, "Invalid map format\n", 19);
		exit(EXIT_FAILURE);
	}
	print_map(map.board);
	return (0);
}
