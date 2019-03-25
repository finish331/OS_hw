#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h> // read the number of the last error
#include <fcntl.h> // file descriptor CONSTANT mode values

int main(int argc, char *argv[])
{
    int pipeFd[2];
    char buffer[1024];
    char childBuffer[1024];
    if (argc != 3)
    {
        printf("Error Input");
        exit(1);
    }

    char *srcFile = argv[1];
    char *dstFile = argv[2];

    if (pipe(pipeFd) < 0)
    {
        printf("Pipe Error!\n"); 
	exit(1);
    }

    pid_t pid = fork();
    //father
    if (pid == 0)
    {
        close(pipeFd[1]);
        ssize_t fileSize = read(pipeFd[0], childBuffer, sizeof(childBuffer));
        close(pipeFd[0]);
        int dstFile_fd = open(dstFile, O_CREAT | O_WRONLY);
        write(dstFile_fd, childBuffer, fileSize);
        close(dstFile_fd);
    }
    // child
    else if (pid > 0)
    {
        close(pipeFd[0]);
        int targetFile_fd = open(srcFile, O_RDONLY);
        ssize_t fileSize = read(targetFile_fd, buffer, sizeof(buffer));
        write(pipeFd[1], buffer, fileSize);
        close(pipeFd[1]);
        close(targetFile_fd);
    }
    else
    {
        printf("Fork Error!\n");
        exit(1);
    }
    return 0;
}

