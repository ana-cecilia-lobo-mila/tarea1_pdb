#include <stdio.h>

void funcion1();
void funcion2();
void funcion3();
void funcion4();
int menu(int valor);

int main(){
    int valor;
    printf("Bienvenido. Seleccione un método de conversión\n");
    printf("1) Texto a código morse.\n");
    printf("2) Código morse a texto.\n");
    printf("3) Texto desplazado.\n");
    printf("4) Diccionario de reemplazo.\n");
    scanf("%d", &valor);

    menu(valor);

    return 0;
}


int menu(int valor){
    if(valor == 1){
        funcion1();
    } else if(valor == 2){
        funcion2();
    } else if(valor == 3){
        funcion3();
    } else if(valor == 4){
        funcion4();
    } else{
        printf("Número no válido\n");
    }
    return valor;
}

void funcion1(){
    printf("Funcion 1\n");
    main();
    
}

void funcion2(){
    printf("Funcion 2\n");
    main();
}

void funcion3(){
    printf("Funcion 3\n");
    main();
}

void funcion4(){
    printf("Funcion 4\n");
    main();
}