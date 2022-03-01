#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

using namespace std;

typedef struct periods{
	int semester;
	int period;
	float average;
	int numSubject;
} periods;

typedef struct student{
	int code;
	int isNew;
	char name[50];
	char adress[40];
	int telephone;
	char status[10];
	int totalPeriods;
	periods scores[12];
} student;

int menu(){
	int option=0;
	printf("\t\tMENU\n\n");
	printf("1. Registrar estudiante.\n");
	printf("2. Registrar periodo.\n");
	printf("3. Definir estado.\n");
	printf("4. Mostrar estudiantes de estado FUERA.\n");
	printf("5. Mostrar todos los estudiantes registrados.\n");
	printf("6. Salir.\n\n");
	printf("Ingrese la opci%cn a realizar: ", 162);
	scanf("%d", &option);
	return option;
}

/*
@param id = codigo del estudiante.
@return student = estudiante registrado.
*/
student isCurrentlyRegistered(int id){
	student data;
	FILE *arch = fopen("alumno.dat","r+b");
	// to read file
	while (arch != NULL && !feof(arch)) {
        //leer la primera linea del archivo y almacenar la info en "data".
        fread(&data,sizeof(student),1,arch);
        if(data.code == id) {
        	fclose(arch);
			return data;
		}
    }
	fclose(arch);
	return student{};//En caso que se recorra TODO el archivo y no se encuentre el estudiante.
}

/*
@param 
@return scores = informaci�n relacionada a su promedio universitario.
*/
periods createPeriods(){
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

student addPeriods(student data) {
	for(int i=data.totalPeriods-1; i<12; i++){
		char choose = 'S';
		//printf("Ingresa otro periodo? (s/n) \n"); scanf("%c", &choose);
		cout << "Desea ingresar periodo? (s/n) \n";
		cin >> choose;
		if(toupper(choose)=='N') {
			break;
		} 
		data.totalPeriods++;
		data.scores[i] = createPeriods();
	}
	return data;
}

/*
@param studentCode = codigo del estudiante.
@return data = estudiante para registrar.
*/
student createStudent(int studentCode){
	student data;
	data.code = studentCode;
	data.isNew = 1;
	data.totalPeriods=1;
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
void saveStudentInfo(student data){
	FILE *arch; 
	arch = fopen("alumno.dat","a+b");	
	if(arch==NULL){
		exit(1);
	}
	fwrite(&data,sizeof(student),1,arch);
	fclose(arch);
}

/*
@param
@return 1 if the student was stored in the file 0 in otherwise
*/
int registerPerson() {
	system("cls");
	int studentCode;
	printf("Ingrese su id: ");
	scanf("%d", &studentCode);
	student data=isCurrentlyRegistered(studentCode);
	if(data.isNew == 0) {
		data=createStudent(studentCode);
		saveStudentInfo(data);
		return 1;
	} else {
		printf("Estudiante ya regitrado.");
		return 0;
	}
}

student defineStudentStatus(){
	student data;
	int sumAverage;
	int ident;
	printf("Ingrese su id: "); scanf("%d", &ident);
	data = isCurrentlyRegistered(ident);
	if(data.isNew != 0){
		for(int i=0; i<data.totalPeriods;i++){
			sumAverage = sumAverage + data.scores[i].average;
		}
		if((sumAverage/data.totalPeriods)<2.5){
			strcpy(data.status, "FUERA");
		}
		if((sumAverage/data.totalPeriods)<3.0){
			strcpy(data.status, "PRUEBA");
		}
		else{
			strcpy(data.status, "NORMAL");
		}
		saveStudentInfo(data);
		return data;
	} else{
		printf("Almuno no registrado.");
		return data;
	}
}

void registerPeriods() {
	system("cls");
	student data;
	int ident;
	printf("Ingrese su id: "); scanf("%d", &ident);
	data = isCurrentlyRegistered(ident);
	if(data.isNew != 0){
		addPeriods(data);
		data= defineStudentStatus();
		saveStudentInfo(data);
	} else{
		printf("Almuno no registrado.");
	}
	system("cls");
}

void showOutStudents(){
	system("cls");
	student data;
	int i=0;
	FILE* arch;
	arch = fopen("alumno.dat","rb");
	// to read file
	while(fread(&data, sizeof(student), 1, arch)) {
        if(strcmp(data.status, "FUERA")==0){
        	printf("Code: %d \n", data.code);
	        printf("Name: %s \n", data.name);
	        printf("Telephone: %d \n", data.telephone);
	        printf("Adress: %s \n", data.adress);
	        printf("Status: %s \n", data.status);
	        printf("Total de periodos: %d \n", data.totalPeriods);
	        for(int i =0; i<data.totalPeriods-1; i++) {
				printf("Average: %f \n", data.scores[i].average);
		        printf("Semester: %d \n", data.scores[i].semester);
		        printf("Period: %d \n", data.scores[i].period);
		        printf("NumSubject: %d \n", data.scores[i].numSubject);
			}
	        printf("\n");
		}
	}
	fclose(arch);
	system("cls");
}

void showAllStudent() {
	system("cls");
	student data;
	FILE* arch;
	arch = fopen("alumno.dat","rb");
	// to read file
	while(fread(&data, sizeof(student), 1, arch)) {
        //leer la primera linea del archivo y almacenar la info en "data".
        printf("Code: %d \n", data.code);
        printf("Name: %s \n", data.name);
        printf("Adress: %s \n", data.adress);
		printf("Telephone: %d \n", data.telephone);
        printf("Status: %s \n", data.status);
        printf("Total de periodos: %d \n", data.totalPeriods);
        for(int i =0; i<data.totalPeriods-1; i++) {
			printf("Average: %f \n", data.scores[i].average);
	        printf("Semester: %d \n", data.scores[i].semester);
	        printf("Period: %d \n", data.scores[i].period);
	        printf("NumSubject: %d \n", data.scores[i].numSubject);
		}
        printf("\n");
	}
	fclose(arch);
}

int main() {
	student data;
	int op=0;
	do{
		op=menu();
		switch(op){
	   	case 1:
		   registerPerson();
		   break;
	   	case 2:
		   registerPeriods();
		   break;
	   	case 3:
		   defineStudentStatus();
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
	}while(op!=6);
	return 0;
}

