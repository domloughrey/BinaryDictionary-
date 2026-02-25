#ifndef _DATA_H
#define _DATA_H

#define FIELD_MAX 35
#define STRLEN    128
#define LINE_MAX  1024

typedef struct {
	char  PFI[STRLEN];
    char  EZI_ADD[STRLEN];
    char  SRC_VERIF[STRLEN];
    char  PROPSTATUS[STRLEN];
    char  GCODEFEAT[STRLEN];
    char  LOC_DESC[STRLEN];
    char  BLGUNTTYP[STRLEN];
    char  HSAUNITID[STRLEN];
    char  BUNIT_PRE1[STRLEN];
    char  BUNIT_ID1[STRLEN];   
    char  BUNIT_SUF1[STRLEN];
    char  BUNIT_PRE2[STRLEN];
    char  BUNIT_ID2[STRLEN];
    char  BUNIT_SUF2[STRLEN];
    char  FLOOR_TYPE[STRLEN];
    char  FLOOR_NO_1[STRLEN];
    char  FLOOR_NO_2[STRLEN];
    char  BUILDING[STRLEN];
    char  COMPLEX[STRLEN];
    char  HSE_PREF1[STRLEN];
    char  HSE_NUM1[STRLEN];
    char  HSE_SUF1[STRLEN];
    char  HSE_PREF2[STRLEN];
    char  HSE_NUM2[STRLEN];
    char  HSE_SUF2[STRLEN];
    char  DISP_NUM1[STRLEN];
    char  ROAD_NAME[STRLEN];
    char  ROAD_TYPE[STRLEN];
    char  RD_SUF[STRLEN];
    char  LOCALITY[STRLEN];
    char  STATE[STRLEN];
    char  POSTCODE[STRLEN];
    char  ACCESSTYPE[STRLEN];
    long double x;  // longitude
    long double y;  // latitude  
} Address;

typedef struct Node {
    Address *data;
    struct Node *next;
} Node;

// Function Prototypes

Node *fill_dictionary(const char *filename);
void key_lookup(const Node *head, const char *query, FILE *output_file);

// Helper Function Prototypes

static Address *make_address(char fields[FIELD_MAX][STRLEN]);
static void print_record_summary(FILE *out, const Address *a);
void free_list(Node *head);


#endif
