#include<bits/stdc++.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
char faf[100];
int fa=0;
int eval(int op1, int op2, char operate) {
   switch (operate) {
      case '*': return op2 * op1;
      case '/': return op2 / op1;
      case '+': return op2 + op1;
      case '-': return op2 - op1;
      default : return 0;
   }
}

// evaluates the postfix operation
// this module neither supports multiple digit integers
// nor looks for valid expression
// However it can be easily modified and some additional
// code can be added to overcome the above mentioned limitations
// it's a simple function which implements the basic logic to
// evaluate postfix operations using stack
int evalPostfix(char postfix[], int size) {
   stack<int> s;
   int i = 0;
   char ch;
   int val;
   while (i < size) {
      ch = postfix[i];
      if (isdigit(ch)) {
         // we saw an operand
         // push the digit onto stack
         s.push(ch-'0');
      }
      else {
         // we saw an operator
         // pop off the top two operands from the
         // stack and evalute them using the current
         // operator
         int op1 = s.top();
         s.pop();
         int op2 = s.top();
         s.pop();
         val = eval(op1, op2, ch);
         // push the value obtained after evaluating
         // onto the stack
         s.push(val);
      }
      i++;
   }
   return val;
}
// Simply determine if character is one of the four standard operators.
bool isOperator(char character) {
    if (character == '+' || character == '-' || character == '*' || character == '/') {
        return true;
    }
    return false;
}


// If the character is not an operator or a parenthesis, then it is assumed to be an operand.
bool isOperand(char character) {
    if (!isOperator(character) && character != '(' && character != ')') {
        return true;
    }
    return false;
}


// Compare operator precedence of main operators.
// Return 0 if equal, -1 if op2 is less than op1, and 1 if op2 is greater than op1.
int compareOperators(char op1, char op2) {
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) { return -1; }
    else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) { return 1; }
    return 0;
}


int main()
{
    // Empty character stack and blank postfix string.
    stack<char> opStack;
    string postFixString = "";

    char input[100];

    // Collect input
    cout << "Enter an expression: ";
    cin >> input;

    // Get a pointer to our character array.
    char *cPtr = input;

    // Loop through the array (one character at a time) until we reach the end of the string.
    while (*cPtr != '\0') {
        // If operand, simply add it to our postfix string.
        // If it is an operator, pop operators off our stack until it is empty, an open parenthesis or an operator with less than or equal precedence.
        if (isOperand(*cPtr)) { postFixString += *cPtr; }
        else if (isOperator(*cPtr)) {
            while (!opStack.empty() && opStack.top() != '(' && compareOperators(opStack.top(),*cPtr) <= 0) {
                postFixString += opStack.top();
                opStack.pop();
            }
            opStack.push(*cPtr);
        }
        // Simply push all open parenthesis onto our stack
        // When we reach a closing one, start popping off operators until we run into the opening parenthesis.
        else if (*cPtr == '(') { opStack.push(*cPtr); }
        else if (*cPtr == ')') {
            while (!opStack.empty()) {
                if (opStack.top() == '(') { opStack.pop(); break; }
                postFixString += opStack.top();
                opStack.pop();
            }
        }

        // Advance our pointer to next character in string.
        cPtr++;
    }

    // After the input expression has been ran through, if there is any remaining operators left on the stack
    // pop them off and put them onto the postfix string.
    while (!opStack.empty()) {
        postFixString += opStack.top();
        opStack.pop();
    }


    // Show the postfix string at the end.
   // cout << "Postfix is: " << postFixString << endl;
   for(int i=0;postFixString[i]!='\0';++i){
    faf[fa++]=postFixString[i];
   }
   for(int i=0;i<fa;++i){
    printf("%c",faf[i]);
   }

    // char postfix[] = {'5','6','8','+','/','2','/'};
   // char postfix[]={'2','3','*','2','1','-','/','5','3','*','+'};
   int size = strlen(faf);
   //printf("%d\n",size);
   int val = evalPostfix(faf, size);
   cout<<"\nExpression evaluates to "<<val;
   cout<<endl;
   return 0;
}
