#include <stdio.h>
#include <stdlib.h>
#define SUCC 0
#define ERR 1

struct _tree;
typedef struct _tree *pos;
typedef struct _tree {
	int el;
	pos left;
	pos right;
}_TREE;

pos createNew();
pos addElement(pos p, int x);
int print(pos p);
pos findMax(pos p);
pos findElement(pos p, int x);
pos deleteElement(pos p, int x);

int main(int argc, char *argv[])
{
	pos root = NULL;
	char c;
	int element;
	do {
		printf("\n1 - add element\n2 - find element\n3 - print elements\n4 - delete element\n5 - exit\n");
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Element value: ");
			scanf(" %d", &element);
			root = addElement(root, element);
			break;
		case '2':
			printf("Element to find: ");
			scanf(" %d", &element);
			findElement(root, element);
			break;
		case '3':
			print(root);
			break;
		case '4':
			printf("Element to delete: ");
			scanf(" %d", &element);
			root = deleteElement(root, element);
			break;
		default:
			break;
		}

	} while (c != '5');

	return 0;
}

pos createNew()
{
	pos q = (pos)malloc(sizeof(_TREE));;
	if (q == NULL) return NULL;
	q->left = q->right = NULL;
	return q;
}

int print(pos p)
{	
	if (p != NULL) {
		print(p->left);
		printf("%d ", p->el);
		print(p->right);
	}
	return SUCC;
}

pos addElement(pos p, int x)
{
	if (p == NULL) {
		p = createNew();
		if (p == NULL) return NULL;
		p->el = x;
	}
	else if (x < p->el) {
		p->left = addElement(p->left, x);
	}
	else if (x > p->el) {
		p->right = addElement(p->right, x);
	}
	else {
		printf("Element already exists!\n");
	}
	return p;
}

pos findMax(pos p)
{
	if (p == NULL) return NULL;
	while (p->right != NULL)
		p = p->right;
	return p;
}

pos findElement(pos p, int x)
{
	if (p == NULL) {
		printf("Element ne postoji!\n");
		return NULL;
	}
	else if (x < p->el) {
		return findElement(p->left, x);
	}
	else if (x > p->el) {
		return findElement(p->right, x);
	}
	else {
		printf("Element pronaden!\n");
	}
	return p;

}

pos deleteElement(pos p, int x)
{
	if (p == NULL) {
		printf("Element ne postoji!\n");
		return NULL;
	}
	else if (x < p->el) {
		p->left = deleteElement(p->left, x);
	}
	else if (x > p->el) {
		p->right = deleteElement(p->right, x);
	}
	else { 
		pos tmp = NULL;
		if (p->left != NULL && p->right != NULL) { 
			tmp = findMax(p->left);
			p->el = tmp->el;
			p->left = deleteElement(p->left, tmp->el);
		}
		else {
			tmp = p;
			if (p->left != NULL)
				p = p->left;
			else
				p = p->right;
			free(tmp);
		}
	}
	return p;
}
