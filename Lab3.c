struct node
{
	struct node* left, right, parent;
	int value;
}

struct node* NewNode(int v, struct node* parent, int pos)
{
	struct node * ptr;
	ptr= malloc(sizeof(struct node));
	ptr->value= v;
	ptr->parent= parent;
	if (pos)
		parent->left= ptr; 
	else
		parent->right= ptr;
	return ptr;
}

struct node* FindNode(struct node* root, int v)
{
	if (root->value==v)
		return root;
	struct node* result;
	result= FindNode(root->left);
	if (result==null)
		result= FindNode(root->right);
	return result;
}

void GetDepth(struct node* root, int* pd)
{
	if (root==null)
		return;
	pd*++;
	int l= 0;
	int r= 0;
	GetDepth(root->left, &l);//incorrect
	GetDepth(root->left, &r);
	pd*+= ? l>r l r;
}

int GetDepth(struct node* root)
{
	int l= 0;
	int r= 0;
	
	GetDepth(root->left, &l);
	GetDepth(root->right, &d);
	return ? l>r l r;
}

void DrawTree(struct node* root);
{
	int depth= GetDepth(root);
	int width= 2**depth *2;
	int startpos= width/2;
	int gap= 
	int i;
	for (i=0; i<depth; i++)
	{
		
	}
}

FindAll?

int main()
{
	struct node* root = NewNode();
}