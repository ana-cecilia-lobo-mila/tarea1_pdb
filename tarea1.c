#include <stdio.h>
#include <string.h>

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m', 'n','o','p','q','r','s','t','u','v','w','x','y','z'};
char alfabetoMayus[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char morse[][5] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
unsigned char acentos[] = {161, 169, 173, 179, 186, 177, 129, 137, 141, 147, 154, 145};
char letras[] = {'a','e','i','o','u','ñ','A','E','I','O', 'U','Ñ'};

void funcion1();
void funcion2();
void funcion3();
void funcion4();
int menu(int valor);

int main(){
    int valor;
    char buffer[10];

    printf("Bienvenido. Seleccione un método de conversión\n");
    printf("1) Texto a código morse.\n");
    printf("2) Código morse a texto.\n");
    printf("3) Texto a texto desplazado.\n");
    printf("4) Diccionario de reemplazo.\n");

    fgets(buffer, 10, stdin);
    valor = buffer[0] - '0';

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

int tiene_repetidos(char str[]) {
    for(int i = 0; str[i] != '\0'; i++){
        for(int j = i + 1; str[j] != '\0'; j++){
            if(str[i] == str[j]){
                return 1; 
            }
        }
    }
    return 0;
}

int leer_entero() {
    char buffer[100];
    int numero = 0;
    int i = 0;
    int signo = 1;

    fgets(buffer, 100, stdin);

    if(buffer[0] == '-'){
        signo = -1;
        i++;
    }

    for(; buffer[i] != '\n' && buffer[i] != '\0'; i++){
        if(buffer[i] >= '0' && buffer[i] <= '9'){
            numero = numero * 10 + (buffer[i] - '0');
        }
    }

    return numero * signo;
}

char normalizar_acento(unsigned char segundo_byte) {
    for (int k = 0; k < 12; k++) {
        if (segundo_byte == acentos[k]) {
            return letras[k];
        }
    }
    return '\0';
}

void funcion1(){
    char nombre_archivo[100];
    char texto[1000];

    printf("Texto a código morse seleccionado. \n");
    printf("Ingrese el nombre del archivo de entrada que contiene el mensaje: \n");
    fgets(nombre_archivo, 100, stdin);

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
        fgets(texto, 1000, stdin);
        texto[strcspn(texto, "\n")] = '\0';
    }else{
        int i = 0;
        while(fgets(texto + i, 1000 - i, archivo) != NULL){
            while(texto[i] != '\0') i++;
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
            for(int j = 0; j < 26; j++){
                if(alfabeto[j] == texto[i]){
                    strcpy(texto_convertido[i], morse[j]);
                    break;
                }
            }
        } else if(texto[i] >= 'A' && texto[i] <= 'Z'){
            for(int j = 0; j < 26; j++){
                if(alfabetoMayus[j] == texto[i]){
                    strcpy(texto_convertido[i], morse[j]);
                    break;
                }
            }
        } else if((unsigned char)texto[i] >= 128){
            char letra = normalizar_acento((unsigned char)texto[i + 1]);
            int encontrado = 0;

            if(letra != '\0'){
                for(int j = 0; j < 26; j++){
                    if(alfabeto[j] == letra || alfabetoMayus[j] == letra){
                        strcpy(texto_convertido[i], morse[j]);
                        encontrado = 1;
                        break;
                    }
                }
            }

            if(!encontrado){
                texto_convertido[i][0] = texto[i];
                texto_convertido[i][1] = texto[i + 1];
                texto_convertido[i][2] = '\0';
            }
            i++; 
        } else {
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
    fgets(nombre_archivo, 100, stdin);

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
        fgets(texto, 1000, stdin);
        texto[strcspn(texto, "\n")] = '\0';
    }else{
        int i = 0;
        while(fgets(texto + i, 1000 - i, archivo) != NULL){
            while(texto[i] != '\0') i++;
        }
        fclose(archivo);
    }

    char texto_convertido[1000];
    int i = 0, x = 0, y = 0;

    while(texto[x] != '\0'){
        char letra[100];
        int k = 0;

        if(texto[x] == '/'){
            texto_convertido[y++] = ' ';
            x++;
        } else if(texto[x] == ' '){
            x++;
        } else if(texto[x] != '.' && texto[x] != '-'){
            texto_convertido[y++] = texto[x++];
        } else {
            for(i = x; texto[i] != ' ' && texto[i] != '\0'; i++){
                letra[k++] = texto[i];
            }
            letra[k] = '\0';

            int encontrado = 0;
            for(int j = 0; j < 26; j++){
                if(strcmp(morse[j], letra) == 0){
                    texto_convertido[y++] = alfabeto[j];
                    encontrado = 1;
                    break;
                }
            }

            if(!encontrado){
                printf("Código morse no válido\n");
                return main();
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
    char nombre_archivo[100];
    char texto[1000];

    printf("Texto a texto desplazado seleccionado.\n");
    printf("Ingrese el nombre del archivo de entrada que contiene el mensaje: \n");
    fgets(nombre_archivo, 100, stdin);

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
        fgets(texto, 1000, stdin);
        texto[strcspn(texto, "\n")] = '\0';
    }else{
        int i = 0;
        while(fgets(texto + i, 1000 - i, archivo) != NULL){
            while(texto[i] != '\0') i++;
        }
        fclose(archivo);
    }

    printf("Ingrese el número de letras a desplazar: \n");
    int desplazo = leer_entero();

    char texto_convertido[1000];
    int y = 0;

    for(int i = 0; texto[i] != '\0'; i++){
        if(texto[i] >= 'a' && texto[i] <= 'z'){
            texto_convertido[y++] = (texto[i] - 'a' + desplazo % 26 + 26) % 26 + 'a';

        } else if(texto[i] >= 'A' && texto[i] <= 'Z'){
            texto_convertido[y++] = (texto[i] - 'A' + desplazo % 26 + 26) % 26 + 'A';

        } else if((unsigned char)texto[i] >= 128){
            char letra = normalizar_acento((unsigned char)texto[i + 1]);

            if(letra >= 'a' && letra <= 'z'){
                texto_convertido[y++] = (letra - 'a' + desplazo % 26 + 26) % 26 + 'a';
            } else if(letra >= 'A' && letra <= 'Z'){
                texto_convertido[y++] = (letra - 'A' + desplazo % 26 + 26) % 26 + 'A';
            } else if(letra != '\0'){
                texto_convertido[y++] = letra;
            }
            i++;
        } else {
            texto_convertido[y++] = texto[i];
        }
    }

    texto_convertido[y] = '\0';

    printf("El texto %s desplazado por %d letras es: ", texto, desplazo);
    printf("%s \n", texto_convertido);

    main();
}

void funcion4(){
    char nombre_archivo[100];
    char texto[1000];

    printf("Texto a diccionario de reemplazo seleccionado \n");
    printf("Ingrese el nombre del archivo de entrada que contiene el mensaje: \n");
    fgets(nombre_archivo, 100, stdin);

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
        fgets(texto, 1000, stdin);
        texto[strcspn(texto, "\n")] = '\0';
    }else{
        int i = 0;
        while(fgets(texto + i, 1000 - i, archivo) != NULL){
            while(texto[i] != '\0') i++;
        }
        fclose(archivo);
    }

    char cambio[100];

    printf("Ingrese el diccionario de caracteres a reemplazar \n");
    printf("FORMATO: ENTRADA:SALIDA \n");
    printf("Sin repetir caracteres \n");

    fgets(cambio, 100, stdin);

    int tiene_dos_puntos = 0;
    for(int i = 0; cambio[i] != '\0'; i++){
        if(cambio[i] == ':'){
            tiene_dos_puntos = 1;
            break;
        }
    }

    if(!tiene_dos_puntos){
        printf("Formato no valido \n");
        main();
    }

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
        diccionario_salida[j++] = cambio[i++];
    }
    diccionario_salida[j] = '\0';

    if(strlen(diccionario_entrada) != strlen(diccionario_salida) || tiene_repetidos(diccionario_entrada) == 1 || tiene_repetidos(diccionario_salida) == 1){
        printf("Diccionario no válido \n");
        main();
    }

    char texto_convertido[100];
    int y = 0;

    for(int k = 0; texto[k] != '\0'; k++){
        int encontrado = 0;

        for(int x = 0; x < (int)strlen(diccionario_entrada); x++){
            if(texto[k] == diccionario_entrada[x]){
                texto_convertido[y++] = diccionario_salida[x];
                encontrado = 1;
                break;
            } else if(texto[k] == diccionario_salida[x]){
                texto_convertido[y++] = diccionario_entrada[x];
                encontrado = 1;
                break;
            }
        }
        if(!encontrado){
            texto_convertido[y++] = texto[k];
        }
    }
    texto_convertido[y] = '\0';

    printf("El texto %s cifrado mediante el diccionario proporcionado es: ", texto);
    printf("%s \n", texto_convertido);

    main();
}

//gcc tarea1.c -o 
//.... --- .-.. .- / .- -. .- !!!
//an:hl

//Hola, ¿Como estas?
//Colea?:Wad4R.

//../archivo.txt
//´áéíóú
//Holá Ana

