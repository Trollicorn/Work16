#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main(){
  key_t key;
  int shmid;
  char * data;

  key = ftok("string",'f');
  shmid = shmget(key, 200, 0666 | IPC_CREAT);

  data = shmat(shmid, (void *) 0, 0);
  
  if (!strlen(data)){
    printf("new segment made\n");
  }
  else{
    printf("stuff: %s\n",data);
  }

  char input[200];
  
  printf("change segment? y/n\n");
  fgets(input,sizeof(input),stdin);
  if (input[0] == 'y'){                //change stuff
    printf("enter new stuff\n");
    fgets(input,sizeof(input),stdin);
    input[strlen(input)-1] = '\0';
    strcpy(data,input);
 //   printf("test:%s\n",data);
  }
  input[0] == 'n';
  shmdt(data);
  printf("delete segment? y/n\n");
  fgets(input,sizeof(input),stdin);
  if (input[0] == 'y'){ //delete    
    shmctl(shmid, IPC_RMID, NULL);
  }
  return 0;
}
