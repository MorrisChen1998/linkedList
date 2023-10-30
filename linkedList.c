#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node* next;
};

typedef struct node Node;

//return head
Node* createLinkedList(int num_nodes) {
	if (num_nodes < 1) {
		printf("number of nodes must to >= 1.\n\n");
		return NULL;
	}

	Node* head, * now, * previous;
	now = (Node*)malloc(sizeof(Node));
	now->value = 0;
	now->next = NULL;
	head = now;
	previous = now;

	for (int i = 1; i < num_nodes; i++)
	{
		now = (Node*)malloc(sizeof(Node));
		now->value = i;
		previous->next = now;
		now->next = NULL;
		previous = now;
	}
	return head;
}

void traverseLinkedList(Node* head) {
	if (head == NULL) {
		printf("It's an empty list, nothing for traverse.\n\n");
		return;
	}
	Node* now = head;
	int nodes_count = 0;
	while (now != NULL) {
		printf("Node #%d: ", nodes_count++);
		printf("address=0x%p, ", now);
		printf("value=%d, ", now->value);
		printf("next=0x%p\n", now->next);
		now = now->next;
	}
	printf("Traversal finished!\n\n");
}

void deleteLinkedList(Node* head) {
	Node* now = head, *tmp;
	while (now!=NULL) {
		tmp = now->next;
		free(now);
		now = tmp;
	}
	head = NULL;
	printf("deletion finished!\n\n");
}

//return new head
Node* insertNode(Node* head, int index, int value) {
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = NULL;

	if (index == 0) {
		newNode->next = head;
		return newNode;
	}
	
	Node* now = head;

	if (index == -1) {
		while (now->next != NULL) {
			now = now->next;
		}
		now->next = newNode;
		return head;
	}

	int count = 0;
	while (now->next != NULL && count<index-1) {
		now = now->next;
		count++;
	}
	Node* tmp = now->next;
	now->next = newNode;
	newNode->next = tmp;
	return head;
}

//return new head
Node* deleteNodebyIndex(Node* head, int index) {
	Node* now = head, * tmp = head;
	
	if (index == 0) {
		tmp = now->next;
		free(now);
		return tmp;
	}

	if (index == -1) {
		while (now->next != NULL) {
			tmp = now;
			now = now->next;
		}
		free(now);
		tmp->next = NULL;
		return head;
	}

	int count = 0;
	while (now->next != NULL && count < index-1) {
		tmp = now;
		now = now->next;
		count++;
	}
	tmp->next = now->next;
	free(now);
	return head;
}

//return new head
Node* deleteNodebyValue(Node* head, int value) {
	Node* now = head, * tmp = head;
	int head_flag = 1;
	while (now != NULL) {
		if (now->value == value) {
			if (head_flag == 1) {
				tmp = now->next;
				free(now); 
				now = tmp;
				head = now;
			}
			else {
				tmp->next = now->next;
				free(now);
				now = tmp;
			}
		}
		else {
			head_flag = 0;
			tmp = now;
			now = now->next;
		}
	}
	return head;
}

//return new head
Node* reverseLinkedList(Node* head) {
	if (head == NULL) {
		printf("It's an empty list.\n\n");
		return NULL;
	}
	Node* now = head, * next = head->next, * prev = NULL;

	while (next != NULL) {
		now->next = prev;
		prev = now;
		now = next;
		next = next->next;
	}
	now->next = prev;
	return now;
}

int main()
{
	int num_nodes = 10;
	//printf("How many Nodes:\n");
	//scanf_s("%d", &num_nodes);

	Node* head = createLinkedList(num_nodes);
	traverseLinkedList(head);
	
	head = insertNode(head, 0, -1);
	head = insertNode(head, 5, -1);
	head = insertNode(head, -1, -1);
	traverseLinkedList(head);

	//head = deleteNodebyIndex(head, 0);
	//head = deleteNodebyIndex(head, 5);
	//head = deleteNodebyIndex(head, -1);
	//traverseLinkedList(head);

	head = deleteNodebyValue(head, -1);
	traverseLinkedList(head);

	head = reverseLinkedList(head);
	traverseLinkedList(head);

	deleteLinkedList(head);
	return 0;
}

