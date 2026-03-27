#include <stdio.h>
#include <string.h>

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m', 'n','o','p','q','r','s','t','u','v','w','x','y','z'};
char *morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void leer_texto();
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

void leer_texto(){

}


void funcion1(){
    char texto[100];
    printf("Texto a código morse seleccionado. \n");
    printf("Ingrese el texto de entrada a continuación: \n");
    getchar();
    fgets(texto, 100, stdin);

    texto[strcspn(texto, "\n")] = '\0';

    char *texto_convertido[100];
    char especiales[100][2];

    for(int i = 0; texto[i] != '\0'; i++){

        if(texto[i] == ' '){
            texto_convertido[i] = "/";
            continue;

        }

        if(texto[i] >= 'a' && texto[i] <= 'z'){
            for(int j = 0; j < 26 ; j++){
                if(alfabeto[j] == texto[i]){
                    texto_convertido[i] = morse[j];
                    break;
                }
            } 
        }else{
            especiales[i][0] = texto[i];
            especiales[i][1] = '\0';

            texto_convertido[i] = especiales[i];
        }
    }

    printf("El texto %s en código morse es: ", texto);
    for(int i = 0; texto_convertido[i] != NULL; i++){
        printf("%s ", texto_convertido[i]);
    }
    //main();
    
}

void funcion2(){
    printf("Funcion 2\n");
    main();
}

void funcion3(){
    char texto[100];
    int desplazo;

    printf("Texto a texto desplazado seleccionado.\n");
    printf("Ingrese el texto de entrada a continuación: \n");
    getchar();
    fgets(texto, 100, stdin);
    printf("Ingrese el número de letras a desplazar: \n");
    scanf("%d", &desplazo);

    printf("%s", texto);

    char resultado[100];
    int i; 

    for (i = 0; texto[i] != '\0'; i++){
        if (texto[i] >= 'a' && texto[i] <= 'z'){
            resultado[i] = (texto[i] - 'a' + desplazo % 26 + 26) % 26 + 'a';
        }else if (texto[i] >= 'A' && texto[i] <= 'Z'){
            resultado[i] = (texto[i] - 'A' + desplazo % 26 + 26) % 26 + 'A';
        }else{
            resultado[i] = texto[i];
            }
    }
    
    resultado[i] = '\0';

    printf("El texto %s desplazado por %d letras es: ", texto, desplazo);
    printf("%s", resultado);

    //main();
}

void funcion4(){
    printf("Funcion 4\n");
    main();
}