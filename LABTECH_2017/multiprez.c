#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/******************************************************
    multiprez.c How to READ a binary file with fread
    @author: Xuan Do
 *****************************************************/
#define MAXENTRIES 45

struct prezinfo {
    char           inits[5];
    unsigned char  num;
};

int main( int argc, char *argv[] )
{
   
    FILE     *saveit;
    struct prezinfo input;

    /* Open the file */
    if ( argc > 1 ) 
    { 
        saveit = fopen( argv[1], "r" );
        if ( saveit == NULL ) 
        { 
            printf("No such file or directory"); 
        } 
    } 

    printf("Num Inits\n");
    while ( fread ( &input, sizeof ( struct prezinfo ), 1, saveit ) ) 
    {
        printf("%d %6s\n", input.num, input.inits);
    }
    fclose( saveit );
    return 0;
}
