#include "Fisica/Necesario2.h"
using namespace std;

/* Descripcion: alias de to_str_offset */
string num_to_string(long n, int digits);

long string_to_num(string n);
/* Descripcion: convierte algo como 20 a un string "00020" donde se completa
     con ceros hasta la cantidad del 2do parametro (usado para serializacion)
 */
string to_str_offset(long offset, int digits);

/* Descripcion: entra algo como "00030" y lo convierte a long = 30 * (deserializacion) */
t_offset to_num_offset(string offset);

/* Sale del programa con el codigo de error  */
void salir(string msg, int codigo);
