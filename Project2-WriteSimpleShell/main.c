#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <dirent.h>
#include <sys/wait.h>
#define clear() printf("\033[H\033[J")
#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */

//150113854 Gulsah Yilmaz
//150113841 Sezin Gumus


void setup(char inputBuffer[], char *args[],int *background, int *pipeline)
{

    int length, /* # of characters in the command line */
        i,      /* loop index for accessing inputBuffer array */
        start,  /* index where beginning of next command parameter is */
        ct;     /* index of where to place the next parameter into args[] */

    ct = 0;


    length = read(STDIN_FILENO,inputBuffer,MAX_LINE);


    start = -1;
    if (length == 0)
        exit(0);

    if ( (length < 0) && (errno != EINTR) ) {
        perror("error reading the command");
    exit(-1);           /* terminate with error code of -1 */
    }

    printf(">>%s<<",inputBuffer);
    for (i=0;i<length;i++){ /* exami;ne every character in the inputBuffer */

        switch (inputBuffer[i]){
        case ' ':
        case '\t' :               /* argument separators */
        if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
            ct++;
        }
                inputBuffer[i] = '\0'; /* add a null char; make a C string */
        start = -1;
        break;

            case '\n':                 /* should be the final char examined */
        if (start != -1){
                    args[ct] = &inputBuffer[start];
            ct++;
        }
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
        break;

        default :             /* some other character */
        if (start == -1)
            start = i;
                if (inputBuffer[i] == '&'){
            *background  = 1;
                    inputBuffer[i-1] = '\0';
        }else if(inputBuffer[i] == '|'){
		*pipeline = 1;	}
    } /* end of switch */
    }    /* end of for */
     args[ct] = NULL; /* just in case the input line was > 80 */

int z;
if(pipeline==1){ for (i = 0; i < ct; i++){
	z++;
        }
}

    createexecfunction(args, *background,ct,*pipeline,z);


} /* end of setup routine */









void createexecfunction(char *const args[], int background, int i,int pipeline,int z){
pid_t pid;
DIR *dir ;
int resultt;
char argi[10];
char buffer [PATH_MAX + 1];
char* cwd;
char inputBuffer[MAX_LINE];
char* cval;




strcpy(argi ,args[0]); // 0. element is out
            if(strcmp(argi,"clr")==0){
            system("clear");
            }else if(strcmp(argi,"dir")==0){
            cwd=getcwd(buffer,PATH_MAX + 1);
            fprintf(stderr,"Working Directory is : %s ",cwd);

            }else if(strcmp(argi,"exit")==0){
            exit(0);
            }else if(strcmp(argi,"cd")==0){

        if ((dir = opendir(args[i-1])) == NULL)
        fprintf(stderr,"\n Error :it is not a directory \n",cval);
		else
		{
		chdir(args[1]);
		fprintf(stderr,"\n my new directory is %s \n",getcwd(buffer,PATH_MAX + 1));}
		}
		else if (strcmp(argi,"wait")==0)
		{
		while ((pid = waitpid(-1,NULL,WNOHANG)) != -1)
		{
		wait(NULL);
		}
            }


else if ( pipeline == 1 ){ //  means there ia pipeline
pid_t childpid; // it creates a child for second exec function
   int fd[2];  // it keeps ouput of first argument and input of second argument

   if ((pipe(fd) == -1) || ((childpid = fork()) == -1)) { //For error checking
      perror("Failed to setup pipeline");
      return 1;
   }

   if (childpid == 0) {       //The process is a child process or not           /* ls is the child */
      if (dup2(fd[1], STDOUT_FILENO) == -1) //It copies output of the first function to fd1 , if it can not copy , it will giv the error
         perror("Failed to redirect stdout of ls"); //Some error checking
      else if ((close(fd[0]) == -1) || (close(fd[1]) == -1))
         perror("Failed to close extra pipe descriptors on ls");
      else {
         execl("/bin/ls", args[0], args[1], NULL);
         perror("Failed to exec ls");
      }
      return 1;
   }
   if (dup2(fd[0], STDIN_FILENO) == -1)               /* sort is the parent */
       perror("Failed to redirect stdin of sort");
   else if ((close(fd[0]) == -1) || (close(fd[1]) == -1))
       perror("Failed to close extra pipe file descriptors on sort");
   else {
      execl("/bin/sort", args[z], NULL);
      perror("Failed to exec sort");
   }
   return 1;
}

else{
pid = fork();

if ( background == 0 ) // We will do foreground process
{

if (pid < 0) //If the child can not be created
 fprintf(stderr,"\n child can not be created \n");

 else if (pid > 0) //If the process is parent , it will wait the child
 wait(&pid);

else if (pid == 0)
 {
 fprintf(stderr,"\nforeground\n");

  if ((dir = opendir(args[i-1])) != NULL) //If there is a directory
    {
     execl("/bin/ls",args[0],args[1],args[2]);
    }
    else
    execvp(args[0],args);

 }

}
else if (background == 1) // We will do background process
{

if (pid == 0) // If the process is child
 {
   fprintf(stderr,"\nbackground\n");
   if ((dir = opendir(args[i-1])) != NULL) //If there is a directory
    {
     execl("/bin/ls",args[0],args[1],args[2]);
    }
    else
    execvp(args[0],&args);

 }

}

}

background = 0; //to set default value of background
pipeline = 0;    //to set default value of pipeline
setup(inputBuffer, args, &background ,&pipeline);

}



int main(void)
{
            char inputBuffer[MAX_LINE]; /*buffer to hold command entered */
            int background;/* equals 1 if a command is followed by '&' */
	        int pipeline; /* equals 1 if a command is followed by '|' */
            char *args[MAX_LINE/2 + 1]; /*command line arguments */


            while (1){


                        printf("CSE333sh: ");
                        /*setup() calls exit() when Control-D is entered */
                        background = 0;
			           pipeline = 0;

                        setup(inputBuffer, args, &background, &pipeline);

  /** the steps are:
                        (1) fork a child process using fork()
                        (2) the child process will invoke execvp() or execl()
                        (3) if background == 0, the parent will wait,
                        otherwise it will invoke the setup() function again. */
            }
}
