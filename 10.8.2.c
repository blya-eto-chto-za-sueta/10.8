#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TypeOperation{
    char* enqueue;
    char* dequeue;
    char* min;
    char* max;
}TypeOperation ;

// узел двусзявного списка для отслеживания максимального и минимального элемментов
struct Node{
    int value;
    struct Node* next;
    struct Node* prev;
}*head ;

//элемент очереди
struct queue {
    int data;
    struct Node *node;
    struct queue *next;
    struct Node* spisokNode;
}*rear = NULL, *front = NULL;

void Type_Initialization( TypeOperation* type){
    type->enqueue = (char*)malloc(8* sizeof(char));
    strcpy(type->enqueue, "enqueue");

    type->dequeue = (char*)malloc(8* sizeof(char));
    strcpy(type->dequeue, "dequeue");

    type->min =(char*)malloc(4* sizeof(char));
    strcpy(type->min, "min");

    type->max = (char*)malloc(4* sizeof(char));
    strcpy(type->max, "max");
}

struct queue* newQNode (int meaning){
    struct queue* queueNode = (struct queue*)malloc(sizeof (struct queue));
    queueNode->data = meaning;
    queueNode->next = NULL;
    return queueNode;
}

struct Node* newSpNode (int data){
    struct Node* node = (struct Node*)malloc(sizeof (struct Node));
    node->value = data;
    node->next = head;
    node->prev = head;
    head->next = node;
    head->prev = node;
    return node;
}

struct Node* addSpNode (int data){
    struct Node* node = (struct Node*)malloc(sizeof (struct Node));
    node->value = data;

    if (node->value <= head->next->value ){
        head->next->prev = node;
        node->next = head->next;
        node->prev = head;
        head->next = node;
    }
    else if (node->value >= head->prev->value){
        head->prev->next = node;
        node->next = head;
        node->prev = head->prev;
        head->prev = node;
    }
    else{
        struct Node* temp;
        temp = head->next;
        while (temp->value < node->value){
            temp = temp->next;
        }
        temp->prev->next = node;
        node->next = temp;
        node->prev = temp->prev;
        temp->prev = node;
    }
    return node;
}

void deleteSpisok (struct Node** node){
    ((*node)->prev)->next = (*node)->next;
    ((*node)->next)->prev = (*node)->prev;
    free(*node);
    *node = NULL;
}


void enqueue (int meaning){
    struct queue* queueNode = newQNode(meaning);
    if (front == NULL){
        front = queueNode;
        rear = queueNode;
        queueNode->spisokNode = newSpNode(queueNode->data);

    }
    else {
        rear->next = queueNode;
        rear = queueNode;
        queueNode->spisokNode = addSpNode(queueNode->data);
    }
}

int dequeue (){
    struct queue* temp = front;
    front = front->next;
    int item = temp->data;
    deleteSpisok(&temp->spisokNode);
    free(temp);
    return item;
}

void myMin(){
    printf("%d\n",head->next->value);
}

void myMax(){
    printf("%d\n",head->prev->value);
}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    TypeOperation typeOperation ;
    Type_Initialization(&typeOperation);

    int N;// number of queue operations
    scanf("%d",&N);

    for (int i=0; i<N; i++){
        char* operation = (char*)malloc(9 *sizeof (char));
        scanf("%s",operation);

        if ( strcmp (operation, typeOperation.enqueue)==0 ){
            int meaning;
            scanf("%d",&meaning);
            enqueue(meaning);

        }
        else if ( strcmp (operation, typeOperation.dequeue)==0 ){
            int res = dequeue();
            printf("%d\n",res);

        }
        else if ( strcmp (operation, typeOperation.min)==0 ){
            myMin();

        }
        else if ( strcmp (operation, typeOperation.max)==0 ){
            myMax();

        }
    }
    return 0;
}
