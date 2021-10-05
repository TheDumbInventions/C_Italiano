#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	FILE *file;
	FILE *filetmp;
	char c; 
	unsigned char newline;
	int slash_pos;
	char filetmp_name[100];
	
	for(int i = 2; i < argc; i++) {
		newline = 1;
		file = fopen(argv[i], "r");
		if (file == NULL) {
			return 1;
		}
		
		slash_pos = 0;
		for(int k = 0; k < strlen(argv[i]); k++) {
			if (argv[i][k] == '\\' || argv[i][k] == '/') {
				slash_pos = k;
			}
		}
		if (slash_pos <= 0) {
			return 1;
		}
		
		strcpy(filetmp_name, argv[1]);
		strcat(filetmp_name, (argv[i]+slash_pos));
		filetmp = fopen(filetmp_name, "w");
		
		if (filetmp == NULL) {
			return 1;
		}
		c = fgetc(file);
		while(c != EOF) {
			fputc(c, filetmp);
			if (c == '\n') {
				newline = 1;
			} else if (c == '#' && newline){
				char directive[20];
				do 
				{
					c = fgetc(file);
				}
				while(c == ' ');		// remove all spaces after #
				int j = 0;
				while(c != EOF && c != ' ') {
					directive[j] = c;
					c = fgetc(file);
					j++;
				}
				directive[j] = '\0';
				if (strcmp(directive, "definisci") == 0) { fputs("define", filetmp); }
				else if (strcmp(directive, "includi") == 0) { fputs("include", filetmp); }
				else if (strcmp(directive, "indefinisci") == 0) { fputs("undef", filetmp); }
				else if (strcmp(directive, "sedef") == 0) { fputs("ifdef", filetmp); }
				else if (strcmp(directive, "sendef") == 0) { fputs("ifndef", filetmp); }
				else if (strcmp(directive, "se") == 0) { fputs("if", filetmp); }
				else if (strcmp(directive, "altrimenti") == 0) { fputs("else", filetmp); }
				else if (strcmp(directive, "altrimentise") == 0) { fputs("elif", filetmp); }
				else if (strcmp(directive, "finese") == 0) { fputs("endif", filetmp); }
				else if (strcmp(directive, "errore") == 0) { fputs("error", filetmp); }
				//else if (strcmp(directive, "pragma") == 0) { fputs("pragma", filetmp); }
				else { fputs(directive, filetmp); }
				if (c != EOF) {
					fputc(c, filetmp);
				} else {
					break;
				}
				newline = 0;
			} else if (c == ' '){
				// do nothing
			} else {
				newline = 0;
			}
			c = fgetc(file);
		}
		
		fclose(file);
		fclose(filetmp);
	}
	
	return 0;
}