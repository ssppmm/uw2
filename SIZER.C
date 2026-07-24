#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    char buf[10000];
    long offset=0;

    FILE *in, *out;

    if((in=fopen("koukai2.dat", "rb"))==NULL) {
	printf("I cann't find save file");
	exit (-1);
    }
    if ((out=fopen("imsi.dat", "wb"))==NULL) {
	printf("I cann't creat save file");
	exit(-1);
    }

    fseek(in, 0, SEEK_SET);
    fseek(out, 0, SEEK_SET);
    while (1) {
	fread(&buf, 10000, 1, in);
	fwrite(&buf, 10000, 1, out);
	offset+=10000;
	if (offset==330000) {
	    fread(&buf, 3551, 1, in);
	    fwrite(&buf, 3551, 1, out);
	    break;
	}
    }
    fclose(in);
    fclose(out);
    unlink("koukai2.dat");
    rename("imsi.dat", "koukai2.dat");
}
