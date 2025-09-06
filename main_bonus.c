/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:36:52 by nel-yama          #+#    #+#             */
/*   Updated: 2025/08/31 12:48:28 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;

	if (ac < 5)
		return (write(1, "pipex: Wrong Input usage\n", 25), 0);
	if (init_parsing(&arg, ac, av) != 0)
		return (1);
	if (create_child_process(&arg) != 0)
		return (1);
	run_children(&arg, envp);
	end_main(&arg);
	return (arg.exit_code);
}
