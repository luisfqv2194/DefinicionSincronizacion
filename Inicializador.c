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


	char* encabezado = "Bitacora Inicializada \n Cantidad de Lineas Solicitadas: \n ";  
	int cantLineas;
	int c;
	int verificador;
    int shmid;
    key_t key;
    int *shm, *s, *m;
	sem_t *sem;
	sem_t *semb;

	key = 6969;

	puts("Ingrese la cantidad de enteros a guardar: ");
    	scanf("%d",&cantLineas);

 //Create the segment

    if ((shmid = shmget(key, sizeof(int)*cantLineas, IPC_CREAT | 0666)) < 0) {
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

    s = shm;

    for (c = 0; c <= cantLineas; c++){
        *s++ = -1;
	}
    s = NULL;
	m=shm;


	for(verificador = 0;verificador <=cantLineas; verificador++){
		printf("%d ",*m);
		m++;
	}
	m = NULL;

	return 1;
	
}

