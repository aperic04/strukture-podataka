#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _StackElement;
typedef struct _StackElement* Position;

typedef struct _StackElement {
    double number;
    Position next;
}StackElement;


Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* resultDestination, Position head);
int PerformOperation(Position head, char operator);
int CalculatePostfixFromFile(double* resultDestination, char* fileName);
int DeleteAll(Position head);

Position CreateElement(double number) {
    Position newElement = NULL;
 newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int InsertAfter(Position position, Position newElement) {
    newElement->next = position->next;
    position->next = newElement;
}

int Push(Position head, double number) {
    Position newElement = NULL;
    newElement = CreateElement(number);
    if (!newElement) {
        return EXIT_FAILURE;
    }

    InsertAfter(head, newElement);
    return EXIT_SUCCESS;
}

int DeleteAfter(Position position) {
    Position temp = position->next;
    if (!temp) {
        return EXIT_SUCCESS;
    }
    position->next = temp->next;
    free(temp);
    return EXIT_SUCCESS;
}
int Pop(double* resultDestination, Position head) {
    Position first = head->next; 

    if (!first)
    {
        printf("Postfix nije dobar!");
        return -1;
    }
    *resultDestination = first->number;

    DeleteAfter(head);

    return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operator) {
    double operand1 = 0;
    double operand2 = 0;
    double result = 0;
    int status1 = EXIT_SUCCESS;
    int status2 = EXIT_SUCCESS;

    status2 = Pop(&operand2, head);
    if (status2 != EXIT_SUCCESS) {
        return -1;
    }

    status1 = Pop(&operand1, head);
    if (status1 != EXIT_SUCCESS) {
        return -2;
    }

    switch (operator)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        if (operand2 == 0) {
            perror("Ne mozete dijeliti s nulom!\n");
            return -3;
        }
        result = operand1 / operand2;
        break;

    default:
        printf("Nepoznata operacija\n");
        return -4;
        break;
    }
    return Push(head, result);
}
int CalculatePostfixFromFile(double* resultDestination, char* fileName) {

    FILE* file = NULL;
    int fileLength = 0;
    char* buffer = NULL;
    char* currentbuffer = NULL;
    int numBytes = 0;
    int number = 0;
    int status = 0;
    char operation = 0;
    StackElement head = { .next = NULL, .number = 0 };

    file = fopen(fileName, "rb");
    if (!file) {
        perror("Nije moguce otvoriti datoteku!\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);

    fileLength = ftell(file);

    buffer = (char*)calloc(fileLength + 1, sizeof(char));

    if (!buffer)
    {
        perror("Nemoguce alocirati memoriju");
        return -2;
    }

    rewind(file);
    fread(buffer, sizeof(char), fileLength, file);

    printf("|%s|\n", buffer);
    fclose(file);
    currentbuffer = buffer;
    while (strlen(currentbuffer) > 0)
    {
        status = sscanf(currentbuffer, " %lf %n", &number, &numBytes);

        if (status == 1)
        {
            status = Push(&head, number);
            if (status != EXIT_SUCCESS) {
                free(buffer);
                DeleteAll(&head);
                return -3;
            }
            currentbuffer += numBytes;
        }
        else
        {

            sscanf(currentbuffer, " %c %n", &operation, &numBytes);
            status = PerformOperation(&head, operation);
            if (status != EXIT_SUCCESS) {

                free(buffer);
                DeleteAll(&head);
                return -4;
            }
            currentbuffer += numBytes;
        }
    }
    free(buffer);

    status = Pop(resultDestination, &head);

    if (status != EXIT_SUCCESS)
    {
        DeleteAll(&head);
        return -5;
    }

    if (head.next)
    {
        printf("Postfix nije dobar");
        DeleteAll(&head);
        return -6;
    }

    return EXIT_SUCCESS;
}

int DeleteAll(Position head) {
    while (head->next)
    {
        DeleteAfter(head);
    }
}



int main()
{


    return EXIT_SUCCESS;
}