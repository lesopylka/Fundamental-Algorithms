#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum VALIDATION_ENUM {
  ok = 0,
    invalidArguments = -1,
    invalidStr = -3,
    fileDidntOpen = -4,
	nomemory = -5
};

typedef struct {
	int id;
	char *name;
	char *surname;
	double wage;
} employee;

int join_symb(char symb, char **str, int *size) {
	if (*size == 0) {
		*size = 2;
		*str = (char*)malloc(sizeof(char) * *size);
		if (!*str) {
			return nomemory;
		}

		(*str)[0] = symb;
		(*str)[1] = 0;

		return ok;
	}

	if (strlen(*str) == *size - 1) {
		*size *= 2;
		*str = (char*)realloc(*str, sizeof(char) * *size);
		if (!*str) {
			return nomemory;
		}
	}

	(*str)[strlen(*str) + 1] = 0;
	(*str)[strlen(*str)] = symb;

	return ok;
}

int get_line(FILE *file_info, char **str) {
	char symb = fgetc(file_info);
	int size_str = 0;

	while (symb != '\n' && symb != EOF) {
		if (join_symb(symb, str, &size_str) == nomemory) {
			return nomemory;
		}
		symb = fgetc(file_info);
	}

	return ok;
}

int word_count(char *str) {
	char _c = ' ';
	char *ptr = str - 1;
	int count = 0;

	while (*++ptr) {
		if (isspace(_c) && !isspace(*ptr)) {
			count++;
		}
		_c = *ptr;
	}

	return count;
}

int get_token_str(char **ptr, char **token) {
	int size = 0;

	while (isspace(**ptr)) {
		(*ptr)++;
	}

	while (!isspace(**ptr) && **ptr) {
		if (join_symb(**ptr, token, &size) == nomemory) {
			return nomemory;
		}
		(*ptr)++;
	}

	return ok;
}

int check_id(char *id) {
	char *ptr = id - 1;

	while (*++ptr) {
		if (!isdigit(*ptr)) {
			return 0;
		}
	}

	return 1;
}

int check_name_surname(char *name) {
	char *ptr = name - 1;

	while (*++ptr) {
		if (!isalpha(*ptr)) {
			return 0;
		}
	}

	return 1;
}

int check_wage(char *wage) {
	char *ptr = wage - 1;
	int count_dots = 0;

	while (*++ptr) {
		if (*ptr == '.') {
			count_dots++;
		} else {
			if (!isdigit(*ptr)) {
				return 0;
			}
		}

		if (count_dots > 1) {
			return 0;
		}
	}

	return 1;
}

int get_employee_info(char *str, employee **item) {
	char *ptr = str;
	*item = (employee*)malloc(sizeof(employee));

	if (!*item) {
		return nomemory;
	}

	if (word_count(str) != 4) {
		free(*item);
		return invalidStr;
	}

	char *id = NULL;
	char *name = NULL;
	char *surname = NULL;
	char *wage = NULL;

	int exit_id = get_token_str(&ptr, &id);
	int exit_name = get_token_str(&ptr, &name);
	int exit_surname = get_token_str(&ptr, &surname);
	int exit_wage = get_token_str(&ptr, &wage);

	if (exit_id == ok && check_id(id)) {
		(*item)->id = atoi(id);
		free(id);
	} else {
		free(id);
		free(name);
		free(surname);
		free(wage);
		free_worker(item);
		return exit_id == ok ? invalidStr : exit_id;
	}

	if (exit_name == ok && check_name_surname(name)) {
		(*item)->name = name;
	} else {
		free(id);
		free(name);
		free(surname);
		free(wage);
		free_worker(item);
		return exit_name == ok ? invalidStr : exit_name;
	}

	if (exit_surname == ok && check_name_surname(surname)) {
		(*item)->surname = surname;
	} else {
		free(id);
		free(name);
		free(surname);
		free(wage);
		free_worker(item);
		return exit_surname == ok ? invalidStr : exit_surname;
	}

	if (exit_wage == ok && check_wage(wage)) {
		(*item)->wage = atof(wage);
		free(wage);
	} else {
		free(id);
		free(name);
		free(surname);
		free(wage);
		free(*item);
		return exit_wage == ok ? invalidStr : exit_wage;
	}

	return ok;
}

int get_workers(char *file_name, employee ***workers, int *size) {
	FILE *file = NULL;

	if ((file = fopen(file_name, "r")) != NULL) {
		char *str = NULL;
		int exit_code = 0;
		int index = 0;
		int length = 1;
		*workers = (employee**)malloc(sizeof(employee*));

		while (!feof(file)) {
			if (get_line(file, &str) == nomemory) {
				return nomemory;
			}

			if (str) { // если строка не пустая
				exit_code = get_employee_info(str, &(*workers)[index]);

				if (exit_code == ok) {
					if (index == length - 1) {
						length *= 2;
						*workers = (employee**)realloc(*workers, sizeof(employee*) * length);
						if (!workers) {
							return nomemory;
						}
					}

					index++;
				}

				free(str);
				str = NULL;
			}
		}

		*size = index;
		fclose(file);

		return ok;
	}

	return fileDidntOpen;
}

int write_in_file(char *name_file, employee **workers, int count_workers) {
	FILE *file = NULL;

	if ((file = fopen(name_file, "w")) != NULL) {
		for (int i = 0; i < count_workers; i++) {
			fprintf(file, "%d %s %s %lf\n", workers[i]->id, workers[i]->name, workers[i]->surname, workers[i]->wage);
		}
		fclose(file);
	} else {
		return fileDidntOpen;
	}

	return ok;
}

void free_worker(employee **item) {
	if (*item) {
		if ((*item)->name) {
			free((*item)->name);
		}
		if ((*item)->surname) {
			free((*item)->surname);
		}
		free(*item);
	}
}

void free_arr_workers(employee ***workers, int size) {
	if (*workers) {
		for (int i = 0; i < size; i++) {
			if ((*workers)[i]) {
				free_worker(&(*workers)[i]);
			}
		}

		free(*workers);
	}
}

void output_workers(employee **workers, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d %s %s %lf\n", workers[i]->id, workers[i]->name, workers[i]->surname, workers[i]->wage);
	}
	printf("\n");
}

void print_error(int exit_code) {
	if (exit_code == fileDidntOpen) {
		fprintf(stderr, "%s\n", "fileDidntOpen: Can't open file");
	}
	if (exit_code == nomemory) {
		fprintf(stderr, "%s\n", "nomemory: The system is out of memory");
	}
	if (exit_code == invalidArguments) {
		fprintf(stderr, "%s\n", "invalidArguments: Entered argumets is invalid");
	}
}
