#include "Fisica/RegVar.h"

RegVar::RegVar()
{
    //dtor
}
RegVar::~RegVar()
{
    //dtor
}

string RegVar::serializar(){
string serialized= num_to_string(this->size(), BYTES_FOR_RV_LENGTH_REPRESENTATION);
return serialized.append(this->get());
}

bool RegVar::hidratar(string serializado)
{
    (this->dato) = serializado.substr(BYTES_FOR_RV_LENGTH_REPRESENTATION, this->size());
return true;
}

