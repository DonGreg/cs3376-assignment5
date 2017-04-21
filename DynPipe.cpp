#// Kyung Du Gi 3376.501
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
 int main(int argc, char **argv){
 int status;
 int pid;// need two id for two children
 int pid2;
 char *cat_args[] = {"ls", "-ltr", NULL};
 char *grep_args[] = {"grep", "3376", NULL};
 char *wc_args[] = {"wc", "-l", NULL}; 
 int pipe1[2];// two pipes
 int pipe2[2];
   pipe(pipe1);
   pipe(pipe2);
    // fork the first child (to execute cat)
     if((pid = fork()) == -1){
      	perror("Error creating a child process");
       	exit(1);
        }
     if((pid2 = fork()) == -1){
      	perror("Error creating a child process");
       	exit(1);
        }
	// first child
         if (pid == 0) {
          // replace cat's stdout with write part of 1st pipe
          dup2(pipe1[1], 1);
          close(pipe1[0]);
	  close(pipe1[1]);
          execvp(*cat_args, cat_args);
          exit(0);
 	}
	//second child
	else if  (pid2 == 0) {
         // second child will run the second process
	  dup2(pipe1[0], 0);
	  close(pipe1[0]);
          close(pipe1[1]);
	  dup2(pipe2[1],1);
	  close(pipe2[0]);
	  close(pipe2[1]);
          execvp(*grep_args, grep_args);
 	}
	// parent
	else {
 	  close(pipe1[0]);
	  }
	  return(0);
}
