#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#include "csv.h"
#include "bit.h"

// Function to fill the dictionary (linked list)
Node* fill_dictionary(const char *filename) {

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[LINE_MAX];
    // header
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return NULL; }

    Node *head = NULL, *tail = NULL;

    while (fgets(line, sizeof(line), fp)) {
        // trim newline
        size_t len = strlen(line);
        while (len && (line[len-1]=='\n' || line[len-1]=='\r')) line[--len] = '\0';
        if (!len) continue;

        char headers[FIELD_MAX][STRLEN];
        line_split(line, headers);
        Address *rec = make_address(headers);

        Node *node = malloc(sizeof(*node));
        if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
        node->data = rec;
        node->next = NULL;

        if (tail) { 
            tail->next = node; tail = node; 
        } else { 
            head = tail = node; 
        }
    }

    fclose(fp);
    return head;   
}

// Function to perform key lookup on dictionary (linked list)

void key_lookup(const Node *head, const char *query, FILE *output_file) {
    int found = 0;
    int nodes = 0;
    int strings = 0;
    int bits = 0;

    fprintf(output_file, "%s\n", query);

    for (const Node *n = head; n != NULL; n = n->next) {
        nodes += 1;                                         // one node visited
        strings += 1;                                       // one strcmp
        bits += bit_comparisons(n->data->EZI_ADD, query);   // bit comparisons

        if (strcmp(n->data->EZI_ADD, query) == 0) {
            print_record_summary(output_file, n->data);
            found++;
        }
    } 
    if (found == 0) {
        fprintf(output_file, "NOTFOUND\n");
    }

    printf("%s --> %d records found - comparisons: b%d n%d s%d\n",
           query, found, bits, nodes, strings);
    fflush(stdout);
}

// Helper function to fill each address

static Address *make_address(char fields[FIELD_MAX][STRLEN]) {
    Address *a = malloc(sizeof *a);
    if (!a) { perror("malloc"); exit(1); }

    char *field_ptrs[FIELD_MAX] = {
        a->PFI, a->EZI_ADD, a->SRC_VERIF, a->PROPSTATUS, a->GCODEFEAT, a->LOC_DESC,
        a->BLGUNTTYP, a->HSAUNITID, a->BUNIT_PRE1, a->BUNIT_ID1, a->BUNIT_SUF1,
        a->BUNIT_PRE2, a->BUNIT_ID2, a->BUNIT_SUF2, a->FLOOR_TYPE, a->FLOOR_NO_1,
        a->FLOOR_NO_2, a->BUILDING, a->COMPLEX, a->HSE_PREF1, a->HSE_NUM1,
        a->HSE_SUF1, a->HSE_PREF2, a->HSE_NUM2, a->HSE_SUF2, a->DISP_NUM1,
        a->ROAD_NAME, a->ROAD_TYPE, a->RD_SUF, a->LOCALITY, a->STATE, a->POSTCODE,
        a->ACCESSTYPE
    };

    // copy 33 string fields
    for (int i = 0; i < (FIELD_MAX-2); i++) {
        strncpy(field_ptrs[i], fields[i], STRLEN-1);
        field_ptrs[i][STRLEN - 1] = '\0';
    }

    // coordinates
    a->x = parse_ld_or_zero(fields[33]);
    a->y = parse_ld_or_zero(fields[34]);  

    return a;
}

// Print Record Function 

static void print_record_summary(FILE *out, const Address *a) {
    fprintf(out,
        "--> PFI: %s || EZI_ADD: %s || SRC_VERIF: %s || PROPSTATUS: %s || "
        "GCODEFEAT: %s || LOC_DESC: %s || BLGUNTTYP: %s || HSAUNITID: %s || "
        "BUNIT_PRE1: %s || BUNIT_ID1: %s || BUNIT_SUF1: %s || "
        "BUNIT_PRE2: %s || BUNIT_ID2: %s || BUNIT_SUF2: %s || "
        "FLOOR_TYPE: %s || FLOOR_NO_1: %s || FLOOR_NO_2: %s || "
        "BUILDING: %s || COMPLEX: %s || "
        "HSE_PREF1: %s || HSE_NUM1: %s || HSE_SUF1: %s || "
        "HSE_PREF2: %s || HSE_NUM2: %s || HSE_SUF2: %s || "
        "DISP_NUM1: %s || ROAD_NAME: %s || ROAD_TYPE: %s || RD_SUF: %s || "
        "LOCALITY: %s || STATE: %s || POSTCODE: %s || ACCESSTYPE: %s || "
        "x: %.5Lf || y: %.5Lf || \n",
        a->PFI, a->EZI_ADD, a->SRC_VERIF, a->PROPSTATUS,
        a->GCODEFEAT, a->LOC_DESC, a->BLGUNTTYP, a->HSAUNITID,
        a->BUNIT_PRE1, a->BUNIT_ID1, a->BUNIT_SUF1,
        a->BUNIT_PRE2, a->BUNIT_ID2, a->BUNIT_SUF2,
        a->FLOOR_TYPE, a->FLOOR_NO_1, a->FLOOR_NO_2,
        a->BUILDING, a->COMPLEX,
        a->HSE_PREF1, a->HSE_NUM1, a->HSE_SUF1,
        a->HSE_PREF2, a->HSE_NUM2, a->HSE_SUF2,
        a->DISP_NUM1, a->ROAD_NAME, a->ROAD_TYPE, a->RD_SUF,
        a->LOCALITY, a->STATE, a->POSTCODE, a->ACCESSTYPE,
        a->x, a->y
    );
}

void free_list(Node *head) {
    while (head) {
        Node *n = head->next;
        free(head->data);
        free(head);
        head = n;
    }
}
