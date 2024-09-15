#include "minimal.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){
    //Pedir ingrese dos numeros y calcule el menor de ellos.
    int numero1, numero2, respuesta ;

    printf("Ingrese un numero entero\n");
    scanf("%i",&numero1);
    printf("Ingrese segundo número entero\n");
    scanf("%i",&numero2);

    printf("the min value is: %d\n",minimal(numero1,numero2));
   
    //usar  funcion pow() elevar el primer número al segundo
    respuesta=pow(numero1,numero2);

     printf("%i elevado a la %i es  %i:\n", numero1, numero2, respuesta);
     
    return 0;

}
