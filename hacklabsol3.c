#include <stdio.h>
#include <stdlib.h>

// Defining the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to add a new node at the beginning of the list
void addNode(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to delete a node at a given position
void deleteNodeAtPosition(struct Node** head_ref, int position) {
    if (*head_ref == NULL)
        return;

    struct Node* temp = *head_ref;

    if (position == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

// Function to delete all nodes containing a specific data
void deleteNodesByData(struct Node** head_ref, int key) {
    struct Node* temp = *head_ref, *prev = NULL;

    while (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        temp = *head_ref;
    }

    while (temp != NULL) {
        while (temp != NULL && temp->data != key) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;

        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

// Function to delete all nodes containing a specific data and the subsequent node
void deleteNodesByDataAndNext(struct Node** head_ref, int key) {
    struct Node* temp = *head_ref, *prev = NULL;

    while (temp != NULL && temp->data == key) {
        if (temp->next != NULL) {
            struct Node* nextNode = temp->next;
            *head_ref = nextNode->next;
            free(temp);
            free(nextNode);
            temp = *head_ref;
        } else {
            *head_ref = temp->next;
            free(temp);
            temp = *head_ref;
        }
    }

    while (temp != NULL) {
        while (temp != NULL && temp->data != key) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;

        if (temp->next != NULL) {
            struct Node* nextNode = temp->next;
            prev->next = nextNode->next;
            free(temp);
            free(nextNode);
            temp = prev->next;
        } else {
            prev->next = temp->next;
            free(temp);
            temp = prev->next;
        }
    }
}

// Function to delete the complete linked list
void deleteLinkedList(struct Node** head_ref) {
    struct Node* current = *head_ref;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = NULL;
}

// Function to display the linked list
void displayList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to display the inverted linked list (without modifying the original list)
void displayInvertedList(struct Node* head) {
    if (head == NULL)
        return;

    displayInvertedList(head->next);
    printf("%d -> ", head->data);
}

// Function to calculate and display the total memory space occupied by the linked list
void displayTotalMemorySpace(struct Node* node) {
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    printf("Total memory space occupied by the linked list: %lu bytes\n", count * sizeof(struct Node));
}

int main() {
    struct Node* head = NULL;

    addNode(&head, 5);
    addNode(&head, 4);
    addNode(&head, 3);
    addNode(&head, 2);
    addNode(&head, 1);
    addNode(&head, 5);
    addNode(&head, 5);

    printf("Original List: ");
    displayList(head);

    deleteNodeAtPosition(&head, 3);
    printf("After Deleting Node at Position 3: ");
    displayList(head);

    deleteNodesByData(&head, 5);
    printf("After Deleting All Nodes with Data 5: ");
    displayList(head);

    addNode(&head, 5);
    addNode(&head, 6);
    addNode(&head, 5);
    printf("List after adding some nodes with data 5: ");
    displayList(head);

    deleteNodesByDataAndNext(&head, 5);
    printf("After Deleting Nodes with Data 5 and Subsequent Nodes: ");
    displayList(head);

    printf("Inverted List: ");
    displayInvertedList(head);
    printf("NULL\n");

    displayTotalMemorySpace(head);

    deleteLinkedList(&head);
    printf("After Deleting Complete Linked List: ");
    displayList(head);

    return 0;
}
