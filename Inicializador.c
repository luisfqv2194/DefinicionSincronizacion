
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>






int main(int argc , char *argv[]){


	char* encabezado = "Bitacora Inicializada \n Cantidad de Lineas Solicitadas: \n ";  
	int cantLineas;
	int c;
	int verificador;
    int shmid;
    key_t key;
    int *shm, *s, *m;
	sem_t *sem;

	key = 6969;

	puts("Ingrese la cantidad de paginas con las que desea trabajar: ");
    	scanf("%d",&cantLineas);

 //Create the segment

   
}

