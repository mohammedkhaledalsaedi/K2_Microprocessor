#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MEMORY_SIZE 100
#define INSTRUCTION_WIDTH 8

unsigned char instruction_memory[MEMORY_SIZE];
unsigned char program_counter = 0;


int J = 0;
int C = 0;
int D1 = 0;
int D0 = 0;
int Sreg = 0;
int S2 = 0;
int S1 = 0;
int S0 = 0;
int imm = 0;
int sum = 0;
int Rcarry = 0;


unsigned char binary_to_byte(const char *binary) {
    unsigned char result = 0;
    for (int i = 0; i < INSTRUCTION_WIDTH; i++) {
        result = (result << 1) | (binary[i] - '0');
    }
    return result;
}


void load_file_to_memory(const char *filename, int *lines_loaded) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error! Could not open file.\n");
        exit(1);
    }

    char line[INSTRUCTION_WIDTH + 2];
    *lines_loaded = 0;

    while (fgets(line, sizeof(line), file) != NULL && *lines_loaded < MEMORY_SIZE) {
        line[strcspn(line, "\n")] = '\0';
        instruction_memory[*lines_loaded] = binary_to_byte(line);
        (*lines_loaded)++;
    }

    fclose(file);
}



void decode_control(unsigned char instruction) {

    J = (instruction >> 7) & 1;
    C = (instruction >> 6) & 1;
    D1 = (instruction >> 5) & 1;
    D0 = (instruction >> 4) & 1;
    Sreg = (instruction >> 3) & 1;
    S2 = (instruction >> 2) & 1;
    S1 = (instruction >> 1) & 1;
    S0 = (instruction >> 0) & 1;
    imm = 0;
    if (S0 ==1){
            imm +=1;
    }
    if (S1==1){
            imm+=2;
    }
    if (S2 ==1){
            imm+=4;
    }

    //printf("imm = %d\n", imm);


}

int decoder(int D1, int D0){
	if (D1 ==0 && D0 ==0){
		return 8;
	}
	else if(D1 == 0 && D0==1){
		return 4;
	}
	else if(D1 == 1&& D0 == 0){
		return 2;
	}
	else if (D1 == 1&& D0 ==1){
		return 1;
	}
	return 0;
}

void alu(int RA, int RB, int S2){
	if (S2 ==0){
		sum = RA + RB;
		if (sum > 15){
			sum = sum -16;
			Rcarry = 1;
		}
		else {
			Rcarry = 0;
		}
	}
	else if (S2 == 1){
		sum = RA - RB;
		if (sum <0){
			sum = sum +16;
			Rcarry = 1;
		}
		else {
			Rcarry = 0;
		}
	}
}

int mux(int sum,int imm, int Sreg){
	if (Sreg == 0){
		return sum;
	}
	else if (Sreg ==1){
		return imm;
	}
	return 0;
}
	
int main(){
	int RA=0;
	int RB=0;
	int R0=0;
	int temp = 0;
	int lines_loaded = 0;
	int dec = 0;
	int prev_carry = 0;
	char s;
	//int n = 0;
	FILE *assem = fopen("binary.asm","r");
	//char line[20];
	int k = 0;
	char assem_mem[9][20];
	while(fgets(assem_mem[k],20,assem)){
		// assem_mem[k] = line;
		k++;
	}
	printf("Select one of the following modes:\n R - Continuous mode\n S - Step-By-Step mode\n");
	scanf(" %c",&s);
	//int prev_R0;
	//int one_count=0;
	load_file_to_memory("binary.bin",&lines_loaded);
	while (program_counter<lines_loaded){

		unsigned char instruction = instruction_memory[program_counter];
		decode_control(instruction);
		//inst = instruction;
		dec = decoder(D1,D0);

		alu(RA, RB, S2);

		temp = mux(sum, imm, Sreg);
		if (s == 'S'){
			printf("instruction %d:  %s",program_counter,assem_mem[program_counter]);
			//assemble(instruction);
		}
		if (s != 'R'&&s != 'S'){
			printf("Error, input 'S' or 'R'\n");
			exit(1);
		}
		if (dec == 8){
			RA = temp;
		}
		else if (dec == 4){
			RB = temp;
		}
		else if (dec == 2){
			R0 = RA;
				printf("R0 = %d\n",R0);
		}

		if (s == 'S'){
			printf("\n");
			getchar();
		}

		if ((prev_carry==1&&C==1)||J==1){
			program_counter = imm;
		}
		else {
			program_counter++;
		}
		//prev_R0 = R0;
		prev_carry = Rcarry;
		//printf("R0 = %d\nRA = %d\nRB = %d\nRcarry = %d\n",R0,RA,RB,prev_carry);
		usleep(200000);
	}

	return 0;

}




