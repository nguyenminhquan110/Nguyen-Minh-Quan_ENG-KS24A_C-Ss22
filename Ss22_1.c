#include <stdio.h>
#include <string.h>
typedef struct{
	char id[20] ;
	char name[50] ;
	int age ;
} Students ;
void show( Students sv[], int n );
void add( Students sv[], int *n );
void update( Students sv[], int n );
void del( Students sv[], int *n );
void search( Students sv[], int n );
void sort( Students sv[], int n );
int main(){
	int choice, n = 0;
	Students sv[100];
	
	do{
		printf("\n---------Menu-------------");
		printf("\n1. In danh sach sinh vien ");
		printf("\n2. Them sinh vien ");
		printf("\n3. Sua thong tin sinh vien ");
		printf("\n4. Xoa sinh vien ");
		printf("\n5. Tim kiem sinh vien ");
		printf("\n6. Sap xep danh sach sinh vien ");
		printf("\n7. Thoat ");
		printf("\nLua chon cua ban: ");
		scanf("%d", &choice);
		fflush(stdin);
		
		switch( choice){
			case 1:{
				show(sv, n);
				break;
			}
			case 2:{
				add(sv, &n);
				break;
			}
			case 3:{
				update(sv, n);
				break;
			}
			case 4:{
				del(sv, &n);
				break;
			}
			case 5:{
				search(sv, n);
				break;
			}
			case 6:{
				sort(sv, n);
				break;
			}
			case 7:{
				printf("\nBan chon thoat!");
				break;
			}
			default:{
				printf("\nVui long chon dung(1-7)!");
				break;
			}
		}
	}while ( choice != 7 );
	return 0;
}
void show( Students sv[], int n ){
	if ( n == 0 ){
		printf("\nMang rong, vui long them thong tin sv!");
	}else{
		FILE *fptr = fopen("ss22-lt1.bin", "rb");
		fread(sv, sizeof(Students), n, fptr);
		fclose(fptr);
		
		printf("\nDanh sach sv: ");
		for ( int i = 0; i<n ; i++){
			printf("\n\nID: %s ", sv[i].id );
			printf("\nTen: %s", sv[i].name );
			printf("\nTuoi: %d", sv[i].age );
		}
	}
}
void add( Students sv[], int *n ){
	printf("\nNhap thong tin sv muon them: ");
	printf("\nNhap id: ");
	fgets(sv[*n].id, 20, stdin );
	sv[*n].id[strlen(sv[*n].id) -1] = '\0' ;
	
	printf("Nhap ten: ");
	fgets(sv[*n].name, 20, stdin );
	sv[*n].name[strlen(sv[*n].name) -1] = '\0' ;
	
	printf("Nhap tuoi: ");
	scanf("%d", &sv[*n].age );
	
	FILE *fptr;
	if ( *n == 0 ){
		fptr = fopen("ss22-lt1.bin", "wb");
	}else{
		fptr = fopen("ss22-lt1.bin", "ab");
	}
	
	fwrite( &sv[*n] , sizeof(Students), 1, fptr );
	fclose(fptr);
	(*n)++;
	printf("\nThem thanh cong!");
}
void update( Students sv[], int n ){
	if ( n == 0 ){
		printf("\nMang rong, vui long them thong tin sv!");
	}else{
		int check = 0;
		char input[20] ;
		printf("\nNhap ma sv muon sua: ");
		fgets(input, 20, stdin );
		input[strlen(input) -1] = '\0' ;
		
		for ( int i = 0; i<n ; i++){
			if ( strcmp(input, sv[i].id ) == 0 ){
				check = 1;
				printf("\nNhap ten: ");
				fgets(sv[i].name, 20, stdin );
				sv[i].name[strlen(sv[i].name) -1] = '\0' ;
				
				printf("Nhap tuoi: ");
				scanf("%d", &sv[i].age );
				break;
			}
		}
		
		if ( check == 0 ){
			printf("\nID khong ton tai!");
		}else{
			FILE *fptr = fopen("ss22-lt1.bin", "wb");
			for ( int i = 0; i<n ; i++){
				fwrite( &sv[i] , sizeof(Students), 1, fptr );
			}
			fclose(fptr);
			printf("\nSua thanh cong!");
		}
	}
}
void del( Students sv[], int *n ){
	if ( n == 0 ){
		printf("\nMang rong, vui long them thong tin sv!");
	}else{
		int check = 0;
		char input[20] ;
		printf("\nNhap ma sv muon xoa: ");
		fgets(input, 20, stdin );
		input[strlen(input) -1] = '\0' ;
		
		for ( int i = 0; i< *n ; i++){
			if ( strcmp(input, sv[i].id ) == 0 ){
				check = 1;
				for ( int j = i; j< *n-1 ; j++ ){
					sv[j] = sv[j+1];
				}
				break;
			}
		}
		
		if ( check == 0 ){
			printf("\nID ko ton tai!");
		}else{
			(*n)--;
			FILE *fptr = fopen("ss22-lt1.bin", "wb");
			for ( int i = 0; i< *n ; i++){
				fwrite( &sv[i] , sizeof(Students), 1, fptr );
			}
			fclose(fptr);
			printf("\nXoa thanh cong!");
		}
	}
}
void search( Students sv[], int n ){
	if ( n == 0 ){
		printf("\nMang rong, vui long them thong tin sv!");
	}else{
		int check = 0;
		char input[20] ;
		printf("\nNhap ma sv muon tim: ");
		fgets(input, 20, stdin );
		input[strlen(input) -1] = '\0' ;
		
		FILE *fptr = fopen("ss22-lt1.bin", "rb");
		fread(sv, sizeof(Students), n, fptr);
		fclose(fptr);
		
		for ( int i = 0; i< n ; i++){
			if ( strcmp(input, sv[i].id ) == 0 ){
				check = 1;
				printf("\nKet qua tim kiem: ");
				printf("\n\nID: %s ", sv[i].id );
				printf("\nTen: %s", sv[i].name );
				printf("\nTuoi: %d", sv[i].age );
				break;
			}
		}
		if ( check == 0 ) printf("\nID khong ton tai!");
	}
}
void sort( Students sv[], int n ){
	if ( n == 0 ){
		printf("\nMang rong, vui long them thong tin sv!");
	}else{
		FILE *fptr = fopen("ss22-lt1.bin", "rb");
		fread(sv, sizeof(Students), n, fptr);
		fclose(fptr);
		
		for ( int i = 0; i<n ; i++){
			for ( int j =0; j<n-i-1; j++ ){
				if ( strcmp(sv[j].id, sv[j+1].id) > 0 ){
					Students temp = sv[j];
					sv[j] = sv[j+1];
					sv[j+1] = temp;
				}
			}
		}
		
		printf("\nKet qua sap xep: ");
		for ( int i = 0; i<n ; i++){
			printf("\n\nID: %s ", sv[i].id );
			printf("\nTen: %s", sv[i].name );
			printf("\nTuoi: %d", sv[i].age );
		}
	}
}
