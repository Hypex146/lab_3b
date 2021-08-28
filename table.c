#include "table.h"
#include "table_ks1.h"
#include "table_ks2.h"

int get_unint(unsigned *a){
    int n;
	int tmp;
    do{
        n = scanf("%u", &tmp);
		if (tmp<0) n=0;
        if (n < 0) return 1;
        if (n == 0){
            printf("Error!\n");
            scanf("%*c");
        }
    } while (n == 0);
	*a=(unsigned)tmp;
    return 0;
}


int get_int(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0) return 0;
        if (n == 0){
            printf("Error!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}


char *get_str(){
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}


void get_const_len_str(KeyType1 str){
	int i = 0;
	char c;
	while(i < (STRLEN+1) && (c=getchar())!=EOF && c!='\n'){
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	//printf("HEHE -> %d\n", i);
}


Table *table_init(void){
	Table *table = (Table*)malloc(sizeof(Table));
	table->msize1 = MAXSIZE1;
	table->csize1 = 0;
	table->ks1 = (KeySpace1*)malloc(table->msize1 * sizeof(KeySpace1));
	for (int i=0; i<table->msize1; i++){
		table->ks1[i].busy = 0;
	};
	table->msize2 = MAXSIZE2;
	table->csize2 = 0;
	table->ks2 = (List_ks2**)malloc(table->msize2 * sizeof(List_ks2*));
	for (int i=0; i<table->msize2; i++){
		table->ks2[i] = NULL;
	}
	return table;
}


static InfoType *info_init(int first_number, int second_number, char *string){
	InfoType *info = (InfoType*)malloc(sizeof(InfoType));
	info->first_number = first_number;
	info->second_number = second_number;
	info->string = string;
	return info;
}


static Item *item_init(int first_number, int second_number, char *string, 
						KeyType1 key1, KeyType2 key2){
	Item *item = (Item*)malloc(sizeof(Item));
	item->next = NULL;
	item->release = 0;
	item->info = info_init(first_number, second_number, string);
	memcpy(item->key1, key1, (STRLEN+1)*sizeof(char));
	item->key2 = key2;
	return item;
}


//=================================================================================


void find_by_double_key(Table *table){
	Item *item = NULL;
	Node2 *node2 = NULL;
	if (table->csize1 > 0){
		printf("Enter the key in ks1 (string)\n");
		KeyType1 key1 = {0};
		scanf("%*c");
		get_const_len_str(key1);
		
		printf("Enter the key in ks2 (unsigned)\n");
		KeyType2 key2;
		get_unint(&key2);
		
		List_nd2 *list = NULL;
		list = get_list_by_ks2_key(table, key2);
		
		if (list){
			int release = get_release_by_key1(list, key1);
			if (release>=0){
				list_take_nd2(list, release, &node2);
				item = node2->info;
				printf("\n");
				printf("key1 -> %s\n", item->key1);
				printf("key2 -> %u\n", item->key2);
				printf("string -> %s\n", item->info->string);
				printf("first number -> %d\n", item->info->first_number);
				printf("second number -> %d\n", item->info->second_number);
				printf("\n");
			} else{
				printf("There are no item with this key\n");
			}
		} else{
			printf("There are no item with this key\n");
		}
	} else{
		printf("Table is empty\n");
	}
}


void table_del(Table *table){
	if (table->csize1 > 0){
		printf("Enter the key in ks1 (string)\n");
		KeyType1 key1 = {0};
		scanf("%*c");
		get_const_len_str(key1);
		
		printf("Enter the key in ks2 (unsigned)\n");
		KeyType2 key2;
		get_unint(&key2);
		
		List_nd2 *list = NULL;
		Item *item = NULL;
		Node2 *node2 = NULL;
		list = get_list_by_ks2_key(table, key2);
		if (list){
			int release = get_release_by_key1(list, key1);
			if (release>=0){
				list_take_nd2(list, release, &node2);
				item = node2->info;
				table_del_ks1_without_del_item(table, key1);
				table_del_ks2_without_del_item(table, key2, release);
				free(item->info->string);
				free(item->info);
				free(item);
				table->csize1--;
				table->csize2--;
			} else{
				printf("This element is not exist\n");
			}
		} else{
			printf("This element is not exist\n");
		}
	} else{
		printf("Table is empty\n");
	}
}


void table_add(Table *table){
	if (table->csize1<table->msize1 && table->csize2<table->msize2){
		printf("Enter the key in ks1 (string)\n");
		KeyType1 key1 = {0};
		scanf("%*c");
		get_const_len_str(key1);
		
		printf("Enter the key in ks2 (unsigned)\n");
		KeyType2 key2;
		get_unint(&key2);
		
		if (!table_check_key_ks1(table, key1)){
			int first_number;
			int second_number;
			char *string;
			printf("Enter first_number\n");
			get_int(&first_number);
			printf("Enter second_number\n");
			get_int(&second_number);
			printf("Enter string\n");
			scanf("%*c");
			string = get_str();
			Item *item = item_init(first_number, second_number, string, key1, key2);
			
			table_add_ks1_static(table, item, key1);
			table->csize1++;
			
			table_add_ks2_static(table, item, key2);
			table->csize2++;
			
		} else{
			printf("We have the same key in ks1\n");
		}
	} else{
		printf("KS1 is FULL or KS2 is FULL\n");
		return;
	}
}


void table_del_by_ks1(Table *table){
	if (table->csize1 > 0){
		printf("Enter the key in ks1 (string)\n");
		KeyType1 key1 = {0};
		scanf("%*c");
		get_const_len_str(key1);
		
		if (table_check_key_ks1(table, key1)==1){
			Item *item = get_item_by_ks1_key(table, key1);
			table_del_ks1_without_del_item(table, key1);
			
			KeyType2 key2 = item->key2;
			List_nd2 *list_nd2 = get_list_by_ks2_key(table, key2);
			int release = get_release_by_key1(list_nd2, key1); 
			table_del_ks2_without_del_item(table, key2, release);
			
			free(item->info->string);
			free(item->info);
			free(item);
			table->csize1--;
			table->csize2--;
		} else{
			printf("This element is not exist\n");
		}
	} else{
		printf("Table is empty\n");
	}
}


void table_del_by_ks2(Table *table){
	if (table->csize1 > 0){
		printf("Enter the key in ks2 (unsigned)\n");
		KeyType2 key2;
		get_unint(&key2);
		printf("Enter the release (int)\n");
		int release;
		get_int(&release);
		Item *item = get_item_by_ks2_key(table, key2, release);
		if (item){
			table_del_ks2_without_del_item(table, key2, release);
			//KeyType1 key1 = item->key1;
			table_del_ks1_without_del_item(table, item->key1);
			free(item->info->string);
			free(item->info);
			free(item);
			table->csize1--;
			table->csize2--;
		} else{
			printf("This element is not exist\n");
		}
	} else{
		printf("Table is empty\n");
	}
}


void table_del_all_by_ks2(Table *table){
	if (table->csize1 > 0){
		printf("Enter the key in ks2 (unsigned)\n");
		KeyType2 key2;
		get_unint(&key2);
		List_nd2 *list = NULL;
		list = get_list_by_ks2_key(table, key2);
		if (list){
			int len = list_len_nd2(list);
			for (int i=0; i<len; i++){
				Item *item = NULL;
				Node2 *node2 = NULL;
				list_take_nd2(list, 0, &node2);
				item = node2->info;
				table_del_ks2_without_del_item(table, key2, 0);
				//KeyType1 key1 = item->key1;
				table_del_ks1_without_del_item(table, item->key1);
				free(item->info->string);
				free(item->info);
				free(item);
				table->csize1--;
				table->csize2--;
			}
		} else{
			printf("There are no item with this key\n");
		}
	} else{
		printf("Table is empty\n");
	}
	
}


void table_print(Table *table){
	table_ks1_debug_print(table);
	printf("\n");
	table_ks2_debug_print(table);
}
/*
void table_write_in_file(Table *table) {
	FILE *file = fopen("table.bin", "w+b");
	fwrite(&table->csize1, 1, sizeof(IndexType1), file);
	fwrite(&table->msize1, 1, sizeof(IndexType1), file);
	fwrite(&table->csize2, 1, sizeof(IndexType2), file);
	fwrite(&table->msize2, 1, sizeof(IndexType2), file);
	for (int i=0; i<table->msize1; i++) {
		fwrite(&table->ks1[i].busy, 1, sizeof(int), file);
		if (table->ks1[i].busy){
			//printf("Mem -> %ld\n", sizeof(table->ks1[i].key));
			fwrite(table->ks1[i].key, STRLEN+1, sizeof(char), file);
		}
	}
	clear_info_file();
	for (int i=0; i<table->msize2; i++){
		if (table->ks2[i]==NULL){
			int len = 0;
			fwrite(&len, 1, sizeof(int), file);
			continue;
		}
		int len = list_len_ks2(table->ks2[i]);
		fwrite(&len, 1, sizeof(int), file);
		if (len==0) {continue;}
		for (KeySpace2 *element=table->ks2[i]->head->next; element; element=element->next) {
			int count = list_len_nd2(element->node);
			if (count==0) {continue;}
			fwrite(&element->key, 1, sizeof(KeyType2), file);
			fwrite(&count, 1, sizeof(int), file);
			for (Node2 *nd2=element->node->head->next; nd2; nd2=nd2->next){
				int offset = info_write_in_file(nd2->info->info);
				fwrite(&offset, 1, sizeof(int), file);
			}	
		}
	}
	fclose(file);
	return;
}

int info_write_in_file(InfoType *info){
	int offset = 0;
	FILE *file = fopen("info.bin", "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
	 	offset = ftell(file);
		fclose(file);
	}
	file = fopen("info.bin", "a+b");
	fwrite(&info->first_number, 1, sizeof(int), file);
	fwrite(&info->second_number, 1, sizeof(int), file);
	fwrite(info->string, strlen(info->string)+1, sizeof(char), file);
	fclose(file);
	return offset;
}

void clear_info_file(){
	FILE *file = fopen("info.bin", "w+b");
	fclose(file);
}

Table *table_read_from_file(){
	Table *table = table_init();
	FILE *file = fopen("table.bin", "rb");
	if (!file) {return table;}
	fread(&table->csize1, 1, sizeof(IndexType1), file);
	fread(&table->msize1, 1, sizeof(IndexType1), file);
	fread(&table->csize2, 1, sizeof(IndexType2), file);
	fread(&table->msize2, 1, sizeof(IndexType2), file);
	for (int i=0; i<table->msize1; i++){
		fread(&table->ks1[i].busy, 1, sizeof(int), file);
		if (table->ks1[i].busy==0) {continue;}
		
	}
	
	fclose(file);
	return table;
}
*/

void table_write_in_file(Table *table){
	file_info_clear();
	FILE *file = fopen("table.bin", "w+b");
	fwrite(&table->csize1, 1, sizeof(IndexType1), file);
	fwrite(&table->msize1, 1, sizeof(IndexType1), file);
	fwrite(&table->csize2, 1, sizeof(IndexType2), file);
	fwrite(&table->msize2, 1, sizeof(IndexType2), file);
	for (int i=0; i<table->msize2; i++){
		if (table->ks2[i]==NULL) {continue;}
		for (KeySpace2 *element=table->ks2[i]->head->next; element; element=element->next){
			int count = list_len_nd2(element->node);
			if (count==0) {continue;}
			//fwrite(&element->key, 1, sizeof(KeyType2), file);
			//fwrite(&count, 1, sizeof(int), file);
			int release = 0;
			for (Node2 *nd2=element->node->head->next; nd2; nd2=nd2->next){
				fwrite(&nd2->info->key1, 1, sizeof(KeyType1), file);
				fwrite(&nd2->info->key2, 1, sizeof(KeyType2), file);
				fwrite(&release, 1, sizeof(int), file);
				int offset = info_write_in_file(nd2->info->info);
				fwrite(&offset, 1, sizeof(int), file);
				release++;
			}
		}
	}
	fclose(file);
	return;
}

void file_info_clear(){
	FILE *file = fopen("info.bin", "w+b");
	fclose(file);
}

int info_write_in_file(InfoType *info){
	int offset = 0;
	FILE *file = fopen("info.bin", "rb");
	/*
	if (file) {
		fseek(file, 0, SEEK_END);
	 	offset = ftell(file);
		fclose(file);
	}
	*/
	file = fopen("info.bin", "a+b");
	fseek(file, 0, SEEK_END);
	offset = ftell(file);
	fwrite(&info->first_number, 1, sizeof(int), file);
	fwrite(&info->second_number, 1, sizeof(int), file);
	int len = strlen(info->string);
	fwrite(&len, 1, sizeof(int), file);
	fwrite(info->string, strlen(info->string)+1, sizeof(char), file);
	fclose(file);
	return offset;
}

InfoType *info_read_from_file(int offset){
	FILE *file = fopen("info.bin", "rb");
	if (!file) {return NULL;}
	InfoType *info = NULL;
	fseek(file, offset, SEEK_SET);
	int first_number, second_number, len;
	char* string = NULL;
	//printf("E1\n");
	fread(&first_number, 1, sizeof(int), file);
	//printf("E2\n");
	fread(&second_number, 1, sizeof(int), file);
	//printf("E3\n");
	fread(&len, 1, sizeof(int), file);
	//printf("E4\n");
	string = (char*)malloc((len+1)*sizeof(char));
	fread(string, len+1, sizeof(char), file);
	//printf("E5\n");
	info = info_init(first_number, second_number, string);
	return info;
}

Table *table_read_from_file(){
	Table *table = table_init();
	FILE *file = fopen("table.bin", "rb");
	if (!file) {return table;}
	int count1, count2;
	fread(&count1, 1, sizeof(IndexType1), file);
	fread(&table->msize1, 1, sizeof(IndexType1), file);
	fread(&count2, 1, sizeof(IndexType2), file);
	fread(&table->msize2, 1, sizeof(IndexType2), file);
	printf("%d\n", count1);
	printf("%d\n", count2);
	for (int i=0; i<count1; i++){
		printf("===========\n");
		KeyType1 key1 = {0};
		KeyType2 key2 = 0;
		int release = 0, offset = 0;
		fread(&key1, 1, sizeof(KeyType1), file);
		fread(&key2, 1, sizeof(KeyType2), file);
		fread(&release, 1, sizeof(int), file);
		fread(&offset, 1, sizeof(int), file);
		InfoType *info = info_read_from_file(offset);
		//--------------
		Item *item = (Item*)malloc(sizeof(Item));
		item->next = NULL;
		item->release = 0;
		item->info = info;
		memcpy(item->key1, key1, (STRLEN+1)*sizeof(char));
		item->key2 = key2;
		//--------------
		table_add_ks1_static(table, item, key1);
		table->csize1++;
		table_add_ks2_static(table, item, key2);
		table->csize2++;
	}
	fclose(file);
	return table;
}


