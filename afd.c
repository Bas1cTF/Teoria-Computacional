//Simulación de un AFD
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *fichero;
int j,k;
int delta[100][100];         //Aquí almacenamos la representación tabular de nuestro AFD,
                             //es decir, su función de transición delta.
int estadoFin[100];          //Aquí almacenamos los estados finales.                   
char alfabeto[100];          //Aquí almacenamos el alfabeto aceptado por el afd

void crearDelta(char *nomArch,int num_lineas){
  int c,t=0;
  j=num_lineas-2;
  //Abrimos el archivo a utilizar
  fichero=fopen(nomArch,"rt");
  //Guardamos el alfabeto recibido
  while (1) {
    c = fgetc(fichero);
    alfabeto[t] = c;
    if (alfabeto[t] == '\n'){
      c=0;
      break;
    }
    t++;
  }
  k = strlen(alfabeto)-1;
  printf("%d  %d\n",c,j);
  printf("%s",alfabeto);  
  //Creamos la delta con los estados proporcionados
  for(int x = 0; x<j;x++){
    for(int y = 0;y<k;y++) {
     c = fgetc(fichero);
     if(c=='\n'){
	c=fgetc(fichero);  //Como solo se recorren los estados se omiten los saltos de linea.
     }
     delta[x][y]=c-48;
     //printf("delta[%d][%d]=%d\n",x,y,delta[x][y]); Quitar comentarios para desplegar la delta
    }
  }
  //Obtenemos los estados finales
  t=0; 
  while (1) {
    c = fgetc(fichero);
    if(feof(fichero)){
      break;
    }
    if(c!=123 && c!=44 && c!=125 && c!=10){
      estadoFin[t]=c-48;
      t++;
    }
  }
  estadoFin[t]=-1; // Define el fin del espacio utilizado en el arreglo.
  fclose(fichero); //Cerramos el archivo utilizado
}

int afd(char *cad){
int estado=0,posCad=0;
  int simbolo,acpt;
  for(posCad=0;posCad<strlen(cad);posCad++){ //Realizamos un ciclo que recorrerá cada posición (símbolo)
      int i = 0;			     //de la cadena de entrada., 
      while(1){
	  if(alfabeto[i]==cad[posCad]){
	    simbolo=i;
	    break;
	  }
	  i++;		  
      }                                    
						     
      estado=delta[estado][simbolo];        //Aquí es donde sucede la transición: 
						     //A partir de un estado y un símbolo, la función delta (codificada 
						     //en la tabla) nos indica a qué estado debemos transitar. 
      printf("%d,%c,%d\n",estado,alfabeto[i],posCad); //Para fines de depuración desplegamos en pantalla
		                                           //una instantanea de cada iteracion.
  }
  printf("Termine en el estado: %d\n",estado);
  int i = 0;
  while(1){
     if(estado==estadoFin[i])           //Realizamos una comparación con cada estado final.
     {  
		        
        acpt=1;
        break;
     }
     if(estadoFin[i]==-1)           	//Recorrimos toda la cadena y el estado en el que terminamos NO pertenece a Qf                                        
     {
        acpt=0;
        break;
     }
     i++;
  }
  return acpt;
}

int contar_lineas(char *nomArch) {
  fichero = fopen(nomArch,"rt");
  int cont = 0;
  int c;
  char aux;
  while (1) {
    c = fgetc(fichero);
    aux = c;
    if(feof(fichero)){
       break;
    }
    if (aux == '\n'){
      cont++;
      ++c;
    }
  }
  fclose(fichero);
  return cont;
}		       

int main(int argc, char** argv) { //Utilizamos el paso de argumentos de la linea de comando.
	                          //El primero es el comando usado. O sea, el nombre de nuestro programa ejecutable.
    int num_lineas;
    char cad [100]; //en cad almacenaremos la cadena que se probará si es aceptada por el AFD.
    if(argc != 3){     //Validamos que el programa reciba la cantidad correcta de argumentos
         printf ("Uso: %s <Archivo> Cadena_a_analizar\n",argv[0]);
	 return 0;	
    }
    strcpy(cad,argv[2]); //En el siguiente argumento, argv[2], recibimos la cadena a analizar.
    num_lineas = contar_lineas(argv[1]); 
    crearDelta(argv[1],num_lineas);
    
    if (afd(cad)==1){   //Si afd devuelve 1, es aceptada...
         printf("La cadena %s ",cad);
	 printf("SI es aceptada\n");	
    }
    else{              //De lo contrario...
         printf("La cadena %s ",cad);
	 printf("NO es aceptada\n");
    }
    return 0;
}

