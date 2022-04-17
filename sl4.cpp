#include <stdio.h>
#include <stdlib.h>
struct Pointer{
	int value;
	int tag;
	int count;
	struct Pointer* next1;
	struct Pointer* next2;
	struct Pointer* next3;
};
struct ListOfPointer{
	Pointer* ptr;
	struct ListOfPointer* next;
};
Pointer *Root1,*Root2;
ListOfPointer* CreateHeap(){
	ListOfPointer *root=NULL,*ptr;
	Pointer* ptr1=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp1=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp1->ptr=ptr1;
	ptr1->value=5;
	ptr1->count=0;
	ptr1->tag=0;
	ptr1->next1=NULL;
	ptr1->next2=NULL;
	ptr1->next3=NULL;
	root=temp1;
	ptr=root;
	Pointer* ptr2=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp2=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp2->ptr=ptr2;
	ptr2->value=1;
	ptr2->count=0;
	ptr2->tag=0;
	ptr2->next1=NULL;
	ptr2->next2=NULL;
	ptr2->next3=NULL;
	ptr->next=temp2;
	ptr=ptr->next;
	Pointer* ptr3=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp3=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp3->ptr=ptr3;
	ptr3->value=2;
	ptr3->count=0;
	ptr3->tag=0;
	ptr3->next1=NULL;
	ptr3->next2=NULL;
	ptr3->next3=NULL;
	ptr->next=temp3;
	ptr=ptr->next;
	Pointer* ptr4=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp4=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp4->ptr=ptr4;
	ptr4->value=7;
	ptr4->count=0;
	ptr4->tag=0;
	ptr4->next1=NULL;
	ptr4->next2=NULL;
	ptr4->next3=NULL;
	ptr->next=temp4;
	ptr=ptr->next;
	Pointer* ptr5=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp5=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp5->ptr=ptr5;
	ptr5->value=8;
	ptr5->count=0;
	ptr5->tag=0;
	ptr5->next1=NULL;
	ptr5->next2=NULL;
	ptr5->next3=NULL;
	ptr->next=temp5;
	ptr=ptr->next;
	Pointer* ptr6=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp6=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp6->ptr=ptr6;
	ptr6->value=9;
	ptr6->count=0;
	ptr6->tag=0;
	ptr6->next1=NULL;
	ptr6->next2=NULL;
	ptr6->next3=NULL;
	ptr->next=temp6;
	ptr=ptr->next;
	Pointer* ptr7=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp7=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp7->ptr=ptr7;
	ptr7->value=3;
	ptr7->count=0;
	ptr7->tag=0;
	ptr7->next1=NULL;
	ptr7->next2=NULL;
	ptr7->next3=NULL;
	ptr->next=temp7;
	ptr=ptr->next;
	Pointer* ptr8=(Pointer*)malloc(sizeof(Pointer));
	ListOfPointer *temp8=(ListOfPointer*)malloc(sizeof(ListOfPointer));
	temp8->ptr=ptr8;
	ptr8->value=10;
	ptr8->count=0;
	ptr8->tag=0;
	ptr8->next1=NULL;
	ptr8->next2=NULL;
	ptr8->next3=NULL;
	ptr->next=temp8;
	ptr=ptr->next;
	ptr->next=NULL;
	ptr1->next1=ptr2;
	ptr2->next1=ptr3;
	ptr2->next2=ptr6;
	ptr2->next3=ptr8;
	ptr4->next1=ptr2;
	ptr4->next2=ptr5;
	ptr5->next1=ptr6;
	ptr7->next1=ptr5;
	ptr7->next2=ptr8;
	Root1=ptr1;
	Root2=ptr2;
	return root;
}

// Reference Counting method

void ReferenceCounting(Pointer* root){
	if(root!=NULL){
		root->count++;
		if(root->next1!=NULL){
			ReferenceCounting(root->next1);
		}
		if(root->next2!=NULL){
			ReferenceCounting(root->next2);
		}
		if(root->next3!=NULL){
			ReferenceCounting(root->next3);
		}
	}
	return;
}
ListOfPointer* GCReferenceCounting(ListOfPointer* lPtr){
	ListOfPointer *garbage=NULL,*p;
	ListOfPointer *lptr=lPtr;
	while(lptr!=NULL){
		if(lptr->ptr->count==0){
			ListOfPointer *g=(ListOfPointer*)malloc(sizeof(ListOfPointer));
			g->ptr=lptr->ptr;
			if(garbage==NULL){
				garbage=g;
				p=garbage;
			}
			else{
				p->next=g;
				p=g;
			}
		}
		lptr=lptr->next;
	}
	p->next=NULL;
	return garbage;
}
void DisplayRC(ListOfPointer* lPtr){
	while(lPtr!=NULL){
		printf("%d\n",lPtr->ptr->value);
		lPtr=lPtr->next;
	}
	return;
}

// Mark and Sweep method

void MarkAndSweep(ListOfPointer* lPtr){
	ListOfPointer *lptr,*ptr;
	lptr=lPtr;
	while(lptr!=NULL){
		ptr=lPtr;
		while(ptr!=NULL){
			if(lptr->ptr==ptr->ptr->next1 || lptr->ptr==ptr->ptr->next2 || lptr->ptr==ptr->ptr->next3 || lptr->ptr==Root1 || lptr->ptr==Root2){
				lptr->ptr->tag=1;
			}
			ptr=ptr->next;
		}
		lptr=lptr->next;
	}
}
ListOfPointer* GCMarkAndSweep(ListOfPointer* lPtr){
	ListOfPointer *garbage=NULL,*p;
	ListOfPointer *lptr=lPtr;
	while(lptr!=NULL){
		if(lptr->ptr->tag==0){
			ListOfPointer *g=(ListOfPointer*)malloc(sizeof(ListOfPointer));
			g->ptr=lptr->ptr;
			if(garbage==NULL){
				garbage=g;
				p=garbage;
			}
			else{
				p->next=g;
				p=g;
			}
		}
		lptr=lptr->next;
	}
	p->next=NULL;
	return garbage;
}
void DisplayMS(ListOfPointer* lPtr){
	while(lPtr!=NULL){
		printf("%d\n",lPtr->ptr->value);
		lPtr=lPtr->next;
	}
	return;
}
int main(){
	ListOfPointer *lPtr = CreateHeap();
	ReferenceCounting(Root1);
	ReferenceCounting(Root2);
	ListOfPointer* garbage1 = GCReferenceCounting(lPtr);
	printf("Through referece counting, the garbage is\n");
	DisplayRC(garbage1);
	MarkAndSweep(lPtr);
	ListOfPointer* garbage2 = GCMarkAndSweep(lPtr);
	printf("Through Mark and Sweep, the garbage is\n");
	DisplayMS(garbage2);
	return 0;
}

