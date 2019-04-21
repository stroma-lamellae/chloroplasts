#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t *register_file;
uint32_t tempt;				//Temporary arithmetic registers
uint32_t temps0;
uint32_t temps1;
void* memory;

void load_tr(uint32_t *tr, char *s0)
{
	if (s0[0] == '#')
	{
		*tr = atoi(&s0[1]);
	}
	else if (s0[0] == '%')
	{
		*tr = register_file[atoi(&s0[1])];
	}
	else if (s0[0] == '@')
	{
		memcpy((void*)tr,memory + atoi(&s0[1]),sizeof(uint32_t));
	}
	else
	{
		exit(-1);
	}
}

void write_tr(uint32_t *tr, char* t)
{
	if (t[0] == '%')
	{
		register_file[atoi(&t[1])] = tempt;
	}
	else if (t[0] == '@')
	{
		memcpy(memory + atoi(&t[1]),(void*)tr,sizeof(uint32_t));
	}
	else
	{
		exit(-1);
	}
}
void move_mm()
{
tempt = temps0;
}
void and_mm()
{
tempt = temps0 & temps1;
}
void or_mm()
{
tempt = temps0 | temps1;
}
void xor_mm()
{
tempt = temps0 ^ temps1;
}
void not_mm()
{
tempt = ~temps0;
}
void add_mm()
{
tempt = temps0 + temps1;
}
void sub_mm()
{
tempt = temps0 - temps1;
}
void mul_mm()
{
tempt = temps0 * temps1;
}
void div_mm()
{
tempt = temps0 / temps1;
}
void rem_mm()
{
tempt = temps0 % temps1;
}
void execute_instruction(char* i, char* t, char* s0, char* s1)
{
	load_tr(&temps0,s0);
	if (s1[0])
	{
		load_tr(&temps1,s1);
	}
	if (!strncmp("MOVE",i,16))
	{
		move_mm();
	}
	else if (!strncmp("AND",i,16))
	{
		and_mm();
	}
	else if (!strncmp("OR",i,16))
	{
		or_mm();
	}
	else if (!strncmp("XOR",i,16))
	{
		xor_mm();
	}
	else if (!strncmp("NOT",i,16))
	{
		not_mm();
	}
	else if (!strncmp("ADD",i,16))
	{
		add_mm();
	}
	else if (!strncmp("SUB",i,16))
	{
		sub_mm();
	}
	else if (!strncmp("MUL",i,16))
	{
		mul_mm();
	}
	else if (!strncmp("DIV",i,16))
	{
		div_mm();
	}
	else if (!strncmp("REM",i,16))
	{
		rem_mm();
	}
	else
	{
		fprintf(stdout,"Flagrant Instruction Error! Computer Over!\n");
		exit(-1);
	}
	write_tr(&tempt,t);		
}

void print_registers()
{
	int i = 0;
	for (i = 0; i < 8; i++)
	fprintf(stdout,"%" PRIu32 "\n", register_file[i]);
}

int main(int argc, char** argv)
{
	char input_buff[64];
	char inst_buff[16];
	char t_buff[16];
	char s0_buff[16];
	char s1_buff[16];
	char *t0,*t1;
	int l,i;
	register_file = malloc(sizeof(int) * 8);
	memory = malloc(1024);
	while(!feof(stdin))
	{
		fgets(input_buff,64,stdin);
		for(i = 0; i < 64; i++)
		{
			if (input_buff[i] == '\n')
			{
				input_buff[i] = '\0';
				break;
			}
		}
		t1 = strchr(input_buff, ' ');			//Isolate the instruction word
		l = (int)(t1 - input_buff)/sizeof(char);
		strncpy(inst_buff,input_buff,l);
		inst_buff[l] = '\0';
		t0 = t1 + 1;					//Point t0 to the start of the first operand
		t1 = strchr(t0, ',');				//Isolate the t operand
		l = (int)(t1 - t0)/sizeof(char);
		strncpy(t_buff,t0,l);
		t_buff[l] = '\0';
		t0 = t1 + 1;					//Point t0 to the start of the second operand
		t1 = strchr(t0,',');
		if (t1)						//A second , is found, there are 3 operands
		{
			l = (int)(t1 - t0)/sizeof(char);
			strncpy(s0_buff,t0,l);
			s0_buff[l] = '\0';
			t0 = t1 + 1;				//Point t0 to the start of the third operand
			strcpy(s1_buff,t0);
		}
		else
		{
			strcpy(s0_buff,t0);
			s1_buff[0] = '\0';
		}
		execute_instruction(inst_buff, t_buff, s0_buff, s1_buff);
	}
	print_registers();
	return 0;
}