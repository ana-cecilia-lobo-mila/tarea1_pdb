#include <stdio.h>
#include <string.h>

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m', 'n','o','p','q','r','s','t','u','v','w','x','y','z'};
char alfabetoMayus[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char morse[][5] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

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
        //main()
    }
    return valor;
}


void funcion1(){
    char nombre_archivo[100];
    char texto[1000];

    printf("Texto a código morse seleccionado. \n");
    printf("Ingrese el nombre del archivo de entrada que contiene el mensaje: \n");
    getchar();
    fgets(nombre_archivo, 100, stdin);

    // eliminar salto de línea
    for(int i = 0; nombre_archivo[i] != '\0'; i++){
        if(nombre_archivo[i] == '\n'){
            nombre_archivo[i] = '\0';
            break;
        }
    }

    FILE *archivo = fopen(nombre_archivo, "r");

    if(archivo == NULL){
        printf("El archivo no existe\n");
        printf("Ingrese el texto de entrada a continuación: \n");
        getchar();
        fgets(texto, 1000, stdin);

        texto[strcspn(texto, "\n")] = '\0';
    }else{
        // leer contenido
        int i = 0;
        while(fgets(texto + i, 1000 - i, archivo) != NULL){
            while(texto[i] != '\0'){
                i++;
            }
        }

        fclose(archivo);

    }

    char texto_convertido[1000][5];
    char especiales[1000][2];

    for(int i = 0; texto[i] != '\0'; i++){

        if(texto[i] == '\n'){
            strcpy(texto_convertido[i], " "); 
            continue;
        }

        if(texto[i] == ' '){
            strcpy(texto_convertido[i], "/");
            continue;
        }

        if(texto[i] >= 'a' && texto[i] <= 'z'){
            for(int j = 0; j < 26 ; j++){
                if(alfabeto[j] == texto[i]){
                    strcpy(texto_convertido[i], morse[j]);
                    break;
                }
            } 
        }else if(texto[i] >= 'A' && texto[i] <= 'Z'){
            for(int j = 0; j < 26 ; j++){
                if(alfabetoMayus[j] == texto[i]){
                    strcpy(texto_convertido[i], morse[j]);
                    break;
                }
            } 
        }else{
            especiales[i][0] = texto[i];
            especiales[i][1] = '\0';

            strcpy(texto_convertido[i], especiales[i]);
        }
    }

    printf("El texto %s en código morse es: ", texto);
    for(int i = 0; texto[i] != '\0'; i++){
        printf("%s ", texto_convertido[i]);
    }
    printf("\n");
    main();
    
}

void funcion2(){
    char nombre_archivo[100];
    char texto[1000];

    printf("Código morse a texto seleccionado. \n");
    printf("Ingrese el nombre del archivo de entrada que contiene el mensaje: \n");
    getchar();
    fgets(nombre_archivo, 100, stdin);

    // eliminar salto de línea
    for(int i = 0; nombre_archivo[i] != '\0'; i++){
        if(nombre_archivo[i] == '\n'){
            nombre_archivo[i] = '\0';
            break;
        }
    }

    FILE *archivo = fopen(nombre_archivo, "r");

    if(archivo == NULL){
        printf("El archivo no existe\n");
        printf("Ingrese el texto de entrada a continuación: \n");
        getchar();
        fgets(texto, 1000, stdin);

        texto[strcspn(texto, "\n")] = '\0';
    }else{
        // leer contenido
        int i = 0;
        while(fgets(texto + i, 1000 - i, archivo) != NULL){
            while(texto[i] != '\0'){
                i++;
            }
        }
        fclose(archivo);
    }

    char texto_convertido[1000];

    int i = 0;
    int x = 0;
    int y = 0;
    while(texto[x] != '\0'){
        char letra[100];
        int k = 0;

        if(texto[x] == '/'){
            texto_convertido[y] = ' ';
            y++;
            x++;
        }else if(texto[x] == ' '){
            x++; 
        }else if(texto[x] != '.' && texto[x] != '-'){
            texto_convertido[y] = texto[x];
            y++;
            x++;
        }else{
            for(i = x; texto[i] != ' '; i++){
                letra[k] = texto[i];
                k++;
            }
            letra[k] = '\0';
            

            for(int j = 0; j < 26 ; j++){
                if(strcmp(morse[j], letra) == 0){
                    texto_convertido[y] = alfabeto[j];
                    y++;
                    break;
                }
            }
            x = i + 1;
        }   
    }

    texto_convertido[y] = '\0';

    printf("El código morse %s en texto ASCII es: ", texto);
    for(int i = 0; texto_convertido[i] != '\0'; i++){
        printf("%c", texto_convertido[i]);
    }
    printf("\n");
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

    main();
}

void funcion4(){
    char texto[100];
    char cambio[100];

    printf("Texto a diccionario de reemplazo seleccionado \n");
    printf("Ingrese el texto de entrada a continuación: \n");

    getchar();
    fgets(texto, 100, stdin);

    printf("Ingrese el diccionario de caracteres a reemplazar \n");
    printf("FORMATO: ENTRADA:SALIDA \n");
    printf("Sin repetir caracteres \n");

    
    fgets(cambio, 100, stdin);

    char diccionario_entrada[100];
    char diccionario_salida[100];

    int i = 0;

    while(cambio[i] != ':'){
        diccionario_entrada[i] = cambio[i];
        i++;
    }
    diccionario_entrada[i] = '\0';
    i++;
    int j = 0;

    while(cambio[i] != '\0' && cambio[i] != '\n'){
        diccionario_salida[j] = cambio[i];
        i++;
        j++;
    }
    diccionario_salida[j] = '\0';
    
    char texto_convertido[100];
    int y = 0;
    for(int k = 0; texto[k] != '\0'; k++){
        int encontrado = 0;

        for(int x = 0; x < strlen(diccionario_entrada); x++){
            if(texto[k] == diccionario_entrada[x]){
                texto_convertido[y] = diccionario_salida[x];
                y++;
                encontrado = 1;
                break;
            }else if(texto[k] == diccionario_salida[x]){
                texto_convertido[y] = diccionario_entrada[x];
                y++;
                encontrado = 1;
                break;
            }
        }
        if(!encontrado){
            texto_convertido[y] = texto[k];
            y++;
        }
    }
    texto_convertido[y] = '\0';

    printf("El texto %s cifrado mediante el diccionario proporcionado es: ", texto);
    printf("%s \n", texto_convertido);
}

//gcc tarea1.c -o 
//.... --- .-.. .- / .- -. .- !!!
//an:hl

//Hola, ¿Cómo estás?
//Coleá?:Wad4R.

//../archivo.txt