#ifndef ARCHIVOBLOQUEREGVARS_H
#define ARCHIVOBLOQUEREGVARS_H
#include "Fisica/Necesario2.h"
#include "RegVar.h"
#include "Bloque.h"

using namespace std;

class ArchivoBloqueRegVars
{
    public:
        /* Descripcion: abre y/o crea el archivo con la longitud de bloque pasada por parametro */
        ArchivoBloqueRegVars(string path, t_block_length l);
        virtual ~ArchivoBloqueRegVars();
       /* Descripcion: agrega en el ultimo bloque el registro pasado por parametro. En caso de
       no haber espacio se agrega un nuevo bloque.
             PRE: -
             POS: devuelve el numero de bloque donde se agregó el registro o NULL en caso de error */
        t_num_block add_reg_var(RegVar reg_var);

        /* Descripcion: devuelve el numero de bloque pasado por parametro.
             PRE: -
             POS: si no existe devuelve NULL */
        Bloque get_block(t_num_block i) ;
        t_num_block size();
        bool add_block(const Bloque block);
        bool update_block(t_num_block i, const Bloque b);
    protected:
    private:
       string path;
       fstream fs;
       bool crear_si_no_existe(string path);
       t_block_length block_size;
};

#endif // ARCHIVOBLOQUEREGVARS_H
