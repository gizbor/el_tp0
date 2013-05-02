#include "Fisica/ArchivoBloqueRegVars.h"


ArchivoBloqueRegVars::ArchivoBloqueRegVars(string path, t_block_length l)
{
    //ctor
   if(crear_si_no_existe(path)==true){
        this->fs.open(path.c_str(), fstream::binary | fstream::out | fstream::in );
   } else {
        throw "No se pudo crear el archivo!";
   }
   this->path=path;
   this->block_size =l;
}

ArchivoBloqueRegVars::~ArchivoBloqueRegVars()
{
    fs.close();
}

bool ArchivoBloqueRegVars::crear_si_no_existe(string path){
    std::fstream file;
    file.open(path.c_str(), std::fstream::in);
    if(file.is_open()==false){
       file.open(path.c_str(), std::fstream::out); file<<flush;
    }
    bool status= file.is_open();
    file.close();
return status;
}

t_num_block ArchivoBloqueRegVars::add_reg_var(RegVar reg_var)
{
        t_num_block n= size();
        Bloque b;
        bool appended_to_last_bloque;
        if( n!=0 ){
            b= get_block(n-1);
            appended_to_last_bloque= b.add(reg_var);
         }
        if(  n==0  || appended_to_last_bloque == false){
       /* si no hay bloques o el últimio no tiene espacio => crear uno nuevo, agregarlo al archivo y reintetar */
                b=Bloque(this->block_size);
                b.add(reg_var);
                add_block(b);
       } else {
                update_block(n-1, b);
       }
return size();
}

/* TODO */
bool ArchivoBloqueRegVars::update_block(t_num_block i,  Bloque b){
    string serializado=b.serializar();
    if(serializado.length()==this->block_size){
        fs.seekp(i*(this->block_size), fs.beg);
        fs << serializado;
        fs << flush;
    return true;
    }
return false;
}

bool ArchivoBloqueRegVars::add_block(Bloque b){
    string serializado = b.serializar();
    if(serializado.length() == (this->block_size)){
        fs.seekp(0, fs.end);
        fs << serializado;
        fs.flush();
        return true;
    }
return false;
}

Bloque ArchivoBloqueRegVars::get_block(t_num_block i)
{
    Bloque bloque = Bloque(this->block_size);
    if(0<=i && i<=size()){
        char* buffer = new char[this->block_size+1];
        buffer[this->block_size]='\0';

        fs.seekg(i*(this->block_size),fs.beg);
        fs.read (buffer,this->block_size);
        if(bloque.hidratar(string(buffer))==false){
            stringstream error;
            error <<"Registro invalido: imposible hidratar bloque: ";
            error << num_to_string(i,sizeof(t_num_block)) << ", (longitud)";
            error << string(buffer).length() << ",  (en disco)" <<buffer << endl;
            salir(error.str(), 1);
        }
    } else { throw bloque; }
return bloque;
}

/* Descripcion: saca la longitud del archivo a partir de la referencia fs y el tamanio del bloque.
     PRE: -
     POS: devuelve el tamanio en bloques y deja el puntero fs en la posicion original
*/
t_num_block ArchivoBloqueRegVars::size(){
   long original_pos = fs.tellp();
   fs.seekg (0, fs.end);
   long length = fs.tellg();
   fs.seekg (original_pos);
//return (length-metadata_length())/(this->block_length);
return length/(this->block_size);
}

// OJO:
// Al archivo hay que abrirlo como binario sino lo trunca !!!!!

