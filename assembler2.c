#include <stdio.h>
#include <string.h>

void assemble(FILE *assembly, FILE *binary,FILE *assem) {
    char line[10];
    const char *bin;
    
    printf("function\n");

    while (fgets(line, sizeof(line), assembly)) {
        
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "RA=RA+RB") == 0) {
            printf("read\n");
            bin = "00000000";
        }
        else if (strcmp(line, "RB=RA+RB") == 0) {
            bin = "00010000";
        }
        else if (strcmp(line, "RA=RA-RB") == 0) {
            bin = "00000100";
        }
        else if (strcmp(line, "RB=RA-RB") == 0) {
            bin = "00010100";
        }
        else if (strcmp(line, "R0=RA") == 0) {
            bin = "00100000";
        }
        else if (strcmp(line, "RA=0") == 0) {
            bin = "00001000";
        }
        else if (strcmp(line, "RA=1") == 0) {
            bin = "00001001";
        }
        else if (strcmp(line, "RA=2") == 0) {
            bin = "00001010";
        }
        else if (strcmp(line, "RA=3") == 0) {
            bin = "00001011";
        }
        else if (strcmp(line, "RA=4") == 0) {
            bin = "00001100";
        }
        else if (strcmp(line, "RA=5") == 0) {
            bin = "00001101";
        }
        else if (strcmp(line, "RA=6") == 0) {
            bin = "00001110";
        }
        else if (strcmp(line, "RA=7") == 0) {
            bin = "00001111";
        }
        else if (strcmp(line, "RB=0") == 0) {
            bin = "00011000";
        }
        else if (strcmp(line, "RB=1") == 0) {
            bin = "00011001";
        }
        else if (strcmp(line, "RB=2") == 0) {
            bin = "00011010";
        }
        else if (strcmp(line, "RB=3") == 0) {
            bin = "00011011";
        }
        else if (strcmp(line, "RB=4") == 0) {
            bin = "00011100";
        }
        else if (strcmp(line, "RB=5") == 0) {
            bin = "00011101";
        }
        else if (strcmp(line, "RB=6") == 0) {
            bin = "00011110";
        }
        else if (strcmp(line, "RB=7") == 0) {
            bin = "00011111";
        }
        else if (strcmp(line, "JC=0") == 0) {
            bin = "01110000";
        }
        else if (strcmp(line, "JC=1") == 0) {
            bin = "01110001";
        }
        else if (strcmp(line, "JC=2") == 0) {
            bin = "01110010";
        }
        else if (strcmp(line, "JC=3") == 0) {
            bin = "01110011";
        }
        else if (strcmp(line, "JC=4") == 0) {
            bin = "01110100";
        }
        else if (strcmp(line, "JC=5") == 0) {
            bin = "01110101";
        }
        else if (strcmp(line, "JC=6") == 0) {
            bin = "01110110";
        }
        else if (strcmp(line, "JC=7") == 0) {
            bin = "01110111";
        }
        else if (strcmp(line, "J=0") == 0) {
            bin = "10110000";
        }
        else if (strcmp(line, "J=1") == 0) {
            bin = "10110001";
        }
        else if (strcmp(line, "J=2") == 0) {
            bin = "10110010";
        }
        else if (strcmp(line, "J=3") == 0) {
            bin = "10110011";
        }
        else if (strcmp(line, "J=4") == 0) {
            bin = "10110100";
        }
        else if (strcmp(line, "J=5") == 0) {
            bin = "10110101";
        }
        else if (strcmp(line, "J=6") == 0) {
            bin = "10110110";
        }
        else if (strcmp(line, "J=7") == 0) {
            bin = "10110111";
        }

        if (bin != NULL) {
            fprintf(binary, "%s\n", bin);
	    fprintf(assem,"%s\n",line);
            bin = NULL; 
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *assembly = fopen(argv[1], "r");
    FILE *binary = fopen("binary.bin", "w");
    FILE *assem = fopen("binary.asm","w");
    if (!assembly || !binary||!assem) {
        perror("Error");
        return 1;
    }

    assemble(assembly, binary,assem);

    fclose(assembly);
    fclose(binary);
    fclose(assem);

    return 0;
}

