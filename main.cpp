#include<necesary.h>
#include<string.h>
#include<stdlib.h>
#include<iostream> // librería para uso de cout
using namespace std;
#include<Sequential.h>
#include<Relative.h>
#define SEQUENTIAL 's'
#define RELATIVE 'r'
#define DIRECT 'd'
#define INDEXED 'i'
#define INVALID_FO 'x'

char get_type(char *argv[]){

char type = INVALID_FO;
  if(strcmp(argv[1],"-s") == 0){
     type= SEQUENTIAL;
  } else {
    if(strcmp(argv[1],"-r") == 0){
     type= RELATIVE;
    } else {
     if(strcmp(argv[1],"-d") == 0){
      type= DIRECT;
     } else {
       if(strcmp(argv[1],"-i") == 0){
         type= INDEXED;
        }
     }
    }
  }
return type;
}

int prn_error(char * msg){
    cout << msg << endl;
    exit;
}

int main(int argc, char *argv[]){

if(argc == 1){ prn_error("Invalid number of paramenters!"); }

const char type_of_file= get_type(argv);
//const char action= get_action(argv);
switch (type_of_file) {
  case SEQUENTIAL:
    cout <<  "Working with a sequential access file..."<< endl;
    break;
  case RELATIVE:
    cout <<  "Working with a relative access file..."<< endl;
    break;
  case DIRECT:
    cout << "Working with a direct access file..."<< endl;
    break;
  case INDEXED:
    cout << "Working with a indexed access file..."<< endl;
    break;
  default:
    cout << "Invalid type of file!"<< endl;

    return 1;
}


    if(get_type(argv) == SEQUENTIAL){
    // TODO: corregir a SEQUENTIAL
    Sequential io = Sequential();

         if(strcmp(argv[3],"-c") == 0 ){


            int error=io.s_create(argv[2]);
            if(error == 0){
               cout<<"File succesfully created!!";
            } else {
               if(error == 1){
                cout << "File already exists!";
               }
            }
         }

         if(strcmp(argv[3],"-r") == 0){

            if(argc != 5){ prn_error("Invalid number of paramenters!");}
            int error= io.s_write(argv[2],argv[4]);
            (error!=0) ? cout << "Error appending line!" << endl : cout << "Line appended successfully!" <<endl;
         }

         if(strcmp(argv[3],"-l") == 0){
            if(argc != 4){ prn_error("Invalid number of paramenters!");}

            if(io.s_open(argv[2],"r")!=0){ prn_error("Error opening file!"); }

            io.s_list(argv[2]);
         }

         if(strcmp(argv[3],"-s") == 0){
            if(argc != 5){ prn_error("Invalid number of paramenters!");}

            if(io.s_open(argv[2],"r")!=0){ prn_error("Error opening file!"); }
            int pos;
            if((pos=io.s_search(argv[2], argv[4])) >= 0 ){
                cout << "Register has been finded in position " << pos << endl;
            } else {
                cout << "Register was not found!" << endl;
            }
         }

        if(strcmp(argv[3],"-d") == 0){
            if(argc != 4){ prn_error("Invalid number of paramenters!");}
            if(io.s_destroy(argv[2]) != 0 ){
                cout << "Error deleting file!" << endl;
            } else {
                cout << "File successfully deleted!" << endl;
            }
         }

         io.s_close();
    } // END SEQUENTIAL
//
//printf("aca");
    // RELATIVE
    if(get_type(argv) == RELATIVE){

        Relative io= Relative(argv[2]);
        if(strcmp(argv[3],"-c") == 0 ){
            if(argc != 4){ prn_error("Invalid number of paramenters!");}
            int error=io.r_create("w");
            if(error == 0){
               cout<<"File succesfully created!!";
            } else {
               if(error == 1){
                cout << "File already exists!";
               }
            }
         }

         if(strcmp(argv[3],"-rt") == 0){
            if(argc != 5){ prn_error("Invalid number of paramenters!");}
//                    printf("aca");
            int error= io.r_write(argv[4], "t");
            (error!=0) ? cout << "Error appending line!" << endl : cout << "Line appended successfully!" <<endl;
         }

         if(strcmp(argv[3],"-d") == 0 ){
            if(argc != 4){ prn_error("Invalid number of paramenters!");}
            if(io.r_destroy() != 0 ){
                cout << "Error deleting file!" << endl;
            } else {
                cout << "File successfully deleted!" << endl;
            }
         }    }
    // END RELATIVE
}

// function get_action(char *args[]){
//    return "f";
//}

// Manejo de Archivos de Texto Plano
// > ./ejecutable [tipo: -[s|r|d|i]] [NOMBRE_ARCHIVO] -c:  Crea el archivo de texto en la ruta [NOMBRE_ARCHIVO].
//
// > ./ejecutable [tipo: -[s|r|d|i]] [NOMBRE_ARCHIVO] -r "[TEXTO]:  Registra el [TEXTO] en una línea del archivo de texto con ruta
// [NOMBRE_ARCHIVO]. Si no está creado devuelve error.
//
// > ./ejecutable [tipo: -[s|r|d|i]] [NOMBRE_ARCHIVO] -l:  Muestra por pantalla las líneas de texto contenidas en el archivo de texto con
// ruta [NOMBRE_ARCHIVO]. Si no está creado devuelve error.
//
// > ./ejecutable [tipo: -[s|r|d|i]] [NOMBRE_ARCHIVO] -s "[TEXTO]: Busca el [TEXTO] en las líneas del archivo de texto con ruta
// [NOMBRE_ARCHIVO]. Muestra por pantalla las líneas que contienen el texto. Si no está creado devuelve error.
//
// > ./ejecutable [tipo: -[s|r|d|i]] [NOMBRE_ARCHIVO] -e: Elimina el archivo de texto con ruta [NOMBRE_ARCHIVO].

// ERRORES
// Segmentation fault: se cerraba en varios lados y el 1ro no ponia a NULL el handler.


// strcpy <cstring>
