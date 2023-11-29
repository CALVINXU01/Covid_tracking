#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HEIGHT(p)    ( (p==NULL) ? -1 : (((AVLNode *)(p))->height) )
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )
typedef struct
{
	char name[20];
	int placesNum;
	char venue[100][100];
}userNode;

typedef struct userTree 
{
	userNode data;
	struct userTree* left;
	struct userTree* right;
	
 int height;
}AVLNode, *AVLTree;


void inorder_avltree(AVLTree tree)
{
	if(tree != NULL)
	 {
	 inorder_avltree(tree->left);
	 inorder_avltree(tree->right);
	 }

}

/*
 * (递归实现)查找"AVL树x"中键值为key的节点
 */
AVLNode* avltree_search(AVLTree x, userNode key)
{
 if (x==NULL || (strcmp(x->data.name,key.name) == 0))
 return x;
 if (strcmp(key.name,x->data.name) < 0)
 return avltree_search(x->left, key);
 else
 return avltree_search(x->right, key);
}

//查找最小结点：返回tree为根结点的AVL树的最小结点。
AVLNode* avltree_minimum(AVLTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

// 查找最大结点：返回tree为根结点的AVL树的最大结点。
AVLNode* avltree_maximum(AVLTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
static AVLNode* left_left_rotation(AVLTree k2)
{
    AVLTree k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = MAX( HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height = MAX( HEIGHT(k1->left), k2->height) + 1;

    return k1;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
static AVLNode* right_right_rotation(AVLTree k1)
{
    AVLTree k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = MAX( HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
    k2->height = MAX( HEIGHT(k2->right), k1->height) + 1;

    return k2;
}

/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
static AVLNode* left_right_rotation(AVLTree k3)
{
    k3->left = right_right_rotation(k3->left);

    return left_left_rotation(k3);
}

/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
static AVLNode* right_left_rotation(AVLTree k1)
{
    k1->right = left_left_rotation(k1->right);

    return right_right_rotation(k1);
}

/*
 * 创建AVL树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     left 是左孩子。
 *     right 是右孩子。
 */
static AVLNode* avltree_create_node(userNode key, AVLNode *left, AVLNode* right)
{
    AVLNode* p;

    if ((p = (AVLNode *)malloc(sizeof(AVLNode))) == NULL)
        return NULL;
    p->data = key;
    p->height = 0;
    p->left = left;
    p->right = right;

    return p;
}

/*
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
AVLNode* avltree_insert(AVLTree tree, userNode key)
{
    if (tree == NULL)
    {
        tree = avltree_create_node(key, NULL, NULL);
        if (tree==NULL)
        {
            return NULL;
        }
    }
    else if(strcmp(key.name,tree->data.name) < 0)
    {
        tree->left = avltree_insert(tree->left, key);
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            if (strcmp(key.name,tree->left->data.name) < 0)
                tree = left_left_rotation(tree);
            else
                tree = left_right_rotation(tree);
        }
    }
    else if (strcmp(key.name,tree->data.name) > 0)
    {
        tree->right = avltree_insert(tree->right, key);

        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            if (strcmp(key.name,tree->right->data.name) > 0)
                tree = right_right_rotation(tree);
            else
                tree = right_left_rotation(tree);
        }
    }

    tree->height = MAX( HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

    return tree;
}

/* 
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     ptree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
static AVLNode* delete_node(AVLTree tree, AVLNode *z)
{
  // 根为空 或者 没有要删除的节点，直接返回NULL。
 if (tree==NULL || z==NULL)
 return NULL;
 if(strcmp(z->data.name,tree->data.name) < 0)// 待删除的节点在"tree的左子树"中
 {
        tree->left = delete_node(tree->left, z);
  // 删除节点后，若AVL树失去平衡，则进行相应的调节。
 if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
 {
            AVLNode *r =  tree->right;
 if (HEIGHT(r->left) > HEIGHT(r->right))
                tree = right_left_rotation(tree);
 else
                tree = right_right_rotation(tree);
 }
 }
 else if (strcmp(z->data.name,tree->data.name) > 0)// 待删除的节点在"tree的右子树"中
 {
        tree->right = delete_node(tree->right, z);
	  // 删除节点后，若AVL树失去平衡，则进行相应的调节。
	 if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
	 {
	            AVLNode *l =  tree->left;
	 if (HEIGHT(l->right) > HEIGHT(l->left))
	                tree = left_right_rotation(tree);
	 else
	                tree = left_left_rotation(tree);
	 }
 }
 else  // tree是对应要删除的节点。
 {
  // tree的左右孩子都非空
 if ((tree->left) && (tree->right))
 {
	 if (HEIGHT(tree->left) > HEIGHT(tree->right))
	 {
	  // 如果tree的左子树比右子树高；
	  // 则(01)找出tree的左子树中的最大节点
	  //   (02)将该最大节点的值赋值给tree。
	  //   (03)删除该最大节点。
	  // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
	  // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
	                AVLNode *max = avltree_maximum(tree->left);
	                tree->data = max->data;
	                tree->left = delete_node(tree->left, max);
	 }
	 else
	 {
	  // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
	  // 则(01)找出tree的右子树中的最小节点
	  //   (02)将该最小节点的值赋值给tree。
	  //   (03)删除该最小节点。
	  // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
	  // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
	                AVLNode *min = avltree_maximum(tree->right);
	                tree->data = min->data;
	                tree->right = delete_node(tree->right, min);
	 }
 }
	 else
	 {
	            AVLNode *tmp = tree;
	            tree = tree->left ? tree->left : tree->right;
	 			free(tmp);
	 }
 }
 return tree;
}


/*
 * 删除结点(key是节点值)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 待删除的结点的键值
 * 返回值：
 *     根节点
 */
AVLNode* avltree_delete(AVLTree tree, userNode key)
{
    AVLNode *z;

    if ((z = avltree_search(tree, key)) != NULL)
    {
    	tree = delete_node(tree, z);
    	printf("delete succed\n");
	}
	else
	{
		printf("delete fail\n");
	}
        
    return tree;
}

/*
 * 销毁AVL树
 */
void destroy_avltree(AVLTree tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy_avltree(tree->left);
    if (tree->right != NULL)
        destroy_avltree(tree->right);

    free(tree);
}

AVLNode* addUserByAVL(AVLTree tree) //用户添加 
{
	userNode data;
	printf("Please input the name of new User\n");
	scanf("%s",data.name);
	data.placesNum = 0;
	printf("Please enter the total number of venues the user has been to\n");
	printf("%d\n",&(data.placesNum));
	printf("Please enter the venues the user has been to in turn\n");
	for(int i = 1; i <= data.placesNum; i++)
	{
		scanf("%s",data.venue[i]);
	}
	tree= avltree_insert(tree,data);
	printf("Introduce succed\n");
	system("pause");
	system("cls");
	return tree;
} 

AVLNode* delUserByAVL(AVLTree tree)   //用户删除通过avl 
{
	userNode data;
	printf("Please enter the name of the user to delete\n");
	scanf("%s", data.name);
	tree = avltree_delete(tree,data);
	system("pause");
	system("cls");
	return tree;
}

void findPlace(AVLTree tree,char* placeName)
{
 if(tree != NULL)
 {
	 findPlace(tree->left,placeName);
	 for(int i = 1; i <= tree->data.placesNum; i++)
	 {
 		if (strcmp(tree->data.venue[i], placeName) == 0)
		{
			printf("%s\n",tree->data.name);
			break;
		}
	 }
	 findPlace(tree->right,placeName);
 }
}
void queryUserByAVL(AVLTree tree) 
{
	char inputPlace[20];
	printf("Please enter a venue\n");
	scanf("%s", inputPlace);
	findPlace(tree,inputPlace);
	printf("The above list has been to %s\n",inputPlace);
	system("pause");
	system("cls");
}


void saveAVL(AVLTree tree,FILE *fp1)
{
 if(tree != NULL)
 {
	 saveAVL(tree->left,fp1);
   	fprintf(fp1, "%s %d ", tree->data.name, tree->data.placesNum);
	for(int i = 1; i <= tree->data.placesNum; i++)
	{
		fprintf(fp1,"%s ",tree->data.venue[i]);
	}
	fprintf(fp1,"\n");
	 saveAVL(tree->right,fp1);
 }
}
void writeFileByAVL(AVLTree tree)
{
	FILE *fp1 = NULL;
	fflush(stdin);
	fp1 = fopen("users.txt", "a");
	saveAVL(tree,fp1);
	fclose(fp1);
	printf("save succed\n");
	system("pause");
	system("cls");
}

AVLNode* readFileByAVL(AVLTree tree)
{
	FILE *fp1 = NULL;
	fflush(stdin);
	fp1 = fopen ("users.txt", "r");
	while (1)
	{

		userNode data;
		int flag = fscanf(fp1,"%s %d",data.name,&(data.placesNum));
		for(int i = 1; i <= data.placesNum; i++)
		{
			flag = fscanf(fp1,"%s",data.venue[i]);
		}
		tree = avltree_insert(tree,data);
		if(flag == EOF)
		{
			break;
		}
	}
	fclose(fp1);
	printf("Retrieve data succed\n");
	system("pause");
	system("cls");
	return tree;
}
//---------------------------avl------------------------------------- 

int main(int argc, char **argv)
{

	printf("avlMenu\n");
	int inputSelect;
	AVLTree root=NULL;
	while(1)
	{
		printf("1.Introduce  user\n");
		printf("2.Remove user\n");
		printf("3.Check which users have been in a particular place\n") ;
		printf("4.Save to file\n");
		printf("5.Retrieve data from file\n");
		printf("6.Exit\n");
		printf("Please enter the corresponding number to perform the corresponding function\n");
		scanf("%d",&inputSelect);
		switch(inputSelect) 
		{
			case 1:
				root = addUserByAVL(root);
			break;
			case 2:
				root = delUserByAVL(root);
			break;
			case 3:
				queryUserByAVL(root);
			break;
			case 4:
				writeFileByAVL(root);
			break;
			case 5:
				root = readFileByAVL(root);
			break;
			case 6:
				return 0;
			break;
		}
		system("pause");
		system("cls");
	}


	
	
	
	
	
	return 0;
 } 
