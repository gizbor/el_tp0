#ifndef BLOQUE_H
#define BLOQUE_H
#include "RegVar.h"
#include "Serializable.h"
#define BYTES_PER_RV_OFFSET_REPRESENTATION 4
#define BYTES_FOR_LENGTH_REPRESENTATION 4

class Bloque: public Serializable
{
    public:
        Bloque();
        Bloque(t_block_length l);
        virtual ~Bloque();
        /* Descripcion: inserta en el bloque el registro variable pasado por parametro si hay espacio.
             PRE: -
             POS: si no habia espacio devuelve false.
             IMPORTANTE: por cada registro que se ingresa se ocupa el tamaño serializado del mismo
             mas una cantidad de bytes especificada por BYTES_PER_RV_OFFSET_REPRESENTATION
             para representar al offset dentro del bloque. Por ejemplo para un offset en 4 bytes:
             Estado del bloque (las X son bytes libres): 0001|0000|0005|Hola?|XXXXX
             Registro serializado: 0001A
             NO entra ya que necesita 4 bytes más (la funcion libre() no los cuenta).
              */
        bool add(RegVar reg_var);

       /* Descripcion: devuelve el registro variable pasado por parametro
             PRE: -
             POS: devuelve puntero a instancia RegVar o tira excepcion en caso de error */
        RegVar  get(t_num_reg_var i);


        t_num_reg_var get_cant_reg_var(){ return cant_reg_var; };

       /* Descripcion: verifica que entre el string dentr del bloque
             PRE: -
             POS: true en caso de que si, sono false */
        bool va_a_entrar(string dato);

        t_block_length size() { return this->block_size ; };

        /* Descripcion: devuelve el espacio libre. */
        t_block_length libre();

        string serializar() ;
        bool hidratar( string serializado);
    protected:
    private:

        t_block_length ocupado_con_datos();
        bool reg_exists(t_num_reg_var i);
        t_offset get_free_pos();
        t_num_reg_var cant_reg_var;
        string offsets;
        string dato; /* Registros variables serializados consecutivos */
        t_block_length block_size;

        t_offset get_offset(t_num_reg_var i);
        t_block_length get_metadata_length();
};

#endif // BLOQUE_H
