#include <iostream>
#include <string>
#include <cmath>
#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
#include "queuecoll.h"
#include "stackcoll.h"

using namespace std;

/* Function prototypes*/
static void printHelp();
bool isOperator(string ch);
QueueCOLL<string> convertToPostfix(string line);
int opPriority(char op);
double calculate(double o1, double o2, string op);
double evaluatePostfixExpression(QueueCOLL<string> &line);
bool checkParenthesis(string expression);
string filterExpr(string expression);

/* Main programm*/
int main()
{

    printHelp();
    while (true) {
        string expr = getLine("Enter an expression an press Enter to calculate the result:\n ");
        if(expr == "q" || expr == "Q"){
            cout << "Goodbye. Pres Alt+F4 to close the window.";
            exit(EXIT_SUCCESS);
        }
        expr = filterExpr(expr);

        if (checkParenthesis(expr)){
            QueueCOLL<string> polNot = convertToPostfix(expr);
            double result = evaluatePostfixExpression(polNot);
            cout << "Result: " + expr + " = " << result << endl << endl;
        } else {
            cout << "Wrong expression!!!" << endl;
        }

    }

    return 0;
}

/**
 * Function: printHelp
 * Usage: printHelp()
 * ----------------------------------------------------------------
 * The function prints the prompt to use the calculator
 */
static void printHelp()
{
    cout << "Calculator commands:\n"
            "+, -, *, / -  Ariphmetic operations\n"
            "^          -  Exponentiation\n"
            "q or Q     -  Exit\n\n";

}



/**
 * Function: isOperator
 * Usage: if (isOperator())
 * ---------------------------------------------------------------
 * @param ch - character for cheking
 * @return - true if ch is operator and false if not
 */
bool isOperator(string ch)
{
     return (ch == "+" || ch == "-" || ch == "/" || ch == "*" || ch == "^");
}

/**
 * Function: convertToPostfix
 * Usage: QueueCOLL<string> polNot = convertToPostfix(expr)
 * ------------------------------------------------------------------
 * Function converts the resulting string to a string reverse Polish notation
 * @param line - infix expression
 * @return - resived string in reverse polish notation in the queue
 */
QueueCOLL<string> convertToPostfix(string line)
{
    QueueCOLL<string> result;
        StackCOLL<string> operators;
        TokenScanner scanner(line);
        scanner.addOperator("+");
        scanner.addOperator("-");
        scanner.addOperator("*");
        scanner.addOperator("/");
        scanner.addOperator("^");
        scanner.scanNumbers();
        scanner.ignoreWhitespace();

        bool minusTrigger = false;
        string prevToken = "";

        while(scanner.hasMoreTokens()){
            string token = scanner.nextToken();

            if (isdigit(token[0]) && minusTrigger){
                string tmpStr = "-" + token;

                result.enqueue(tmpStr);
                minusTrigger = false;
            } else if (isdigit(token[0])){
                result.enqueue(token);
            } else if ((token == "-" && prevToken == "") || (token == "-" && prevToken == "(")){
                minusTrigger = true;

            } else if (token == "(") {
                operators.push(token);
            } else if (token == ")") {
                while (operators.top() != "(" ) {
                    result.enqueue(operators.pop());
                }
                operators.pop();
            } else if (isOperator(token)) {
                while (operators.size() > 0 && opPriority(operators.top()[0]) >= opPriority(token[0]) ) {
                    result.enqueue(operators.pop());
                }
                operators.push(token);
            }
            prevToken = token;
        }
        while (!operators.isStackEmpty()) {
            result.enqueue(operators.pop());
        }

        return result;
}

/**
 * Function: opPriority
 * Usage: while (operators.size() > 0 && opPriority(operators.top()[0]) >= opPriority(token[0]))
 * ---------------------------------------------------------------------------------------------
 * The function determines the sequence of math operations
 * @param op - operator to check
 * @return  priority of the operator
 */
int opPriority(char op)
{
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;

        }
        return 0;
}

/**
 * Function: calculate
 * Usage: numbers.push(calculate(o1,o2,tmp))
 * --------------------------------------------
 * Function produces the mathematical operation with the received operands
 * @param o1 - left operand
 * @param o2 - right operand
 * @param op - operator
 * @return - result
 */
double calculate(double o1, double o2, string op)
{
    double result = 0.0;

        if (op == "+"){
            result = o1 + o2;
        } else if (op == "-") {
            result = o1 - o2;
        } else if (op == "*") {
            result = o1 * o2;
        } else if (op == "/") {
            result = o1 / o2;
        } else if (op == "^") {
            result = pow(o1, o2);
        }
        return result;
}

/**
 * Function: evaluatePostfixExpression
 * Usage: double result = evaluatePostfixExpression(polNot)
 * ---------------------------------------------
 * This function takes an expression in Postfix notation, and computes
 * its value according to Shunting-yard algorithm
 * @param line -  recived queue in RPN
 * @return - result of the expression
 */
double evaluatePostfixExpression(QueueCOLL<string> &line)
{
    StackCOLL<double> numbers;

        while (!line.isQueueEmpty()) {
            string tmp = line.dequeue();
            if (tmp.length() > 1 && tmp[0] == '-'){
                numbers.push(-stod(tmp.substr(1)));
            } else if (tmp.length() > 1 && isdigit(tmp[0])){
                numbers.push(stod(tmp));
            } else if (isdigit(tmp[0])){
                numbers.push(stod(tmp));
            } else {
                double o2 = numbers.pop();
                double o1 = numbers.pop();
                numbers.push(calculate(o1, o2, tmp));
            }
        }
        return numbers.pop();
}

/**
 * Function: checkParenthesis
 * Usage: if (checkParenthesis(expr))
 * ---------------------------------------------------
 * This function verifies the correct placement of brackets
 * @param expression - The string in which you want to check the correct placement of brackets
 * @return - true if recived expression is corect and false if isn't
 */
bool checkParenthesis(string expression)
{
    bool result = true;
       StackCOLL<char> stack;
       for(char ch: expression){
           if(ch == '('){
               stack.push(ch);
           }
           if (ch == ')' && !stack.isStackEmpty()){
               stack.pop();
           } else if (ch == ')' && stack.isStackEmpty()) {
               result = false;
           }

       }
       if (!stack.isStackEmpty()){
           result = false;
       }

       return result;
}

/**
 * Function: filterExpr
 * Usage: expr = filterExpr()
 * ------------------------------------------
 * This function filters the given expression
 * @param expression - the filtered string
 * @return A string without extra characters
 */
string filterExpr(string expression)
{
    string result;
       for(char ch: expression){
           if (isdigit(ch) || isOperator(string(1,ch)) || ch == '(' || ch == ')' || ch == '.'){
               result += ch;
           }
       }


       return result;
}



