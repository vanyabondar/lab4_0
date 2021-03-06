// lab4_0.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct stack_int {
	int data;
	stack_int* next;
};

struct stack_char {
	char data;
	stack_char* next;
};

void Push(stack_int** next_Node, int data) {
	stack_int* temp = new stack_int;
	temp->data = data;
	temp->next = *next_Node;
	*next_Node = temp;
}

void Push(stack_char** next_Node, char data) {
	stack_char* temp = new stack_char;
	temp->data = data;
	temp->next = *next_Node;
	*next_Node = temp;
}

int Pop(stack_int** Stack) {
	stack_int* temp = (*Stack)->next;
	int rez = (*Stack)->data;
	delete *Stack;
	*Stack = temp;
	return rez;
}

char Pop(stack_char** Stack) {
	stack_char* temp = (*Stack)->next;
	char rez = (*Stack)->data;
	delete *Stack;
	*Stack = temp;
	return rez;
}


string delete_passes(string s) {
	string rez = "";
	for (int i = 0; i < s.length(); i++)
		if (s[i] != ' ')
			rez += s[i];
	return rez;
}

bool is_operator(char ch) {
	return (ch == '+') || (ch == '-')
		|| (ch == '*') || (ch == '/')
		|| (ch == '(') || (ch == ')')
		|| (ch == '^') || (ch == ':');
}

int Perform(int a, int b, char op) {
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
	case ':':
		return a / b;
	case '^':
		return pow(a, b);
	}
}

void Take_out(stack_char** sc, stack_int** si) {
	int b = Pop(si);
	int a = Pop(si);
	char op = Pop(sc);
	Push(si, Perform(a, b, op));
}

int prioritet(char c){
	switch (c)
	{
	case '+':
		return 4;
	case '-':
		return 4;
	case '*':
		return 3;
	case '/':
	case ':':
		return 3;
	case '^':
		return 2;
	case '(':
		return 5;
	case ')': 
		return 1;
	}
}
void Add_operator(stack_char** sc, stack_int** si, char op) {
	if (!(*sc)) {
		Push(sc, op);
		return;
	}
	if (op == ')') {
		while ((*sc)->data != '(')
			Take_out(sc, si);
		Pop(sc);
		return;
	}
	if (op == '(') {
		Push(sc, op);
		return;
	}
	while ((*sc) && (prioritet((*sc)->data) <= prioritet(op)))
		Take_out(&*sc, si);
	Push(sc, op);
	
}
int calc(string s) {
	s = "(" + s + ")";
	int i = 0;
	stack_char* sc = nullptr;
	stack_int* si = nullptr;
	
	while (i < s.length()) {
		string op = "";
		while (!is_operator(s[i])) {
			op += s[i];
			i++;
		}
		if (op != "") {
			Push(&si, stoi(op));
			op = "";
		}
		Add_operator(&sc, &si, s[i]);
		i++;
	}
	return 	Pop(&si);

}
int main()
{
	string expression;
	getline(cin, expression);
	expression = delete_passes(expression);
	int rez = calc(expression);
	cout << rez << endl;
	system("pause");
	return 0;
}

