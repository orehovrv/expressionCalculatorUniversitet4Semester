#include "LIST.h"

LIST::LIST() {
    begin = NULL;
    end = NULL;
    cur = NULL;

    count = 0;
}

LIST::~LIST() {
    cur = begin;
    while(cur) {
        begin = begin->next;
        free(cur);
        cur = begin;
    }
}

void LIST::viewList() {
    printf("\n");
    printf("======LIST=====\n");
    NODE *cur = begin;
    while(cur) {
        printf("%lf, %c\n", cur->data.num, cur->data.oper);
        cur = cur->next;
    }
    printf("====END=LIST====\n");
    printf("Count elements: %d\n\n", count);
}

void LIST::addEnd(double num, char oper) {
    NODE *node = (NODE*)malloc(sizeof(NODE));
    node->next = NULL;
    node->data.num = num; node->data.oper = oper;

    if(end != NULL){
        node->prev = end;
        end->next = node;
        end = node;
    } else {
        begin = node;
        end = node;
        node->prev = NULL;
    }
    count++;
}

bool LIST::empty() {
    return begin == NULL;
}

void LIST::curSetStart(){
    cur = begin;
}

void LIST::curSetEnd(){
    cur = begin;
}

void LIST::next(){
    cur = cur->next;
}

void LIST::prev(){
    cur = cur->prev;
}

DATA LIST::getData(){
    return cur->data;
}

void LIST::delCur() {
    if(!begin) return;
    if(!cur) return;

    NODE *temp;

    if(cur == begin && cur == end) {
        free(cur);
        begin = end = NULL;
        cur = NULL;
    } else if(cur == begin && cur != end) {
        temp = begin->next;
        temp->prev = NULL;
        free(cur);
        begin = temp;
        cur = begin;
    } else if(cur != begin && cur == end) {
        temp = end->prev;
        temp->next = NULL;
        free(cur);
        end = temp;
        cur = end;
    } else {
        temp =
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    count--;
}

int LIST::getCount() {
    return count;
}

void LIST::editDataCur(DATA input) {
    if(cur)
        cur->data = input;
}

bool LIST::curEnd() {
    return cur == end;
}
