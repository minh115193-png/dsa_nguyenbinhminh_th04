#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
}Data;
typedef struct tagNode {
    Data infor;
    struct tagNode *next, *prev;
}Node;
typedef struct {
    Node *pHead;  
    Node *pTail;
    int spt;
}LList;
void initList(LList *L) {
    L->pHead = NULL;
	L->pTail = NULL;
	L->spt = 0;
}
int emptyList(LList L) {
    return (L.spt == 0); 
}

void insert_Head(LList *L, Data x) {
    Node *pp;
    pp = (Node*) malloc(sizeof(Node));
    pp->infor = x;
    pp->next = NULL;
	pp->prev = NULL;
    if(emptyList(*L)) {
    	L->pHead = pp;
    	L->pTail = pp;
    }  	
    else {
    	L->pHead->prev = pp;
    	pp->next = L->pHead;
    	L->pHead = pp;
    }
    L->spt++;
}
void insert_Tail(LList *L, Data x) {
	Node *pp;
	pp = (Node *) malloc(sizeof(Node));
	pp->infor = x;
	pp->next = NULL;
	pp->prev = NULL;
	if(emptyList(*L)) {
		L->pHead = pp;
		L->pTail = pp;
	}
	else {
		L->pTail->next = pp;
		pp->prev=L->pTail;
		L->pTail = pp;
	}
	L->spt++;
}
void insert_After(LList *L, Node *q, Data x) {
	Node *pp;
	if (NULL == q) return;
	else {
		if (q != L->pTail) {
			pp = (Node *) malloc(sizeof(Node));
			pp->infor = x;
			pp->next = q->next;
			q->next->prev = pp;
			q->next = pp;
			pp->prev = q;
			L->spt++;
		}
		else
			insert_Tail(L, x);
	}
}

Node* search_ma(LList L, int ma) {
    Node *pp = L.pHead;
    while(pp != NULL && pp->infor.masv != ma)
        pp = pp->next;
    return pp;
}
Node* search_ten(LList L, char t[30]) {
	Node *pp = L.pHead;
	while(pp != NULL && !strstr(pp->infor.hoten, t))
		pp = pp->next;
	return pp;

}

void del_Head(LList *L) {
	Node *pp;
	if (emptyList(*L)) return;
	else {
		pp = L->pHead;
		L->pHead = pp->next;
		if(L->pHead != NULL)
			L->pHead->prev = NULL;
		free(pp);
		L->spt--;
		if(L->pHead == NULL)
			L->pTail = NULL;
	}
}
void del_After(LList *L, Node *q) {
	Node *pp;
	if (NULL == q || q->next == NULL) return;
	else {
		pp = q->next;
		q->next = pp->next;
		if (pp->next != NULL)
			pp->next->prev = q;
		free(pp);
		L->spt--;
		if(L->pTail == NULL || L->pTail == pp)
			L->pTail = q;
	}
}
void del_theo_maSV(LList *L, int ma) {
	Node *pp = L->pHead, *q;
	while (pp != NULL && pp->infor.masv != ma) {
		q = pp;
		pp = pp->next;
	}
	if (NULL == pp) return;
	else {
		if(pp == L->pHead)
			del_Head(L);
		else
			del_After(L, q);
	}
}
void del_theo_tenSV(LList *L, char t[30]) {
	Node *pp = L->pHead, *q;
	while(pp != NULL && !strstr(pp->infor.hoten, t)){
		q = pp;
		pp = pp->next;
	}
	if(NULL == pp) return;
	else {
		if(pp == L->pHead)
			del_Head(L);
		else
			del_After(L, q);
	}
}

void sapxep_theo_ten(LList *L) {
	Node *pp, *q;
	Data tg;
	for(pp = L->pHead; pp != NULL; pp = pp->next) {
		for(q = pp->next; q != NULL; q = q->next)
			if(strcmp(pp->infor.hoten, q->infor.hoten) > 0) {
				tg = pp->infor;
				pp->infor = q->infor;
				q->infor = tg;
			}
	}
}

void tach(LList L, LList *L1, LList *L2) {
	initList(L1);
	initList(L2);
	Node *pp = L.pHead;
	while(pp != NULL) {
		float avg = (pp->infor.d1 + pp->infor.d2 + pp->infor.d3)/3;
		if(avg > 5)
			insert_Head(L1, pp->infor);
		else
			insert_Head(L2, pp->infor);
		pp = pp->next;
	}
}
void ghep(LList *L, LList L1, LList L2) {
	initList(L);
	Node *p1 = L1.pHead;
	Node *p2 = L2.pHead;
	if(L1.spt < L2.spt) {
		while (p1 != NULL) {
			insert_Head(L, p1->infor);
			insert_Head(L, p2->infor);
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p2 != NULL) {
			insert_Head(L, p2->infor);
			p2 = p2->next;
		}
	}
	else {
		while (p2 != NULL) {
			insert_Head(L, p2->infor);
			insert_Head(L, p1->infor);
			p2 = p2->next;
			p1 = p1->next;
		}
		while (p1 != NULL) {
			insert_Head(L, p1->infor);
			p1 = p1->next;
		}
	}
}

void nhap(Data *x){
    printf("Nhap ma sv: ");
    scanf("%d", &(x->masv));
    if(x->masv > 0) {
        printf("Nhap ho ten sv: ");
        scanf("%s", (x->hoten));
        printf("Nhap diem mon 1: ");
        scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: ");
        scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: ");
        scanf("%f", &(x->d3));
    }
}
void in(Data x){
    printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f\n", 
            x.hoten, x.masv, x.d1, x.d2, x.d3);
}
void processList(LList L){
    Node *pp = L.pHead;
    while(pp != NULL){
        in(pp->infor);
        pp = pp->next;
    }
}

int main(){
    LList L;
	Data x;
	initList(&L);
	int chon;
	
	LList L1, L2; initList(&L1); initList(&L2);
	
	do {
	    printf("\nChuong trinh lam viec voi DSLK don SV\n");
	    printf("\n1: Them nut vao dau danh sach");
	    printf("\n2: Them nut vao cuoi danh sach");
	    printf("\n3: Them nut vao sau mot nut khac trong danh sach");
	    printf("\n4: Xoa nut theo ma sinh vien");
	    printf("\n5: Xoa nut theo ten sinh vien");
	    printf("\n6: Tim kiem theo ma sinh vien");
	    printf("\n7: Tim kiem theo ten sinh vien");
	    printf("\n8: Sap xep danh sach theo ten sinh vien");
	    printf("\n9: Duyet ds");
	    printf("\n10: Tach danh sach");
	    printf("\n11: Ghep danh sach");
	    printf("\n0: Thoat");
	    printf("\nMoi ban chon: ");
		scanf("%d", &chon);
	    switch(chon){
	        case 1: {
	            printf("Nhap so thong tin sv can them\n");
	            nhap(&x);
	            if(x.masv > 0) 
                	insert_Head(&L, x);
                printf("\nThem thanh cong\n");
            	break;
            }
            case 2:	{
	            printf("Nhap so thong tin sv can them\n");
	            nhap(&x);
	            if(x.masv > 0)
	            	insert_Tail(&L, x);
	            printf("\nThem thanh cong\n");
            	break;
            }
            case 3: {
            	int ma;
            	printf("Nhap ma sv: ");
				scanf("%d", &ma);
            	Node *q;
            	q = search_ma(L, ma);
            	if(q == NULL) printf("Khong tim thay ma sv\n");
            	else {
	            	printf("Nhap so thong tin sv can them sau ma %d\n", ma);
	            	nhap(&x);
					if(x.masv > 0)
	            		insert_After(&L, q, x);
	            	printf("\nThem thanh cong\n");
				}
            	break;
            }
            case 4: {
            	int ma;
                printf("Nhap ma cua sinh vien muon xoa: ");
				scanf("%d", &ma);
                if(ma > 0)
                	del_theo_maSV(&L, ma);
                printf("\nXoa thanh cong\n");
                break;
            }
            case 5: {
            	char ten[30];
            	printf("Nhap ten cua sinh vien muon xoa: ");
            	scanf("%s", ten);
            	del_theo_tenSV(&L, ten);
            	printf("\nXoa thanh cong\n");
				break;
			}
            case 6: {
            	int ma;
            	printf("Nhap ma sv: ");
            	scanf("%d", &ma);
            	Node *q;
            	q = search_ma(L, ma);
            	if(q == NULL) printf("Khong tim thay ma sv\n");
            	else {
            		printf("Thong tin sinh vien:\n");
            		in(q->infor);
				}
				break;
			}
            case 7: {
            	char ten[30];
            	printf("Nhap ten sv: ");
            	scanf("%s", ten);
            	Node *q;
            	q = search_ten(L, ten);
            	if(q == NULL) printf("Khong tim thay ten sv");
            	else {
            		printf("Thong tin sinh vien:\n");
            		in(q->infor);
				}
				break;
			}
            case 8: {
            	sapxep_theo_ten(&L);
            	printf("Danh sach sinh vien duoc sap xep theo ten:\n");
            	processList(L);
				break;
			}
            case 9: {
                processList(L);
                break;
            }
            case 10: {
            	tach(L, &L1, &L2);
            	processList(L1);
            	printf("---------------------------------------------------");
            	processList(L2);
				break;
			}
        	case 11: {
        		if(emptyList(L1) && emptyList(L2))
        			printf("Khong co danh sach can ghep");
        		else {
	        		LList Ll;
	        		ghep(&Ll, L1, L2);
	        		processList(Ll);
				}
				break;
			}
            case 0: 
                printf("Bye bye\n"); break;
            default:
            	printf("Vui long lua chon 0, 1, 2, 3, 4, 9");
        }
	}while(chon != 0);
}
