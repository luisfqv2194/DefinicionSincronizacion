#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>

//IMPORTANT; To delete shared memory use ipcrm -M <key>


int main(int argc , char *argv[]){


	char* encabezado = "Bitacora Inicializada \n Cantidad de espacios Solicitadas: \n ";  
	int cantInt;
	int iteratorNum;
	int displayIterator;
    int shmid;
    key_t key;
    int *shm, *shmPos1, *shmPos2;
	sem_t *semMemoria;
	sem_t *semBitacora;

	key = 6969;

	puts("Ingrese la cantidad de espacios a guardar: ");
    	scanf("%d",&cantInt);

 //Create the segment

    if ((shmid = shmget(key, sizeof(int)*cantInt, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return(1);
	}

	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return(1);
    }

     /* Now put some things into the memory for the
     * other process to read.
     */

    shmPos1 = shm;

    for (iteratorNum = 0; iteratorNum <= cantInt; iteratorNum++){
        *shmPos1++ = -1;
	}
    shmPos1 = NULL;
	shmPos2=shm;


	for(displayIterator = 0;displayIterator <=cantInt; displayIterator++){
		printf("%d ",*shmPos2);
		shmPos2++;
	}
	shmPos2 = NULL;

	semMemoria = sem_open("Sem_S", O_CREAT | O_EXCL, 0644, 1);
	printf("\n\nInicializacion del semaforo para la memoria\n");

	semBitacora = sem_open("Sem_B", O_CREAT | O_EXCL, 0644, 1);
	printf("\nInicializacion del semaforo para la bitacora\n\n");


	FILE *f;
	f = fopen("Bitacora.txt","a");
	fwrite(encabezado,strlen(encabezado),1,f);
	fprintf(f,"%d",cantInt);
	fclose(f);

	return 1;
	
}

