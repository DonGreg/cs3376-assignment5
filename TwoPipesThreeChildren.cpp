// Kyung Du Gi 3376.501
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
 int main(int argc, char **argv){
 int status;
 int pid;// need 3 id for two children
 int pid2;
 int pid3;
 char *cat_args[] = {"ls", "-ltr", NULL};
 char *grep_args[] = {"grep", "3376", NULL};
 char *wc_args[] = {"wc", "-l", NULL}; 
 int pipe1[2];// three pipes
 int pipe2[2];
 int pipe3[2];
   pipe(pipe1);
   pipe(pipe2);
   pipe(pipe3);
    // fork the first child (to execute cat)
     if((pid = fork()) == -1){
      	perror("Error creating a child process");
       	exit(1);
        }
     if((pid2 = fork()) == -1){
      	perror("Error creating a child process");
       	exit(1);
        }
     if((pid3 = fork()) == -1){
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
	else if  (pid3 == 0) {
         // third child will run the the shell part
	 
          close(pipe2[0]);
	  close(pipe2[1]);
	  dup2(pipe3[0],0); // redirect input to child 2 end
	  close(pipe3[0]);
	  close(pipe3[1]);
          execvp(*wc_args, wc_args);
 	}
	// parent should do nothing
	else {

 	}
 return(0);
}
