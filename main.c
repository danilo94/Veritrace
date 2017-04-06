#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "generate_buf.c"
#include "calc.c"
#include "generate_manager.c"
#include "generate_trace.c"
#include "Structure.h"
int main(int argc,char *argv[]){
        structure estrutura;
        process_args(argc,argv,&estrutura);
        int bus_size,buffer_size;
        bus_size = estrutura.width;
        buffer_size = estrutura.depth;
        char bufffer_size[25];
        char buss_size[25];

        if (estrutura.JTAG==0 && estrutura.debugger==0){
            sprintf (bufffer_size, "%d",buffer_size);
            sprintf (buss_size,"%d",bus_size);
            generate_manager(bus_size,buffer_size,bufffer_size,buss_size);
            gen_buffer(bus_size,buffer_size,bufffer_size,buss_size);
            generate_trace(bus_size,buffer_size,bufffer_size,buss_size);
            printf ("The Tracebuffer module was successfully built.\nYour memory size is:%d bytes.\n",(bus_size*buffer_size)/8);
        }




        }

void process_args(int argc, char **argv,structure *estrutura){
    int width;
    int size;
    char c;
   while((c = getopt(argc, argv,"s:w:dj")) != -1){
      //printf("Entrou!!!\n");
      switch(c) {
         case 'w':
            width   = atoi(optarg);
            estrutura->width= width;
            estrutura->JTAG=0;
            estrutura->debugger=0;
            break;
        case 's':
            size = atoi(optarg);
            estrutura->depth = size;
            break;
        case 'd':
            estrutura->debugger=1;
        case 'j':
            estrutura->JTAG=1;
        break;
         default:
            printf ("-w Define Trace buffer width.\n -s Define  Trace buffer size.\n -d Insert Restorability Signal Plataform (ALPHA).\n -j Insert the JTAG protocol(Not Implemented Yet).\n");
            exit(1);
      }
   }
   if (size <= 0 || width <= 0 ){
        printf ("Please, insert a Valid Value to size and width.\n");
        exit(1);
   }
}








