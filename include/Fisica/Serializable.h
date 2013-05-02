#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include "Fisica/Necesario2.h"
using namespace std;
class Serializable
{
    public:
        virtual string serializar() = 0;
        virtual bool hidratar( string serializado) = 0;
};
#endif
