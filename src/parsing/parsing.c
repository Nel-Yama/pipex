/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:45:19 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/26 23:45:19 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_args(t_arg *arg, int ac, char **av)
{
	arg->ac = ac;
	arg->av = av;
	arg->cmd_count = arg->ac - 3;
	arg->cmds = arg->av + 2;
	arg->pid = NULL;
	arg->status = NULL;
	arg->fd_pipe = NULL;
	arg->exit_code = 0;
}

static void	file_error(t_arg *arg)
{
	if (arg->in_file < 0)
		perror("pipex: infile");
	if (arg->out_file < 0)
		perror("pipex: outfile");
}

/**
 * Argument parsing - 
 * We assume that the first arg is input file and last arg is output file
 * Parsing for Minishell should check each arg and assign the correct type
 **/
int	init_parsing(t_arg *arg, int ac, char **av)
{
	int	i;

	init_args(arg, ac, av);
	arg->in_file = open(arg->av[1], O_RDONLY);
	arg->out_file = open(arg->av[arg->ac - 1], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (arg->in_file < 0 || arg->out_file < 0)
		file_error(arg);
	i = 2;
	while (i < ac - 1)
	{
		if (!arg->av[i] || !arg->av[i][0])
		{
			close_fds(arg, -1, -1);
			write(2, "pipex: empty command\n", 21);
			return (-1);
		}
		i++;
	}
	return (0);
}
