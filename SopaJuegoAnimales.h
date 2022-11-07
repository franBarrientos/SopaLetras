/* TIPO DE DATOS ABSTRACTO: CATEGORIA ANIMALES */

/* librerias */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* valores constantes */
#define CADENA 30
#define MAX_PAL 8
#define MAX_COLUM 8
#define MAX_FILA 8 

/* definicion tipo de dato cadena */
typedef char tc_cadCar[CADENA];

/* definicion registro de palabra */
typedef struct {
	int categoria;
	tc_cadCar palabra;
}tr_sopaLetras;

/* definicion tipo vector de registro (palabras) */
typedef tr_sopaLetras tArrayPalCat[MAX_PAL];

/* definicion estructura lista estatica */
typedef struct {
	tArrayPalCat listaPalabras;
	int indice;
} tLista;

/* definicion estructura pila estatica */
typedef struct {
	tArrayPalCat pilaPalabras;
	int tope;
} tPila;

/* definicion de matriz */
typedef char tMatriz[MAX_FILA][MAX_COLUM];

/* prototipado funciones - archivo binario */
void iniciarProceso();
void leerArchivo();
void procesarRegistros();
void finalizarProceso();

/* prototipado funciones definidas por el programador */
void inicializarFunciones();
void ingresarPalabra();
void comparaPalabras(tLista, tPila);
void condBuscarPalabra();
void procesaBusqueda();
void cantPalabrasEncontradas();

/* prototipado funciones - lista estática */
void inicializarLista();
bool listaVacia(tLista);
bool listaLlena(tLista);
void insertarElementos(tr_sopaLetras);
void visualizarElementos(tLista);

/* prototipado funciones - pila */
void crearPila();
bool pilaVacia(tPila);
bool pilaLlena(tPila);
void apilarPalabra(tr_sopaLetras);
void visualizarPila();
void desapilarPalabra();

/* prototipado funciones - matriz */
void inicializarMatriz();
void asignarLetrasSopa();
void asignarLetrasAzar();
void visualizarMatriz();

/* variables registro, fichero, lista estática,Temporizador pila y matriz */
tr_sopaLetras vr_sopaLetras;
FILE * vf_sopaLetras;
tLista lista;
tPila pila;
tMatriz sopa;


/* variable de entrada( palabra ingresada por teclado ) */
tc_cadCar palabra;

/* var de entrada( define si sigue o no comparando palabras ) */
char condComparaPal;

/* contadores */
int palCorrectas, palIncorrectas;

/* inicializaciones de lista - pila - archivo y matriz */

void inicializarFunciones() {
	inicializarLista();
	crearPila();
	inicializarMatriz();
	iniciarProceso();
	
	/* inicializacion de contadores */
	palCorrectas = 0;
	palIncorrectas = 0;
}

/* declaración de instrucciones funciones de archivo */

void iniciarProceso() {
	/* apertura del archivo en modo "lectura" */
	vf_sopaLetras = fopen("SopaLetrasJuego.dat", "rb");
	
	/* lectura adelantada */
	leerArchivo();
}

void leerArchivo() {
	/* lectura de cada registro dentro del archivo bianrio */
	fread(&vr_sopaLetras, sizeof(tr_sopaLetras), 1, vf_sopaLetras);
}

void procesarRegistros() {
		/* mientras que, no sea el ultimo registro leido en el archivo, y se cumpla la condicion que la categoria pertenezca al nro 1 (frutas) 
	   el registro se almacena en una lista estatica *//* se realiza la insercion de datos, partiendo del registro hasta una lista estatica */
	while( !feof(vf_sopaLetras) ) {
		if ((vr_sopaLetras.categoria == 3) ){
			insertarElementos(vr_sopaLetras);
		}
		/* realiza la lectura del siguiente registro */
		leerArchivo();
	}
	/* una vez que inserta el ultimo dato, se corta la iteracion y se cierra el archivo */
	finalizarProceso();
}

void finalizarProceso() {
	/* cierre del archivo binario */
	fclose(vf_sopaLetras);
}

/* declaracion de instrucciones funciones de matriz categoria animales */

void inicializarMatriz() {
	/* se realiza el correspondiente recorrido para asignar cada posicion de la matriz (fila/columna) como valor inicial 'vacio' */
	int i, j;
	
	for (i = 0; i < MAX_FILA; i++) {
		for (j = 0; j < MAX_COLUM; j++) {
			sopa[i][j] = ' ';
		}
	}
	/* se muestra titulo de presentacion */
	printf("\n\t *** ENSOPA-2 - CATEGORIA ANIMALES ***\n\n");
}

void asignarLetrasAzar() {
	/* de acuerdo con la funcion rand(), se asigna a cada posicion de la matriz un caracter al azar entre la A y la Z mayuscula */
	int i, j;
	
	srand(time (NULL) );
	
	for (i = 0; i < MAX_FILA; i++) {
		for (j = 0; j < MAX_COLUM; j++) {
			sopa[i][j] = 'A' + rand() % ('Z' - 'A'+1 );
		}
	}
}

void asignarLetrasSopa() {
	/* para cada posicion (fila/columna) se define el caracter a ocupar, para luego, formar y determinar el sentido de la palabra (vertical u horizontal) */
	sopa[0][4] = 'L'; sopa[0][5] = 'E'; sopa[0][6] = 'O'; sopa[0][7] = 'N';
	sopa[3][6] = 'O'; sopa[4][6] = 'S'; sopa[5][6] = 'O';
	sopa[1][2] = 'C'; sopa[2][2] = 'I'; sopa[3][2] = 'E'; sopa[4][2] = 'R'; sopa[5][2] = 'V'; sopa[6][2] = 'O';
	sopa[7][0] = 'O'; sopa[7][1] = 'V'; sopa[7][2] = 'E'; sopa[7][3] = 'J'; sopa[7][4] = 'A';
	sopa[1][0] = 'R'; sopa[2][0] = 'A'; sopa[3][0] = 'N'; sopa[4][0] = 'A';
	sopa[2][2] = 'I'; sopa[2][3] = 'G'; sopa[2][4] = 'U'; sopa[2][5] = 'A'; sopa[2][6] = 'N'; sopa[2][7] = 'A';
	sopa[5][2] = 'V'; sopa[5][3] = 'A'; sopa[5][4] = 'C'; sopa[5][5] = 'A';
	sopa[5][7] = 'P'; sopa[6][7] = 'E'; sopa[7][7] = 'Z';
}

void visualizarMatriz() {
	/* a partir del recorrido desde el inicio hasta el final de la matriz, se muestran los caracteres correspondientes */	
	int i, j;
	
	for (i = 0; i < MAX_FILA; i++) {
		printf("\t");
		for (j = 0; j < MAX_COLUM; j++) {
			printf(" %c | ", sopa[i][j] );
		}
		printf("\n");
	}
}

/* declaración de instrcucciones funciones de lista estática */

void inicializarLista() {
	/* el valor de la lista se inicializa en -1, porque el primer elemento a insertar lo hará en la posicion 0 */
	lista.indice = -1;
}

bool listaVacia(tLista pLista) {
	/* devuelve "true" si el valor de la lista es -1, es decir, si esta vacia. 
	Caso contrario, si tiene por lo menos 1 elemento, devuelve "false" */
	return pLista.indice == -1;
}

bool listaLlena(tLista pLista) {
	/* devuelve "true" si el valor de la lista es igual al limite maximo de palabras admitidas, en ese caso, 7 palabras. 
	   De lo contratio, devuelve "false" */
	return pLista.indice == MAX_PAL - 1;	
}

void insertarElementos(tr_sopaLetras pSopa) {
	/* si la lista no esta llena, significa que tenemos espacio para seguir insertando datos. el indice avanza un valor 
	   y se realiza la insercion de lo que se recibe por parametro en la lista de palabras. 
	   de lo contrario, si la lista esta llena, se informara un aviso */
	if(!listaLlena(lista)) {
		lista.indice+=1;
		lista.listaPalabras[lista.indice] = pSopa;
	} else {
		printf("\n\t\t *** No pueden agregar mas de %d palabras. La lista esta llena *** \n", MAX_PAL);
	}
}

void visualizarElementos(tLista pLista) {
	/* si la lista no esta vacia, significa que hay elementos para mostrar, lo hace a traves de un recorrido que muestra los elementos 
	   a medida que se desplaza por el vector, el recorrido inicia desde 0 hasta el elemento final (indice) */
	int i;
	if(!listaVacia(lista)) {
		printf("\n Palabras en la lista \n\n");
		
		for(i=0; i <= pLista.indice; i++) {
			printf(" %s - ", pLista.listaPalabras[i].palabra);
		}
	} else {
		printf("\n\t\t *** No es posible listar los elementos. Lista vacia! *** \n");
	}
	printf("\n\n");
}

/* declaración de instrucciones funciones de pila */

void crearPila() {
	/* el valor de la pila se inicializa en -1, porque el primer elemento a insertar lo hará en la posicion 0 */
	pila.tope = -1;
}

bool pilaVacia(tPila pPila) {
	/* devuelve "true" si el valor de la pila es -1, es decir, si esta vacia. 
	Caso contrario, si tiene por lo menos 1 elemento, devuelve "false" */
	return pPila.tope == -1;
}

bool pilaLlena(tPila pPila) {
	/* devuelve "true" si el valor de la pila es igual al limite maximo de palabras admitidas, en ese caso, 7 palabras. 
	   De lo contratio, devuelve "false" */
	return pPila.tope == MAX_PAL-1;
}

void apilarPalabra(tr_sopaLetras pPalYcat) {
	/* si la pila no esta llena, significa que tenemos espacio para seguir insertando datos. el tope incrementa un valor 
	   y se realiza la insercion de lo que se recibe por parametro en la pila de palabras. 
	   de lo contrario, si la pila esta llena, se informara un aviso */
	if(!pilaLlena(pila)) {
		pila.tope+=1;
		pila.pilaPalabras[pila.tope] = pPalYcat;
	} else {
		printf("\n *** No es posible almacenar mas de %d elementos *** \n", MAX_PAL);
	}
}

void visualizarPila() {
	/* si la pila esta vacia, significa que no hay elementos por mostrar y se notificará mediante un aviso, de lo contrario, 
	muestra los elementos a medida que se desplaza por el vector, el recorrido inicia desde 0 hasta el elemento final (tope) */
	int i;
	
	if(pilaVacia(pila)) {
		printf("\n *** No se encontraron palabras! *** \n");
	} else {
		printf("\n\t *** FIN DEL JUEGO *** \n\n Palabras encontradas: \n");
		
		for(i=0; i <= pila.tope; i++) {
			printf(" %s - ", pila.pilaPalabras[i].palabra);
		}
	}
	/* al final del juego se muestran los resultados correspondientes a las palabras acertadas y los errores */
	cantPalabrasEncontradas();

}

/* declaracion de instrucciones funciones definidas por el programador */

void cantPalabrasEncontradas() {
	/* se muestran los resultados correspondientes */
	printf("\n\n Encontraste %d palabras correctas", palCorrectas);
	printf("\n Realizaste %d palabras incorrectas\n", palIncorrectas);
}

void condBuscarPalabra() {
	/* pregunta al usuario si ha encontrado una palabra */
	printf("\n Ha encontrado una palabra? (s/n): ");
	fflush(stdin);
	scanf("%c", &condComparaPal);
	
	/* invocacion a la funcion que realizara el proceso de busqueda y comparacion de la palabra */
	procesaBusqueda();
}

void procesaBusqueda() {

	/* mientras que el usuario haya encontrado palabras, es decir, ingresa la letra 's', registrará esa palabra por teclado, 
	   se realiza la comparacion de la palabra ingresada por teclado con la palabra almacenada en la lista y la pila, una vez terminado este proceso,
	   se vuelve a preguntar al usuario si encontro alguna otra palabra, la condicion terminara su ejecucion cuando el usuario ingrese la letra 'n' */
	while(condComparaPal == 's' || condComparaPal == 'S') {
		ingresarPalabra();
		comparaPalabras(lista, pila);
		condBuscarPalabra();
	}

}

void ingresarPalabra() {
	/* ingresa por teclado la palabra que descubre el usuario */
	printf("\n Escriba la palabra: ");
	fflush(stdin);
	scanf("%s", &palabra);
}

bool estaEnPila(tPila pPila, tc_cadCar palabra){
	/* si el valor del tope es el valor del inicio (-1) significa que la palabra no esta dentro de la pila, por lo tanto, devuelve 'false' 
	   si el valor es distinto del tope, se recorre la pila desde el inicio hasta el final (tope) comparando si la palabra que se ingreso por teclado 
	   coincide con alguna palabra ya almacenada en la pila, si esto es asi, devuelve 'true', de otra manera, devuelve 'false' */
	int i;
	
	if(pPila.tope == -1){
		return false;
	}else{
		for(i=0; i <= pPila.tope; i++){
			if(strcmp(pPila.pilaPalabras[i].palabra, palabra) == 0){
				return true;
			}
		}
		return false;
	}
}

void comparaPalabras(tLista pLista, tPila pPila) {
	/* recorre la lista de palabras almacenadas desde el inicio hasta el final (indice) y compara la palabra que se ingreso 
	   por teclado con alguna de las palabras que se encuentra en la lista, si la misma coincide y
	   ademas se cumple que dicha palabra no se encuentra almacenada en la pila, la misma va a apilarse y cambia el valor de la variable bandera.
	   luego, si la bandera es valor 'true' significa que apilo la palabra y la misma se encuentra en la cuadricula, incrementa el contador de la palabra correcta
	   si, por el contrario, la bandera es valor 'false', significa que la palabra ya fue almacenada, o, que no se encuentra en la cuadricula e,  incrementa el contador de la palabra incorrecta */
	int i;
	bool flag = false;
	
	for(i=0; i <= pLista.indice && flag != true; i++) {
		if(strcmp(pLista.listaPalabras[i].palabra, palabra) == 0) {
			
			if(!estaEnPila(pPila, palabra)){
				apilarPalabra(pLista.listaPalabras[i]);
				flag = true;
			}
		}
	}
	
	if(flag) {
		printf(" La palabra se encuentra en la sopa! \n");
		palCorrectas += 1;
	} else {
		printf(" Ups! Esa palabra ya la encontraste, o no esta dentro de la sopa\n Intentalo de nuevo! \n");
		palIncorrectas += 1;
	}
}
