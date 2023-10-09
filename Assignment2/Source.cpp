#include <iostream>
using namespace std;

class node {
public:
	char symbol;
	node *next;
};


class Saves {
private:
	node* saves[7];
	const int center = 3;

	node* GenerateSave(node* head) {
		node* newHead = (struct node*)malloc(sizeof(struct node));
		newHead->symbol = head->symbol;
		newHead->next = NULL;
		node* pointer = head->next;
		node* newPointer = newHead;
		while (pointer != NULL) {
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->symbol = pointer->symbol;
			newnode->next = NULL;
			newPointer->next = newnode;
			pointer = pointer->next;
			newPointer = newPointer->next;
		}
		return newHead;
	}

	void DeleteSave(node* head) {
		if (head == NULL) return;
		node* pointer = head;
		node* pointer2 = head->next;
		while (pointer2 != NULL) {
			free(pointer);
			pointer = pointer2;
			pointer2 = pointer2->next;
		}
		free(pointer);
	}
public:
	void Save(node* headToSave) {
		node* save = GenerateSave(headToSave);
		if (saves[center] == NULL) {
			saves[center] = save;
		}
		else {
			free(saves[0]);
			for (int i = 0; i < center; i++) {
				saves[i] = saves[i + 1];
			}
			saves[center] = save;
		}
	}
	node* Back() {
		if (saves[center - 1] == NULL) {
			return NULL;
		}
		else {
			DeleteSave(saves[6]);
			for (int i = 6; i > 0; i--) {
				saves[i] = saves[i - 1];
			}
			saves[0] = NULL;
			return saves[center];
		}
	}
	node* Forward() {
		if (saves[center + 1] == NULL) {
			return NULL;
		}
		else {
			DeleteSave(saves[0]);
			for (int i = 0; i < 6; i++) {
				saves[i] = saves[i + 1];
			}
			saves[6] = NULL;
			return saves[center];
		}
	}
};


class LinkedString {
private:
	node* head;
	Saves saves;
	string buffer;

	void Save() {
		this->saves.Save(this->head);
	}
	void LoadSave(node* save) {
		this->head->symbol = save->symbol;
		this->head->next = NULL;
		node* savePointer = save->next;
		node* pointer = head;
		while (savePointer != NULL) {
			if (pointer->next == NULL) {
				struct node* newnode = (struct node*)malloc(sizeof(struct node));
				newnode->symbol = savePointer->symbol;
				newnode->next = NULL;
				pointer->next = newnode;
			}
			else {
				pointer->next->symbol = savePointer->symbol;
			}
			savePointer = savePointer->next;
			pointer = pointer->next;
		}
		
		if (pointer->next != NULL)
		{
			node* pointer2 = pointer->next;
			pointer->next = NULL;
			pointer = pointer2;
			pointer2 = pointer->next;
			while (pointer2 != NULL) {
				free(pointer);
				pointer = pointer->next;
				pointer2 = pointer2->next;
			}
			free(pointer);
		}
	}
public:
	LinkedString() {
		this->head = (struct node*)malloc(sizeof(struct node));
		this->head->next = NULL;
		Save();
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
		Save();
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
		Save();
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
		Save();
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
		Save();
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
		Save();
	}

	void Undo() {
		node* save = saves.Back();
		if (save == NULL) {
			cout << "no such save:(";
			return;
		}
		LoadSave(save);
	}
	void Redo() {
		node* save = saves.Forward();
		if (save == NULL) {
			cout << "no such save:(\n";
			return;
		}
		LoadSave(save);
	}
	void Cut() {
		int line;
		int sym;
		int num;
		this->buffer = "";
		cout << "Choose line, index and number of symbols:";
		cin >> line >> sym >> num;
		struct node* pointer = this->head;

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
			num--;
			pointer = pointer->next;
			if (pointer == NULL) {
				cout << "no such symbol";
				buffer = "";
				break;
			}
			
			this->buffer = this->buffer + pointer->symbol;
			
			
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
		Save();
	}
	void Copy() {
		int line = 0;
		int sym;
		int num;
		this->buffer = "";
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
		while (num > 0) {
			if (pointer == NULL) {
				cout << "no such symbol";
				buffer = "";
				break;
			}
			num--;
			this->buffer += pointer->symbol;
			pointer = pointer->next;
		}
	}

	void Paste() {
		int line;
		int sym;
		int num;
		cout << "Choose line and index:";
		cin >> line >> sym;
		struct node* pointer = this->head;
		
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
			cout << "-";
		}
		node* tail = pointer->next;
		int i = 0;
		while (this->buffer[i] != '\0') {
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->symbol = this->buffer[i];
			newnode->next = NULL;
			pointer->next = newnode;
			pointer = pointer->next;
			i++;
		}
		pointer->next = tail;
		Save();
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
		case 9:
			text.Undo();
			break;
		case 10:
			text.Redo();
			break;
		case 11:
			text.Cut();
			break;
		case 12:
			text.Copy();
			break;
		case 13:
			text.Paste();
			break;
		default:
			break;
		}
	}
	return 0;
}