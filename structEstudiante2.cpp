#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

using namespace std;

typedef struct periods
{
	int semester;
	int period;
	float average;
	int numSubject;
} periods;

typedef struct student
{
	int code;
	int isNew;
	char name[50];
	char adress[40];
	int telephone;
	char status[10];
	int totalPeriods;
	float totalScores;
	periods scores[12];
} student;

int menu()
{
	int option = 0;
	printf("\t\tMENU\n\n");
	printf("1. Registrar estudiante.\n");
	printf("2. Registrar periodo.\n");
	printf("3. Definir estado.\n");
	printf("4. Mostrar estudiantes de estado FUERA.\n");
	printf("5. Mostrar todos los estudiantes registrados.\n");
	printf("6. Salir.\n\n");
	printf("Ingrese la opci%cn a realizar: ", 162);
	scanf("%d", &option);
	system("cls");
	return option;
}

/*
@param id = codigo del estudiante.
@return student = estudiante registrado.
*/
student isCurrentlyRegistered(int id)
{
	student data;
	FILE *arch = fopen("alumno.dat", "r+b");
	// to read file
	while (arch != NULL && !feof(arch))
	{
		// leer la primera linea del archivo y almacenar la info en "data".
		fread(&data, sizeof(student), 1, arch);
		if (data.code == id)
		{
			fclose(arch);
			return data;
		}
	}
	fclose(arch);
	return student{}; // En caso que se recorra TODO el archivo y no se encuentre el estudiante.
}

/*
@param
@return scores = informaci�n relacionada a su promedio universitario.
*/
periods createPeriods()
{
	periods scores;
	cout << "Ingrese el semestre: ";
	cin >> scores.semester;
	printf("Ingrese el periodo: ");
	scanf("%d", &scores.period);
	printf("Ingrese el promedio: ");
	scanf("%f", &scores.average);
	printf("Ingrese el n%cmero de materias: ", 163);
	scanf("%d", &scores.numSubject);
	return scores;
}

student addPeriods(student data)
{
	int i = data.totalPeriods;
	for (; i < 12; i++)
	{
		char choose = 'S';
		// printf("Ingresa otro periodo? (s/n) \n"); scanf("%c", &choose);
		cout << "\nDesea ingresar periodo? (s/n) \n";
		cin >> choose;
		if (toupper(choose) == 'N')
		{
			break;
		}
		data.totalPeriods++;
		data.scores[i] = createPeriods();
		data.totalScores += data.scores[i].average;
	}
	return data;
}

/*
@param studentCode = codigo del estudiante.
@return data = estudiante para registrar.
*/
student createStudent(int studentCode)
{
	student data;
	data.code = studentCode;
	data.isNew = 1;
	data.totalPeriods = 0;
	data.totalScores = 0.0;
	fflush(stdin);
	printf("Ingrese su nombre: ");
	gets(data.name);
	printf("Ingrese su direcci%cn: ", 162);
	gets(data.adress);
	printf("Ingrese su tel%cfono: ", 130);
	scanf("%d", &data.telephone);
	strcpy(data.status, "NORMAL");
	data = addPeriods(data);
	return data;
}

/*
@param student = informaci�n del estudiante a guardar.
@return
*/
void saveStudentInfo(student data)
{
	FILE *arch;
	arch = fopen("alumno.dat", "a+b");
	if (arch == NULL)
	{
		exit(1);
	}
	fwrite(&data, sizeof(student), 1, arch);
	fclose(arch);
}

/*
@param
@return 1 if the student was stored in the file 0 in otherwise
*/
int registerPerson()
{
	system("cls");
	int studentCode;
	printf("Ingrese su id: ");
	scanf("%d", &studentCode);
	student data = isCurrentlyRegistered(studentCode);
	if (data.isNew == 0)
	{
		data = createStudent(studentCode);
		saveStudentInfo(data);
		return 1;
	}
	else
	{
		printf("Estudiante ya regitrado.");
		return 0;
	}
}

student setStudentStatus(student data)
{
	float averageCareer = data.totalScores / data.totalPeriods;
	if (averageCareer < 2.5f)
	{
		strcpy(data.status, "FUERA");
	}
	else if (averageCareer < 2.9f)
	{
		strcpy(data.status, "PRUEBA");
	}
	else
	{
		strcpy(data.status, "NORMAL");
	}
	printf("%s", data.status);
	system("pause");
	return data;
}

student setStudentStatus()
{
	student data;
	int ident;
	printf("Ingrese su id: ");
	scanf("%d", &ident);
	data = isCurrentlyRegistered(ident);
	if (data.isNew != 0)
	{
		data = setStudentStatus(data);
		saveStudentInfo(data);
	}
	else
	{
		printf("Almuno no registrado.");
		return data;
	}
}

float getAverageCareer(student data)
{
	float sumAverage = 0;
	for (int i = 0; i < data.totalPeriods; i++)
	{
		sumAverage = sumAverage + data.scores[i].average;
	}
	return sumAverage / data.totalPeriods;
}

void registerPeriods()
{
	system("cls");
	student data;
	int ident;
	printf("Ingrese su id: ");
	scanf("%d", &ident);
	data = isCurrentlyRegistered(ident);
	if (data.isNew != 0)
	{
		data = addPeriods(data);
		data = setStudentStatus(data);
		printf("%f\n", data.scores[0].average);
		system("pause");
		saveStudentInfo(data);
	}
	else
	{
		printf("Almuno no registrado.");
	}
	system("cls");
}

void showDataStudent(student data)
{
	printf("#### DATA STUDENT ####\n");
	printf("Code: %d \n", data.code);
	printf("Name: %s \n", data.name);
	printf("Adress: %s \n", data.adress);
	printf("Telephone: %d \n", data.telephone);
	printf("Status: %s \n", data.status);
	printf("Summatory total scores: %.2f\n", data.totalScores);
	printf("Total periods: %d\n", data.totalPeriods);
	printf("Total average: %.2f\n", data.totalScores/data.totalPeriods);
	printf("\n");
}

void showDataScore(periods score)
{
	printf("#### DATA SCORES ####\n");
	printf("Average: %.2f \n", score.average);
	printf("Semester: %d \n", score.semester);
	printf("Period: %d \n", score.period);
	printf("NumSubject: %d \n", score.numSubject);
	printf("\n");
}

void showDataScores(int totalPeriods, periods scores[])
{
	for (int i = 0; i < totalPeriods; i++)
	{
		showDataScore(scores[i]);
	}
}

void showOutStudents()
{
	student data;
	FILE *arch;
	arch = fopen("alumno.dat", "rb");
	// to read file
	while (fread(&data, sizeof(student), 1, arch))
	{
		if (strcmp(data.status, "FUERA") == 0)
		{
			showDataStudent(data);
			showDataScores(data.totalPeriods, data.scores);
			printf("\n");
		}
	}
	fclose(arch);
	system("pause");
	system("cls");
}

void showAllStudent()
{
	system("cls");
	student data;
	FILE *arch;
	arch = fopen("alumno.dat", "rb");
	// to read file
	while (fread(&data, sizeof(student), 1, arch))
	{
		// leer la primera linea del archivo y almacenar la info en "data".
		showDataStudent(data);
		showDataScores(data.totalPeriods, data.scores);
		printf("\n\n\n");
	}
	fclose(arch);
	system("pause");
	system("cls");
}

int main()
{
	student data;
	int op = 0;
	do
	{
		op = menu();
		switch (op)
		{
		case 1:
			registerPerson();
			break;
		case 2:
			registerPeriods();
			break;
		case 3:
			setStudentStatus();
			break;
		case 4:
			showOutStudents();
			break;
		case 5:
			showAllStudent();
			break;
		case 6:
			printf("\nHasta luego.");
			break;
		}
	} while (op != 6);
	return 0;
}
