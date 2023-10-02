#include <iostream>
using namespace std;

class node {
public:
	char symbol;
	node *next;
};


class LinkedString {
private:
	node* head;
public:
	LinkedString() {
		this->head = (struct node*)malloc(sizeof(struct node));
		this->head->next = NULL;
	}


	void AppendInput() {
		node* pointer;
		char text[80];
		printf("Enter text to append:");
		char clear;
		scanf_s("%c", &clear);
		scanf_s("%[^\n]", text, sizeof(text));
		int i = 0;
		pointer = this->head;
		while (pointer->next != NULL) {
			pointer = pointer->next;
		}
		while (text[i] != '\0') {
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->symbol = text[i];
			newnode->next = NULL;
			pointer->next = newnode;
			pointer = pointer->next;
			i++;
		}
	}


	void StartNewLine() {
		struct node* pointer;
		pointer = this->head;
		while (pointer->next != NULL) {
			pointer = pointer->next;
		}
		struct node* newnode = (struct node*)malloc(sizeof(struct node));
		newnode->symbol = '\n';
		newnode->next = NULL;
		pointer->next = newnode;
		printf("New line is started\n");
	}


	void SaveToFile() {
		printf("Enter file name for saving:");
		char filename[40];
		scanf_s("%s", filename, sizeof(filename));
		FILE* myFile;
		fopen_s(&myFile, filename, "w");
		struct node* pointer = this->head->next;
		while (pointer != NULL) {
			fprintf(myFile, "%c", pointer->symbol);
			pointer = pointer->next;
		}
		fflush(myFile);
		fclose(myFile);
	}


	void AppendFromFile() {
		FILE* myFile;
		char filename[40];
		printf("Enter file name for reading:");
		scanf_s("%s", filename, sizeof(filename));
		fopen_s(&myFile, filename, "r");
		char symbol;
		struct node* pointer = this->head;
		while (pointer->next != NULL) {
			pointer = pointer->next;
		}
		if (myFile == NULL) {
			perror("Error opening file");
			return;
		}
		while ((symbol = fgetc(myFile)) != EOF) {
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->symbol = symbol;
			newnode->next = NULL;
			pointer->next = newnode;

			pointer = pointer->next;
		}
		fclose(myFile);
	}


	void Print() {
		struct node* pointer = this->head;
		while (pointer->next != NULL) {
			printf("%c", pointer->next->symbol);
			pointer = pointer->next;
		}
		printf("\n");
	}


	void Insert() {
		printf("Choose line and index:");
		int line, sym;
		scanf_s("%i %i", &line, &sym);
		struct node* pointer = this->head->next;
		while (line > 0 || sym > 0) {
			if (pointer == NULL) {
				printf("no such symbol");
				break;
			}
			if (pointer->symbol == '\n') {
				line--;
			}
			if (line == 0) {
				sym--;
			}
			pointer = pointer->next;
		}
		if (pointer == NULL) {
			return;
		}
		printf("Enter text to append:");
		char clear;
		char text[80];
		scanf_s("%c", &clear);
		scanf_s("%[^\n]", text, sizeof(text));
		int i = 0;
		struct node* tail = pointer->next;
		while (text[i] != '\0') {
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->symbol = text[i];
			newnode->next = NULL;
			pointer->next = newnode;
			pointer = pointer->next;
			i++;
		}
		pointer->next = tail;
	}


	void Search() {
		printf("Enter text to search:");
		char text[80];
		char clear;
		scanf_s("%c", &clear);
		scanf_s("%[^\n]", text, sizeof(text));
		struct node* pointer = this->head->next;
		int line = 0;
		int sym = 0;
		while (pointer->next != NULL)
		{

			if (pointer->symbol == text[0]) {
				struct node* pointer2 = pointer->next;
				int i = 1;
				while (text[i] != '\0' && pointer2 != NULL)
				{
					if (text[i] != pointer2->symbol) {
						break;
					}
					i++;
					pointer2 = pointer2->next;
				}
				if (text[i] == '\0') {
					printf("Text is present in this position: %i %i\n", line, sym);
				}
			}
			sym++;
			if (pointer->symbol == '\n') {
				line++;
				sym = 0;
			}
			pointer = pointer->next;
		}
	}

	void Delete() {
		int line;
		int sym;
		int num;
		cout << "Choose line, index and number of symbols:";
		cin >> line >> sym >> num;
		struct node* pointer = this->head->next;

		while (line > 0 || sym > 0) {
			if (pointer == NULL) {
				cout << "no such symbol";
				break;
			}
			if (pointer->symbol == '\n') {
				line--;
			}
			if (line == 0) {
				sym--;
			}
			pointer = pointer->next;
		}
		if (pointer == NULL) {
			return;
		}
		node* tail = pointer;
		while (num > 0) {
			if (pointer == NULL) {
				cout << "no such symbol";
				break;
			}
			num--;
			pointer = pointer->next;
		}
		if (pointer == NULL) {
			return;
		}
		if (pointer->next == NULL) {
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->symbol = NULL;
			newnode->next = NULL;
			pointer->next = newnode;
		}
		tail->next = pointer->next;
	}
};

int main() {
	LinkedString text;
	int command;
	while (true) {
		cout << "Enter command: ";
		cin >> command;
		switch (command)
		{
		case 1:
			text.AppendInput();
			break;
		case 2:
			text.StartNewLine();
			break;
		case 3:
			text.SaveToFile();
			break;
		case 4:
			text.AppendFromFile();
			break;
		case 5:
			text.Print();
			break;
		case 6:
			text.Insert();
			break;
		case 7:
			text.Search();
			break;
		case 8:
			text.Delete();
			break;
		default:
			break;
		}
	}
	return 0;
}