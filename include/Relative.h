#ifndef RELATIVE_H
#define RELATIVE_H
#define MAX_FILENAME_LENGTH 50
#define MAX_TEXT_REG_LENGTH 100

#include "necesary.h"
struct index_reg {
   unsigned int index, offset;
};

class Relative
{
    private:
        char filename[MAX_FILENAME_LENGTH];
        char index_filename[MAX_FILENAME_LENGTH+5];
        FILE * f_i_handler, * f_d_handler;
    public:
        Relative(char *url);
        virtual ~Relative();
        void r_close();
        int r_open(char *mode);
        int r_create(char* mode);
        size_t get_reg_offset(size_t n);
        char* r_i_read(size_t n);
        int r_write(char *reg, char *type);
        char* serialize_text(char *reg);
        char* r_read(size_t n);
        int append_index();
        void show_i_reg(size_t n);
        int r_i_seek(unsigned int n, FILE* fh);
        int get_reg_size();
        index_reg create_i_reg(size_t index, size_t offset);
        void r_list();
        int r_show(int offset, char *type);
        int r_search(char *reg);
        int r_destroy();
        int is_open();
        char* index_name();
        void create_treg(char** treg, char* text);
    protected:

};

#endif // RELATIVE_H


