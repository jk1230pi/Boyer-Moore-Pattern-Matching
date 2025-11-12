#include <stdio.h>
#include <string.h>
#include <time.h>
#define NO_OF_CHARS 256

// Function to create the bad character heuristic table
void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(unsigned char)str[i]] = i;
}

// Boyer–Moore search function
int search(char *txt, char *pat, int *comparisons, int *positions, int max_positions) {
    int m = strlen(pat);
    int n = strlen(txt);
    int badchar[NO_OF_CHARS];
    int found_count = 0;
    *comparisons = 0;

    badCharHeuristic(pat, m, badchar);

    int s = 0;  // pattern shift index
    while (s <= (n - m)) {
        int j = m - 1;

        // Compare characters from end of pattern to beginning
        while (j >= 0 && pat[j] == txt[s + j]) {
            j--;
            (*comparisons)++;
        }

        if (j >= 0)
            (*comparisons)++;

        if (j < 0) {
            // Found a match
            if (found_count < max_positions)
                positions[found_count] = s;
            found_count++;

            // Shift for next possible match
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        } else {
            int shift = j - badchar[(unsigned char)txt[s + j]];
            if (shift < 1)
                shift = 1;
            s += shift;
        }
    }

    return found_count;
}

int main() {
    FILE *ftext, *fpattern;
    static char txt[2000000];  // Large buffer for big text files
    static char pat[1000];
    int positions[1000];       // Store up to 1000 match positions
    int comparisons = 0;
    int total_found = 0;

    // Open files
    ftext = fopen("data.txt", "r");
    fpattern = fopen("pattern.txt", "r");

    if (ftext == NULL || fpattern == NULL) {
        printf("⚠️ Error: Could not open input files.\n");
        return 1;
    }

    // Read dataset safely
    size_t text_len = fread(txt, 1, sizeof(txt) - 1, ftext);
    txt[text_len] = '\0';
    fclose(ftext);

    // Read pattern safely
    if (fgets(pat, sizeof(pat), fpattern) == NULL) {
        printf("⚠️ Error reading pattern file.\n");
        fclose(fpattern);
        return 1;
    }
    fclose(fpattern);

    // Remove newline
    pat[strcspn(pat, "\n")] = '\0';

    if (strlen(pat) == 0) {
        printf("⚠️ Pattern file is empty!\n");
        return 1;
    }

    printf("\n🔍 Searching for pattern '%s' in dataset text...\n\n", pat);

    // Measure execution time
    clock_t start = clock();

    total_found = search(txt, pat, &comparisons, positions, 1000);

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // in ms

    // Print results
    if (total_found > 0) {
        printf("✅ Pattern found %d time(s).\n", total_found);
        printf("📍 First few positions: ");
        for (int i = 0; i < total_found && i < 20; i++)
            printf("%d ", positions[i]);
        if (total_found > 20)
            printf("... (only first 20 shown)");
        printf("\n");
    } else {
        printf("❌ Pattern not found in the text.\n");
    }

    printf("\n🧠 Total character comparisons: %d\n", comparisons);
    printf("⏱️  Execution time: %.3f ms\n", time_taken);

    return 0;
}
