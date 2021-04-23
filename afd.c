//Simulación de un AFD
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *fichero;
int j,k;
//int delta[100][100-k];         //Aquí almacenamos la representación tabular de nuestro AFD,
//int j,k;                            //es decir, su función de transición delta.

/*int afd(char *cad){ //Analiza la cadena
 
}
struct delta{:
  int estado [100];
  char simbolo [100];
};*/
int afd(char *nomArch,char *cad,int num_lineas){
  int delta[j][k];
  int y=0;
  j=num_lineas-2;
  char alfabeto [100];
  char aux;
  char aux2 [100];
  char estadoFin[100];
  fichero=fopen(nomArch,"rt");
  //fgets(alfabeto,100,fichero);
  while (1) {
    c = fgetc(fichero);
    aux = c;
    if (aux == '\n'){
      c=0;
      break;
    }
  }
  k = strlen(aux)-1;
  for(int i=0;i<j;i++){
    fgets(aux,100,fichero);
    for(int x = 0;x<k;x++){
      delta[i][alfabeto[x]]=aux[x];
      //printf("delta[%d][%d]:%c\n",i,alfabeto[x],delta[i][alfabeto[x]]);
    }
  }
  fgets(aux2,100,fichero);
  for(int l=0;l<strlen(aux2)-1;l++){
    if(aux2[l]!=123 && aux2[l]!=44 && aux2[l]!=125){
      estadoFin[y]=aux[l];
      y++;
    }
  }
  /*printf("\n%c\n",estadoFin[1]);
  //fclose(fichero);
  for(int h=0; h<j;h++){
     for(int z=0; z < k;z++){
        printf("delta[%d][%d]:%c\n",h,alfabeto[z],delta[h][alfabeto[z]]);
     }
  }*/
  fclose(fichero);
  int estado=0,posCad=0;
  int simbolo;
  for(posCad=0;posCad<strlen(cad);posCad++){ //Realizamos un ciclo que recorrerá cada posición (símbolo)
	 					     //de la cadena de entrada., 
	       simbolo=cad[posCad];               //Ojo aquí: La dualidad de los símbolos del código ASCII:
		                                     //Es un símbolo(caracter) y también es un número entero entre
						     //cero y 127
	       estado=delta[estado][simbolo];        //Aquí es donde sucede la transición: 
						     //A partir de un estado y un símbolo, la función delta (codificada 
						     //en la tabla) nos indica a qué estado debemos transitar. 
	       printf("%c,%c,%d\n",estado,simbolo,posCad); //Para fines de depuración desplegamos en pantalla
		                                           //una instantanea de cada iteracion.
  }
  printf("Termine en el estado: %c\n",estado);
  if((estado-48)==2){   //Verificamos si terminamos en un estado final del AFD. En nuestro caso, el único 
		         // estado final, es el estado q2. Si es así, nuestra cadena es aceptada por este AFD,
     return 1;
  }
  else             //Recorrimos toda la cadena y el estado en el que terminamos NO pertenece a Qf
     return 0;

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
    /* delta[0][0]=0; //Estado q0, transicion con el símbolo '0'
     delta[0][1]=1; //Estado q0, transicion con el simbolo '1'
     delta[1][0]=2; //Estado q1 ...
     delta[1][1]=1; //...
     delta[2][0]=0;
     delta[2][1]=1; *///¿Que lenguaje acepta nuestro AFD?
    //delta[3][2]={{0,1},{2,1},{0,1}}; //Alternativamente, Podemos inicializar la delta en forma compacta.
    int c,acpt;
    char cad [100]; //en cad almacenaremos la cadena que se probará si es aceptada por el AFD.

    if(argc != 3){     //Validamos que el programa reciba la cantidad correcta de argumentos
         printf ("Uso: %s <Archivo> Cadena_a_analizar\n",argv[0]);
	 return 0;	
    }
    strcpy(cad,argv[2]); //En el siguiente argumento, argv[2], recibimos la cadena a analizar.

    c = contar_lineas(argv[1]); 
    acpt = afd(argv[1],cad,c);
    
   	 
    if (acpt==1){   //Si afd devuelve 1, es aceptada...
         printf("La cadena %s ",cad);
	 printf("SI es aceptada\n");	
    }
    else{              //De lo contrario...
         printf("La cadena %s ",cad);
	 printf("NO es aceptada\n");
    }
    return 0;
}

