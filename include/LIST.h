#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _DATA {
    double num;
    char oper;
} DATA;

typedef struct _NODE {
    struct _NODE  *prev, *next;
    DATA data;
} NODE;

class LIST {
    private:
        NODE *begin, *end;
        NODE *cur;
        int count;

    public:
        LIST();
        virtual ~LIST();

        void viewList();
        void addEnd(double, char);

        bool empty();
        int getCount();

        void curSetStart();
        void curSetEnd();
        void next();
        void prev();
        DATA getData();
        void delCur();

        bool curEnd();

        void editDataCur(DATA);
};

#endif // LIST_H
