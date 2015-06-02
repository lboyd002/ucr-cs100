nclude <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //perror
#include <stdlib.h> //exit
using namespace std;

int main()
{
    const int PIPE_READ = 0;
    const int PIPE_WRITE = 1;
    int fd[2];
    if (-1 == pipe(fd))
    {
        perror("Error: pipe()");
    }
    int pid = fork();
    if(pid == -1)
    {
        perror("Error: fork()");
    }
    else if(pid == 0) 
    {
        //child closes input part of pipe (we dont need it)
        if(close(fd[0]) == -1)
        {
            perror("Error: close()");
        }
        //Sent "Hello World" through the output side of pipe
        if(-1 == write(fd[1],"Hello World", 11))
        {
            perror ("Error: write()");
        }
        exit(0);
    }
    else if(pid > 0)
    {
        //Parent closes output side of pipe (we dont need it)
        if(close(fd[1]) == -1)
        {
            perror("Error: close()");
        }
        //Read in "Hello World" from the input side of pipe
        char buf[12];
        read(fd[0], buf, 11);
        cout << "Received string: " << buf << endl;
    }
    return 0;
}
