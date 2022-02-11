// #include<unistd.h>
// // int main(int argc, char *argv[], char *env[])
// // {
// // 	int i = 0;
// // 	printf ("%s\n", argv[1]);
// // 	while (i++<10)
// // 		printf ("%s\n", (env[i]));
// // 	return 0;
// // }
// int main(int argc, char const *argv[])
// {
// 	return 0;
// }

// int main(int argc, char const *argv[])
// {
// 	int pipefd[2];
// 	if (pipe (pipefd) == -1)
// 	{
// 		perror("pipe");
// 		exit (EXIT_FAILURE);
// 	}
// 	printf("open file error%m\n");
// 	return 0;
// }

// int main(int argc, char *argv[])
// {
// 	char	*cmd = argv[1];
// 	char	*file_name = argv[2];
// 	int	in = open(file_name, O_RDONLY);
// 	dup2(in, 0);
// 	close(in);
// 	int fds_pair[2];
// 	pipe (fds_pair);
// 	pid_t pid = fork();
// 	if (0 == pid)
// 	{
// 		printf("1\n");
// 		dup2(fds_pair[1], 1);
// 		close(fds_pair[1]);
// 		execlp(cmd, cmd, NULL);
// 	}
// 	else
// 	{
// 		printf("2\n");
// 		close(fds_pair[1]);
// 	}
// 	return 0;
// }

/*
int main(int argc, char *argv[])
{
	int	pid;
	int	rv;
	int	status;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("CHILD: Это процесс-потомок!\n");
		printf("CHILD: Мой PID -- %d\n", getpid());
		printf("CHILD: PID моего родителя -- %d\n", getppid());
		printf("CHILD: Введите мой код возврата (как можно меньше):");
		printf("CHILD: Выход!\n");
		exit(rv);
	}
	else
	{
		wait(&status);
		//while(wait(NULL) != -1 || errno != ECHILD)
		//	printf("Whaited for a child to finish\n");
		printf("---------------------------\n");
		printf("PARENT: Это процесс-родитель!\n");
		printf("PARENT: Мой PID -- %d\n", getpid());
		printf("PARENT: PID моего потомка %d\n",pid);
		printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
		printf("PARENT: Код возврата потомка:%d\n",WEXITSTATUS(rv));
		printf("PARENT: Выход!\n");
	}
	// if (pid != 0)
	// 	wait();
}*/

// int main(int argc, char *argv[], char *envr[])
// {
// 	t_pip	*pip;
// 	pip = (t_pip *)malloc(sizeof(t_pip));
// 	if (!pip)
// 		print_error("Error: malloc can't create a structure\n");
// 	// if (argc != 5)
// 	// 	print_error("Error: wrong number of input parameters\n");
// 	free (pip);
// 	char	cmd[] = "/usr/bin/ls";
// 	char	*argV[] = {"ls", "-l", NULL};
// 	char	*envv[] = {NULL};
// 	execve(cmd, argV, envr);
// 	return 0;
// }

/*
int main(int argc, char const *argv[])
{
	int	id1 = fork();
	int	id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("I'm child/child, my perent are main child\n");
		else
			printf("I'm a main child\n");
	}
	else if (id2 == 0)
		printf("I'm second child\n");
	else
		printf("I'm parent\n");
	while (wait(NULL) != -1 || errno != ECHILD)//если wait(NULL) = -1-ждать нечего, errno == ECHILD -Нет процессов-потомков
		printf("Whaited for a child to finish\n");
	return 0;
}
*/

/*
int main(int argc, char *argv[])
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		printf("An error ocurredd with opening the pipe\n");
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		printf("An error ocurredd with fork\n");
		return 4;
	}
	if (id == 0)
	{
		close(fd[0]);
		int file = open("qq.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return 2;
		printf("The fd to pingResults: %d\n", file);
		int ds = dup(1);
		int file2 = dup2(file, STDOUT_FILENO);// STDOUT_FILENO = 1
		printf("The duplicate fd: %d\n", file2);
		dup2(ds, 1);
		close(file);
		int	x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("An error ocurred with writting to the pipe\n");
			return (2);
		}
		close(fd[1]);
		
	}
	else
	{
		int	status;
		wait(&status);
		printf("status: %d\n", status);
		close(fd[1]);
		int	y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("An error ocurred with reading to the pipe\n");
			return (3);
		}
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return (0);
}
*/

// int main(int argc, char *argv[], char *envr[])
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 		return 1;
// 	char	cmd[] = "/usr/bin/ls";
// 	char	*argV[] = {"ls", "-l", NULL};
// 	char	*envv[] = {NULL};
// 	if (pid == 0)
// 	{
// 		//int	err = execve("/usr/bin/ls", argV, envv);
// 		// if (err == -1)
// 		// {
// 		// 	printf("ERROR: execve\n");
// 		// 	return 2;
// 		// }
// 		//exit(10);
// 		return 3;
// 	}
// 	else
// 	{
// 		int	wstatus;
// 		wait(&wstatus);
// 		printf("|%d|\n", wstatus/256);
// 		printf("|%d|\n", WEXITSTATUS(wstatus));
// 	}
// 	return (0);
// }

// int main(int argc, char const *argv[])
// {
// 	int	fd[2];
// 	if (pipe(fd) == -1)
// 	{
// 		write(2,"ERROR: pipe - FAILED\n", 21);
// 		return 1;
// 	}
// 	int pid1 = fork();
// 	if (pid1 < 0)
// 	{
// 		write(2, "ERROR: fork first - FAILED\n", 27);
// 		return 2;
// 	}
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("ls", "ls", "-l", NULL);
// 		write(2, "ERROR: pid1 - FAILED\n", 21);
// 	}
// 	int	pid2 = fork();
// 	if (pid2 < 0)
// 	{
// 		write(2, "ERROR: fork second - FAILED\n", 28);
// 		return 3;
// 	}
// 	if (pid2 == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("grep", "grep", "a", NULL);
// 		write(2, "ERROR: pid2 - FAILED\n", 21);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return 0;
// }