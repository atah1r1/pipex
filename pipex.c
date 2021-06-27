/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 09:32:24 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/27 12:40:52 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_func(char *msg, int code)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(code);
}

void free_d_p(char **ptr)
{
	int i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);	
}

void	free_all()
{
	free(g_all.cmd1_path);
	free(g_all.cmd2_path);
	free_d_p(g_all.cmd1);
	free_d_p(g_all.cmd2);
}

void	exec_cmd1(char **envp)
{
	int in_fd;

	in_fd = open(g_all.input, O_RDONLY);
	if (in_fd == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_all.input, ft_strlen(g_all.input));
		write(2, ": No such file or directory\n", 28);
	}
	else 
	{
		close(g_all.fd[0]);
		dup2(in_fd, STDIN_FILENO);
		dup2(g_all.fd[1], STDOUT_FILENO);
		close(g_all.fd[1]);
		if (execve(g_all.cmd1_path, g_all.cmd1, envp) == -1)
		{
			write(2, "pipex: ", 7);
			write(2, g_all.cmd1[0], ft_strlen(g_all.cmd1[0]));
			exit_func(": command not found", 127);
		}
	}
}

void	exec_cmd2(char **envp)
{
	int out_fd;

	out_fd = open(g_all.output, O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (out_fd == -1)
	{
		write(2, "pipex: ", 7);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		exit_func(g_all.output, 1);
	}
	close(g_all.fd[1]);
	dup2(out_fd, STDOUT_FILENO);
	dup2(g_all.fd[0], STDIN_FILENO);
	close(g_all.fd[0]);
	if (execve(g_all.cmd2_path, g_all.cmd2, envp) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_all.cmd2[0], ft_strlen(g_all.cmd2[0]));
		exit_func(": command not found", 127);
	}
	exit(EXIT_SUCCESS);
}

void	exec_command(char **envp)
{
	pid_t	pid_1;
	pid_t	pid_2;
	
	if (pipe(g_all.fd) == -1)
		exit_func("Error in PIPE", EXIT_FAILURE);
	pid_1 = fork();
	if (pid_1 < 0)
		exit_func("Error in FORK", EXIT_FAILURE);
	else if (pid_1 == 0)
		exec_cmd1(envp);
	else
		waitpid(pid_1,&g_all.status,0);
	pid_2 = fork();
	if (pid_1 < 0)
		exit_func("Error in FORK", EXIT_FAILURE);
	else if (pid_2 == 0)
		exec_cmd2(envp);
	else 
	{
		close(g_all.fd[0]);
		close(g_all.fd[1]);
		waitpid(pid_2,&g_all.status,0);	
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
				command = ft_strjoin("/", cmd); // need to be freed
				full_path = ft_strjoin(paths[j], command);
				free(command);
				if (open(full_path, O_RDONLY) != -1)
				{
					return full_path;
					free(full_path);
				}
			}
		}
	}
	free_d_p(paths);
	return (NULL);
}

void	get_commands(char **argv, char **envp)
{
	g_all.input = argv[1];
	g_all.cmd1 = ft_split(argv[2], ' ');
	g_all.cmd2 = ft_split(argv[3], ' ');
	g_all.output = argv[4];
	g_all.cmd1_path = get_path(envp, g_all.cmd1[0]);
	g_all.cmd2_path = get_path(envp, g_all.cmd2[0]);
	
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(1, "Usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45);
		return -1;
	}
	get_commands(argv, envp);
	exec_command(envp);
	// free_all();
	// while (1);
	
	// printf("input_file %s | output_file %s | cmd1 %s | cmd2 %s | cmd1_path %s | cmd2_path %s", g_all.input, g_all.output, g_all.cmd1[0], g_all.cmd2[0], g_all.cmd1_path, g_all.cmd2_path);
	return (WEXITSTATUS(g_all.status));
}
