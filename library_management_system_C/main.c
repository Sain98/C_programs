#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Book
{
	int book_id;

	char* name;
	char* author;
	char* category;
	char* release_date;
};

char* FILE_NAME = "books.txt";

/* ================ */

/* BOOK DISPLAY */

void book_print_array(struct Book* b, int i)
{
	printf("============\n");
	printf("ID: %d\n", 				b[i].book_id);
	printf("Name: %s\n", 			b[i].name);
	printf("Author: %s\n", 			b[i].author);
	printf("Category: %s\n", 		b[i].category);
	printf("Release date: %s\n\n",	b[i].release_date);
}

void book_print(struct Book* b)
{
	printf("============\n");
	printf("ID: %d\n", 				b->book_id);
	printf("Name: %s\n", 			b->name);
	printf("Author: %s\n", 			b->author);
	printf("Category: %s\n", 		b->category);
	printf("Release date: %s\n\n",	b->release_date);
}

/* ================ */

/* BOOK HANDLING */

void book_write_new(struct Book* b)
{
	// Add new book to the list and write to books file
	FILE *fp;

	fp = fopen( FILE_NAME, "a");

	fputs(b->name, fp);
	fputs("\n", fp);

	fputs(b->author, fp);
	fputs("\n", fp);

	fputs(b->category, fp);
	fputs("\n", fp);

	fputs(b->release_date, fp);
	fputs("\n", fp);
	
	fclose(fp);
}

void book_new()
{
	struct Book b;

	char buff[128];
	memset(buff, 0, 128);

	printf("Name: ");
	fgets(buff, 128, stdin);
	strtok(buff, "\n");
	if (strcmp(buff, "\n") == 0) { 
		printf("No name given\n"); 
		strcpy(buff,"[NONE]");
	}
	b.name = malloc((strlen(buff)+1)*sizeof(char));
	strcpy(b.name, buff);

	printf("Author: ");
	fgets(buff, 128, stdin);
	strtok(buff, "\n");
	if (strcmp(buff, "\n") == 0) { 
		printf("No author given\n"); 
		strcpy(buff,"[NONE]");
	}
	b.author = malloc((strlen(buff)+1)*sizeof(char));
	strcpy(b.author, buff);

	printf("Category: ");
	fgets(buff, 128, stdin);
	strtok(buff, "\n");
	if (strcmp(buff, "\n") == 0) {
		printf("No category given\n"); 
		strcpy(buff,"[NONE]");
	}
	b.category = malloc((strlen(buff)+1)*sizeof(char));
	strcpy(b.category, buff);

	printf("Release date: ");
	fgets(buff, 128, stdin);
	strtok(buff, "\n");
	if (strcmp(buff, "\n") == 0) { 
		printf("No date given\n"); 
		strcpy(buff,"[NONE]");
	}
	b.release_date = malloc((strlen(buff)+1)*sizeof(char));
	strcpy(b.release_date, buff);

	b.book_id = 0;

	printf("New book values:\n");
	book_print(&b);

	printf("Adding new book to file... ");
	book_write_new(&b);
	printf("Done\n");
}

void book_edit(struct Book* b)
{
	// Edit existing book
}

struct Book* book_load(int id)
{
	FILE *fp;
	struct Book b;

	// line containing our book: id * 4 
	// (4 lines for each book)
	int book_location = id * 4;

	fp = fopen( FILE_NAME, "r");

	if (fp == NULL)
	{
		printf("No bookfile found! Add a book first\n");
	}
	else
	{
		printf("TODO\n");
	}

	/* TODO */
	/*
	for (int x = 0; x < book_location; x+=4)
	{
		//fgets();
	}
	*/

	fclose(fp);
	// Load book (id)
}

int book_count()
{
	FILE *fp;

	fp = fopen(FILE_NAME, "r");

	if (fp == NULL)
	{
		printf("No bookfile found!\n");
		fclose(fp);
		return 0;
	}
	else
	{
		int lines = 0;
		char ch;

		while(!feof(fp))
		{
			ch = fgetc(fp);
			if (ch == '\n')
			{
				lines++;
			}
		}

		fclose(fp);
		return lines / 4;
	}
}

void book_list()
{
	int count = book_count();

	printf("Detected %d books available\n", count);

	printf("Allocating array...\n");

	struct Book* b = (struct Book*)malloc(count*sizeof(struct Book));
	int x = 0;

	FILE *fp;
	fp = fopen( FILE_NAME, "r");
	if (fp == NULL) { printf("Book file not found\n"); }
	else
	{
		// printf("FILE OPEN\n");
		char buff[128];
		memset(buff, 0, 128);

		// b[x].name = "TEST BOOK";
		// printf("b0 name: %s\n", b[x].name);

		int lc = 1;
		int r = 0;
		while (fgets(buff, 128, fp)) // While not end of file -> ...
		{
			r = lc % 4;

			strtok(buff, "\n");
            if (r==1)
            {
                b[x].name=malloc((strlen(buff)+1)*sizeof(char));
                strcpy(b[x].name, buff);
            }
            if (r==2)
            {
                b[x].author=malloc((strlen(buff)+1)*sizeof(char));
                strcpy(b[x].author, buff);
            }

            if (r==3)
            {
                b[x].category=malloc((strlen(buff)+1)*sizeof(char));
                strcpy(b[x].category, buff);
            }

            if (r==0)
            {
                b[x].release_date=malloc((strlen(buff)+1)*sizeof(char));
                strcpy(b[x].release_date, buff);
                b[x].book_id = lc / 4;
                x++;
            }
			lc++;
		}

		fclose(fp);
	}

	for (int y = 0; y < x; y++)
	{
		book_print_array(b, y);
	}

	free(b);
}

/* ================ */

/* TEST CASES */

void testBook()
{
	struct Book b;
	b.book_id = 1;
	b.name = "Book name";
	b.author = "Sander";
	b.category = "Yes";
	b.release_date = "11/29/2019";

	book_print(&b);

	printf("Adding new book to file\n");

	book_write_new(&b);
}

/* ================ */

/* OPTION HANDLING */

void search(char* search)
{
	// TODO
}

void handle_choice(int* opt)	// int pointer to -> choice (main)
{
	printf("\nOPTION %i ( @ 0x%x )\n", *opt, opt);	// point to value in choice
	// printf("MEMORY LOC: 0x%x\n", opt);			// point to location of choice

	switch (*opt)
	{
		case 1:
			book_list();
			break;
		case 2:
			book_new();
			break;
		case 3:
		case 4:
			printf("TODO\n");
			break;
		case 5:
			testBook();
			break;
		default:
			printf("DEFAULT\n");
	}
}


/* ================ */

/* DRAWINGS */

void draw_menu() {
	printf("=============================\n");
	printf("| Library Management System |\n");
	printf("|       Written in C        |\n");
	printf("=============================\n");
	printf("| Options:                  |\n");
	printf("| 1 - List all books        |\n");
	printf("| 2 - Add a new book        |\n");
	printf("| 3 - Edit a book           |\n");
	printf("| 4 - Search                |\n");
	printf("| 0 - Exit                  |\n");
	printf("=============================\n");
	printf("\nChoice $> ");
}

/* ================ */

/* MAIN */

int main()
{

	char* inp;
	int in_size = 1 + 1; // +1 for null/string terminator
	int choice = 1;

	while (choice) // while choice != 0 -> ...
	{

		draw_menu();

		fgets(inp, in_size, stdin);
		while ((getchar()) != '\n');

		choice = atoi(inp);

		handle_choice(&choice);

	}
	
	return 0;
}

/* ================ */

/******
	// POINTERS BASICS
	int x = 5;
	printf("%i\n", x); 		// -> '5'			(VALUE OF X)
	printf("0x%x\n", &x); 	// -> '0x7a945c94'	(LOCATION OF X)
	int* y = &x;
	printf("%i\n", *y); 	// -> '5'		   	(VALUE OF 	 *Y -> X)
	printf("0x%x\n", y); 	// -> '0x7a945c94' 	(LOCATION OF *Y -> X)
	printf("0x%x\n", &y);	// -> '0x7a945c96' 	(LOCATION OF Y)

******/
