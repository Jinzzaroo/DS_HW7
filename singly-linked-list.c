/* 연결 리스트를 통한 노드의 insert, delete, invert 구현*/

#include <stdio.h>
#include <stdlib.h>

/* 노드의 구조 정의 (key값과 link 값) */
typedef struct Node
{
    int key;
    struct Node *link;
} listNode;

/* 헤드 노드의 정의 */
typedef struct Head
{
    struct Node *first;
} headNode;

/* 함수 리스트 */
headNode *initialize(headNode *h);  //연결 리스트 초기화
int freeList(headNode *h);          //노드 메모리 반환

int insertFirst(headNode *h, int key);
int insertNode(headNode *h, int key);
int insertLast(headNode *h, int key);

int deleteFirst(headNode *h);
int deleteNode(headNode *h, int key);
int deleteLast(headNode *h);
int invertList(headNode *h);

void printList(headNode *h);

int main()
{
    char command;
    int key;
    headNode *headnode = NULL;
    printf("\n[----- [Annotations by JinYeongKim] [2019038030] -----]\n");

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            headnode = initialize(headnode);
            break;
        case 'p':
        case 'P':
            printList(headnode);
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e':
        case 'E':
            deleteLast(headnode);
            break;
        case 'f':
        case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't':
        case 'T':
            deleteFirst(headnode);
            break;
        case 'r':
        case 'R':
            invertList(headnode);
            break;
        case 'q':
        case 'Q':
            //메모리 반환 후 종료
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* 연결 리스트 초기화 */
headNode *initialize(headNode *h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode *temp = (headNode *)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode *h)
{
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */
    listNode *p = h->first;

    listNode *prev = NULL;
    while (p != NULL)
    {
        prev = p;
        p = p->link;
        free(prev);
    }
    free(h);
    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    /* 만약 headnode만 있을 때 헤드노드 뒤에 바로 연결*/
    if (h->first == NULL)
    {
        h->first = node;
        return 0;
    }

    /* 노드의 key값을 뒤의 노드의 key값과 비교하여 삽입하고자 하는 노드의 위치 추적 */
    listNode *n = h->first;
    listNode *trail = h->first;

    /* 마지막 노드까지 비교한다. */
    while (n != NULL)
    {
        /* 삽입하려는 노드보다 더 큰 key값을 갖는 노드 n이 있을 경우 */
        if (n->key >= key)
        {
            /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 first -> node -> n */
            if (n == h->first)
            {
                h->first = node;
                node->link = n;
            }
            else
            { /* 중간이거나 마지막인 경우 trail -> node -> n*/
                node->link = n;
                trail->link = node;
            }
            return 0;
        }

        /* trail은 현재 n이 있는 노드, n은 다음 노드로 */
        trail = n;
        n = n->link;
    }

    /* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 (삽입하려는 노드의 key값이 제일 클 경우) trail -> node */
    /* n이 NULL이 될 때까지 찾았으므로 현재 trail이 가장 마지막 노드 */
    trail->link = node;
    return 0;
}

/* 키값에 관계없이 노드를 맨 마지막에 삽입 */
int insertLast(headNode *h, int key)
{
    /* 삽입하려는 노드 선언 */
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    /* 만약 아무 노드도 없을 때 바로 첫 노드로 삽입*/
    if (h->first == NULL)
    {
        h->first = node;
        return 0;
    }
    /* n을 마지막 노드까지 이동시키고 n 뒤에 node 삽입 */
    listNode *n = h->first;
    while (n->link != NULL)
    {
        n = n->link;
    }
    n->link = node;
    return 0;
}

/* 첫 노드에 삽입 */
int insertFirst(headNode *h, int key)
{

    /* 삽입 하려는 노드 선언 */
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;

    /* 삽입한 노드가 기존에 있던 첫번째 노드를 가리키게끔 하고 헤드노드가 삽입한 노드를 가리키게끔 설정 */
    node->link = h->first;
    h->first = node;

    return 0;
}

/* 노드 삭제 */
int deleteNode(headNode *h, int key)
{
    /* 만약 아무 노드도 없을 때 */
    if (h->first == NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }

    /* 삭제하고자 하는 노드를 n으로 설정 */
    listNode *n = h->first;
    listNode *trail = NULL;

    /* key를 기준으로 삭제할 노드의 위치를 찾는다 */
    while (n != NULL)
    {
        if (n->key == key)
        {
            /* 삭제하고자 하는 노드가 첫번째 노드일 때 */
            if (n == h->first)
            {
                /* 기존 헤드노드가 n을 가리키고 있던 것을 n 다음 노드를 가리키게끔 한다. */
                h->first = n->link;
            }
            else
            { /* 중간인 경우거나 마지막인 경우 기존 trail 노드가 n을 가리키고 있던 것을 n 다음 노드를 가리키게끔 한다. */
                trail->link = n->link;
            }
            /* 삭제시킨 n 노드 메모리 반환 */
            free(n);
            return 0;
        }
        trail = n;
        n = n->link;
    }

    /* 찾지 못한 경우 */
    printf("cannot find the node for key = %d\n", key);
    return 0;
}

/* list의 마지막 노드 삭제 */
int deleteLast(headNode *h)
{
    /* 만약 아무 노드도 없을 때 */
    if (h->first == NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }

    listNode *n = h->first;
    listNode *trail = NULL;

    /* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
    if (n->link == NULL)
    {
        h->first = NULL;
        free(n);
        return 0;
    }

    /* 마지막 노드까지 이동 */
    while (n->link != NULL)
    {
        trail = n;
        n = n->link;
    }

    /* 현재 마지막 n이므로 trail과 n의 연결을 끊고 n의 메모리 반환 */
    trail->link = NULL;
    free(n);

    return 0;
}

/* list의 첫번째 노드 삭제 */
int deleteFirst(headNode *h)
{
    /* 아무 노드도 없을 때 */
    if (h->first == NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }
    listNode *n = h->first;

    /*헤드 노드가 n 다음 노드를 가리키게끔 설정 후 n 노드의 메모리 반환*/
    h->first = n->link;
    free(n);

    return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h)
{
    /* 아무 노드도 없을 때 */
    if (h->first == NULL)
    {
        printf("nothing to invert...\n");
        return 0;
    }
    listNode *n = h->first;
    listNode *trail = NULL;
    listNode *middle = NULL;

    /* 서로 가리키고 있는 포인터 방향을 반대로 바꾸어 준다. */
    while (n != NULL)
    {
        trail = middle;
        middle = n;
        n = n->link;
        middle->link = trail;
    }
    /* 마지막 노드를 헤드노드가 가리키게끔 설정 */
    h->first = middle;

    return 0;
}

void printList(headNode *h)
{
    int i = 0;
    listNode *p;

    printf("\n---PRINT\n");

    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while (p != NULL)
    {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}
