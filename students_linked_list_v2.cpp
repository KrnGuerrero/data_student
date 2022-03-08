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
    periods *next = NULL;
} periods;

typedef struct student
{
    int code;
    char name[50];
    char adress[40];
    int telephone;
    char status[10];
    int totalPeriods;
    float totalScores;
    periods *rootPeriod = NULL;
    student *next = NULL;
} student;

typedef struct outList
{
    student *studentOut;
    outList *next;
} outList;

student *root = NULL;

/*
@param code = codigo del estudiante.
@return student = estudiante registrado.
*/
student *findStudent(int code)
{
    student *temp = root;
    if (root == NULL)
    {
        return root;
    }
    do
    {
        if (temp->code == code)
        {
            return temp;
        }
        temp = temp->next;
    } while (temp != NULL);
    return NULL;
}

periods *createPeriod()
{
    periods *scores;
    scores = (periods *)malloc(sizeof(periods));
    cout << "Ingrese el semestre: ";
    cin >> scores->semester;
    printf("Ingrese el periodo: ");
    scanf("%d", &scores->period);
    printf("Ingrese el promedio: ");
    scanf("%f", &scores->average);
    printf("Ingrese el n%cmero de materias: ", 163);
    scanf("%d", &scores->numSubject);
    scores->next = NULL;
    return scores;
}

/*
@param data = información del estudiante.
@return student = información modificada del estudiante a partir de nuevos scores.
*/
student *addPeriods(student *data)
{
    periods *temp = data->rootPeriod;
    int i = data->totalPeriods;
    for (; i < 12; i++)
    {
        char choose = 'S';
        cout << "\nDesea ingresar periodo? (s/n) \n";
        cin >> choose;
        if (toupper(choose) == 'N')
        {
            break;
        }
        if (data->totalPeriods == 0)
        {
            data->rootPeriod = createPeriod();
            temp = data->rootPeriod;
            data->totalScores += data->rootPeriod->average;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = createPeriod();
            temp = temp->next;
            data->totalScores += temp->average;
        }
        data->totalPeriods++;
    }
    return data;
}

/*
@param data= información del estudiante.
@return data= información del estudiante con status cambiado.
*/
student *setStudentStatus(student *data)
{
    float averageCareer = data->totalScores / data->totalPeriods;
    if (averageCareer < 2.5f)
    {
        strcpy(data->status, "FUERA");
    }
    else if (averageCareer < 2.9f)
    {
        strcpy(data->status, "PRUEBA");
    }
    else
    {
        strcpy(data->status, "NORMAL");
    }
    return data;
}

/*
@param
@return data= información del estudiante con status cambiado para guardarlo.
*/
student *setStudentStatus()
{
    student *data;
    int ident;
    printf("Ingrese su id: ");
    scanf("%d", &ident);
    data = findStudent(ident);
    if (data != NULL)
    {
        data = setStudentStatus(data);
    }
    else
    {
        printf("Almuno no registrado.");
        return data;
    }
}

/*
@param studentCode = codigo del estudiante.
@return data = estudiante para registrar.
*/
student *createStudent(int studentCode)
{
    student *data;
    data = (student *)malloc(sizeof(student));
    data->code = studentCode;
    data->totalPeriods = 0;
    data->totalScores = 0.0;
    fflush(stdin);
    printf("Ingrese su nombre: ");
    gets(data->name);
    printf("Ingrese su direcci%cn: ", 162);
    gets(data->adress);
    printf("Ingrese su tel%cfono: ", 130);
    scanf("%d", &data->telephone);
    strcpy(data->status, "NORMAL");
    data = addPeriods(data);
    data = setStudentStatus(data);
    data->next = NULL;
    return data;
}

void registerStudent()
{
    system("cls");
    int studentCode;
    printf("Ingrese su id: ");
    scanf("%d", &studentCode);
    student *data = findStudent(studentCode);
    if (data == NULL)
    {
        if (root == NULL)
        {
            root = createStudent(studentCode);
        }
        else
        {
            student *temp = root;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = createStudent(studentCode);
        }
    }
    else
    {
        printf("Estudiante ya regitrado. \n\n\n");
    }
}

void registerPeriods()
{
    system("cls");
    student *data;
    int code;
    printf("Ingrese su id: ");
    scanf("%d", &code);
    data = findStudent(code);
    if (data != NULL)
    {
        data = addPeriods(data);
        data = setStudentStatus(data);
    }
    else
    {
        printf("Alumno no registrado.");
    }
    system("cls");
}

/*
@param data= información del estudiante.
@return
*/
void showDataStudent(student *data)
{
    printf("#### DATA STUDENT ####\n");
    printf("C%cdigo: %d \n", 162, data->code);
    printf("Nombre: %s \n", data->name);
    printf("Direcci%cn: %s \n", 162, data->adress);
    printf("Tel%cfono: %d \n", 130, data->telephone);
    printf("Estado: %s \n", data->status);
    printf("Sumatoria de promedios: %.2f\n", data->totalScores);
    printf("Total de periodos: %d\n", data->totalPeriods);
    printf("Promedio total: %.2f\n", data->totalScores / data->totalPeriods);
    printf("\n");
}

/*
@param data= información del estudiante.
@return
*/
void showDataScore(periods *score)
{
    printf("#### DATA SCORES ####\n");
    printf("Promedio: %.2f \n", score->average);
    printf("Semestre: %d \n", score->semester);
    printf("Periodo: %d \n", score->period);
    printf("N%cmero de materias: %d \n", 163, score->numSubject);
    printf("\n");
}

/*
@param data= información del estudiante.
@return data= información del estudiante con status cambiado.
*/
void showDataScores(int totalPeriods, periods *scores)
{
    periods *temp = scores;
    for (int i = 0; i < totalPeriods; i++)
    {
        showDataScore(temp);
        temp = temp->next;
    }
}

void showStudent()
{
    system("cls");
    int studentCode;
    printf("Ingrese su id: ");
    scanf("%d", &studentCode);
    student *data = findStudent(studentCode);
    if (data != NULL)
    {
        showDataStudent(data);
        showDataScores(data->totalPeriods, data->rootPeriod);
    }
    else
    {
        printf("Estudiante no regitrado.");
    }
}

/*
@param data= información del estudiante.
@return data= información del estudiante con status cambiado.
*/
void studentsOutList()
{
    student *temp = root;
    outList *newList = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->status, "FUERA") == 0)
        {
            if (newList == NULL)
            {
                newList = (outList *)malloc(sizeof(outList));
                newList->studentOut = temp;
                newList->next = NULL;
                showDataStudent(newList->studentOut);
                showDataScores(newList->studentOut->totalPeriods, newList->studentOut->rootPeriod);
                printf("\n");
            }
            else
            {
                newList->studentOut = temp;
                newList->next = NULL;
                showDataStudent(newList->studentOut);
                showDataScores(newList->studentOut->totalPeriods, newList->studentOut->rootPeriod);
                printf("\n");
            }
        }
        temp = temp->next;
    }
}


/*
@param data= información del estudiante.
@return data= información del estudiante con status cambiado.
*/
void showOutStudents()
{
    student *temp = root;
    while (temp != NULL)
    {
        if (strcmp(temp->status, "FUERA") == 0)
        {
            showDataStudent(temp);
            showDataScores(temp->totalPeriods, temp->rootPeriod);
            printf("\n");
        }
        temp = temp->next;
    }
}

void showAllStudent(student *temp){
    while (temp != NULL)
    {
        showDataStudent(temp);
        showDataScores(temp->totalPeriods, temp->rootPeriod);
        temp = temp->next;
        printf("\n\n\n");
    }
}
void showAllStudent()
{
    system("cls");
    student *temp = root;
    char choose = 'T';
    cout << "\nDesea ver la lista con todos los estudiantes o solo los que estan fuera? (T/F) \n";
    cin >> choose;
    if (toupper(choose) == 'F'){
        studentsOutList();
    }
    else{
        showAllStudent(temp);
    }
}

int menu()
{
    int option = 0;
    printf("\n\n\t\tMENU\n\n");
    printf("1. Registrar estudiante.\n");
    printf("2. Registrar periodo.\n");
    printf("3. Definir estado.\n");
    printf("4. Mostrar estudiante.\n");
    printf("5. Mostrar lista de estudiantes FUERA.\n");
    printf("6. Mostrar estudiantes de estado FUERA.\n");
    printf("7. Mostrar todos los estudiantes registrados.\n");
    printf("8. Salir.\n\n");
    printf("Ingrese la opci%cn a realizar: ", 162);
    scanf("%d", &option);
    system("cls");
    return option;
}

int main()
{
    int op = 0;
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            registerStudent();
            break;
        case 2:
            registerPeriods();
            break;
        case 3:
            setStudentStatus();
            break;
        case 4:
            showStudent();
            break;
        case 5:
            studentsOutList();
            break;
        case 6:
            showOutStudents();
            break;
        case 7:
            showAllStudent();
            break;
        case 8:
            printf("\nHasta luego.");
            break;
        }
    } while (op != 8);
    return 0;
}