#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

struct motherboard //структура мат. платы
{
	char* model;
	char* soket;
	char* type_memory;
};

struct cpu //структура процессора
{
	int amount_core;
	double clock_rate;
	int power;
	char* model;
	char* soket;
};

struct gpu //структура видеокарты
{
	int clock_rate;
	int bandwidth;
	int memory_size;
	int power;
	char* model;
};

struct ram //структура ОЗУ
{
	int clock_rate;
	int memory_size;
	char* model;
	char* type_memory;
};

struct psu //структура блока питания
{
	int power;
	char* model;
};

struct pc //структура компютера
{
	motherboard motherboard;
	cpu cpu;
	gpu gpu;
	ram ram;
	psu psu;
};

void init(struct pc* you_pc) //инициализация структуры
{
	you_pc->motherboard.model = (char*)calloc(32, (sizeof(char)));
	you_pc->motherboard.soket = (char*)calloc(8, (sizeof(char)));
	you_pc->motherboard.type_memory = (char*)calloc(8, (sizeof(char)));;
	you_pc->cpu.amount_core = 0;
	you_pc->cpu.clock_rate = .0;
	you_pc->cpu.power = 0;
	you_pc->cpu.model = (char*)calloc(16, (sizeof(char)));;
	you_pc->cpu.soket = (char*)calloc(8, (sizeof(char)));
	you_pc->gpu.bandwidth = 0;
	you_pc->gpu.clock_rate = 0;
	you_pc->gpu.memory_size = 0;
	you_pc->gpu.power = 0;
	you_pc->gpu.model = (char*)calloc(32, (sizeof(char)));
	you_pc->ram.clock_rate = 0;
	you_pc->ram.memory_size = 0;
	you_pc->ram.type_memory = (char*)calloc(8, (sizeof(char)));
	you_pc->ram.model = (char*)calloc(32, (sizeof(char)));
	you_pc->psu.power = 0;
	you_pc->psu.model = (char*)calloc(32, (sizeof(char)));
}

void input(struct pc* you_pc) //ввод данных
{
	setlocale(LC_ALL, "Rus");
	printf("Введите модель, сокет и тип памяти мат. платы (через \"Enter\")\n");
	scanf("%s", you_pc->motherboard.model);
	scanf("%s", you_pc->motherboard.soket);
	scanf("%s", you_pc->motherboard.type_memory);

	printf("Введите модель, сокет, кол-во ядер, частоту и энергопротребление процессора (через \"Enter\")\n");
	scanf("%s", you_pc->cpu.model);
	scanf("%s", you_pc->cpu.soket);
	scanf("%i", &you_pc->cpu.amount_core);
	scanf("%lf", &you_pc->cpu.clock_rate);
	scanf("%i", &you_pc->cpu.power);

	printf("Введите модель, частоту, пропускную способность памяти, объём памяти и энергопротребление видеокарты (через \"Enter\")\n");
	scanf("%s", you_pc->gpu.model);
	scanf("%i", &you_pc->gpu.clock_rate);
	scanf("%i", &you_pc->gpu.bandwidth);
	scanf("%i", &you_pc->gpu.memory_size);
	scanf("%i", &you_pc->gpu.power);

	printf("Введите модель, тип, частоту и объём ОЗУ (через \"Enter\")\n");
	scanf("%s", you_pc->ram.model);
	scanf("%s", you_pc->ram.type_memory);
	scanf("%i", &you_pc->ram.clock_rate);
	scanf("%i", &you_pc->ram.memory_size);

	printf("Введите модель и мощность блока питания (через \"Enter\")\n");
	scanf("%s", you_pc->psu.model);
	scanf("%i", &you_pc->psu.power);

	while (getchar() != '\n');
}

void compatibility_check(struct pc you_pc) //проверка совместимости комплектующих
{
	setlocale(LC_ALL, "Rus");
	strcmp(you_pc.motherboard.soket, you_pc.cpu.soket) ? printf("Сокеты процессора и платы разные!\n") : printf("Процессор и мат.плата совместимы\n");
	strcmp(you_pc.motherboard.type_memory, you_pc.ram.type_memory) ? printf("Тип пямяти мат.платы и ОЗУ разные!\n") : printf("Мат. плата и ОЗУ совместимы\n");
	(you_pc.cpu.power + you_pc.gpu.power) < you_pc.psu.power ? printf("Мощности БП хватает (в запасе примерно %i ватт)\n", you_pc.psu.power - (you_pc.cpu.power + you_pc.gpu.power)) : printf("Слабый БП, не хватает %i ватт\n", (you_pc.cpu.power + you_pc.gpu.power) - you_pc.psu.power);
}

void output(struct pc you_pc) //вывод 
{
	printf("Материнская плата\n\t-модель: %s\n\t-сокет: %s\n\t-тип памяти: %s", you_pc.motherboard.model, you_pc.motherboard.soket, you_pc.motherboard.type_memory);
	printf("\nПроцессор\n\t-модель: %s\n\t-сокет: %s\n\t-кол-во ядер: %i\n\t-частота: %lf\n\t-энергопотребление: %i", you_pc.cpu.model, you_pc.cpu.soket, you_pc.cpu.amount_core, you_pc.cpu.clock_rate, you_pc.cpu.power);
	printf("\nВидеокарта\n\t-модель: %s\n\t-частота: %i\n\t-пропускная способность памяти: %i\n\t-объём памяти: %i\n\t-энергопотребление: %i", you_pc.gpu.model, you_pc.gpu.clock_rate, you_pc.gpu.bandwidth, you_pc.gpu.memory_size, you_pc.gpu.power);
	printf("\nОЗУ\n\t-модель: %s\n\t-тип памяти: %s\n\t-частота: %i\n\t-объём: %i", you_pc.ram.model, you_pc.ram.type_memory, you_pc.ram.clock_rate, you_pc.ram.memory_size);
	printf("\nБлок питания:\n\t-модель: %s\n\t-мощность: %i", you_pc.psu.model, you_pc.psu.power);
}

int scoring(int numbers[3], double amount) //функция оценки
{
	if (amount > numbers[0] && amount <= numbers[1])
		return 1;
	else if (amount > numbers[1] && amount <= numbers[2])
		return 2;
	else if (amount > numbers[2])
		return 3;
	return 0;
}

void score(struct pc you_pc) //оценка сборки
{
	double score_cpu = you_pc.cpu.clock_rate * you_pc.cpu.amount_core;
	double score_gpu = (you_pc.gpu.clock_rate / 1000.) * you_pc.gpu.memory_size * (you_pc.gpu.bandwidth / 100.);
	double score_ram = (you_pc.ram.clock_rate / 1000.) * you_pc.ram.memory_size;
	int total_score = 0;

	int cpu[3] = { 4, 8, 16 };
	int gpu[3] = { 0, 5, 57 };
	int ram[3] = { 12, 50, 105 };

	total_score += scoring(cpu, score_cpu);
	total_score += scoring(gpu, score_gpu);
	total_score += scoring(ram, score_ram);

	if (total_score <= 2)
		printf("Это ОЧЕНЬ слабый ПК");
	else if (total_score > 2 && total_score < 6)
		printf("Это слабый ПК");
	else if (total_score >= 6 && total_score < 9)
		printf("Это хороший, мощный ПК");
	else if (total_score >= 9)
		printf("Это мощнейший ПК");
}

void recom(struct pc you_pc)
{
	double score_cpu = you_pc.cpu.clock_rate * you_pc.cpu.amount_core;
	double score_gpu = (you_pc.gpu.clock_rate / 1000.) * you_pc.gpu.memory_size * (you_pc.gpu.bandwidth / 100.);
	double score_ram = (you_pc.ram.clock_rate / 1000.) * you_pc.ram.memory_size;

	int cpu[3] = { 4, 8, 16 };
	int gpu[3] = { 0, 5, 57 };
	int ram[3] = { 12, 50, 105 };

	int f_score_cpu = scoring(cpu, score_cpu);
	int f_score_gpu = scoring(gpu, score_gpu);
	int f_score_ram = scoring(ram, score_ram);

	if ((f_score_cpu > f_score_gpu) && (f_score_cpu > f_score_ram))
	{
		printf("\nПроцессор слишком мощный. Рекомендуется выбрать другой или более мощные видеокарту и ОЗУ");
		return;
	}

	if ((f_score_cpu < f_score_gpu) && (f_score_gpu > f_score_ram))
	{
		printf("\nВидеокарта слишком мощная. Рекомендуется выбрать другою или более мощные процессор и ОЗУ");
		return;
	}

	if ((f_score_cpu < f_score_ram) && (f_score_gpu < f_score_ram))
	{
		printf("\nСлишком много памяти. Рекомендуется выбрать другою или более мощные процессор и видеокарту");
		return;
	}

	printf("Ваша сборка сбалансирована");
	return;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	struct pc my_pc;
	init(&my_pc);
	input(&my_pc);
	int choice;
	do
	{
		printf("\n1. Список комплектующих\n2. Проверить совместимость\n3. Оценка сборки\n4. Рекомендации\n5. Ввести новые комплектующие\n6. Выход\n");
		scanf("%i", &choice);
		switch (choice)
		{
		case 1:
			output(my_pc);
			break;
		case 2:
			compatibility_check(my_pc);
			break;
		case 3:
			score(my_pc);
			break;
		case 4:
			recom(my_pc);
			break;
		case 5:
			input(&my_pc);
			break;
		case 6:
			break;
		default:
			printf("Неверный пункт меню");
			break;
		}

	} while (choice != 6);
}