#include "Fisica/Bloque.h"
#include "Fisica/Serializable.h"

Bloque::Bloque(){}

Bloque::Bloque(t_block_length l)
{
        this->cant_reg_var=0;
        this->offsets=string(BYTES_PER_RV_OFFSET_REPRESENTATION, '0');
        this->dato= string(l-get_metadata_length(), 'X');
        this->block_size = l;
}

Bloque::~Bloque(){    //dtor
}

bool Bloque::reg_exists(t_num_reg_var i){
return i<=(this->cant_reg_var);
}

RegVar Bloque::get(t_num_reg_var i){
RegVar reg_var=RegVar();
    if(reg_exists(i)==true){
            t_offset offset= get_offset(i);
            t_reg_size size= string_to_num((this->dato).substr(offset, BYTES_FOR_RV_LENGTH_REPRESENTATION));
            string reg_dato=(this->dato).substr(offset+BYTES_FOR_RV_LENGTH_REPRESENTATION, size);
            reg_var.set(reg_dato);
            return reg_var;
    }
throw reg_var;
}

bool Bloque::add(RegVar reg_var){
    string serializado=reg_var.serializar();
    if(va_a_entrar(serializado)==true) {
        t_offset offset=get_free_pos();
        if(get_cant_reg_var() != 0){
            offsets.append(num_to_string(offset, BYTES_PER_RV_OFFSET_REPRESENTATION));
        }
        (this->cant_reg_var)+=1;
        /* Inserto y recorto el dato para que mantenga la longitud al serializarlo (por la lista variable de offsets)*/
        dato.replace(offset, serializado.length(), serializado);
        if(get_cant_reg_var()>1){
            this->dato=dato.substr(0, dato.length()-BYTES_PER_RV_OFFSET_REPRESENTATION);
        }
    return true;
    }
return false;
}

t_offset Bloque::get_free_pos(){
return ocupado_con_datos();
}


t_block_length Bloque::libre(){
return (this->block_size)-ocupado_con_datos()-get_metadata_length();
}

bool Bloque::va_a_entrar(string dato){
t_block_length meta_a_agregar=0;
if(get_cant_reg_var()!=0){
    meta_a_agregar=BYTES_PER_RV_OFFSET_REPRESENTATION;
}
return libre() >= dato.length()+meta_a_agregar;
}

t_block_length Bloque::ocupado_con_datos(){
    t_block_length ocupado=0;
    if(get_cant_reg_var()!=0){
        /* el offset del ultimo dato mas su longitud */
        /* TODO: calcularlo sin instanciar nada */
        RegVar last_reg_var = get(get_cant_reg_var()-1);
        t_offset last_offset= get_offset(get_cant_reg_var()-1);
        ocupado= last_offset + last_reg_var.serializar().size();
    }
return ocupado;
}

/* Descripcion: -
     PRE: Entrada CANT_REGS|OFFSETS*|REGISTROS* en formato valido.
     POS: objeto Bloque hidratado
*/
bool Bloque::hidratar(const string serializado){
     if(serializado.length() <= this->block_size){
             long offset=0, longitud= BYTES_FOR_LENGTH_REPRESENTATION;
             string campo_1= serializado.substr(offset , longitud);
             this->cant_reg_var = string_to_num(campo_1);
             offset+= BYTES_FOR_LENGTH_REPRESENTATION; longitud=BYTES_PER_RV_OFFSET_REPRESENTATION*this->cant_reg_var;
             this->offsets = serializado.substr(offset, longitud); // campo 2
             offset+= BYTES_PER_RV_OFFSET_REPRESENTATION*( this->cant_reg_var);
             this->dato = serializado.substr(offset, this->block_size- offset);
     return true;
     } else {
        cout << "No se puede serializar.." << endl;
     }
return false;
}

string Bloque::serializar() {
     return num_to_string(get_cant_reg_var(), BYTES_FOR_LENGTH_REPRESENTATION) + \
                  (this->offsets) + \
                  (this->dato);
}

/* private: */
t_offset Bloque::get_offset(t_num_reg_var i){
return string_to_num((this->offsets).substr(BYTES_PER_RV_OFFSET_REPRESENTATION*i, BYTES_PER_RV_OFFSET_REPRESENTATION));
}

t_block_length Bloque::get_metadata_length(){
return BYTES_FOR_LENGTH_REPRESENTATION+(this->offsets).length();
}
