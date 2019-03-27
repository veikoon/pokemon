#define MAX_SIZE 20

void load(char list[151][MAX_SIZE], char name[MAX_SIZE], int *nb);
void save(char list[151][MAX_SIZE], char name[MAX_SIZE], int nb);
void ask(int *nb, char liste[151][MAX_SIZE]);
void tab_init(char liste[151][MAX_SIZE]);
void tab_show(char liste[151][MAX_SIZE]);
int compare(char test1[], char test2[]);
int read_pokemon(char value[MAX_SIZE]);
void copy(char dest[], char source[]);
int lenght(char value[]);
void welcome(void);
FILE* loadfile();