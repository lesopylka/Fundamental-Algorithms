#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

enum VALIDATION_ENUM {
    noArguments,
    wrongNumberOfArguments,
    unexpectedToggles,
    symbolBeforeTogglesNotFound,
    ok,
};

void printValidationError(enum VALIDATION_ENUM error) {
    switch (error) {
        case noArguments:
            printf("Invalid Input: no arguments");
            break;
        case wrongNumberOfArguments:
            printf("");
            break;
        case unexpectedToggles:
            printf("");
            break;
        case symbolBeforeTogglesNotFound:
            printf("");
            break;
        default:
            printf("Unexpected eror");
    }
}

enum VALIDATION_ENUM validationArg(int argc, char * argv[]) {
  if (argc == 1) {
    return noArguments;
  }
  if (argc != 4) {
    return wrongNumberOfArguments;
  }
  if (strlen(argv[3]) != 2) {
    return unexpectedToggles;
  }
  
  if (!(argv[3][0] == '-' || argv[3][0] == '/')) {
    return symbolBeforeTogglesNotFound;
  }

  return ok;
}
struct node {
    struct node* parent;     // указатель на отца
    struct node* child;      // указатель на одного из сыновей
    struct node* left;       // указатель на левого брата
    struct node* right;      // указатель на правого брата
    int degree;       // количество дочерних узлов
    bool mark;        // метка - был ли удален один из дочерних элементов
    int key;          // числовое значение узла
};

struct fib_heap {
    struct node* min;        // узел с минимальным корнем
    int roots_amount; // количество узлов
};

void read() {

}

int logic() {

}

struct employee {
    unsigned int id;
    char name;
    char surname;
    float wage;
};

togglesA(){

}

togglesD(){

}

int main(int argc, char * argv[]) {
    enum VALIDATION_ENUM validationResult = validationArg(argc, argv);
    if (validationResult != ok) {
        printValidationError(validationResult);
        return 1;
    }
}


// 1. ввод аргументов +
// 2. валидация аргументов +
// 3. отображение ошибки (если есть) +
// 4. чтение файла
// 5. валидация строк (проверка на соотвествие структуре)
// 6. заполнить фибоначчиеву пирамиду данными с пукта 5
// 7. сортировка пирамиды в зависимости от поданного флага
// 8. вывод отсортированной даты в файл 