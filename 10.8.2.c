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
}*max = NULL, *min = NULL;

//элемент очереди
struct queue {
    int data;
    struct Node *node;
    struct queue *next;
    struct Node* spisokNode;
}*rear = NULL, *front = NULL;

void Type_Initialization( TypeOperation* type){
    type->enqueue = (char*)malloc(7* sizeof(char));
    type->enqueue = "enqueue";

    type->dequeue = (char*)malloc(7* sizeof(char));
    type->dequeue = "dequeue";

    type->min =(char*)malloc(4* sizeof(char));
    type->min = "min\0";

    type->max = (char*)malloc(4* sizeof(char));
    type->max = "max";
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
    node->next = NULL;
    node->prev = NULL;
    max = node;
    min = node;
    return node;
}

struct Node* addSpNode (int data){
    struct Node* node = (struct Node*)malloc(sizeof (struct Node));
    int* tempData = (int*)malloc(sizeof (int));
    node->value = data;

    if (node->value <= min->value ){
        min->prev = node;
        node->next = min;
        node->prev = NULL;
        min = node;
    }
    else if (node->value >= max->value){
        max->next = node;
        node->next = NULL;
        node->prev = max;
        max = node;
    }
    else{
        struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
        temp = min;
        while (temp->value < node->value){
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    return node;
}

void deleteSpisok (struct Node** node){
    if ((*node)->prev == NULL){
        min = (*node)->next;
    }
    if((*node)->next == NULL){
        max = (*node)->prev;
    }
    if ((*node)->prev != NULL) {
        ((*node)->prev)->next = (*node)->next;
    }
    if ((*node)->next != NULL) {
        ((*node)->next)->prev = (*node)->prev;
    }
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
    printf("%d\n",min->value);
}

void myMax(){
    printf("%d\n",max->value);
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
    fclose(stdin);
    fclose(stdout);
}