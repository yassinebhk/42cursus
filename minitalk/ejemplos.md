#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
 
void manejadora(int s){
    signal(s,manejadora);
} 

int main(){
    signal(SIGUSR1,manejadora);
    pid_t pidHijo1 = fork();
    if(pidHijo1 < 0){
        perror("Error fork() 1");
        exit(1);
    }else if(pidHijo1 > 0){//zona exclusiva padre
        pid_t pidHijo2 = fork();
        if(pidHijo2 < 0){
            perror("Error fork() 2");
            exit(1);
        }else if(pidHijo2 > 0){//zona exclusiva padre
            pause(); //espera la señal del hijo 2
            printf("Padre: recibida señal\n");
            wait(0);//Espero a que acabe un hijo
            printf("Padre: primer hijo ha acabado\n");
            printf("Soy padre y envio señal a Hijo 1 (%ld)\n", pidHijo1);
            kill(pidHijo1,SIGUSR1);
            wait(0);//Espero a que acabe otro hijo
            printf("Padre: segundo hijo ha acabado. FIN\n");
       
        }else{// zona exclusiva del Hijo 2
            printf("Soy Hijo 2 [%ld] y envio señal a mi padre\n", getpid());
            kill(getppid(),SIGUSR1); /*ver nota al final*/
            printf("Hijo 2 [%ld]: FIN\n", getpid());
            exit(0);
        }
    }else{//zona exclusiva del Hijo 1	
        printf("Soy Hijo 1 [%ld] y espero señal de mi padre\n", getpid());
        pause(); //espera la señal del padre
        printf("Hijo 1 [%ld]: recibida señal. FIN\n", getpid());
        exit(0);
    }
    return 0;
}

/* NOTA:
-En algunas ejecuciones, y debido a la concurrencia,
puede que el padre envíe la señal al hijo 1 pero éste aún no haya
salido de su fork(). Resulta que fork(), antes de terminar y devolver
el valor cero, limpia la cola de señales pendientes por ser recibidas
en el proceso, con lo cual, la señal SIGUSR1, si estaba en cola, nunca llega.

Es por eso que algunas veces el programa hace lo esperado según
el enunciado y termina bien, y otras se queda bloqueado en el pause() 
del hijo 1

¿POSIBLE SOLUCION PARA EVITAR UN BLOQUEO INDEFINIDO EN UNA LLAMADA AL SISTEMA? 
(OJO, ESTO NO ES PARTE DEL ENUNCIADO DE ESTE PROBLEMA, ES UNA SOLUCIÓN GENERAL)

1) COMPILAR EN MODO SYSTEM V
2) REGISTRAR UNA FUNCION MANEJADORA PARA SIGALRM (puede estar vacía)
3) ACTIVAR UNA ALARMA ANTES DE EJECUTAR LA LLAMADA AL SISTEMA BLOQUEANTE. 
Si al salir del bloqueo el resultado es -1 y errno == EINTR, ya puedes proseguir
con la ejecución de tu programa. Pero ojo, como no has conseguido que la llamada
al sistema funcione, no deberías seguir como si no hubiera pasado nada. Podrías,
por ejemplo, hacer algunos reintentos y luego salirte del programa. 
Esto técnica es muy útil cuando llamas al open() de fifos, con un read(), pause(), etc.

*/

