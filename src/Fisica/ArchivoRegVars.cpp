#include "Fisica/ArchivoRegVars.h"


ArchivoRegVars::ArchivoRegVars(char *url){ //ctor
    strcpy(&filename[0],url);
    if(r_file_exists()==1){
        cout << "El archivo no existe!" << endl;
        if(r_create()==0){
            cout << "El archivo ha sido creado con exito!" << endl;
        } else {
            cout << "Error al intentar crear el archivo!" << endl;
            salir("",ERROR_DE_CREACION);
        }
    }
    if(r_open("r+b")==0){
        cout << "El archivo se ha abierto exitosamente!" << endl;
    } else {
        salir("",ERROR_DE_APERTURA);
    }
}

ArchivoRegVars::~ArchivoRegVars(){ //dtor
    r_close();
}

t_num_ref ArchivoRegVars::add(string data){
        fseek(f_d_handler, 0, SEEK_END);
        t_reg_var_size data_length=data.length();
        // Almaceno el offset donde se va a escribir
        t_offset offset= ftell(f_d_handler);
        fwrite(&data_length,1, sizeof(t_reg_var_size), f_d_handler);
        fwrite(data.c_str(), 1, data.length(), f_d_handler);
        fflush(f_d_handler);
        if(ferror(f_d_handler)==0){
            append_index(offset);
        } else {
            salir("",ERROR_DE_ESCRITURA_DATOS);
        }
return ferror(f_d_handler);
}

string ArchivoRegVars::get(t_num_ref n){
    t_reg_var_size reg_size;
    int bytes_para_campo_longitud=sizeof(t_reg_var_size);

    t_offset offset=get_offset(n);
    fseek(f_d_handler, offset, SEEK_SET);
    fread(&reg_size, 1, bytes_para_campo_longitud, f_d_handler);
    char* buffer= (char*) malloc(reg_size+1);
    fread(buffer, 1, reg_size, f_d_handler);
    *(buffer+reg_size)='\0';

    if(ferror(f_d_handler)!=0){
        salir("",ERROR_DE_LECTURA_DATOS);
    }
    string data=buffer;
    free(buffer);
return data;
}

t_offset ArchivoRegVars::get_offset(t_num_ref i_referencia){
    t_offset index_reg=-1;
    if( i_referencia >= 0 && i_referencia <=size() ){
        fseek(f_i_handler, sizeof(t_index_size)+i_referencia*sizeof(t_offset), SEEK_SET);

        fread(&index_reg, 1, sizeof(t_offset), f_i_handler);
        if(ferror(f_i_handler)!=0){
            salir("",ERROR_DE_LECTURA_INDICE);
        }
    } else {
        return -1;
    }
return index_reg;
}

t_num_ref ArchivoRegVars::append_index(t_offset offset){
    t_index_size index_size = size()+1;
    // Actualizo contador
    fseek(f_i_handler, 0, SEEK_SET);
    fwrite(&index_size, 1, sizeof(t_index_size), f_i_handler);
    // Agrego offset
    fseek(f_i_handler, 0, SEEK_END);
    fwrite(&offset, 1, sizeof(t_offset), f_i_handler);
    fflush(f_i_handler);

    if(ferror(f_i_handler)!=0){
        salir("",ERROR_DE_ESCRITURA_INDICE);
    }
return index_size;
}


t_index_size ArchivoRegVars::size(){
    t_index_size counter;
    fseek(f_i_handler, 0, SEEK_SET);
    fread(&counter, 1, sizeof(t_index_size), f_i_handler);
    if(ferror(f_i_handler)!=0){
        return -1;
    }
return counter;
}

string ArchivoRegVars::index_name(){
    string name=this->filename;
return name.append(".index");
}


int ArchivoRegVars::r_destroy(){
  if( remove(filename) != 0 || remove(index_name().c_str()) != 0 ){
    return 1;
  }
return 0;
}


int ArchivoRegVars::r_file_exists(){
    FILE *fpd=fopen(filename,"r"), *fpi=fopen(index_name().c_str(),"r");
    if(fpd==NULL|| fpi==NULL){
        return 1;
    }
    fclose(fpd); fclose(fpi);
return 0;
}

int ArchivoRegVars::r_create(){
    FILE *fpd=fopen(filename, "w");
    FILE *fpi=fopen(index_name().c_str(), "w");
    if(fpd==NULL||fpi==NULL) { return 1; }
    t_index_size counter=0;
    fwrite(&counter, 1, sizeof(t_index_size), fpi);
    fclose(fpd); fclose(fpi);
return 0;
}

void ArchivoRegVars::close_file(FILE** fp){
        if(*fp!=NULL){
             fclose(*fp);
             *fp=NULL;
        }
}

void ArchivoRegVars::r_close(){
    if(f_d_handler==NULL){
        close_file(&f_d_handler);
    }

    if(f_i_handler==NULL){
        close_file(&f_d_handler);
    }
}

int ArchivoRegVars::r_open(string mode){
   f_d_handler= fopen(filename, mode.c_str()); //data binary
   f_i_handler= fopen(index_name().c_str(), mode.c_str()); //index binary

   if(f_d_handler!=NULL && f_i_handler!= NULL){
       return 0;
    }
 return 1;
}


