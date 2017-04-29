#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;

    if(argc < 3){
        printf("This program needs to receive the input and output.\n");
        return 0;
    }

    FILE *fp;

    fp = fopen(argv[1], "r");

    if(!fp) {
        printf("%s doesn't exist.\n", argv[1]);
        return 0;
    }

    while(1)
    {
        c = fgetc(fp);
        if( feof(fp) )
        { 
            break ;
        }
        printf("%c", c);
    }
    fclose(fp);
    
    printf("\n");
    return 0;
}