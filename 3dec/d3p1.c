#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxJolt(char *battery) {
	int maxNum = 0;
	int firstNum = 0;
	int secondNum = 0;
	char digit;
	int maxJolt;
	int currJolt;
	int idx = 0;
	size_t len = strlen(battery);
	for (size_t i = 0; i < len; i++) {
		digit = battery[i];
		currJolt = atoi(&digit);
		if (currJolt > firstNum && i != (len - 1)) {
			firstNum = currJolt;
			idx = i;
		}
	}
	for (size_t i = idx + 1; i < len; i++) {
		digit = battery[i];
		currJolt = atoi(&digit);
		if (currJolt > secondNum) {
			secondNum = currJolt;
		}
	}
	maxJolt = (firstNum * 10) + secondNum;
	return maxJolt;
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	//FILE *fp = fopen("eg_input.txt", "r");
	char line[1024];
	if (!fp) {
		printf("Error opening file\n");
		return 1;
	}

	int *joltArr = NULL;
	int totJolt = 0;
	int topJolt = 0;

	while(fgets(line, sizeof(line), fp)) {
		char *token = strtok(line, "\n");
		topJolt = maxJolt(token);
		printf("Top Joltage: %d\n", topJolt);
		totJolt += topJolt;
	}
	printf("Total Joltage Required: %d\n", totJolt);
	return 0;
}
