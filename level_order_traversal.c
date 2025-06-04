#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int data) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}

void printTree(struct Node* root, int level, char branch_char) {
    if (root == NULL) return;

    printTree(root->right, level + 1, '/');

    for (int i = 0; i < level * 4; i++) {
        printf(" ");
    }

    if (branch_char == '/') {
        printf("/-- %d\n", root->data);
    } 
    else if (branch_char == '\\') {
        printf("\\-- %d\n", root->data);
    }
    else {
        printf("%d\n", root->data);
    }

    printTree(root->left, level + 1, '\\');
}

void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        int nodesAtCurrentLevel = rear - front;
        for (int i = 0; i < nodesAtCurrentLevel; i++) {
            struct Node* current = queue[front++];
            printf("%d ", current->data);

            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
        printf("\n");
    }
}

void calculateLevelSumsAndAverages(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int level = 0;

    printf("\nSum and Average of Levels:\n");

    while (front < rear) {
        int nodesAtCurrentLevel = rear - front;
        int levelSum = 0;

        for (int i = 0; i < nodesAtCurrentLevel; i++) {
            struct Node* current = queue[front++];
            levelSum += current->data;

            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }

        printf("Level %d -> Sum = %d, Average = %.2f\n", level, levelSum, (double)levelSum / nodesAtCurrentLevel);
        level++;
    }
}

int main() {
    struct Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(2);
    root->left->right = newNode(7);
    root->right->left = newNode(20);

    printf("\nTree Structure:\n\n");
    printTree(root, 0, ' ');
    
    printf("\nOutput (Level Order):\n");
    levelOrderTraversal(root);

    calculateLevelSumsAndAverages(root);
    system("pause");
    return 0;
}