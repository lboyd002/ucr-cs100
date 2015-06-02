#include <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //perror
using namespace std;

int main()
{
    int savestdout = dup(1);
    //open the file we want the output going to
    int fd = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 00664);
    if(-1 == fd)
    {
        perror("Error: open()");
    }
    if(dup2(fd, 1) == -1)
    {
        perror("Error: dup");
    }
    cout << "This should print to file" << endl;
    //restore output back to the terminal
    if(dup2(savestdout, 1) == -1)
    {
        perror("Error: dup()");
    }
    cout << "This should print to terminal" << endl;
    return 0;
}
