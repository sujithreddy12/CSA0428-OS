#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float salary;
};

int main() {
    FILE *file;
    struct Employee emp;

    file = fopen("employee_records.dat", "rb+");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int targetEmpId;
    printf("Enter an employee ID to search: ");
    scanf("%d", &targetEmpId);

    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.empId == targetEmpId) {
            printf("Employee found:\n");
            printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.empId, emp.empName, emp.salary);

            printf("Enter new salary: ");
            scanf("%f", &emp.salary);
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            printf("Salary updated successfully!\n");
            break;
        }
    }

    fclose(file);

    return 0;
}

