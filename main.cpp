#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "LIST.h"

void deleteSpace(char*);
double func(char*, bool*);

int main() {
    //char strInput[100] = "(123.5+56.12)*56+325.98-65.5-(78+8*(2.5-1326))+1000";
    char strInput[100] = "56.12+((325-M_PI+65.6)-((78.64+8*2)-1326+M_PI))+2.5-5+M_PI*10";
    //char strInput[100] = "M_PI + 10";
    //char strInput[100] = "(sin(M_PI/2) + sin(M_PI/2)) * (sin(M_PI/2)) + M_PI * (sin(M_PI/2)-4)";
    //char strInput[100] = "sin((M_PI/6+M_PI/6)*3)+sin(M_PI/2) + ((cos(M_PI) + cos(M_PI)) + 3*cos(M_PI))";
    //char strInput[100] = "sin(M_PI/2)";
    //char strInput[100] = "3+(7-(15*1)+15-27+35)";

    //printf("Input str: ");
    //gets(strInput);
    //printf("str: %s\n", strInput);

    deleteSpace(strInput);
    //if(checkStr(strInput)) return 0;

    bool check = 1;
    double res = func(strInput, &check);
    if(check) printf("answer: %lf\n", res);
    else printf("bad str\n");

    return 0;
}

double func(char *cur, bool *check) {
    LIST list;
    double sum = 0, num = 0;
    bool flag = 1;

    char mass[100], *curN;

    printf("%s\n", cur);

    do {
        switch(*cur){
            case '.':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                num = atof(cur);
                while(*cur >= '0' && *cur <= '9' || *cur == '.') cur++;
                cur--;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
                list.addEnd(num, *cur);
                break;

            case '(': {
                curN = cur + 1;
                int temp = 0;
                do {
                    switch(*cur) {
                        case '(': temp++; break;
                        case ')': temp--; break;
                    }
                    cur++;
                } while (temp && *cur);

                strncpy(mass, curN, cur-curN - 1);
                mass[cur-curN-1] = 0;

                num = func(mass, check);

                if(*cur == 0) list.addEnd(num, ')');
                else list.addEnd(num, *cur);

                break; }

            case ')':
                flag = 0;
                list.addEnd(num, ')');
                break;

            case 0:
                list.addEnd(num, ')');
                break;

            default:
                char mass2[100];
                char *cur2 = cur;

                while(*cur != '(' && *cur != '+' && *cur != '-' && *cur != '*' && *cur != '/' && *cur != 0)
                    cur++;

                strncpy(mass2, cur2, cur - cur2);
                mass2[cur - cur2] = 0;
                printf("str = |%s|\n", mass2);

                int qq = 0;

                if(!strcmp(mass2, "sin")) qq = 1;
                else if(!strcmp(mass2, "cos")) qq = 2;
                else if(!strcmp(mass2, "tg")) qq = 3;
                else if(!strcmp(mass2, "ctg")) qq = 4;
                else if(!strcmp(mass2, "M_PI")) qq = 0;
                else *check = 0;

                if(qq) {
                    curN = cur + 1;
                    int temp = 0;
                    do {
                        switch(*cur) {
                            case '(': temp++; break;
                            case ')': temp--; break;
                        }
                        cur++;
                    } while (temp && *cur);
                    strncpy(mass, curN, cur-curN - 1);
                    mass[cur-curN-1] = 0;

                    switch(qq) {
                        case 1: num = sin(func(mass, check)); break;
                        case 2: num = cos(func(mass, check)); break;
                        case 3: num = tan(func(mass, check)); break;
                        case 4: num = 1/tan(func(mass, check)); break;
                    }

                    if(*cur == 0) list.addEnd(num, ')');
                    else list.addEnd(num, *cur);

                    break;
                }

                switch(*cur) {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                        if(!strcmp(mass2, "M_PI")) num = M_PI;
                        list.addEnd(num, *cur);

                        break;
                    case 0:
                        if(!strcmp(mass2, "M_PI")) num = M_PI;
                        list.addEnd(num, *cur);

                        break;
                }
                break;
        }
    } while(*cur++ && flag);

    list.viewList();
    DATA temp1, temp2;

    while(list.getCount() > 1) {
        list.curSetStart();
        while(!list.curEnd()) {
            temp1 = list.getData();
            if(temp1.oper == '*' || temp1.oper == '/')
                break;
            list.next();
        }

        if(temp1.oper == '*' || temp1.oper == '/') {
            list.next();
            temp2 = list.getData();
            switch(temp1.oper) {
                case '*': num = temp1.num * temp2.num; break;
                case '/': num = temp1.num / temp2.num; break;
            }
            list.prev();
            list.delCur();
            temp2.num = num;
            list.editDataCur(temp2);
        } else {
            list.curSetStart();
            temp1 = list.getData();
            list.next();
            temp2 = list.getData();
            switch(temp1.oper) {
                case '+': num = temp1.num + temp2.num; break;
                case '-': num = temp1.num - temp2.num; break;
            }
            list.curSetStart();
            list.delCur();
            temp2.num = num;
            list.editDataCur(temp2);
        }
    }

    list.curSetStart();
    temp1 = list.getData();

    return temp1.num;
}

void deleteSpace(char *str) {
    char *cur = str;

    if(str && *str)
        while(*str) {
            if(*str == ' ') {
                cur = str;
                while(*cur)
                    *cur++ = *cur;
                *cur = 0;
            } else str++;
        }
}
