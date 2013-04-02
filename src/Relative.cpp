#include "Relative.h"

struct index_reg {
  unsigned int index, offset;
};

Relative::Relative(char *url){ //ctor
    f_d_handler=NULL;
    f_i_handler=NULL;
    strcpy(&filename[0],url);
}

Relative::~Relative(){ //dtor
    r_close();
}

void Relative::r_close(){
    fclose(f_d_handler);
    fclose(f_i_handler);
}

int Relative::r_open(char *mode){
    f_d_handler= fopen(filename, strcat(mode,"b")); //data binary
    f_i_handler= fopen(filename, strcat(mode,"b")); //index binary
//    if(feof(f_i_handler)){
//      init_index_file();
//    }
return is_open();
}

//void init_index_file(){
//    FILE* fh= fopen(url, "wb");
//    unsigned int n_regs=0;
//    fwrite(&n_regs, 1, sizeof(unsigned int), fh);
//    fclose(fh);
//}

int Relative::r_create(){
    if(r_open("r")==1){ return 1; }
return 0;
}
 // PRE: debe terminar en '\0' si es tipo "t" (text)
int Relative::r_write(char *reg, char *type){ // type: text or binary (another file)
   if(!is_open()){return 1;} // open as write

   if(strcmp(type,"t")){
        serialize_text(reg);
        unsigned int size=strlen(reg)+1;
        fwrite(&size, 1, sizeof(unsigned int), f_d_handler);
        fwrite(reg, 1, size, f_d_handler);
        append_index();
   } else {

     if(strcmp(type,"b")){

     } else {
        return 1; // invalid type paramenter
     }

   }
return 0;
}

char* Relative::serialize_text(char *reg){
return reg;
}

int Relative::append_index(){
    unsigned int n;
    unsigned int *pn;

    FILE * ifh=fopen(index_name(), "wb"); //OJO: abro handler nuevo por las dudas

    if(fh != NULL){
        if(feof(ifh)){ // 0 regs
         n=1;
        } else {
         fread(pn, 1, size_of(unsigned int), ifh); // read n: total
         n++;
        }
        fwrite(pn, 1, size_of(unsigned int), ifh); //update total
        r_i_seek(n, ifh);
        index_reg ir= create_i_reg(n);
        fwrite(ir.index, 1, sizeof(ir.index), ifh); // write new reg
        fwrite(ir.offset, 1, sizeof(ir.offset),ifh);
        fclose(ifh);
    }
return 0;
}

int Relative::r_i_seek(unsigned int n, FILE* fh){
    fseek(fh, get_reg_size()*n,SEEK_SET);
}

int Relative::get_reg_size(){
return 2*sizeof(unsigned int);
}

index_reg Relative::create_i_reg(unsigned int index){
    index_reg i_reg;
    reg.index = index;
    reg.offset = n*get_reg_size();
return i_reg;
}

void Relative::r_list(){
}

int Relative::r_show(int offset, char *type){ // type: p-> bytes, n -> register
return 0;
}

int Relative::r_search(char *reg){
return 0;
}

int Relative::r_destroy(){
return 0;
}

int is_open(){
    if(f_d_handler==NULL || f_i_handler==NULL){ return 1; }
return 0;
}

char* index_name(){
return strcat(&filename[0], ".index");
}

//Manejo de Archivos de Registros Variables (estructura: [longitud, dato_valor])
//- ./ejecutable [NOMBRE_ARCHIVO] -c
//Crea el archivo de registros variables en la ruta [NOMBRE_ARCHIVO].
//
//- ./ejecutable [NOMBRE_ARCHIVO] -rt "[TEXTO]
//Registra el [TEXTO] en un registro variable del archivo con ruta [NOMBRE_ARCHIVO]. Si no está creado devuelve error.
//
//- ./ejecutable [NOMBRE_ARCHIVO] -rb [NOMBRE_ARCHIVO_R]
//Registra el archivo ubicado en la ruta [NOMBRE_ARCHIVO_R] en un registro variable del archivo con ruta [NOMBRE_ARCHIVO]. Si no está creado devuelve error.
//
//- ./ejecutable [NOMBRE_ARCHIVO] -l
//Muestra por pantalla la lista de registros variables incluidos en el archivo ubicado en la ruta y las posiciones relativas de cada registro. Estructura del
//listado: Nro. Registro - Posición en Bytes del Registro.
//
//- ./ejecutable [NOMBRE_ARCHIVO] -lp [POSICION_REGISTRO]
//Muestra por pantalla los datos del registro variable ubicado en la posición absoluta [POSICION_REGISTRO], en Bytes, contenido en el archivo de ruta [NOMBRE_ARCHIVO]. Si no está creado devuelve error.
//Ejemplo para probar un archivo binario de imagen: ./ejecutable [NOMBRE_ARCHIVO] -lp [POSICION_REGISTRO] >[archivo_de_imagen_salida];
//[programa_visualizador_de_imagen] [archivo_de_imagen_salida].
//
//- ./ejecutable [NOMBRE_ARCHIVO] -ln [NUMERO_REGISTRO]
//Muestra por pantalla los datos del registro variable ubicado en la posición
//relativa [NUMERO_REGISTRO], en número de registros, contenido en el
//archivo de ruta [NOMBRE_ARCHIVO]. Si no está creado devuelve error.
//
//- ./ejecutable [NOMBRE_ARCHIVO] -s "[TEXTO]
//Busca el [TEXTO] en los registros del archivo con ruta
//[NOMBRE_ARCHIVO]. Muestra por pantalla los números de registro, y las
//posiciones relativas de los mismos, que contengan el texto. Si no está creado
//devuelve error.
//
//- ./ejecutable [NOMBRE_ARCHIVO] -e
//Elimina el archivo con ruta [NOMBRE_ARCHIVO].
