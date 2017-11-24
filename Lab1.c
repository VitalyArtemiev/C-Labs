#include<stdio.h>

struct filestruct
{
    int a;
    char s[256];
    float f;
};

int main(int argc, char **argv){
    FILE* fp;

    fp= fopen(argv[1],"rb");
    if (!fp)
		{
			printf("Unable to open file!");
			return -1;
		}

	fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int c = size / sizeof(struct filestruct);

    printf("Filesize is %i\n", size);

    struct filestruct* pr = malloc(size);

    struct filestruct r;

    fread(pr, sizeof(struct filestruct), c, fp);

    int i;
	for (i = 0; i < c; i++)
    {
        r= pr[i];
        if (r.s[255] != 0)
        {
            r.s[255]= 0;
            printf("Warning: Possible data corruption\n");
        }
        printf("%i\t%s\t%f\n", r.a, &r.s[0], r.f);
    }

    fclose(fp);

    return 0;
}
