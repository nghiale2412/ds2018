#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct keyvalues{
    char* key;
    char* value;
}keyvalue;

typedef struct lists{
    keyvalue kv;
    struct lists *next;   
}node;

typedef struct listDetail{
    int size;
    node *head;
}listdetail;

void init(listdetail *ld){
    ld->size = 0;
    ld->head = NULL;
}

node* initNode(keyvalue kvTemp){
    node* l = (node *) malloc(sizeof(node));
    l->kv = kvTemp;
    return l;
}

int isEmpty(listdetail *l){
    if (l->size == 0)
        return 1;
    else return 0;
}

void insert(node *listNew, listdetail *l){
    node *pTemp = l->head;
    int i = 0;
    int temp=0;
    for (i = 0; i < l->size; i++)
    {
        if (pTemp->kv.key == listNew->kv.key)
        {
            temp = 1;
        }
    }
    printf("%d\n", temp);

    listNew->next = l->head;
    l->head = listNew;
    l->size++;
}

void delete(listdetail *l, char *keyTemp){
    node *pTemp;
    pTemp = l->head;
    if (pTemp->kv.key == keyTemp)
    {
        l->head = pTemp->next;
        free(pTemp);
        l->size--;
        return;
    }

    node *q = pTemp->next;
    int cnt = 1;
    while((pTemp->kv.key != keyTemp)&&(cnt<l->size)){
        q = pTemp;
        pTemp = pTemp->next;        
    }
    if (pTemp!=NULL)
    {
        q->next = pTemp->next;
        l->size--;
        free(pTemp);
    }
}

void testString(char* a,char *b){
	printf("%d\n", strcmp(a,b));
}

int main(int argc, char const *argv[])
{

	listdetail ld;
	// printf("asdads\n");
	init(&ld);
	node *newNode;

	keyvalue kv;
	kv.key = "this is key";

	kv.value = "this is value";
	newNode = initNode(kv);
	insert(newNode,&ld);

	keyvalue kv2;
	kv2.key = "this is key2";

	kv2.value = "this is value2";
	
	newNode = initNode(kv2);
	
	insert(newNode,&ld);
	int i=0;
	node *nodeTemp = ld.head;
	printf("%d\n", ld.size);
	char *str;
	str = "this is key";
	delete(&ld,str);
	printf("%d\n", ld.size);
	for ( i = 0; i < ld.size; ++i)
	{

		printf("%s\n", nodeTemp->kv.key);
		printf("%s\n", nodeTemp->kv.value);	
		nodeTemp = nodeTemp->next;
	}
	return 0;
}