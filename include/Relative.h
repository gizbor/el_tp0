#ifndef RELATIVE_H
#define RELATIVE_H
#define MAX_FILENAME_LENGTH 50
#include "necesary.h"
class Relative
{
    public:
        Relative(char *url);
        virtual ~Relative();
        void r_close();
        int r_open(char *mode);
        int r_create();
        int r_write(char *reg, char *type);
        void r_list();
        int r_show(int offset, char *type);
        int r_search(char *reg);
        int r_destroy();
        int is_open(){
    protected:
    private:
        char filename[MAX_FILENAME_LENGTH];
        FILE * f_i_handler, * f_d_handler;
};

#endif // RELATIVE_H
