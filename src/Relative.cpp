#include "Relative.h"


Relative::Relative(char *url){ //ctor
    f_d_handler=NULL;
    f_i_handler=NULL;
    strcpy(&filename[0],url);
}

Relative::~Relative(){ //dtor
    r_close();
}

void close_file(FILE** fp){
        if(*fp!=NULL){ fclose(*fp); *fp=NULL; }
}

void Relative::r_close(){
    if(is_open()==0){
        close_file(&f_d_handler);
        close_file(&f_i_handler);
    }
}
// +
int Relative::r_open(char *mode){
    if(r_file_exists() == 0){
        char m[4]; strcpy(m,mode); strcat(m,"b");
        f_d_handler= fopen(filename, m); //data binary
        f_i_handler= fopen(index_name(), m); //index binary
    } else {
        return 1;
    }
return 0;
}

// + Description: open or create files and leave them thus.
int Relative::r_create(){
    if(r_file_exists() == 1){
        f_d_handler=fopen(filename, "w+b");
        f_i_handler=fopen(index_name(), "w+b");
    }
    if(f_d_handler==NULL||f_i_handler==NULL) { return 1; }
return 0;
}
// +
int Relative::r_file_exists(){
    FILE *fpd=fopen(filename,"r+b"), *fpi=fopen(index_name(),"r+b");
    if(fpd==NULL||fpi==NULL){
        return 1;
    }
    fclose(fpd); fclose(fpi);
return 0;
}
// +
int Relative::is_open(){
    if(f_d_handler==NULL || f_i_handler==NULL){ return 1; }
return 0;
}

// PRE:
// 1- The strings must end with the character '\0'.
// 2- The files must be created before a write operation.
int Relative::r_write(char *data, char *type){ // type: text or binary (another file)


   if(r_open("r+")==1){
        printf("There was an error opening the files!!");
        return 1;
   }

   if(strcmp(type,"t")==0){
        size_t size=sizeof(size_t), data_length;
        size_t full_data_reg_size=size+1+MAX_TEXT_REG_LENGTH;

// TODO: create data reg
        char treg[full_data_reg_size];
        data_length=strlen(data)+1;
        memcpy(treg, &data_length, size);
        memcpy(treg+size, "\t",1);
        memcpy(treg+size+1, data, data_length);

        fseek(f_d_handler, 0, SEEK_END);
        size_t error= fwrite(treg,1, sizeof(size_t)+1+strlen(data)+1, f_d_handler); // hay que abrir en append
        close_file(&f_d_handler); // OJO: hasta que no cierra no escribe el archivo.
        append_index();
   } else {

     if(strcmp(type,"b")==0){
// http://www.cplusplus.com/reference/cstdio/fread/
     } else {
        return 1; // invalid type paramenter
     }
   }
return 0;
}

void Relative::create_treg(char ** treg, char* text){
    //eg: 0005\thola
    size_t size=strlen(text)+1;
    memcpy(*treg, &size, sizeof(size_t)); // save text length (withot '\0') and '\t' (+1)
    treg+=sizeof(size_t);
    memcpy(treg, "\t", 1); // just copy '\t' (without '\0')
    memcpy(treg+1, text, strlen(text)+1); // OJO: el +1 es del fin
    printf(*treg);
}

// Basura: sacar el tamaño de un archivo:
//  fseek(ifh, 0, SEEK_END);
//  size_t lSize = ftell(ifh);
//        printf("%d\n", lSize);

// PRE: 0 <= n <= N-1, N: number of registers
size_t Relative::get_reg_offset(size_t n){
    char * index_reg=r_i_read(n);
    size_t offset;
    if(index_reg==NULL){
        offset= 0;
    } else {
        memcpy(&offset, index_reg+sizeof(size_t), sizeof(size_t)); // OJO: size_t por ahi es chico para el offset (TODO)
        free(index_reg);
    }
return offset;
}

// OJO con el free (devuelve NULL si no hay regs) +

// PRE: 0 <= n <= N-1, N: number of registers
char* Relative::r_i_read(size_t n){
    char* index_reg;
    FILE * ifh=fopen(index_name(), "rb"); // TODO
    rewind(ifh);
    size_t header_admin_data_size=sizeof(size_t); // N
    fseek(ifh, n*get_reg_size()+header_admin_data_size, SEEK_SET);
    index_reg= (char*)malloc(get_reg_size());

    if(fread(index_reg, 1, get_reg_size(), ifh)==0){ // No regs
        free(index_reg);
        index_reg=NULL;
    }

    fclose(ifh);
return index_reg;
}

// PRE: 0 <= n <= N-1, N: number of registers
char* Relative::r_read(size_t n){
    size_t reg_size, attr_regsize_size=sizeof(size_t);
    size_t offset=get_reg_offset(n);
    char* data;
    FILE* dfh= fopen(filename, "rb");
    fseek(dfh, offset, SEEK_SET);
    if(fread(&reg_size, 1, attr_regsize_size, dfh) != 0){
        fseek(dfh, offset, SEEK_SET);
        data= (char*) malloc(reg_size+attr_regsize_size);
        fread(data, 1, reg_size+attr_regsize_size, dfh); //long
    } else {
        data=NULL; //empty data file
    }
    fclose(dfh);
return data; // TODO
}

void cargar_prueba(){
    FILE* fpi=fopen("a.index","wb");
    size_t size=sizeof(size_t), num=2;
    printf("\nOffset 0: %d\n",ftell(fpi));
    fwrite(&num,1, size, fpi);
    printf("Offset 1: %d\n",ftell(fpi)); num=0;
    fwrite(&num,1, size, fpi);
    printf("Offset 2: %d\n",ftell(fpi)); num=5;
    fwrite(&num,1, size, fpi);
    printf("Offset 3: %d\n",ftell(fpi)); num=1;
    fwrite(&num,1, size, fpi);
    printf("Offset 4: %d\n",ftell(fpi)); num=8;
    fwrite(&num,1, size, fpi);
    rewind(fpi);
    printf("Offset 5 (rewind): %d\n",ftell(fpi));
    fclose(fpi);
}

// PRE: 0 <= n <= N-1, N: number of registers
void Relative::show_i_reg(size_t n){
   char* data=r_i_read(n); //n-1);
   size_t num;
   memcpy(&num, data, sizeof(size_t));
   printf("\nReg.: %d\n", num+1);
   memcpy(&num, data+sizeof(size_t), sizeof(size_t));
   printf("Offset: %d\n", num);
   free(data);
}

// PSEUDO: -> agregar registro N: [N | OFFSET(N)=L(N-1)+O(N-1)]: [(size_t:4bytes)|(size_t:4bytes)]
// 0) GET N-1
// 1) READ(DATOS, RD(N-1)) -> No se la longitud maxima => paso al 2
// 2) GET_LONG(Rn-1) -> L(N-1)
// 3) READ(INDEX, RI(N-1))
// 4) GET_OFFSET(RI(N-1)) -> O(N-1)
// 5) Add new index reg.
int Relative::append_index(){
    size_t size=sizeof(size_t), n, data_length;
    long position=ftell(f_i_handler);
    FILE *f_i_handler=fopen(index_name(),"r+b");
    char serialized_reg[get_reg_size()];
    size_t offset, bytes_readed;
    char * data;
    int error;
    if(f_i_handler!=NULL){
       //cargar_prueba();
        bytes_readed=fread(&n, 1, size, f_i_handler);
        if(bytes_readed==0){ // emply index file => 0 regs
            n=0;
            error=fwrite(&n, 1, size, f_i_handler);
        }
        // 1) -> 2)
        printf("Registros de indice: %d\n", n);

        data=r_read(n);
        memcpy(&data_length, data, size);
        printf("Tamaño del dato: %d\n", data_length);
        free(data);

        // 3) -> 4)
        (n==0) ? offset=0 : offset=size+1+data_length+get_reg_offset(n-1);
        // 5)
        index_reg ir=create_i_reg(n, offset);
        memcpy(serialized_reg, &(ir.index), size);
        memcpy(serialized_reg+size, &(ir.offset), size);
        fseek(f_i_handler, 0, SEEK_END);
        error=fwrite(serialized_reg, 1, get_reg_size(), f_i_handler); // write new reg

        if(error!=0){
            printf("Registro agregado!\n");
            fseek(f_i_handler, 0, SEEK_SET);
            n++;
            fwrite(&n, 1, size, f_i_handler);
            close_file(&f_i_handler); // OJO!: cierro handlers
            show_i_reg(n-1);
        }
    } else { return 1; }// file doesnt exists
return 0;
}



int Relative::r_i_seek(unsigned int n, FILE* fh){
    fseek(fh, get_reg_size()*n+sizeof(size_t),SEEK_SET);
}

int Relative::get_reg_size(){
return 2*sizeof(unsigned int);
}

index_reg Relative::create_i_reg(size_t index, size_t offset){
    index_reg i_reg;
    i_reg.index = index;
    i_reg.offset = offset;
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
  if( remove(filename) != 0 || remove(index_name()) != 0 ){
    return 1;
  }
return 0;
}



char* Relative::index_name(){
    strcpy(index_filename, filename);
    strcat(index_filename, ".index");
return index_filename;
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


// NOTAS (BUGS):
// Linea 85 cierro el archivo para que escriba.
