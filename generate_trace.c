#include <stdio.h>
void generate_trace (int bus_size, int buffer_size,char bufffer_size[],char buss_size[]){



char final_path[8190];
char x[2]="x";
char xx[2]="_";
char verilog[3]=".v";
char trace [12]="tracebuffer";
strcpy (final_path,trace);
strncat (final_path,xx,strlen(xx));
strncat (final_path,buss_size,strlen(buss_size));
strncat (final_path,x,strlen(x));
strncat (final_path,bufffer_size,strlen(bufffer_size));
strncat (final_path,verilog,strlen(verilog));
FILE *fp = fopen(final_path,"w+");
int addr_size = calc(buffer_size);


fprintf (fp,"`include  \"buffer_%dx%d.v\"\n",bus_size,buffer_size);
fprintf (fp,"`include  \"manager_%dx%d.v\"\n",bus_size,buffer_size);
fprintf(fp,"`define tamanho_enderec %d\n`define tamanho_buffer %d \n`define tamanho_bloco %d\n\n",addr_size,buffer_size,bus_size);
fprintf (fp,"module tracebuffer (clk,reset,datain,dataout,pause);\n input clk,reset;\n output pause; \n\n input [`tamanho_bloco-1:0]datain;\n");
fprintf (fp,"output [`tamanho_bloco-1:0]dataout;\nwire ler,escrever,vazio,cheio;\nwire [`tamanho_enderec-1:0]itens;\n");
fprintf (fp,"manager manager01(.clk(clk),.reset(reset),.write(escrever),.read(ler),.itens(itens),.pause(pause),.vazio(vazio),.cheio(cheio));\n");
fprintf (fp,"Buffer buffer01(.clock(clk),.reset(reset),.datain(datain),.dataout(dataout),.escreve(escrever),.le(ler),.elementos(itens),.vazio(vazio),.cheio(cheio));\n\n\nendmodule");
fclose (fp);
}
