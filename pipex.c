/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 09:32:24 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/28 21:55:38 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd1(char **envp, int fd[2])
{
	g_all.fd1 = open(g_all.input, O_RDONLY);
	if (g_all.fd1 == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_all.input, ft_strlen(g_all.input));
		exit_func(": No such file or directory", EXIT_FAILURE);
	}
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(g_all.fd1, 0);
	close(fd[1]);
	if (execve(g_all.cmd1_path, g_all.cmd1, envp) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_all.cmd1[0], ft_strlen(g_all.cmd1[0]));
		exit_func(": command not found", 127);
	}
	close(g_all.fd1);
}

void	exec_cmd2(char **envp, int fd[2])
{
	g_all.fd2 = open(g_all.output, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (g_all.fd2 == -1)
	{
		write(2, "pipex: ", 7);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		exit_func(g_all.output, EXIT_FAILURE);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(g_all.fd2, 1);
	close(fd[0]);
	if (execve(g_all.cmd2_path, g_all.cmd2, envp) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_all.cmd2[0], ft_strlen(g_all.cmd2[0]));
		exit_func(": command not found", 127);
	}
	close(g_all.fd2);
}

void	exec_command(char **envp)
{
	int		fd_pipe[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (pipe(fd_pipe) == -1)
		exit_func("Error: PIPE\n", EXIT_FAILURE);
	pid_1 = fork();
	if (pid_1 < 0)
		exit_func("Error: FORK\n", EXIT_FAILURE);
	else if (pid_1 == 0)
		exec_cmd1(envp, fd_pipe);
	pid_2 = fork();
	if (pid_1 < 0)
		exit_func("Error: FORK\n", EXIT_FAILURE);
	if (pid_2 == 0)
		exec_cmd2(envp, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid_1, &g_all.status, 0);
	waitpid(pid_2, &g_all.status, 0);
}

void	get_commands(char **argv, char **envp)
{
	g_all.input = strdup(argv[1]);
	g_all.cmd1 = ft_split(argv[2], ' ');
	g_all.cmd2 = ft_split(argv[3], ' ');
	g_all.output = strdup(argv[4]);
	g_all.cmd1_path = get_path(envp, g_all.cmd1[0]);
	g_all.cmd2_path = get_path(envp, g_all.cmd2[0]);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(1, "Usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45);
		return (-1);
	}
	get_commands(argv, envp);
	exec_command(envp);
	free_all_func();
	while(1);
	return (WEXITSTATUS(g_all.status));
}
