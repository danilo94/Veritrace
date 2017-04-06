#include <stdio.h>

void gen_buffer(int bus_size, int buffer_size,char *bufffer_size,char *buss_size){

char final_path[8190];
char x[2]="x";
char xx[2]="_";
char verilog[3]=".v";
char buff [7]="buffer";
strcpy (final_path,buff);
strncat (final_path,xx,strlen(xx));
strncat (final_path,buss_size,strlen(buss_size));
strncat (final_path,x,strlen(x));
strncat (final_path,bufffer_size,strlen(bufffer_size));
strncat (final_path,verilog,strlen(verilog));
FILE *fp = fopen(final_path,"w+");


int addr_size = calc(buffer_size);

fprintf (fp,"`define tamanho_enderec %d\n`define tamanho_buffer %d \n`define tamanho_bloco %d\n\n",addr_size,buffer_size,bus_size);
fprintf (fp,"module Buffer(clock,reset,datain,dataout,escreve,le,elementos,vazio,cheio);\n\n");
fprintf (fp,"input reset, clock, escreve, le;\ninput [`tamanho_bloco-1:0]datain;\n");
fprintf (fp,"output[`tamanho_bloco-1:0]dataout;\n");
fprintf (fp,"output[`tamanho_enderec-1:0] elementos;\n");
fprintf (fp,"output vazio,cheio;\nreg[`tamanho_bloco-1:0] dataout;\nreg vazio, cheio;\nreg[`tamanho_enderec-1:0]    elementos;\nreg[`tamanho_enderec -1:0]  ponteiro_leitura, ponteiro_escrita;\n");
fprintf (fp,"reg[`tamanho_bloco-1:0]memoria[`tamanho_buffer-1 : 0];\n\n");
fprintf (fp,"always @(elementos) begin\n   vazio = (elementos==0);\n   cheio = (elementos== `tamanho_buffer-1);\nend\n");
fprintf (fp,"always @(posedge clock or posedge reset)begin\n   if( reset )\n       elementos <= 0;\n\n   else if( (!cheio && escreve) && ( !vazio && le ) )\n       elementos <= elementos;\n");
fprintf (fp,"   else if( !cheio && escreve )\n       elementos <= elementos + 1;\n\n   else if( !vazio && le )\n       elementos <= elementos - 1;\n\n   else\n      elementos <= elementos;\nend\n\n");
fprintf (fp,"always @( posedge clock or posedge reset) begin\n   if( reset )\n      dataout <= 0;\n   else begin\n      if( le && !vazio )\n         dataout <= memoria[ponteiro_leitura];\n\n      else\n         dataout <= dataout;\n\n   end\nend\n\n");
fprintf (fp,"always @(posedge clock) begin\n\n   if( escreve && !cheio )\n      memoria[ ponteiro_escrita ] <= datain;\n\n   else\n      memoria[ ponteiro_escrita ] <= memoria[ ponteiro_escrita ];\nend\n\n");
fprintf (fp,"always@(posedge clock or posedge reset) begin\n   if( reset ) begin\n      ponteiro_escrita <= 0;\n      ponteiro_leitura <= 0;\n   end\n");
fprintf (fp,"   else begin\n	if (ponteiro_escrita == `tamanho_buffer-1) begin \n			ponteiro_escrita=0;\n			ponteiro_leitura=0;\n	end\n");
fprintf (fp,"   else begin \n			if( !cheio && escreve )    ponteiro_escrita <= ponteiro_escrita + 1;\n				else  ponteiro_escrita <= ponteiro_escrita;\n");
fprintf (fp,"			if( !vazio && le )   ponteiro_leitura <= ponteiro_leitura + 1;\n				else ponteiro_leitura <= ponteiro_leitura;\n				end\n   end\n\nend\nendmodule\n");
fclose(fp);
}
