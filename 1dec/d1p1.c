#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int abs_diff(int num1, int num2) {
    unsigned int abs_diff = num1 > num2 ?
        (unsigned int)num1 - (unsigned int)num2 :
        (unsigned int)num2 - (unsigned int)num1;

    return abs_diff;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	//FILE *fp = fopen("ex_inp.txt", "r");

	int start_val = 50;
	int max = 99;
	int min = 0;
	int counts = 0;
	int change;
	char r = 'R';
	char l = 'L';

	if (!fp) {
		perror("fopen");
		return 1;
	}

	char line[128];
	int curr_val = start_val;
	int next_val;

	printf("Starting Value: %d", start_val);
	printf("\n");

	while (fgets(line, sizeof(line), fp)) {
		// Remove newline
		line[strcspn(line, "\n")] = '\0';

		// Get direction of dial turn
		char c = line[0];

		// Parse the integer from the rest of the string
		// Get number of turns for dial from integer
		int value = atoi(&line[1]);
		
		while (value >= 100) {
			value -= 100;
		}

		if (c == r) {
			next_val = curr_val + value;
		} else if (c == l) {
			next_val = curr_val - value;
		}

		printf("Previous Value: %d", curr_val);
		printf("\n");
		if (next_val >= 100) {
			curr_val = abs_diff(next_val, 100);
		} else if (next_val < 0) {
			curr_val = 100 - abs_diff(curr_val, value);
		} else {
			curr_val = next_val;
		} 

		if (curr_val == 0) {
			counts++;
		} 

		/*
		printf("Current Value: %d", curr_val);
		printf("\n");
		printf("Turn Number: %d", value);
		printf("\n");
		printf("Turn Direction: %c", c);
		printf("\n");
		printf("Tally: %d", counts);
		printf("\n");
		*/
		
		next_val = curr_val;
	}
	printf("Password: %d", counts);

	fclose(fp);
	return 0;
}
