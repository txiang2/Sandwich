#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

/**
** Read buffer from FIFO Pipe (sent by Vim)
** "Diff" buffer with original file
** Creates patch file and sends to server
**/
int main(int argc, char * argv[]){
  char * pipe = "/tmp/pipe";
  
  FILE * fifo = fopen(pipe, "r");
  fseek(fifo, 0, SEEK_END);
  long file_size = ftell(fifo);
  rewind(fifo);

  char * command = calloc(1024, sizeof(char));
  strcpy(command, "diff -c ");
  strcat(command, argv[1]);
  strcat(command, " /tmp/pipe > .diff.txt");  // command = "diff -c filename /tmp/pipe > .diff.txt"

  system(command); // diffs original file and piped file and stores into .diff.txt

  system("patch < .diff.txt"); // patches changes into the original file

  free(command);

  return 0;
}
