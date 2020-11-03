//JUEGO TÍPICO DE SNAKE EN EL QUE CRECÍA A MEDIDA QUE COMÍA

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define V 21
#define H 85
#define N 100

typedef struct{
	int x, y;  //coordenadas
	int modX, modY; //modificadores con los que se suma para que avance
	char imagen;
}snk;

typedef struct{
	int x, y;
}frt;

snk snake[N];
frt fruta;

void inicio(int *tam, char campo[V][H]);
void intro_campo(char campo[V][H]);
void intro_datos(char campo[V][H], int tam);
void dibujar(char campo[V][H]);
void loop(char campo[V][H], int tam);
void input(char campo[V][H], int *tam, int *muerto);
void update(char campo[V][H], int tam);
void intro_datos2(char campo[V][H],int tam);


int main(){
	int tam;
	char campo[V][H];
	
	inicio(&tam, campo);
	loop(campo, tam);
	
	system("pause");
	return 0;	
}


/**************FUNCIÓN: DONDE VOY A INICIALIZAR ALGUNAS PARTES. INTRODUZCO FUNCIONES PARA EMPEZAR ***************/
void inicio(int *tam, char campo[V][H]){
	
	int i, j;
	
	//inicializo el tamaño gusano
	*tam = 4;
	
	//inicializamos la cabeza
	snake[0].x = 32;
	snake[0].y = 10;
	
	//inicializo la fruta
	srand(time(NULL));
	fruta.x = rand() % (H-1);
	fruta.y = rand() % (V-1);
	
	while(fruta.x == 0){ //creo que se puede arreglar poníendole un sumando para que no de 0 nunca
		fruta.x = rand() % (H-1);
	}
	
	while(fruta.y == 0){
		fruta.y = rand() % (V-1);
	}
	
	//inicializamos los modificadores para que vaya avanzando
	for(i=0;i<*tam; i++)
	{
		snake[i].modX = 1;
		snake[i].modY = 0;
		
	}
		
	intro_campo(campo); 
	intro_datos(campo, *tam);
		
}


/**************FUNCIÓN: INICIO LOS VALORES DE MI CAMPO ***************/
void intro_campo(char campo[V][H]){
	
	int i, j;	
	
	for(i=0;i<V;i++){
		
		for(j=0;j<H;j++){
			
			if(i==0 || i==V-1)
			{
				campo[i][j]='-';
			}
			else
			{
				if(j==0 || j==H-1)
				{
					campo[i][j]='|';
				}
				else{
					campo[i][j]=' ';
				}
			
			}
		}
	}
}


/**************FUNCIÓN: INICIO LOS VALORES RESTANTES: GUSANO,  ***************/
void intro_datos(char campo[V][H], int tam){
	
	int i;
	
	for(i=1;i<tam;i++){ //fijamos el tamaño del gusano en base a la cabeza (i-1 = 0). Luego vamos sacando las cordenadas siempre en base al anterior
		snake[i].x = snake[i-1].x-1;
		snake[i].y = snake[i-1].y;
		
		snake[i].imagen = 'X';
	}
	
	snake[0].imagen = 'O';
	
	//añadimos las imágenes a sus coordenadas que apuntamos previamente
	for(i=0;i<tam;i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen; //meter siempre la coordenada vertical primero
	}
	
	campo[fruta.y][fruta.x] = '%';
}

/**************FUNCIÓN: LOOPING CON LAS FUNCIONES DE MODIFICACIÓN  ***************/

void loop(char campo[V][H], int tam){

	int muerto;
	muerto=0;

	do{
		Sleep(50);
		system("cls");
		dibujar(campo);
		input(campo, &tam, &muerto); 
		update(campo, tam);
	}while(muerto==0);
	
}

/**************FUNCIÓN VARIAS: SI TOCO CON LAS PAREDES O YO MISMO, SI COMIO LA FRUTA O PARA MOVERLO ***************/
void input(char campo[V][H], int *tam, int *muerto){
	
	int i, key;
	
	
	//comprobación de si hemos tocado alguna pared del tablero
	if( (snake[0].x == 0) || (snake[0].x == H-1) || (snake[0].y == 0) || (snake[0].y == V-1))
	{
		*muerto = 1;
	}
	
	//comprobación de si nos hemos comido a nosotros mismos
	for(i=1;i<*tam && *muerto==0;i++)
	{
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			*muerto = 1;
		}
	}
	
	//comprobación de si nos hemos comido la fruta
	if( (snake[0].x == fruta.x) && (snake[0].y == fruta.y) ){
		*tam+=1;
		snake[*tam-1].imagen='X';
		fruta.x = (rand() % (H-2))+1;
		fruta.y = (rand() % (V-2))+1;
	}
	
	/*while(fruta.x == 0){ //creo que se puede arreglar poníendole un sumando para que no de 0 nunca
		fruta.x = rand() % (H-1);
	}
	
	while(fruta.y == 0){
		fruta.y = rand() % (V-1);
	}*/
	
	
	//acción de movimiento con el teclado
	if(*muerto==0)
	{
		if(kbhit()==1)
		{
			key=getch();
			if(key=='8' && snake[0].modY!=1)
			{
				snake[0].modY = -1;
				snake[0].modX = 0;
			}
			
			if(key=='2' && snake[0].y!=-1)
			{
				snake[0].modY = 1;
				snake[0].modX = 0;
			}
			
			if(key=='4' && snake[0].modX!=1)
			{
				snake[0].modY = 0;
				snake[0].modX = -1;
			}
			
			if(key=='6' && snake[0].modX!=-1)
			{
				snake[0].modY = 0;
				snake[0].modX = 1;
			}
			
		}
	}
}

/**************FUNCIÓN: ACTUALIZAR LOS VALORES ***************/
void update(char campo[V][H], int tam){
	
	//borrar todos los datos de la matriz y dibujar la tabla otra vez
	intro_campo(campo);
	
	//introducir los nuevos datos 
	intro_datos2(campo,tam);
}

/**************FUNCIÓN: INTRODUCIR NUEVOS VALORES ***************/
void intro_datos2(char campo[V][H], int tam){
	
	int i;
	
	//con avanzamos con el cuerpo. Las coordenadas del penúltimo pasan al último y así hasta llegar a 1
	for(i=tam-1;i>0;i--){
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	
	//las coordenadas de la cabeza se tienen que sumar a los modificadores para que avancen
	snake[0].x = snake[0].x + snake[0].modX;
	snake[0].y = snake[0].y + snake[0].modY;
	
	
	for(i=0;i<tam;i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '%';
}



/**************FUNCIÓN: DIBUJO TODOS LOS VALORES  ***************/
void dibujar(char campo[V][H]){
		
		int i, j;
		
		for(i=0;i<V;i++){
			
			for(j=0;j<H;j++){
				
				printf("%c",campo[i][j]);
			}
			printf("\n");
		}
}
