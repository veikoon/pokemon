#include <stdio.h>
#include "find_151_pokemon.h"

FILE* loadfile(char name[MAX_SIZE])
{
	int lenght_name;
	char temp[MAX_SIZE];
	FILE *file;

	printf("Veuillez entrer le nom de la sauvegarde : ");
	scanf("%s", &temp);
	copy(name,temp);
	lenght_name 		= lenght(name);
	name[lenght_name] 	= '.';
	name[lenght_name+1] = 's';
	name[lenght_name+2] = 'a';
	name[lenght_name+3] = 'v';
	name[lenght_name+4] = '\0';
	file 				= fopen(name, "r+");
	if (file == NULL)
		printf("%s\n", "Sauvegarde introuvable\n");
	return (file);
}

void save(char list[151][MAX_SIZE], char name[MAX_SIZE], int nb)
{	
	FILE *file;
	file = loadfile(name);

	if (!file){
		file = fopen(name, "wb");
		printf("Nouvelle sauvegarde cree\n");
	}

	fprintf(file, "%d\n", nb);

	for (int i = 0; i < 151; ++i){
		fputs(list[i], file);
		fputc('\n', file);
	}

	printf("Save finished\n");
	fclose(file);
}

void copy(char dest[], char source[])
{
	int i;
	i = 0;

	while (source[i] != '\0'){
		dest[i] = source[i];
		i++;
	}

	dest[i] = source[i];
}

int lenght(char value[])
{
	int i;
	i = 0;

	while (value[i] != '\0'){
		i++;	
	}

	return (i);
}

void load(char list[151][MAX_SIZE], char name[MAX_SIZE], int *nb)
{
	int i;
	FILE *file;

	i 		= 1;
	file 	= loadfile(name);

	if (!file)
		return;

	char pokemon[MAX_SIZE];
	fscanf (file, "%d", nb);

	while (fgets(pokemon, MAX_SIZE, file) != NULL){

		if (pokemon[lenght(pokemon)-1] == '\n')
			pokemon[lenght(pokemon)-1] = '\0';

		copy(list[i], pokemon);
		i++;
	}

}

int compare(char test1[], char test2[])
{
	int i;
	int same 	= 0;
	i 			= 0;

	while (test1[i] != '\0'){

		if (test1[i] != test2[i]){
			same = 1;
			break;
		}

		i++;
	}

	return (same);
}

void tab_init(char liste[151][MAX_SIZE])
{

	for (int i = 0; i < 151; ++i)
		copy(liste[i], "******");

}

void tab_show(char liste[151][MAX_SIZE])
{

	for (int i = 0; i < 151; ++i)
		printf("%s\n", liste[i]);

}

void welcome(void)
{
	printf("Bienvenu(e) !\nAfin de gagner vous devez trouver tous les pokemons de la premiere generation !");
	printf("Pour ce faire entrez le nom d'un pokemon il s'ajoutera a la liste\n");
	printf("commandes disponnibles : list, nombre, regle, save, load\n\n");
}

int read_pokemon(char value[MAX_SIZE])
{
	FILE* 	file;
	char 	pokemon[MAX_SIZE];
	int rank_pokemon;

	file 			= fopen("pokemon.txt", "r");
	rank_pokemon 	= 1;

	while (fgets(pokemon, MAX_SIZE, file) != NULL){

		if (pokemon[lenght(pokemon)-1] == '\n')
			pokemon[lenght(pokemon)-1] = '\0';

		if (!compare(value, pokemon)){
			return rank_pokemon;

		}

		rank_pokemon++;
	}

	return 0;
}

void ask(int *nb, char liste[151][MAX_SIZE])
{
	char value[MAX_SIZE];
	char name[20];
	printf("Veuillez entrer le nom d'un pokemon : ");
	scanf("%s", &value);

	for (int i = 0; i < 151; ++i){

		if (!compare(value,liste[i])){
			printf("Tu as dejà trouve ce pokemon\n\n");
			return;
		}

	}

	if (read_pokemon(value)){
		printf("Bravo tu as trouve un pokemon !\n\n");
		*nb -= 1;
		copy(liste[read_pokemon(value)-1], value);
	}

	if (!compare(value,"nombre"))
		printf("%d\n", *nb);

	if (!compare(value, "list"))
		tab_show(liste);

	if (!compare(value, "regle"))
		printf("On ecrira les caracteres speciaux en toute lettre\nIl n\'y a pas d\'accent.\n\n");

	if (!compare(value, "save"))
		save(liste, name, *nb);

	if (!compare(value, "load"))
		load(liste, name, nb);

}

int main(int argc, char const *argv[])
{
	char liste[151][MAX_SIZE];
	int number = 151;
	welcome();
	tab_init(liste);

	while (1){
		ask(&number, liste);

		if (number == 0){
			printf("Bravo tu as gagne !!\n");
			break;
		}

	}
	
	return 0;
}