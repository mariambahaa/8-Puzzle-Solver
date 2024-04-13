#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *data;
    struct Node *left;
    struct Node *right;

} Node;

Node* newNode(char *data);
Node *insert(Node *root, char *data);
Node *search(Node *root, char *data);
Node *searchNew(Node *root, char *data);
int max(int x, int y);
int height(Node *root);
int count(Node *root);
Node *minNode(Node *root);
Node *maxNode(Node *root);
Node *successor(Node *root, Node *newN);
Node *predecessor(Node *root, Node* newN);

Node* newNode(char *data)
{
    Node *n = malloc(sizeof(Node));
    n -> data = malloc(200);
    strcpy(n -> data, data);
    n -> left = NULL;
    n -> right = NULL;
    return n;
}

Node *insert(Node *root, char *data)
{
    if(root == NULL)
        return newNode(data);
    if(strcasecmp(data, root -> data) == 1)
        root -> right = insert(root -> right, data);
    else if(strcasecmp(data, root -> data) == -1)
        root -> left = insert(root -> left, data);
    return root;
}

Node *search(Node *root, char *data)
{
    if (root == NULL ||  strcasecmp(data, root->data) ==0)
        return root;

    if (strcasecmp(data, root->data) == 1)
        return search(root->right, data);

    return search(root->left, data);
}

Node *searchNew(Node *root, char *data)
{
    if(root == NULL)
        return NULL;
    else
    {
        while(root != NULL)
        {
            if(strcasecmp(data, root -> data) == 1)
            {
                if(root -> right != NULL)
                    root = root -> right;
                else
                    return root;
            }
            else
            {
                if(root -> left != NULL)
                    root = root -> left;
                else
                    return root;
            }
        }
    }
}

Node *minNode(Node *root)
{
    if(root -> left == NULL)
        return root;
    else
    {
        while(root -> left != NULL)
        {
            root = root -> left;
        }
        return root;
    }
}

Node *maxNode(Node *root)
{
    if(root -> right == NULL)
        return root;
    else if(root->right!=NULL)
        return maxNode(root->right);
    else
        return root;
}


Node *successor(Node *root, Node *newN)
{
    Node *s = NULL;

    if(newN -> right != NULL)
    {
        return minNode(newN -> right);
    }
    else
    {
        while(root != NULL)
        {
            if(strcasecmp(newN->data, root -> data) == -1)
            {
                s = root;
                root = root -> left;
            }
            else if(strcasecmp(newN->data, root -> data) == 1)
            {
                root = root -> right;
            }
            else
                break;
        }
        return s;
    }
}

Node *predecessor(Node *root, Node *newN)
{
    Node *s = NULL;

    if(newN ->left !=NULL)
    {
        return maxNode(newN-> left);
    }
    else
    {
        while(root != NULL)
        {
            if(strcasecmp(newN->data, root -> data) == 1)
            {
                s = root;
                root = root -> right;
            }
            else if (strcasecmp(newN->data, root -> data) == -1)
            {
                root = root -> left;
            }
            else
                break;
        }
    }
    return s;
}

int max(int x,int y )
{
    return x>y?x:y;
}

int height(Node* root)
{
    if(root==NULL)
        return -1;
    else
        return 1+max(height(root->left),height(root->right));

}

int count(Node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1+count(root->left)+count(root->right);

}

int main()
{
    Node *root = NULL;
    Node *searchWord = NULL;
    Node *searchWordNew;
    Node *successorWord;
    Node *predecessorWord;

    FILE *f=fopen("EN-US-Dictionary.txt","r");
    char line[200];

    if (f == NULL)
    {
        printf("Could not open file");
    }
    else
    {
        fscanf(f,"%[^\n]",line);
        root = insert(root, line);
        fscanf(f,"\n");
        while(fgets(line, 200, f)!=NULL)
        {
            line[strlen(line)-1]='\0';
            root = insert(root, line);
        }
    }
    fclose(f);

    printf("Dictionary Loaded Successfully....!\n");
    printf(".......................\n");
    printf("Size = %d\n", count(root));
    printf(".......................\n");
    printf("Height = %d\n", height(root));
    printf(".......................\n");

    printf("Enter sentence : \n");
    char sentence[300];
    gets(sentence);

    char *token = strtok(sentence, " ");
    while(token != NULL)
    {
        searchWord = search(root, token);
        if(searchWord != NULL)
        {
            printf("%s - CORRECT\n", searchWord -> data);
        }
        else
        {
            printf("%s - Incorrect, ", token);
            searchWordNew = searchNew(root, token);
            printf("Suggestions : ");
            printf(" %s ", searchWordNew -> data);
            successorWord = successor(root, searchWordNew);
            if(successorWord!=NULL)
                printf(" %s ", successorWord -> data);
            else
                printf("NO SUCCESSOR!\n");
            predecessorWord = predecessor(root, searchWordNew);
            if(predecessorWord!=NULL)
                printf(" %s  \n", predecessorWord -> data);
            else
                printf("NO PREDECESSOR!\n");

        }
        token = strtok(NULL, " ");
    }

    return 0;
}
