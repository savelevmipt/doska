
#include <stdio.h>
#include <string.h>
#include "util/BigInteger.h"

int main(){
    BigInteger numb = bigint_new_hex("1", 1);
    printf("num + 'value' - to save\n");
    printf("print + 'base' - to print\n");
    printf("+   to add\n");
    printf("-   to subtract\n");
    printf("*   to multiply\n");
    printf("/   to divide\n");
    printf("%%   - mod\n");
    printf("log2 - log with basis 2\n");
    printf("exit - to exit\n");
    char* cmd = NULL;
    char* param = NULL;
    while(1) {
        int retcode = scanf("%ms", &cmd);
        if(retcode != 1) {
            break;
        }
        if(!strcmp(cmd, "num")){
            bigint_free(numb);
            scanf("%ms", &param);
            numb = bigint_new_dec(param, strlen(param));
            free(param);
        }else if(!strcmp(cmd, "print")){
            size_t base;
            retcode = scanf("%lu", &base);
            if(retcode != 1){
                base = 10;
            }
            char* str = bigint_toString(numb, base);
            printf("Val: %s\n", str);
            free(str);
        }else if(!strcmp(cmd, "exit")) {
            free(cmd);
            break;
        }else if(!strcmp(cmd, "log2")){
            printf("log2: %lu\n", bigint_log2(numb));
        }else if(strlen(cmd) == 1){
            scanf("%ms", &param);
            BigInteger b = bigint_new_dec(param, strlen(param));
            free(param);
            if(cmd[0] == '+'){
                bigint_add(&numb, b);
            }else if(cmd[0] == '-'){
                bigint_sub(&numb, b);
            }else if(cmd[0] == '*'){
                bigint_mul(&numb, b);
            }else if(cmd[0] == '/'){
                bigint_div(&numb, b);
            }else if(cmd[0] == '%'){
                bigint_mod(&numb, b);
            }
            bigint_free(b);
        }
        free(cmd);
    }
    bigint_free(numb);
    return 0;
}
