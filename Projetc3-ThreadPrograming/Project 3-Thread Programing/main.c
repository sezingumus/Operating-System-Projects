#include <stdio.h>
#include <stdlib.h>
#include "kuyruk.h"
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
struct Queue *q;
struct Queue *q2;
struct Queue *q3;


int buffer; 
sem_t lock1;
sem_t lock2;
sem_t lock3;   //Semapores
sem_t lock4;
sem_t lock5;
sem_t lock6;
FILE *flog;
FILE *ff;
char text;
char cdizi[63]; //Our lines
int i;

void linebyline ( );
void reederthread ();  //Methods
void writer ();
void upper ();
void replacethread ();



int main (int argc, char *argv[]){

pthread_t thread1,thread2,thread3,thread4;

q = createQueue();
q2 = createQueue();
q3 = createQueue();


sem_init(&lock1, 0,1);
sem_init(&lock2,0,1);
sem_init(&lock3,0,1);
sem_init(&lock4, 0,1);
sem_init(&lock5,0,1);
sem_init(&lock6,0,1);



/*
while(1){
struct QNode* n = deQueue(q);
    if (n == NULL)
   	break;

replacethread(n->key);
}


sem_wait(&lock1);
sem_wait(&lock2);
sem_wait(&lock3);
*/
int i;


pthread_create(&thread1, NULL,linebyline, (void *) argv[1]);
//pthread_create(&thread1, NULL,linebyline, "veri.txt");
pthread_create(&thread2, NULL,replacethread, (void *)q2);
pthread_create(&thread3, NULL,upper, (void *)q3);
pthread_create(&thread4, NULL,writer, (void *)q);

pthread_join(&thread1,NULL);
pthread_join(&thread2,NULL);
pthread_join(&thread3,NULL);
pthread_join(&thread4,NULL);

sem_destroy(&lock1);
sem_destroy(&lock2);
sem_destroy(&lock3);




return 0;
}




void linebyline (void * argv){ //It reads the file which is entered from user and creates a log file to write updates
	flog=fopen("log.txt","w");
	char const* const fileName=argv;
	
	FILE * file=fopen(fileName, "r");
	char line[63];
	while (fgets(line,sizeof(line),file)){
        
	
		fprintf(flog,"%s",line);
		printf("%s",line);

		
		sem_wait(&lock2);
		enQueue(q, line);
		sem_post(&lock2);
	}
	fclose(file);
}




void replacethread (struct queue* x){ //This method replace the blank with "-"
	
	while(1){
	
	sem_wait(&lock2);
	struct QNode* n = deQueue(q); 
	sem_post(&lock2);
	
   	  if (n == NULL)
   		break;
	for(int i = 0; i < 64; i++){
		if(n->key[i]==' '){
			n->key[i] = '-';
		}

	fprintf(flog,"%s\n", n->key[i]);
	printf("%s",n->key[i]);
}
	
	

	sem_wait(&lock3);
	enQueue(x, n->key);
	sem_post(&lock3);
}
}
void upper(struct queue* y){ //This method changes the lower letters to upper letters

	while(1){
	sem_wait(&lock3);
	struct QNode* n = deQueue(q2);
	sem_post(&lock3);
   	  if (n == NULL)
   		break;
	  for(int i=0;i<64;i++){
		if(97<= n->key[i] && n->key[i] <=122){
			n->key[i]=n->key[i]-32;
		}
	fprintf(flog,"%s\n", n->key[i]);
	printf("%s\n", n->key[i]);
	
	}
    
	fprintf(flog,"%s\n", n->key);
	
	sem_wait(&lock4);
	enQueue(y, n->key);
	sem_post(&lock4);printf("%s",n->key);
}
}





void writer(struct queue* z) //It counts lines of input file,writes all updates that is made by other meethods to "log.txt"
{
				
				while(1){
				sem_wait(&lock4);
				struct QNode* n = deQueue(q3);
            			sem_post(&lock4);
   	 			 if (n == NULL)
   					break;
				
                       
					fprintf(flog,"%s",n->key);
					
					i++;
					
					printf("%s",n->key);
						}fprintf(stderr,"Number of line %d",i);
						

				


}















