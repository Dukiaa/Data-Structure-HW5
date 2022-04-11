#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ); //Queue를 비우는 함수
int isEmpty(QueueType *cQ); //Queue가 비어있을때 문구 출력하는 함수
int isFull(QueueType *cQ); //Queue가 가득 차있을때 문구 출력하는 함수
void enQueue(QueueType *cQ, element item); //Queue에 데이터를 삽입하는 함수
void deQueue(QueueType *cQ, element* item); //Queue에 데이터를 삭제하는 함수
void printQ(QueueType *cQ); //Queue를 출력하는 함수
void debugQ(QueueType *cQ); //Queue를 디버그하는 함수
element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

    printf("[----- [조정동] [2017015041] -----]\n");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { //switch-case문으로 입력값을 받아 수행
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0; //front를 0으로 설정
	cQ->rear = 0; //rear를 0으로 설정
	return cQ;
}

int freeQueue(QueueType *cQ) //Queue를 초기화 하는 함수
{
    if(cQ == NULL) return 1; //cQ가 Null값이면 free시킨다
    free(cQ);
    return 1;
}

element getElement() //문자를 입력받는 함수
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ) //Queue가 비어있을경우 문구 출력
{
	if (cQ->front == cQ->rear){ //front 와 rear가 같을경우 = Queue가 비어있는 경우
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ) //Queue가 가득 차있는경우 문구 출력
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) //Queue에 데이터 삽입
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //Max Queue size로 나눈 나머지 값 = rear로 설정
		cQ->queue[cQ->rear] = item; //item값으로 만듬
	}
}

void deQueue(QueueType *cQ, element *item) //Queue에 데이터 삭제
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ) //Queue 출력
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first값은 front로 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last값은 rear로

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //Queue를 디버그하는 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}