#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 10

	/*NOTE:
	* All IDs, even of odd, with any repeating sequence of numbers are considered invalid
	*/

/* NOTE: 
 * Go back to sliding logic, i.e., check if a sequence has been repeated at least twice
 * Sequence can be of any length
 * ONLY invalid IDs are ones that are solely made up of repeating sequences
 * Check if current digit is equal to a previous one
 * If true, check if following digit is equal to the digit that came after the first previous one
 * If true, keep checking until sequence has been processed 
 */
bool checkID(long long id) {
	bool inValid = false;
	char str[32];

	sprintf(str, "%lld", id);
	size_t len = strlen(str);
	size_t half = len / 2;
	int part = 0;
	int seq = 0;

	if (len == 2) {
		if (str[0] == str[1]) {
			return true;
		}
	}

	if (len < 2) {
		return false;
	}

	size_t pos = 0;
	for (size_t i = 1; i <= half; i++) {
		if (len % i == 0) {
			int repCount = len / i;
			char seqArr[i + 1];
			strncpy(seqArr, str, i);
			seqArr[i] = '\0';
			char rep[len + 1];
			rep[0] = '\0';
			for (int j = 0; j < repCount; j++) {
				strcat(rep, seqArr);
			}
			if (strcmp(rep, str) == 0) {
				return true;
			}
		}
	}

	return inValid;
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	//FILE *fp = fopen("eg_inp.txt", "r");
	//FILE *fp = fopen("ex_inp.txt", "r");
	char line[1024];
	if (!fp) {
		printf("Error opening file\n");
		return 1;
	}
	int i = 0;
	int idx = 0;
	long long id1;
	long long id2;
	long long prev;
	long long sum;
	long long *invalidIdArr = NULL;	
	size_t cap = 1024;
	invalidIdArr = malloc(cap * sizeof(long long));
	size_t invalidCount = 0;
	bool invalid;

	while (fgets(line, sizeof(line), fp)) {
		char *token = strtok(line, ",-");
		while (token) {
			if (strlen(token) > 9) {
				printf("Test Long Long\n");
				id1 = strtoll(token, NULL, 10);
				printf("ID 1: %lld\n", id1);
			} else {
				printf("Test int\n");
				id1 = atoi(token);
				printf("ID 1: %d\n", id1);
			}
			//id1 = atoll(token);
			//id1 = strtoll(token, NULL, 10);
			//printf("ID 1: %d\n", id1);
			token = strtok(NULL, ",-");
			if (!token) {
				break;
			}
			//id2 = atoll(token);
			//id2 = strtoll(token, NULL, 10);
			if (strlen(token) > 9) {
				printf("Test Long Long\n");
				id2 = strtoll(token, NULL, 10);
				printf("ID 2: %lld\n", id2);
			} else {
				printf("Test int\n");
				id2 = atoi(token);
				printf("ID 2: %d\n", id2);
			}
			//printf("ID 2: %d\n", id2);
			for (long long j = id1; j < id2; j++) {
				if (checkID(j)) {
					//printf("Test\n");
					if (invalidCount == cap) {
						cap *= 2;
						invalidIdArr = realloc(invalidIdArr, cap * sizeof(long long));
					}
					//invalidIdArr = realloc(invalidIdArr, (invalidCount + 1) * sizeof(long long));
					invalidIdArr[invalidCount++] = j;
					//printf("Invalid ID: %lld\n", j);
					//idx++;
				}
			}
			//sum = id1 + id2;
			//printf("Sum: %d\n", sum);
			token = strtok(NULL, ",-");
			i++;
		}
	}

	fclose(fp);
	printf("Number of Invalid IDs: %zu\n", invalidCount);
	long long tot = 0; 
	for (size_t i = 0; i < invalidCount; i++) {
		printf("%lld\n", invalidIdArr[i]);
		tot += invalidIdArr[i];
	}
	printf("Sum of invalid IDs: %lld\n", tot);
	free(invalidIdArr);
	return 0;
}
