
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct ItemNum
{
	int num;
	struct ItemNum* next;
	struct ItemNum* prev;

} t_ItemNum;
t_ItemNum* Head;
t_ItemNum* Tail;

void logTime() {

	time_t t;
	time(&t);
	struct tm* timeInfo;
	timeInfo = localtime(&t);
	char strTime[100];
	sprintf(strTime, "[%d/%d/%d-%d:%d:%d] -", timeInfo->tm_year + 1900,
		timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);

	printf("LogEventTime: %s\n", strTime);
}

void LogEvent(char msg[100])
{
	printf("LogEvent: %s\n", msg);
}
void LogError(char msg[100])
{
	printf("LogError: %s\n", msg);
}

void LogEventVal(char msg[100], int val)
{
	char str[100];
	sprintf(str, "Item val %d : %s", val, msg);
	printf("LogEventVal: %s\n", str);
}

void ReplaceItem(t_ItemNum* item)
{
	if (item == NULL)
	{
		LogEventVal("No need to swap. No Items in list", item->num);

	}
	else if (item->next == NULL)
	{
		LogEventVal("No need to swap", item->num);

	}
	else if (item == Head && item->next == Tail)
	{
		item->next = NULL;
		item->prev = Tail;
		Tail->prev = NULL;
		Tail->next = item;
		Tail = item;
		Head = item->prev;
	}
	else if (item == Head && item->next != NULL)
	{
		item->next = item->next->next;
		item->next->prev->next = item;
		item->next->prev->prev = NULL;
		item->prev = item->next->prev;
		item->next->prev = item;
		Head = item->prev;
	}
	else if (item->next == Tail)
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
		item->next->next = item;
		item->prev = item->next;
		item->next = NULL;
		Tail = item;
	}
	else {
		// regular swap
		item->prev->next = item->next;
		item->next->prev = item->prev;
		item->next->next->prev = item;
		item->prev = item->next;
		item->next = item->next->next;
		item->prev->next = item;
	}
}



void AddItemVal(int val)
{
	t_ItemNum* newItem = malloc(sizeof(t_ItemNum));
	LogEventVal("Create new Item", val);

	newItem->num = val;
	newItem->next = NULL;

	if (Head == NULL) {
		LogEventVal("List is started now ", val);

		Head = newItem;
		Tail = newItem;
		newItem->prev = NULL;
	}
	else
	{
		LogEventVal("Val is Added  ", val);
		Tail->next = newItem;
		newItem->prev = Tail;
		Tail = newItem;
	}
}

void Sort()
{
	t_ItemNum* curr = Head;

	if (!curr) {
		LogEvent("The List is empty");
		return;
	}
	char change = 1;

	while (change != 0)
	{
		change = 0;
		while (curr != NULL)
		{
			if (curr->next != NULL && curr->num > curr->next->num)
			{
				ReplaceItem(curr);
				change++;
			}
			curr = curr->next;
		}
		curr = Head;
	}

}

void printList() {
	struct ItemNum* curr = Head;
	while (curr)
	{
		printf("%d\n", curr->num);
		curr = curr->next;
	}
}

void freeList() {

	struct ItemNum* curr = Head;
	while (Head)
	{
		curr = Head;
		Head = Head->next;
		free(curr);
	}
	Head = Tail = NULL;
}

void newRandListNsort() {
	
	int x=0;
	int num = 0 ;

	printf("choose a size for the list:");
	scanf("%d", &num);

	for (int i = 0; i < num; i++)
	{
		x= rand();
		AddItemVal(x);
	}
	Sort();
}

void 
main()
{
	logTime();
	Head = NULL;
	Tail = NULL;
	time_t t = time(NULL);
	srand(t);


#ifdef DEBUG_REPLACE_FUNCTION
	AddItemVal(1);
	AddItemVal(2);
	//	ReplaceItem(Head);
	AddItemVal(3);
	//	ReplaceItem(Head);
	AddItemVal(4);
	//	ReplaceItem(Tail);
	ReplaceItem(Tail->prev->prev);
#endif
/*
	AddItemVal(1);
	AddItemVal(100);
	AddItemVal(34);
	AddItemVal(33);
	AddItemVal(14);
	AddItemVal(1444);
	AddItemVal(-4);
	Sort();*/
	newRandListNsort();
	printList();
	freeList();
	logTime();


}
