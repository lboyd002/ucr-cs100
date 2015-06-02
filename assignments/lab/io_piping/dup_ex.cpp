nclude <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //perror
using namespace std;

int main()
{
    int savestdout = dup(1);
    close file descriptor 1 so we can use it for output
        if(-1 == close(1))
        {
            perror("Error: close()");
        }
    //open the file we want the output going to
    int fd = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 00664);
    if(-1 == fd)
    {
        perror("Error: open()");
    }
    if(dup(fd) == -1)
    {
        perror("Error: dup");
    }
    cout << "fd: " << fd << endl;
    cout << "This should print to file" << endl;
    //restore output back to the terminal
    if(-1 == close(1))
    {
        perror("Error: close()");
    }
    if(dup(savestdout) == -1)
    {
        perror("Error: dup()");
    }
    cout << "This should print to terminal" << endl;
    return 0;
}

