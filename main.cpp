#include "Fisica/Necesario2.h"
#include "Fisica/ArchivoRegVars.h"
#include "Fisica/ArchivoBloqueRegVars.h"
#include "Fisica/Bloque.h"
#include "Fisica/RegVar.h"

using namespace std;

int main(int argc, char *argv[]){

//cout << "#### PRUEBAS CON ARCHIVO DE REG VARIABLES ####"<< endl;
//
//ArchivoRegVars* archi=  new ArchivoRegVars("archivo_reg_var.dat");
//
//t_num_ref i= archi->add("Este es el primer registro.");
//
//cout << "Referencia: " <<i<< endl;
//
//archi->add("Hola");
//archi->add("Holaaaaaaaaaaaaaaaaaaaaa");
//archi->add("SASDasdsadasdasdasddddddddddddddddddddddddddddwaaaaaaaaaaaaaaadsacascascascs4");
//
//for(i=0; i<=(archi->size())-1;i++){
//    cout << "        Registro " << i << ": "<<archi->get(i)<< endl;
//}


// Pruebas con archivo en bloques
cout << "#### PRUEBAS CON ARCHIVO DE BLOQUES ####"<< endl;
ArchivoBloqueRegVars* archivo= new ArchivoBloqueRegVars("bloques.dat", 26);

Bloque b= Bloque(26);
RegVar r=RegVar("Hola!");
cout << "Bloque serializado: " << b.serializar() << endl;
cout << "Libre: " << b.libre() << endl;
cout << "Reg Var: " << r.serializar() << ", ocupa en total (serializado): " << r.serializar().size() <<endl;
if(b.add(r)==true){
    cout << "R1) Entra en el bloque!"<< endl;
};

cout << "Y este entra??" << endl;
RegVar r2= RegVar("A");
cout << "Bloque serializado: " << b.serializar() << endl;
cout << "Libre: " << b.libre() << endl;
cout << "Reg Var: " << r2.serializar() << ", ocupa en total (serializado): " << r2.serializar().size() <<endl;
if(b.add(r2)==true){
    cout << "Entra en el bloque!"<< endl;
    cout << "Bloque serializado: " << b.serializar() << endl;
    cout << "Espacio: " << b.libre() << endl;
};


///* Formato por bloque: CANT_DE_REGS(4bytes),   LISTA_DE_OFFSETS(4bytes)*,    DATOS */
// 0002,00000009,0005Hola?0001A
if((archivo->add_block(b))==true){
cout << "Primer Bloque metido!!!!" <<endl;
}

//t_num_block n = archivo->add_reg_var(RegVar("hola mundo!"));
t_num_block n = archivo->add_reg_var(RegVar("A"));
/* No entro en el primer bloque => agrego uno nuevo con el dato */
// 0002,000000090005,Hola!0001A|0001,0000,0001AXXXXXXXXXXXXX
cout << "Reg var metido en: " << n<<endl;

 n = archivo->add_reg_var(RegVar("B"));
/* Entra en el ultimo bloque => lo meto */
// 0002,000000090005,Hola!0001A|0001,00000005,0001A0001BXXXX
cout << "Reg var metido en: " << n<<endl;

n = archivo->add_reg_var(RegVar("CCC"));
cout << "Reg var metido en: " << n<<endl;

 n = archivo->add_reg_var(RegVar("DDD"));
cout << "Reg var metido en: " << n<<endl;

// Sacar datos:
// 1) Sacar bloques:
 Bloque bloque;
 cout << "Cant de bloques " << archivo->size() << endl;

int j;
// Bucle que muesta todos los bucles
for(n=0; n<=(archivo->size()-1); n++){
Bloque b=    archivo->get_block(n);
cout << "Bloque "<< n << " recuperado: " << b.serializar() << endl;
    cout << "       Registros recuperados: " << endl;
    // Bucle que muestra los registros almacenados dentro del bloque

    for(j=0;j<=b.get_cant_reg_var()-1; j++){
       RegVar r=b.get(j);
       cout << "            Reg. Var. " << j << " Serializado: " <<r.serializar() << "---> Dato: " << r.get()<< endl;
    }
}

return 0;

}

// OJO: si al archivo se lo inicializa de otra forma a Archivo* archivo = new Archivo("...") pincha por todos lados (!!!!!!!)
