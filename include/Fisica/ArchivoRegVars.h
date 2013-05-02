#ifndef ARCHIVOREGVARS_H
#define ARCHIVOREGVARS_H
#include "Fisica/Necesario1.h"
#include "RegVar.h"
#define MAX_FILENAME_LENGTH 50
#define MAX_TEXT_REG_LENGTH 100

struct index_reg {
   unsigned int index, offset;
};

using namespace std;

class ArchivoRegVars

{
    private:
        char filename[MAX_FILENAME_LENGTH];
        char index_filename[MAX_FILENAME_LENGTH+5];
        FILE * f_i_handler, * f_d_handler;
        void close_file(FILE ** pf);
        void r_close();
        int r_open(string mode);
        /* Descripcion: crea ambos archivos, el de datos y el indice. Si alguno existe se sobreescribe (trunca).
        */
        int r_create();
        /* Descripcion: agrega el offset al archivo de indice y actualiza el contador (ubicado al comienzo)
         PRE: el archivo indice debe estar abierto en modo r+b y con el contador de registros seteado
         correctamente.
         POS: actualiza indice y devuelve la posicion (referencia)
        */
        t_num_ref append_index(t_offset offset);
        /* Descripcion: verifica la existencia de ambos archivos, el de datos y el indice
             POS: 1 en caso de que no, 0 si ambos existen
        */
        int r_file_exists();
        string index_name();
        /* Descripcion: devuelve el offset del registro n en el archivo de datos.
         PRE: 0 <= n <= N-1, N: numero de registros (referencias).
         POS: si el registro no existe devuelve -1.
         */
        t_offset get_offset(t_num_ref i_referencia);
    public:
        ArchivoRegVars(char *url);
        virtual ~ArchivoRegVars();

        /* Descripcion: escribe n bytes desde la direccion apuntada por data con
            metadata que indica la longitud.
            PRE: entrada string
            POS: devuelve numero distinto de cero si falló.
        */
        t_num_ref add(string);
        /* Descripcion: devuelve string el registro n.
         PRE:  0 <= n <= N-1, N: numero de registro (Ref)
         POS: -
        */
        string get(t_num_ref ref);

        int r_destroy();

        /* Descripcion: devuelve la cantidad de registros que contiene el archivo
         PRE: archivo abierto en modo a+ y correctamente formateado.
         POS: si hubo un error devuelve -1
        */
        t_index_size size();
    protected:

};
#endif

// Cambios: refactorizacion, saco el campo id del indice
