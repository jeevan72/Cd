#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
#define MAX 200
 
char opStack[MAX];
char valStack[MAX][20];
int topOp = -1, topVal = -1;
int tempCount = 1;
 
int precedence(char op) {
   if (op == '+' || op == '-') return 1;
   if (op == '*' || op == '/') return 2;
   return 0;
}
 
void pushOp(char op) {
   opStack[++topOp] = op;
}
 
char popOp() {
   return opStack[topOp--];
}
 
void pushVal(char *val) {
   strcpy(valStack[++topVal], val);
}
 
void popVal(char *val) {
   strcpy(val, valStack[topVal--]);
}
 
void generate() {
   char op = popOp();
   char op1[20], op2[20], temp[20];
 
   popVal(op2);
   popVal(op1);
 
   sprintf(temp, "t%d", tempCount++);
   printf("%s = %s %c %s\n", temp, op1, op, op2);
 
   pushVal(temp);
}
 
int main() {
   char exp[MAX];
   printf("Enter Expression: ");
   scanf("%s", exp);
 
   for (int i = 0; exp[i] != '\0'; i++) {
       char ch = exp[i];
 
       if (isalnum(ch)) {
           char operand[2] = {ch, '\0'};
           pushVal(operand);
       }
       else if (ch == '(') {
           pushOp(ch);
       }
       else if (ch == ')') {
           while (opStack[topOp] != '(') {
               generate();
           }
           popOp(); // remove '('
       }
       else {
           while (topOp != -1 && precedence(opStack[topOp]) >= precedence(ch))
{
               generate();
           }
           pushOp(ch);
       }
   }
 
   while (topOp != -1) {
       generate();
   }
 
   return 0;
}