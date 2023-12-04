/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:37 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/04 15:43:40 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_map(char **argv)
{
	int		fd;
	int		bytes_read;
	int		content_size;
	char	*content;
	char	*buffer[BUFFER_SIZE];

	bytes_read = 1;
	content_size = 0;
	content = (char *)malloc(BUFFER_SIZE);
	if (!content)
		exit(write(2, "failed content malloc\n", 22));
	fd = open(argv[1], O_RDONLY);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			exit(write(2, "Error while reading\n", 20));
		ft_memcpy(content + content_size, buffer, bytes_read);
		content_size += bytes_read;
	}
	close(fd);
	content[content_size] = '\0';
	return(content);
}

void	input_n_file_checks(int argc, char **argv, char ***map)
{
	int	len;
	char	*content;

	if (argc != 2)
		exit(write(2, "wrong number of arguments\n", 26));
	if (access(argv[1], F_OK) == -1)
		exit(write(2, "File does not exist\n", 20));
	len = ft_strlen(argv[1]);
	if (len < 5)
		exit(write(2, "Invalid filename\n", 17));
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c' || argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b')
		exit(write(2, "Not a .cub file\n", 16));
	content = get_map(argv);
	(*map) = ft_split(content, '\n');
	free(content);
}

void	init_file_reqs(t_file_reqs *reqs)
{
	reqs->no = 0;
	reqs->so = 0;
	reqs->we = 0;
	reqs->ea = 0;
	reqs->f = 0;
	reqs->c = 0;
}

int	check_nm(int *i, char *str, char **sprite_loc)
{
	char	*temp;
	
	(*i) += 2;
	while (ft_isspace(str[(*i)]))
		(*i)++;
	temp = cp_until_sp(str, i);
	(*sprite_loc) = temp;
	while (str[(*i)] != '\0')
	{
		if (!(ft_isspace(str[(*i)])))
		{
			free(temp);
			return (1);
		}
		(*i)++;
	}
	if (access(temp, F_OK) == -1)
	{
		free(temp);
		return (1);
	}
	return (0);
}

int	check_texture(char *str, int *i)
{
	t_file_reqs	check;
	t_file_loc	*locs;
	int		len;

	locs = (t_file_loc *)malloc(sizeof(t_file_loc));
	init_file_reqs(&check);
	while (str[(*i)])
	{
		len = ft_strlen(str);
		if ((*i) + 2 < len)
		{
			if (str[(*i)] == 'N' && str[(*i) + 1] == 'O')
			{
				if (check_nm(i, str, &locs->n_wall) == 1)
					return (1);
				check.no = 1;
			}
		}
		(*i)++;
		// if (str[(*i)] == 'S' && str[(*i) + 1] == 'O')
		// if (str[(*i)] == 'W' && str[(*i) + 1] == 'E')
		// if (str[(*i)] == 'E' && str[(*i) + 1] == 'A')
	}
	return (0);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		if (check_texture(str, &i) == 1)
			return (1);
	// if (str[i] == 'C' || str[i] == 'F')
	// 	if (check_cnf(str[i]) == 1)
	// 		return (1);
	return (0);
}

int	check_format(char **map)
{
	int		i;

	i = 0;
	// printf("%s\n", map[1]);
	while (map[i])
	{
		if (ft_strlen(map[i]) < 7)	// protects from segfaults later by catching unrealistic short lines before the extensive checks
			return (1);
		if (check_line(map[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

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
