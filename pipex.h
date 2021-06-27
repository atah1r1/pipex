/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 09:32:40 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/27 19:30:06 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>

typedef struct s_pipex {
	int		fd1;
	int		fd2;
	char	*input;
	char	**cmd1;
	char	**cmd2;
	char	*output;
	char	*cmd1_path;
	char	*cmd2_path;
	int		status;
}				t_pipex;

t_pipex	g_all;

char	**ft_split(const char *ss, char c);
int		ft_strlen(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
#endif