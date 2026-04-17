#include <stdio.h>
#include <string.h>
 
#define MAX 10
#define LEN 50
 
char prod[MAX][LEN];
int n;
 
void eliminateLeftRecursion() {
   printf("\n--- Eliminating Left Recursion ---\n");
 
   for (int i = 0; i < n; i++) {
       char lhs = prod[i][0];
       char alpha[MAX][LEN], beta[MAX][LEN];
       int a = 0, b = 0;
 
       char *token = strtok(prod[i] + 3, "|");
 
       while (token != NULL) {
           if (token[0] == lhs) {
               strcpy(alpha[a++], token + 1);
           } else {
               strcpy(beta[b++], token);
           }
           token = strtok(NULL, "|");
       }
 
       if (a > 0) {
           printf("%c -> ", lhs);
           for (int j = 0; j < b; j++) {
               printf("%s%c' ", beta[j], lhs);
               if (j < b - 1) printf("| ");
           }
 
           printf("\n%c' -> ", lhs);
           for (int j = 0; j < a; j++) {
               printf("%s%c' | ", alpha[j], lhs);
           }
           printf("ε\n");
       } else {
           printf("%s (No Left Recursion)\n", prod[i]);
       }
   }
}
 
void leftFactoring() {
   printf("\n--- Left Factoring ---\n");
 
   for (int i = 0; i < n; i++) {
       char lhs = prod[i][0];
       char temp[MAX][LEN];
       int count = 0;
 
       char *token = strtok(prod[i] + 3, "|");
       while (token != NULL) {
           strcpy(temp[count++], token);
           token = strtok(NULL, "|");
       }
 
       char prefix = temp[0][0];
       int flag = 1;
 
       for (int j = 1; j < count; j++) {
           if (temp[j][0] != prefix) {
               flag = 0;
               break;
           }
       }
 
       if (flag && count > 1) {
           printf("%c -> %c%c'\n", lhs, prefix, lhs);
           printf("%c' -> ", lhs);
 
           for (int j = 0; j < count; j++) {
               printf("%s", temp[j] + 1);
               if (j < count - 1) printf(" | ");
           }
           printf("\n");
       } else {
           printf("%s (No Left Factoring)\n", prod[i]);
       }
   }
}
 
int main() {
   printf("Enter number of productions: ");
   scanf("%d", &n);
 
   printf("Enter productions (e.g., A->Aa|b):\n");
   for (int i = 0; i < n; i++) {
       scanf("%s", prod[i]);
   }
 
   eliminateLeftRecursion();
   leftFactoring();
 
   return 0;
}