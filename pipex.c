/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:57:36 by akhachat          #+#    #+#             */
/*   Updated: 2021/08/03 16:00:53 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     get_index(char **env)
{
    int i;
    
    i = 0;
    while (env[i])
    {
        if (!(ft_strncmp(env[i], "PATH", 4)))
            return (i);
        ++i;
    }
    return (0);
}

char    *env_path(char **env, char *ar)
{
    int     index;
    char    **path;
    int     j;
    char    *final_path;
    int     fd;
    char    *cur;

    index = get_index(env);
    if (ar[0] == '/')
        return (ar);
    else
    {
        path = ft_split(env[index] + 5, ':');
        j = 0;
        while(path[j])
        {
            cur = ft_strjoin(path[j], "/");
            final_path = ft_strjoin(cur, ar);
            fd = open(final_path, O_RDONLY);
            if(fd > -1)
            {
                close(fd);
                free(cur);
                return (final_path);
            }
            free(cur);
            j++;
        }
    }
    return (final_path);
}

void    child_p(char **argv, char **env, int *fd)
{
    char    **ar;
    int     file1;

    ar = ft_split(argv[2], ' ');
    close(fd[0]);
    if(dup2(fd[1], 1) == -1)
    {
        ft_putstr_fd("Can't duplicate", 2);
        exit(1);
    }
    close(fd[1]);
    if (access(argv[1], R_OK) == -1)
    {
        ft_putstr_fd("Can't find the file", 2);
        exit(1);
    }
    file1 = open(argv[1], O_RDONLY);
    if(file1 == -1)
    {
        ft_putstr_fd("Can't open the file", 2);
        exit(1);
    }
    dup2(file1, 0);
    if(execve(env_path(env, ar[0]), ar, env) == -1)
    {
        ft_putstr_fd("Can't find the commant", 2);
        exit(1);
    }
    close(file1);
}

void    parent_p(char **argv, char **env, int *fd)
{
    char    **ar;
    int     file2;

    ar = ft_split(argv[3], ' ');
    wait(NULL);
    file2 = open(argv[4], O_WRONLY | O_CREAT, 0777);
    if(file2 == -1)
    {
        ft_putstr_fd("Can't open or create the file", 2);
        exit(1);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(file2, 1);
    if(execve(env_path(env, ar[0]), ar, env) == -1)
    {
        ft_putstr_fd("Can't find the command", 2);
        exit(1);
    }
    close(file2);
}

int     main(int argc, char **argv, char **env)
{
    int fd[2];
    int pid;

    if (argc != 5)
    {
        ft_putstr_fd("Error\nWrong number of arguments", 2);
        return (0);
    }
    if (pipe(fd) == -1)
    {
        ft_putstr_fd("An error ocurred with opening the pipe\n",2);
        return (0);
    }
    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("Error\nCan't fork",2);
        return (0);
    }
    if (pid == 0)
        child_p(argv, env, fd);
    else
        parent_p(argv, env, fd);
    return (0);
    
}
