#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H
#include "necesary.h"
class Sequential
{
    public:
        Sequential();
        virtual ~Sequential();
        int s_create(char *url);
        int s_write(char *url, char * text);
        int s_open(char *url, const char mode[2]);
        void s_list(char *url);
        int s_read(char *url, char *reg);
        int s_search(char *url, char *str);
        int s_destroy(char *url);
        void s_close();
        bool is_sequential();
        int type;
        FILE* f_handler;
    protected:
    private:
};

#endif // SEQUENTIAL_H
