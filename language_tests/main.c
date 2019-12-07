#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INT
void alloc_int(char* name, char* value);
void modify_int(char* name, char* new_val);

// BOOL
void alloc_bool(char* var_name, unsigned char var_value);

// STRING
void alloc_str();

// STACK
void print_stack();

// INTERPRETER?/HANDLER
void handle_input(char* inp);

int MAX = 10;


struct Stack {
	int sp;	// stack pointer (last value on stack)

	// Variable storage
	char types[10];		// 'i' -> int, 's' -> str, 'b' -> bool
	char* names[10];	// variable names
	int values[10];		// variable values
	int* locations[10];	// variable pointers
};
struct Stack stack;


int main() {
	char* test_in = "int a = 4";
	char* in = malloc(sizeof(char) * 64);
	memset(in, 64, 0);

	stack.sp = 0;

	while(1) {

		printf("$> ");

		fgets(in, 64, stdin);
		//while ((getchar()) != '\n');

		strtok(in, "\n");

		if (strcmp(in, "exit") == 0)
		{
			break;
		}

		handle_input(in);

		print_stack();

	}

	return 0;
}

/*
	Programming language tests
	- making variables:
	types = int, str, bool;
	ex usage:
	int a = 4;
*/

void print_stack()
{
	int x = 0;

	printf("=================\n");
	printf("SP: %d\n", stack.sp);
	printf("\nVARIABLES:\n");

	for (; x < stack.sp; x++)
	{
		printf("TYPE: %c | NAME: %s | VALUE: %d | LOCATION: 0x%x |\n",
			stack.types[x], stack.names[x], 
			stack.values[x], stack.locations[x]
			);
	}

	printf("=================\n");
}

void handle_input(char* inp)
{
	printf("%s | %ld\n", inp, strlen(inp));

	char split[MAX][MAX];

	int x = 0;
	int y = 0;
	int z = 0;
	for (x = 0; x < strlen(inp); x++)
	{
		if (inp[x] == ' ') {
			printf("Match x: %d | y: %d | z: %d\n", x, y, z);
			split[y][z] = '\0';
			y++;
			z = 0;
		}
		else
		{
			printf("%d | %c\n", x, inp[x]);

			split[y][z] = inp[x];

			z++;
		}
	}

	// Print split:
	printf("SPLIT:\n");
	for (x = 0; x < y+1; x++)
	{
		printf("'%s'\n", split[x]);
	}

	//    0          1       2      3
	// var type | var name | = | var value
	char* var_type  = malloc(sizeof(char) * strlen(split[0]));
	strcpy(var_type, split[0]);

	char* var_name  = malloc(sizeof(char) * strlen(split[1]));
	strcpy(var_name, split[1]);

	char* var_value = malloc(sizeof(char) * strlen(split[3]));
	strcpy(var_value, split[3]);


	printf("\nVARIABLE ALLOCATING\n");
	if (strcmp(var_type, "int") == 0)
	{
		printf("Allocating int size variable\n");
		alloc_int(var_name, var_value);
	}
	else
	{
		// var_type is not a known type?
		// Perhaps a var_name
		printf("Unknown variable type..\n");
		printf("%s | %s\n", var_type, split[2]);
		modify_int(var_type, split[2]);
	}
}

void alloc_int(char* name, char* value)
{
	stack.types[stack.sp] = 'i';

	stack.names[stack.sp] = malloc(sizeof(char) * strlen(name));
	strcpy(stack.names[stack.sp], name);

	stack.values[stack.sp] = atoi(value);

	stack.locations[stack.sp] = &stack.values[stack.sp];

	stack.sp++;
}

void modify_int(char* name, char* new_val)
{
	// Find 'name' location in stack
	int x;
	for (x = 0; x < stack.sp; x++)
	{
		if (strcmp(stack.names[x], name) == 0)
		{
			// printf("MATCH FOUND\n");
			stack.values[x] = atoi(new_val);
			break;
		}
	}
}

void alloc_str() 
{

}

void alloc_bool(char* var_name, unsigned char var_value)
{

}