#include<stdio.h>

struct st{
	int id;
	char name[30];
};

void add_five(int *id)
{
	*id += 5;
}

int main(void){
	int i;
	struct st data[5];

	for (i=0;i<5;i++){
		scanf("%d", &data[i].id);
		scanf("%s", &data[i].name);
	}
	for (i=0;i<5;i++){
		add_five(&data[i].id);
	}
	for (i=0;i<5;i++){
		printf("%-5d", data[i].id);
		printf("%-5s\n", data[i].name);
	}
	return 0;
}

