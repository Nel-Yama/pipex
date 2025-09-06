/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:38:15 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/24 20:38:15 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# include "libft.h"
# include "ft_printf.h"

typedef struct s_arg
{
	int		ac;
	int		cmd_count;
	int		*pid;
	int		*status;
	int		(*fd_pipe)[2];
	int		in_file;
	int		out_file;
	int		exit_code;
	char	**av;
	char	**cmds;
}	t_arg;

int		init_parsing(t_arg *arg, int ac, char **av);
char	*ft_get_env(const char *var, char **envp);
int		run_cmd(t_arg *arg, char *cmd, char **envp);
int		create_child_process(t_arg *arg);
void	run_first_child(t_arg *arg, char **envp);
void	run_last_child(t_arg *arg, char **envp);
void	run_mid_child(t_arg *arg, char **envp, int i);
void	run_children(t_arg *arg, char **envp);
void	print_custom_error(int fd, const char *s1, const char *s2);
void	close_fds(t_arg *arg, int in_pipe, int out_pipe);
void	exit_error(t_arg *arg, char *msg, int i0, int i1);
void	free_and_exit(t_arg *arg);
void	free_and_return(t_arg *arg);
int		end_main(t_arg *arg);

#endif
