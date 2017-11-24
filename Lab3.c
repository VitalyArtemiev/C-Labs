#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<strings.h>

typedef enum {aar, anode, aparent, aroot, asibling} TreeAction;
typedef enum {pNone, pLeft, pRight} NodePos;

const char commands[9][7] = {"quit", "apr", "ap", "as", "show", "save", "load"};

typedef struct node node;

struct node
{
	node* left;
	node* right;
	node* parent;
	int value;
};

typedef node* pnode;

pnode NewNode(int v, pnode parent, NodePos pos)
{
	pnode ptr;
	ptr= malloc(sizeof(struct node));
	ptr->value= v;
	ptr->parent= parent;
	ptr->left= NULL;
	ptr->right= NULL;
	if (pos==pLeft)
		parent->left= ptr;
	else
        if (pos==pRight)
            parent->right= ptr;
	return ptr;
};

pnode FindNode(pnode root, int v)
{
    if (root==NULL)
        return NULL;
	if (root->value==v)
		return root;
	pnode result= NULL;
	result= FindNode(root->left, v);
	if (result==NULL)
		result= FindNode(root->right, v);
	return result;
}

pnode AddByParent(pnode root, int v, int p)
{
    if (root==NULL)
        return NULL;
    pnode prt= FindNode(root, p);
    if (prt==NULL)
        return NULL;
    if (prt->left==NULL)
        return NewNode(v, prt, pLeft);
    else
        if (prt->right==NULL)
            return NewNode(v, prt, pRight);
        else
        {
            pnode o= prt->right;
            pnode n= NewNode(v, prt, pRight);
            n->left= o->left;
            n->right= o->right;
            return n;
        }
}

pnode AddBySibling(pnode root, int v, int s)
{
    if (root==NULL)
        return NULL;
    pnode prt= FindNode(root, s)->parent;

    if ((prt->left==NULL)||(prt->left->value!=v))
        return NewNode(v, prt, pLeft);
    else
        if (prt->right==NULL)
            return NewNode(v, prt, pRight);
        else
        {
            pnode o= prt->right;
            pnode n= NewNode(v, prt, pRight);
            n->left= o->left;
            n->right= o->right;
            return n;
        }
}

void pGetDepth(pnode root, int* pd)
{
	if (root==NULL)
		return;

    printf("cuck\n");
	int l= 1;
	int r= 1;
	pGetDepth(root->left, &l);//incorrect
	pGetDepth(root->right, &r);
	*pd+=  l>r ? l: r;
}

int GetDepth(pnode root)
{
    if (root==NULL)
        return 0;
	int l= 1;
	int r= 1;

	pGetDepth(root->left, &l);
	pGetDepth(root->right, &r);
	return l>r ? l : r;
}

struct sSE
{
    pnode value;
    struct sSE* next;
};

//struct sSE* stack= NULL;

void push(pnode p, struct sSE* stack)
{
    struct sSE* ptr= malloc(sizeof(struct sSE));
    ptr->next= stack;
    stack= ptr;
    stack->value= p;
}

pnode pop(struct sSE* stack)
{
    pnode result= stack->value;

    struct sSE* ptr= stack->next;
    free(stack);
    stack= ptr;

    return result;
}

void DrawNodes(int level, pnode root)
{
    int CurrentLevel = 0;
    pnode CurrentNode= root;

}

void DrawTree(struct node* root)
{
	int depth= GetDepth(root);
	int width= pow(2, depth) *2;
	int gap= width/3;
    int pad;
	pnode** lines;
	lines= malloc(sizeof(pnode)*depth);
	int i;
	for (i = 0; i< depth; i++)
        lines[i]= malloc(sizeof(pnode)*pow(2,i));

    lines[0][0]= root;
    char format[4]= "%4i";
    char format1[4]= "%4c";

	int count= 0;
	if (root != NULL)
    {
        pad= gap;
        if (pad>9)
        {
            gap-= 9;
            pad= 9;
        }
        else
            gap= 0;

        for (i=0;i< gap;i++)
            putc(' ', stdout);
        format[1]= '0'+pad;
        format1[1]= '0'+pad;

        for (i=0;i< gap;i++)
            putc(' ', stdout);
        printf(&format, root->value);
        printf("\n");
        for (i=1; i<depth; i++)
        {
            int j, k;

            //startpos= startpos/2;
            gap= width/(pow(2,i)+1);

            pad= gap;
            if (pad>9)
            {
                gap-= 9;
                pad= 9;
            }
            else
                gap= 0;

            for (k=0;k< gap;k++)
                putc(' ', stdout);
            format[1]= '0'+pad;
            format1[1]= '0'+pad;

            for (j=0; j<pow(2,i-1); j++)
            {
                if (lines[i-1][j]!= NULL)
                {

                    lines[i][2*j]= lines[i-1][j]->left;
                    lines[i][2*j+1]= lines[i-1][j]->right;


                    if (lines[i][2*j] != NULL)
                        printf(&format, lines[i][2*j]->value);
                    else
                        printf(&format1, '#');

                    for (k=0;k< gap;k++)
                        putc('*', stdout);

                    if (lines[i][2*j+1] != NULL)
                        printf(&format, lines[i][2*j+1]->value);
                    else
                        printf(&format1, '#');

                    for (k=0;k< gap;k++)
                        putc('*', stdout);

                }
                else
                {
                    lines[i][2*j]= NULL;
                    lines[i][2*j+1]= NULL;
                    for (k=0;k< (gap+pad+1)*2;k++)
                        putc('^', stdout);
                }

            }
            printf("\n");

        }
    }
}

//FindAll?

int main()
{
	pnode root = NewNode(1,NULL,pNone);

	NewNode(2,root,pLeft);
	NewNode(3,root,pRight);
    NewNode(0,root->right,pRight);
    NewNode(-2,root->right,pLeft);
    NewNode(-1,root->right->right,pRight);
	NewNode(4,root->left,pRight);
	NewNode(6,root->left,pLeft);
	NewNode(5,root->left->right,pRight);
	NewNode(8,root->right->right->right,pRight);
	AddByParent(root,33,3);
	AddBySibling(root,10,-1);
	AddBySibling(root,9,8);

	pnode n= FindNode(root, -2);
	printf("%i\n", n->value);

	int quit = 1;
	char input[128];

	while (!quit)
    {
        fgets(&input, 128, stdin);

        char *pos;
        if ((pos=strchr(&input, '\n')) != NULL)
        *pos = '\0';
        if ((pos=strchr(&input, '\r')) != NULL)
        *pos = '\0';

        printf("%s. %s.\n", &input, &commands[0]);
        if (strcmp(input, commands[0])==0)
            quit= 1;
    }

	//printf("%i", GetDepth(root));

	DrawTree(root);
	return(0);
}
