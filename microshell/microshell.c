#include "microshell.h"

ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int err(char *str) 
{
	write(2, str, ft_strlen(str));
	return 1;
}

int cd(char **argv, int i) 
{
	if (i != 2)
		return err("error: cd: bad arguments\n");
	else if (chdir(argv[1]) == -1)
		return err("error: cd: cannot change directory to "), err(argv[1]), err("\n");
	return 0;
}

int exec(char **argv, char **envp, int i) 
{
	int fd[2];
	int status;
	bool has_pipe = argv[i] && !strcmp(argv[i], "|");

	if (has_pipe && pipe(fd) == -1)
		return err("error: fatal\n");

	int pid = fork();
	if (pid < 0)
		return err("error : pipe error\n");
	if (!pid) 
	{
		argv[i] = 0;
		if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return err("error: fatal\n");
		execve(*argv, argv, envp);
		return err("error: cannot execute "), err(*argv), err("\n");
	}
	if (waitpid(pid, &status, 0) < 0)
		return err("wait pid failed\n");
	if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		return err("error: fatal\n");
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return WTERMSIG(status);
	return 42;
}

int main(int argc, char **argv, char **envp) 
{
	int	i = 0;
	int	status = 0;

	if (argc > 1) 
	{
		while (argv[i] && argv[++i]) 
		{
			argv += i;
			i = 0;
			while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
				i++;
			if (!strcmp(*argv, "cd"))
				status = cd(argv, i);
			else if (i)
				status = exec(argv, envp, i);
		}
	}
	return status;
}
