#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5  // numero de filosofos
#define ESQUERDA (i+N-1)%N // vizinho a esquerda de i left
#define DIREITA (i+1)%N   // vizinho a direita de i rigth
#define PENSANDO 0 // filosofo pensando
#define COM_FOME 1 // filosofo tentando pegar garfos co fome
#define COMENDO 2 // filosofo comendo comendo
#define VERDADE 1 //variavel true ou false

sem_t s[N]; //um semaforo por filosofo
sem_t mutex; //exclusao mutua para secoes criticas

int   state[N]; //array para controlar os filosofos
pthread_t thread1, thread2, thread3, thread4, thread5; //uma thread para cada filósofo

// funções
void pegar_talher(int i); //pegue garfos - take_forks
void devolver_talher(int i); //devolver garfos - put_forks
void teste(int i); // teste - test
void pensar(int i); // pensar - think
void comer(int i); //comer - eat

//numero do filosofo, de 0 a n-1

// metodo filosofo 
void filosofo(int i) {
	while (VERDADE) {  // repete eternamente
 		pensar(i);  // o filosofo esta pensando
 		pegar_talher(i); // pega dois garfos ou bloqueia
 		comer(i);  // come 
 		devolver_talher(i); // coloca os dois garfos na
	}
}

//metodo pega_talher
void pegar_talher(int i) {
	sem_wait(&mutex);//down(&mutex); /* entra na regiao cri­tica */
	state[i] = COM_FOME; /* registra que o filosofo i esta com fome */
	printf("FILOSOFO %d PENSANDO\n",i);
	teste(i);  /* tenta pegar 2 garfos */
	sem_post (&mutex);//up(&mutex);  /* sai da regiao cri­tica */
	sem_wait(&s[i]);//down(&s[i]); /* bloqueia se os garfos nao foram pegos */
}

//metodo devolver_talher
void devolver_talher(i) {
	sem_wait(&mutex); //down(&mutex) entra na regiao critica
	state[i] = PENSANDO;//o filosofo acabou de comer
	printf("FILOSOFO %d PENSANDO \n",i);
	teste(ESQUERDA);  //verifica se o vizinho da esquerda pode comer
	teste(DIREITA); //verifica se o vizinho da direita pode comer
	sem_post(&mutex);//up(&mutex) sair da regiao critica 
}

//metodo de teste
void teste(i) {  //testa se os filosofos vizinhos podem comer
     if (state[i] == COM_FOME && state[ESQUERDA] != COMENDO && state[DIREITA] != COMENDO){
   		state[i] = COMENDO;
   		printf("FILOSOFO %d COMENDO\n",i);
   		sem_post(&s[i]);
     }
}

// metodo pensar Filosofo esta pensando
void pensar(int i) {
	sleep(1);
	return;
}

//metodo comer Filosofo esta comendo
void comer(int i) {
	sleep(1);
	return;
}

main(){
int  iret1, iret2, iret3, iret4, iret5;

int i;
int p[N] ;

//inicialização dos semaforos
int sem_init(sem_t *sem, int pshared, unsigned int value);
     for(i= 0; i < N ;i++ ){
	 sem_init(&s[i], 0, 1);
	 p[i] = i;
}

sem_init(&mutex, 0, 1);

// criação de threads independentes que executarao
iret1 = pthread_create( &thread1, NULL,(void *) filosofo,(int*)p[1]);
iret2 = pthread_create( &thread2, NULL,(void *) filosofo,(int*)p[2]);
iret3 = pthread_create( &thread3, NULL,(void *) filosofo,(int*)p[3]);
iret4 = pthread_create( &thread4, NULL,(void *) filosofo,(int*)p[4]);
iret5 = pthread_create( &thread5, NULL,(void *) filosofo,(int*)p[0]);

pthread_join( thread1, NULL);
pthread_join( thread2, NULL);
pthread_join( thread3, NULL);
pthread_join( thread4, NULL);
pthread_join( thread5, NULL);

exit(0);
}
