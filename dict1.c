#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"

int main(int argc, char *argv[]) {
    // Check the number of command line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <stage> <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int stage = atoi(argv[1]);
    const char *input_filename = argv[2];
    const char *output_filename = argv[3];

    if (stage == 1) {

        Node *head = fill_dictionary(input_filename);

        FILE *output_file = fopen(output_filename, "w");
        if (!output_file) {
            perror("Error opening output file");
            return EXIT_FAILURE;
        }

        // Read queries from stdin until EOF
        char* query = NULL;
        size_t size = 0;
        while (getline(&query, &size, stdin) > 0) {
            // Remove newline character
            query[strcspn(query, "\n")] = '\0';

            // Perform search and output results
            key_lookup(head, query, output_file);
        }
        free(query);
        fclose(output_file);
        free_list(head);  
    }         
    
}
