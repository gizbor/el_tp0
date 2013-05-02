#include "Fisica/Necesario2.h"
#define IMPRIMIR_ERROR_STDOUT 1
using namespace std;

/* Descripcion: alias de to_str_offset */
string num_to_string(long n, int digits)
{
    string n_str=string(digits, '0');
    stringstream ss;
    ss << n;
    n_str.append(ss.str());
    n_str= n_str.substr(n_str.length()-digits,n_str.length()-1);

    return n_str;
}

long string_to_num(string n)
{
    return atoi(n.c_str());
}

/* Descripcion: convierte algo como 20 a un string "00020" donde se completa
     con ceros hasta la cantidad del 2do parametro (usado para serializacion)
 */
string to_str_offset(long offset, int digits)
{
    string offset_s=num_to_string(offset, digits);
    return offset_s;
}

/* Descripcion: entra algo como "00030" y lo convierte a long = 30 * (deserializacion) */
t_offset to_num_offset(string offset)
{
    return string_to_num(offset);
}


void salir(string msg, int codigo){
    if(IMPRIMIR_ERROR_STDOUT ==1){
        cout << msg << endl;
    }
    cerr << msg << endl;
    exit(codigo);
}
