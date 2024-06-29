#include <stdio.h>
#include <stdlib.h>
#include "document.h"
#include "document.c"

/*IN HERE I WILL BE TEST THE TWO FUNCTIONS I ADDED TO DOCUMENT.C*/

int main() {
   Document doc;
   const char *doc_name = "Exercise Description";
   int paragraph_number;

   if (init_document(&doc, doc_name) == FAILURE) {
      printf("Intialization failed\n");
   } else {
      print_document(&doc);       
   }

   /* Adding first paragraph */
   paragraph_number = 0;
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);
   add_paragraph_after(&doc, paragraph_number);   add_paragraph_after(&doc, paragraph_number);
   if (add_paragraph_after(&doc, paragraph_number) == FAILURE)
      printf("Success\n");


   print_document(&doc);

   return 0;
}