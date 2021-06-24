/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 09:32:24 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/24 13:30:29 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_command(void)
{
	pid_t	pid_1;
	pid_t	pid_2;
	
	if (pipe(g_all.fd) == -1)
	{
		write(2, "Error: PIPE", 11);
		exit(EXIT_FAILURE);
	}
	
	
}

char	*get_path(char **envp, char *cmd)
{
	char **paths;
	char *command;
	char *full_path;
	int i;
	int j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':');
			while (paths[++j])
			{
				command = ft_strjoin("/", cmd);
				full_path = ft_strjoin(paths[j], command);
				if (open(full_path, O_RDONLY) != -1)
					return full_path;
			}
		}
	}
	return (NULL);
}

void	get_commands(char **argv, char **envp)
{
	g_all.input = argv[1];
	g_all.cmd1 = ft_split(argv[2], ' ');
	g_all.cmd2 = ft_split(argv[3], ' ');
	g_all.output = argv[4];
	// g_all.path = get_path(envp);
	g_all.cmd1_path = get_path(envp, g_all.cmd1[0]);
	g_all.cmd2_path = get_path(envp, g_all.cmd2[0]);
	
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(1, "Usage: ./pipex [file1] [cmd1] [cmd2] [file2]", 44);
	}
	get_commands(argv, envp);
	// printf("input_file %s | output_file %s | cmd1 %s | cmd2 %s | cmd1_path %s | cmd2_path %s", g_all.input, g_all.output, g_all.cmd1[0], g_all.cmd2[0], g_all.cmd1_path, g_all.cmd2_path);
	return (0);
}
