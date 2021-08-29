#include "reader.h"

int getUnint(unsigned *a){
    int n;
	int tmp;
    do{
        n = scanf("%u", &tmp);
		if (tmp<0) n=0;
        if (n < 0) return 1;
        if (n == 0){
            printf("<Error>!\n");
            scanf("%*c");
        }
    } while (n == 0);
	*a=(unsigned)tmp;
    return 0;
}


int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0) return 0;
        if (n == 0){
            printf("<Error>!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}


char *getStr(){
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


int getConstLenStr(KeyType1 str, int len){
	int i = 0;
	char c;
	while(i<(len+1) && (c=getchar())!=EOF && c!='\n'){
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return 0;
}


int readKey1(KeyType1 key1, int len){
	printf("Enter the key in ks1 (string)\n");
	scanf("%*c");
	return getConstLenStr(key1, len);
}


int readKey2(KeyType2 *key2){
	printf("Enter the key in ks2 (unsigned)\n");
	return getUnint(key2);
}


int readFirstNumber(int *firstNumber){
	printf("Enter first number (int)\n");
	return getInt(firstNumber);
}


int readSecondNumber(int *secondNumber){
	printf("Enter second number (int)\n");
	return getInt(secondNumber);
}


int readString(char **string){
	printf("Enter string (string)\n");
	scanf("%*c");
	*string = getStr();
	return 0;
}

int readRelease(int *release){
	printf("Enter release (int)\n");
	return getInt(release);
}



