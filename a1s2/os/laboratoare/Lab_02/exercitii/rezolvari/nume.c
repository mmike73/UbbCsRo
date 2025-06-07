#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char *name;
	struct node* next;
};
//aici este vorba de o lista inlantuita
//elementul curent refera la elementul urmator

struct node* add(struct node* head, char* name) {
	struct node* n, p;

	n = (struct node*)malloc(sizeof(struct node));
	n->name = (char *)malloc(strlen(name) + 1); //se aloca loc pentru numele de retinut

	strcpy(n->name, name);
	n->next = NULL;
	
	if(head == NULL) return n;

	p = &head;
	while(p->next != NULL)
		p = p->next;
	//se parcurg toate numele astfel incat sa se ajunga la numele curent

	p->next = n;
	return head;
}

void clear(struct node* head) {
	if( head == NULL) return;
	clear(head->next);
	free(head->name);
	free(head);
}

int known( struct node* head, char* name) {
	struct node* p;

	if( head == NULL) {
		return 0; //nu avem elemente in vector
	}
	p = *head;//ambii pointeri, se atribuie natural
	while( p != NULL && strcmp(p->name, name) != 0) {
		p = p->next; 
	}
	if( p == NULL) {
		return 0;
	}
	return 1;
}

int main(int argc, char** argv) {
	char name[64];
	
	//primul nod, nodul "cap", treuie initializat cu null;
	struct node* head = NULL;

	while(scanf("%s", name) == 1) { //nu se pune referinta la citirea unui string
		if( known(head, name)) { //head e un pointer by default, toate se transmit natural
			printf("Hello again, %s!\n", name);	
		}
		else {
			head = add(head, name);
			printf("Hello %s!\n", name);
		}
	}
	clear(head);
	//dealoca toata memoria aloccata dinamic
	return 0;
} 

