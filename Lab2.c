#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
typedef enum {abegin, aend, amovl, amovr, ainc, adec, aprintc, aprint, aget} TuringAction;

const char commands[9][7] = {"begin", "end", "movl", "movr", "inc", "dec", "printc", "print", "get" };

const int maxvalue = 4;

struct strip
{
    struct strip* left;
    struct strip* right;
    short int* cells;
};

struct strip* CreateStrip(int CellCount)
{
    printf("Creating new strip\n");
    struct strip* ptr = malloc(sizeof(struct strip));
    ptr->cells = malloc(sizeof(int)*CellCount);
    int i;
    for (i = 0; i<CellCount; i++)
    {
        ptr->cells[i]= 0;
    }
    ptr->left= NULL;
    ptr->right= NULL;
    return ptr;
}

struct sHead
{
    struct strip* Current;
    int pos;
};

struct sSE
{
    int value;
    struct sSE* next;
};

struct sHead head;
const int DefStrip = 8;

struct sSE* stack= NULL;

void movl()
    {
        head.pos--;
        if (head.pos < 0)
        {
            if (head.Current->left == NULL)
                head.Current->left= CreateStrip(DefStrip);
            head.Current->left->right= head.Current;
            head.Current= head.Current->left;
            head.pos= DefStrip - 1;
        }
        print();
    }

    void movr()
    {
        head.pos++;
        if (head.pos == DefStrip)
        {
            if (head.Current->right == NULL)
                head.Current->right= CreateStrip(DefStrip);
            head.Current->right->left = head.Current;
            head.Current= head.Current->right;
            head.pos= 0;
        }
    }

    void inc()
    {
        head.Current->cells[head.pos]++;
        if (head.Current->cells[head.pos] == maxvalue+1)
        {
            head.Current->cells[head.pos]= 0;
            printf("Integer overflow at pos %i\n", head.pos);
        }

    }

    void dec()
    {
        head.Current->cells[head.pos]--;
        if (head.Current->cells[head.pos] == -1)
        {
            head.Current->cells[head.pos]= maxvalue;
            printf("Integer underflow at pos %i\n", head.pos);
        }
    }

    void print()
    {
        printf("Value at pos %i: %u\n", head.pos, head.Current->cells[head.pos]);
    }

    void printc()
    {
        printf("Char at pos %i: %c\n", head.pos, head.Current->cells[head.pos]);
    }

    void get()
    {
        head.Current->cells[head.pos]= getc(stdin);
        while(getchar()!='\n');
        if (head.Current->cells[head.pos] > maxvalue)
        {
            head.Current->cells[head.pos]= 0;
            printf("Integer overflow at pos %i\n", head.pos);
        }
        if (head.Current->cells[head.pos] < 0)
        {
            head.Current->cells[head.pos]= maxvalue;
            printf("Integer underflow at pos %i\n", head.pos);
        }
    }

    int exitcycle= 0;
    int begincount= 0;
    int level= 0;
    FILE* fp;

    void begin()
    {
        begincount++;
        printf("+%i\n", begincount);
        if (exitcycle)
           return;
        if (head.Current->cells[head.pos] == 0)
        {
            exitcycle= 1;
        }
        else
        {
            int ce;
            fgetpos(fp, &ce);
            ce-= 7;
            if (stack==NULL||(stack->value!=ce))
            {
                struct sSE* ptr= malloc(sizeof(struct sSE));
                ptr->next= stack;
                stack= ptr;
                //printf("1\n");
                stack->value= ce;
                printf("Entered cycle at %i\n", stack->value);
                level++;
            }
        }
    }

    void end()
    {
        begincount--;
        printf("-%i\n", begincount);
        if (begincount < 0)
        {
            printf("Error: missing begin\n");
            //begincount= 0;
            exit(-2);
            return;
        }

        if (begincount >= level)
            return;

        printf("End value at pos %i: %i\n", head.pos, head.Current->cells[head.pos]);
        if (exitcycle)
        {
            exitcycle= 0;
        }
        else
        {
            //printf("%i\n", stack);
            if (stack->value >= 0)
            {
                printf("Returning to %i, bc %i\n", stack->value, begincount);
                fsetpos(fp, &(stack->value));
            }
                struct sSE* ptr= stack->next;
                free(stack);
                stack= ptr;
                level--;
                //printf("pop %i\n", stack->value);
        }
    }

int main(int argc, char **argv){


    head.Current= CreateStrip(DefStrip);
    head.pos= DefStrip/2;

    fp= fopen("prog.txt"/*argv[1]*/,"r");
    if (!fp)
		{
			printf("Unable to open file!\n");
			return -1;
		}

	fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char s[9];

    while (ftell(fp)<size)
    {
        //int ce;
            //fgetpos(fp, &ce);
          // printf("do \n" );

        fgets(&s, 9, fp);

        /*fgetpos(fp, &ce);
            printf("posle %i\n", ce);*/
        char *pos;
        if ((pos=strchr(&s, '\n')) != NULL)
        *pos = '\0';
        if ((pos=strchr(&s, '\r')) != NULL)
        *pos = '\0';
        //printf("%s1\n", &s);
        TuringAction i;
        for (i=abegin; i<=aget; i++)
        {
            printf("%s. %s.\n", &s, &commands[i]);
            if (strcmp(s, commands[i])==0)
                break;
        }
        //printf("%i\n",i);

        switch (i)
        {
            case abegin:  begin(); break;
            case aend:    end();   break;
            case amovl:   if ((!exitcycle)) movl();   break;
            case amovr:   if ((!exitcycle)) movr();   break;
            case ainc:    if ((!exitcycle)) inc();    break;
            case adec:    if ((!exitcycle)) dec();    break;
            case aprintc: if ((!exitcycle)) printc(); break;
            case aprint:  if ((!exitcycle)) print();  break;
            case aget:    if ((!exitcycle)) get();    break;
        }
    }

    if (begincount > 0)
        printf("Error: missing end");

    fclose(fp);
    //deallocation
    return 0;
}


