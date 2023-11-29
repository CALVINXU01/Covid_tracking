#include<stdio.h>
#include<string.h>
typedef struct
{
	char name[20];
	int placesNum;
	char venue[100][100];
}userNode;

typedef struct LinkNode
{
	userNode data;
	struct LinkNode *next;
}LinkNode,*LinkList;

LinkList users;

//用户添加 
void addUser() 
{
	LinkNode* newNode = (LinkList)malloc(sizeof(LinkNode));
	printf("Please input the name of new User\n");
	scanf("%s",newNode->data.name);
	newNode->data.placesNum = 0;
	newNode->next = users->next;
	users->next =  newNode; 
	printf("Introduce succed\n");
	system("pause");
	system("cls");
} 

//增加用户去过的聚集地 
void addVenue()
{
	char inputName[20];
	printf("Please enter the user name to add the venue\n");
	scanf("%s",inputName);
	LinkNode* newNode = users;
	while (newNode->next != NULL)
	{
		if (strcmp(newNode->next->data.name, inputName) == 0)
		{
			LinkNode* now = newNode->next;
			printf("Please enter the total number of venues the user has been to\n");
			scanf("%d",&(now->data.placesNum));
			printf("Please enter the venues the user has been to in turn\n");
			for(int i = 1; i <= now->data.placesNum; i++)
			{
				scanf("%s",now->data.venue[i]);
			}
			printf("Introduce succed\n");
			return;
		}
		newNode = newNode->next;
	}
	printf("Introdice fail\n");
	system("pause");
	system("cls");
	return;
}


//删除用户 
void delUser()
{
	char inputName[10];
	printf("Please enter the name of the user to delete\n");
	scanf("%s", inputName);
	LinkNode* newNode = users;
	while (newNode->next != NULL)
	{
		if (strcmp(newNode->next->data.name, inputName) == 0)
		{
			LinkNode* temp = newNode->next;
			newNode->next = newNode->next->next;
			free(temp);
			printf("delete succed\n");
			system("pause");
			system("cls");
			return;
		}
		newNode = newNode->next;
	}
	printf("delete faild\n");
	system("pause");
	system("cls");
	return;
}


//查询有多少用户去过指定地点 
void queryUser() 
{
	char inputPlace[20];
	printf("Please enter a venue\n");
	scanf("%s", inputPlace);
	LinkNode* newNode = users;
	while (newNode->next != NULL)
	{
		for(int i = 1; i <= newNode->next->data.placesNum; i++)
		{
			if (strcmp(newNode->next->data.venue[i], inputPlace) == 0)
			{
				printf("%s\n",newNode->next->data.name);
				break;
			}
		}
		newNode = newNode->next;
	}
	printf("The above list has been to %s\n",inputPlace);
	system("pause");
	system("cls");
}


//检索文件 
void readFile()
{
	FILE *fp1 = NULL;
	fflush(stdin);
	fp1 = fopen("users.txt", "r");
	while (1)
	{

		LinkNode* newNode = (LinkList)malloc(sizeof(LinkNode));
		int flag = fscanf(fp1,"%s %d",newNode->data.name,&(newNode->data.placesNum));
		for(int i = 1; i <= newNode->data.placesNum; i++)
		{
			flag = fscanf(fp1,"%s",newNode->data.venue[i]);
		}
		newNode->next = users->next;
		users->next = newNode;
		if(flag == EOF)
		{
			break;
		}
	}
	fclose(fp1);
	printf("Retrieve data succed\n");
	system("pause");
	system("cls");
}


//保存文件 
void writeUser()
{
	FILE *fp1 = NULL;
	fflush(stdin);
	fp1 = fopen("users.txt", "a");
	LinkNode* newNode = users;
	while (newNode->next != NULL)
	{
		fprintf(fp1, "%s %d ", newNode->next->data.name, newNode->next->data.placesNum);
		for(int i = 1; i <= newNode->next->data.placesNum; i++)
		{
			fprintf(fp1,"%s ",newNode->next->data.venue[i]);
		}
		fprintf(fp1,"\n");
		newNode = newNode->next;
	}
	fclose(fp1);
	printf("save succed\n");
	system("pause");
	system("cls");
}


int main(int argc, char **argv)
{

	printf("listMenu\n");
	int inputSelect;
	users = (LinkList)malloc(sizeof(LinkNode));
	users->next = NULL;
	while(1)
	{
		printf("1.Introduce  user\n");
		printf("2.Introduce visit to venue\n");
		printf("3.Remove user\n");
		printf("4.Check which users have been in a particular place\n") ;
		printf("5.Save to file\n");
		printf("6.Retrieve data from file\n");
		printf("7.Exit\n");
		printf("Please enter the corresponding number to perform the corresponding function\n");
		scanf("%d",&inputSelect);
		switch(inputSelect) 
		{
			case 1:
				addUser();
			break;
			case 2:
				addVenue();
			break;
			case 3:
				delUser();
			break;
			case 4:
				queryUser();
			break;
			case 5:
				writeUser();
			break;
			case 6:
				readFile();
			break;
			case 7:
				return 0;
			break;
		}
		system("pause");
		system("cls");
	}



	
	
	
	
	
	return 0;
 } 
