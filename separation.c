#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    char filename[100];
    char ch;
    int insideString = 0;

    printf("Enter the filename containing the C code: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    printf("\nFormatted Output:\n\n");

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '"') {
            insideString = !insideString;
        }

        if (!insideString) {
            if (ch == '(' || ch == ')' || ch == '{' || ch == '}' ||
                ch == ';' || ch == ',' || ch == '+' || ch == '-' ||
                ch == '*' || ch == '/' || ch == '=' || ch == '<' ||
                ch == '>' || ch == '!' || ch == '&' || ch == '|' ||
                ch == '[' || ch == ']' || ch == '%') {
                printf("\n%c\n", ch);
            } else if (isspace(ch)) {
                printf("\n");
            } else {
                printf("%c", ch);
            }
        } else {
            printf("%c", ch);
        }
    }

    fclose(file);
    return 0;
}
