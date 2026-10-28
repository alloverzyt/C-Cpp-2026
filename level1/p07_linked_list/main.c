#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

Node *createList(const int values[], int count) {
    Node *head = NULL;
    Node *tail = NULL;
    for (int i = 0; i < count; i++) {
        Node *node = createNode(values[i]);
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    return head;
}

void printList(const Node *head) {
    for (const Node *node = head; node != NULL; node = node->next) {
        printf("%d", node->value);
        if (node->next != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

Node *reverseList(Node *head) {
    Node *prev = NULL;
    Node *cur = head;
    while (cur != NULL) {
        Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

int findValue(const Node *head, int value, int startPos) {
    int pos = 0;
    for (const Node *node = head; node != NULL; node = node->next) {
        pos++;
        if (pos >= startPos && node->value == value) {
            return pos;
        }
    }
    return -1;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main() {
    int values[] = {3, 5, 8, 5, 1, 5, 9};
    int count = sizeof(values) / sizeof(values[0]);

    Node *head = createList(values, count);
    printf("原链表：\n");
    printList(head);

    head = reverseList(head);
    printf("反序后的链表：\n");
    printList(head);

    int firstPos = findValue(head, 5, 1);
    printf("第一个值为 5 的节点序号：%d\n", firstPos);

    int nextPos = (firstPos == -1) ? -1 : findValue(head, 5, firstPos + 1);
    printf("下一个值为 5 的节点序号：%d\n", nextPos);

    freeList(head);
    return 0;
}
