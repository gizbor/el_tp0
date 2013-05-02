#ifndef RVAR_H
#define RVAR_H
#define MAX_VAR_REG_SIZE 4096
#include "Fisica/Necesario2.h"
#include "Serializable.h"
#define BYTES_FOR_RV_LENGTH_REPRESENTATION 4


using namespace std;

class RegVar: public Serializable
{
    public:
        RegVar();
        RegVar(const string rdata) { this->dato=rdata; };
        virtual ~RegVar();
        t_reg_size size() const { return this->dato.length(); };
        string  get() const { return dato; };
        void set(const string rdata) { this->dato=rdata;};

        string serializar() ;
        bool hidratar( string serializado);
    protected:
    private:
        string dato;

};

#endif // RVAR_H
