/* doubly linked list */

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

//노드 구조체 선언(이중 연결 리스트를 사용하여 양방향 연결 가능하게 만듦)
typedef struct Node
{
    int key;
    struct Node *llink;
    struct Node *rlink;
} listNode;

typedef struct Head
{
    struct Node *first;
} headNode;

/* note: 여기서는 initialize는 이중포인터를 매개변수로 받는 방식을 썼는데
         그 이유는 헤드노드에 바로 주소를 넣어주는 방식의 함수이기 때문이다. */
int initialize(headNode **h);

/* note: freeList는 싱글포인터를 매개변수로 받음 */
int freeList(headNode *h);

int insertNode(headNode *h, int key);
int insertLast(headNode *h, int key);
int insertFirst(headNode *h, int key);
int deleteNode(headNode *h, int key);
int deleteLast(headNode *h);
int deleteFirst(headNode *h);
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
        printf("                     Doubly Linked  List                        \n");
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
            initialize(&headnode);
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
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

//헤드 노드에 메모리 할당
int initialize(headNode **h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (headNode *)malloc(sizeof(headNode));
    (*h)->first = NULL;
    return 1;
}

//
int freeList(headNode *h)
{
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */

    listNode *p = h->first; // 첫번째 헤드를 p로 설정
    listNode *prev = NULL;  // p의 직전 헤드를 prev로 설정

    //마지막 헤드까지 검사
    while (p != NULL)
    {
        //p노드와 prev노드를 한 노드씩 뒤로 이동하면서 노드에 할당된 메모리를 하나씩 반환한다.
        prev = p;
        p = p->rlink;
        free(prev);
    }
    free(h);    //헤드노드의 메모리 반환
    return 0;
}

//노드 프린트
void printList(headNode *h)
{
    int i = 0;
    listNode *p;

    printf("\n---PRINT\n");

    //헤드노드에 연결된 노드가 없을 때
    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;   //p를 첫 번째 노드로 설정

    //마지막 노드까지 검사
    while (p != NULL)
    {
        printf("[ [%d]=%d ] ", i, p->key);  //리스트 순서대로 노드의 키값 출력
        p = p->rlink;                       //p를 다음 노드로 이동
        i++;
    }

    printf("  items = %d\n", i);    //노드의 개수 출력
}

/**
 * list에 key에 대한 노드하나를 추가
 */
//마지막 순서에 노드 추가
int insertLast(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode));  //추가할 노드의 메모리 할당
    node->key = key;    //추가할 노드에 키값 넣어줌

    //아직은 추가할 노드가 기존 연결리스트에 연결되어 있지 않고 독립적인 상태
    node->rlink = NULL;
    node->llink = NULL;

    //헤드 노드만 있을 때 헤드 노드 다음 순서에 노드 삽입
    if (h->first == NULL)
    {
        h->first = node;
        return 0;
    }

    //헤드 노드에 연결된 노드가 있을 때 n을 첫 번째 노드로 설정
    listNode *n = h->first;

     //n이 마지막 노드가 될 때까지 이동
    while (n->rlink != NULL)
    {
        n = n->rlink;
    }

    n->rlink = node;    //n이 현재 마지막 노드이므로 n 다음 순서에 노드 삽입
    node->llink = n;    //노드와 n노드 연결(doubly-linked-list니까)
    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{
    //헤드노드밖에 없을 때 = 헤드노드에 연결된 노드가 없을 때
    if (h->first == NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }

    listNode *n = h->first; //n을 리스트의 첫번째 노드로 설정
    listNode *trail = NULL; //n 직전 노드를 trail 노드로 설정

    /* 노드가 하나만 있는 경우, 즉 first node == last node인 경우 하나만 있는 노드 n 삭제 */
    if (n->rlink == NULL)
    {
        h->first = NULL;
        free(n);
        return 0;
    }

    /* 마지막 노드까지 이동 */
    while (n->rlink != NULL)
    {
        trail = n;      //trail노드를 n노드로 이동
        n = n->rlink;   //n노드를 다음 노드로 이동
    }

    //현재 n이 마지막 노드이므로 trail노드와의 링크를 끊고 n에 대한 메모리 반환
    trail->rlink = NULL;
    free(n);

    return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{

    listNode *node = (listNode *)malloc(sizeof(listNode));  //추가할 노드에 대한 메모리 할당
    node->key = key;                                        //추가할 노드에 키값 넣어줌
    node->rlink = node->llink = NULL;                       //아직은 추가할 노드가 기존 연결리스트에 연결되어 있지 않고 독립적인 상태

    //헤드노드밖에 없을 때 헤드노드 다음에 추가할 노드 삽입
    if (h->first == NULL)
    {
        h->first = node;
        return 1;
    }

    //헤드노드에 연결된 노드가 존재할 때
    //기존의 첫번째 노드와 추가할 노드를 연결시킨다. 이 때 노드의 rlink와 기존 첫번째 노드를 링크시켜서 노드가 첫번째로 삽입되게 한다.
    node->rlink = h->first;
    node->llink = NULL;

    //헤드 노드와 첫번째 노드 사이에 노드를 삽입하고 서로 연결 시켜준다.
    listNode *p = h->first;
    p->llink = node;
    h->first = node;

    return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode *h)
{
    //헤드노드에 연결된 노드가 없을 때
    if (h->first == NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }
    
    //헤드노드에 연결된 노드가 있을 때
    //기존 첫번째 노드와 연결되어 있던 헤드노드를 두번째 노드와 연결시킴으로써 첫번째 노드에 대한 링크 삭제
    listNode *n = h->first;
    h->first = n->rlink;

    free(n);

    return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h)
{
    //헤드노드에 연결된 노드가 없을 때
    if (h->first == NULL)
    {
        printf("nothing to invert...\n");
        return 0;
    }
    
    listNode *n = h->first;     //첫번째 노드를 n으로 설정
    listNode *trail = NULL;     //n 전 전 노드를 trail로 설정
    listNode *middle = NULL;    //n과 trail 사이의 노드를 middle 로 설정

    while (n != NULL)
    {
        trail = middle;
        middle = n;
        n = n->rlink;

        //trail -> middle -> n 에서 trail <- middle <- n으로 left와 right 포인터 방향 바꿈
        middle->rlink = trail;
        middle->llink = n;
    }

    //현재 n이 null이므로 마지막 노드는 middle, middle이 첫번째 노드가 되게(헤드노드에 연결된 노드가 되게) 설정
    h->first = middle;

    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{
    listNode *node = (listNode *)malloc(sizeof(listNode));  //추가할 노드에 메모리 할당
    node->key = key;    //추가할 노드에 키값 넣어줌
    node->llink = node->rlink = NULL;

    //노드가 없으면 헤드노드 다음 순서에 삽입
    if (h->first == NULL)
    {
        h->first = node;
        return 0;
    }

    listNode *n = h->first;

    /* key를 기준으로 삽입할 위치를 찾는다 */
    while (n != NULL)
    {
        /* 삽입하려는 노드보다 더 큰 key값을 갖는 노드 n이 있을 경우 */
        if (n->key >= key)
        {
            /*  만약 더 큰 key값을 갖는 노드가 바로 첫번째에 나와버리면 */
            if (n == h->first)
            {
                insertFirst(h, key);
            }
            else
            { /* 중간이거나 마지막에 더 큰 key값을 갖는 n이 나오면 node -> n */
                node->rlink = n;
                node->llink = n->llink;
                n->llink->rlink = node;
            }
            return 0;
        }

        n = n->rlink;   //검사할 노드를 다음 노드로 이동
    }

    /* 마지막 노드까지 검사했는데 node보다 더 큰 key값을 갖는 n이 없으면, 마지막에 삽입 */
    insertLast(h, key);
    return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{

    /* 헤드노드밖에 없을 때 */
    if (h->first == NULL)
    {
        printf("nothing to delete.\n");
        return 1;
    }

    listNode *n = h->first;

    //마지막 노드까지 검사
    while (n != NULL)
    {
        //삭제하고자 하는 노드를 찾으면
        if (n->key == key)
        {
            if (n == h->first)
            { /* 그 노드가 첫번째 노드 인경우 */
                deleteFirst(h);
            }
            else if (n->rlink == NULL)
            { /* 그 노드가 마지막 노드인 경우 */
                deleteLast(h);
            }
            else
            { /* 중간인 경우 n노드의 양 링크 삭제 후 메모리 반환 */
                n->llink->rlink = n->rlink;
                n->rlink->llink = n->llink;
                free(n);
            }
            return 1;
        }

        n = n->rlink;
    }

    /* 찾지 못 한경우 */
    printf("cannot find the node for key = %d\n", key);
    return 1;
}
