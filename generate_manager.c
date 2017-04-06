#include <stdio.h>


void generate_manager (int bus_size, int buffer_size,char bufffer_size[],char buss_size[]){

char final_path3[8190];
char x[2]="x";
char xx[2]="_";
char verilog[3]=".v";
char manager [11]="manager";
strcpy (final_path3,manager);
strncat (final_path3,xx,strlen(xx));
strncat (final_path3,buss_size,strlen(buss_size));
strncat (final_path3,x,strlen(x));
strncat (final_path3,bufffer_size,strlen(bufffer_size));
strncat (final_path3,verilog,strlen(verilog));
FILE *fp = fopen(final_path3,"w+");
int addr_size = calc(buffer_size);

fprintf(fp,"`define tamanho_enderec %d\n`define tamanho_buffer %d \n`define tamanho_bloco %d\n\n",addr_size,buffer_size,bus_size);
fprintf (fp,"module manager(clk,reset,write,read,itens,pause,vazio,cheio);\n\n");
fprintf (fp,"input clk,reset,vazio,cheio;\ninput [`tamanho_enderec-1:0] itens;\noutput reg write=1;\noutput reg read=0;\noutput  pause;\nreg pause=0;\n\n");
fprintf (fp,"always @(posedge clk or posedge reset) begin\n	if (reset) begin\n		write<=0;\n	end  \n	else begin \n		if (itens==0)begin\n		write<=1;\n		end\n		if (itens ==`tamanho_buffer-1)begin\n		write<=0;\n		end\n	end\nend\n\n");
fprintf (fp,"always @(posedge clk or posedge reset) begin\n	if (reset) begin\n		read<=0;\n	end  \n else begin \n		if (itens==`tamanho_buffer-1)begin\n		read<=1;\n		end\n		if (itens==0) begin\n		read<=0;\n		end\n	end\nend\n\n");
fprintf (fp,"always @(posedge clk or posedge reset) begin\n	if (reset) begin\n		pause<=0;\n	end \n	else begin \n		if (read) begin\n			pause <=1;\n		end \n		else begin\n			pause<=0;\n		end \n	end\nend\n\nendmodule");
fclose(fp);
}
