#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define SUBJECT_COUNT 5
#define NAME_LENGTH 32

const char *SUBJECT_NAMES[SUBJECT_COUNT] = { "C Programming", "Java", "Python", "DSA", "AI & ML" };
  
typedef struct 
{
    int   roll_number;
    char  name[NAME_LENGTH];
    float marks[SUBJECT_COUNT];
    float total;
    float percentage;
} Student;

void main_menu(Student *students, int *count);
void student_menu(Student *students, int *count);
void file_menu(Student *students, int count);
void insights_menu(Student *students, int count);
void reports_menu(Student *students, int count);

void read_full_name(char *name, int size);

void input_students(Student *students, int count);          
void calculate_results(Student *students, int count);        
void display_students(Student students[], int count);
void update_students(Student students[], int count);
void search_student(Student students[], int count);
void delete_student(Student students[], int *count);

void save_to_file(Student students[], int count);
void load_from_file(Student students[], int count);
void saving_sorted_csv(Student students[], int count);

int roll_compare(const void *a, const void *b);
int percentage_compare(const void *a, const void *b);
int name_compare(const void *a, const void *b);

int roll_exists(Student students[], int count, int roll, int ignore_index);

void clear_input_buffer();

void subject_wise_topper(Student students[], int count);
void overall_topper(Student students[], int count);
void distinction_students(Student students[], int count);
void failed_students(Student students[], int count);

void generate_report_card(Student students[], int count);

char calculate_grade(float percentage);

void class_analytics_dashboard(Student students[], int count);

void print_line()
{
    printf("============================================================\n");
}

int main(void)
{
    int student_count;

    printf("Enter number of students: ");
    if (scanf("%d", &student_count) != 1 || student_count <= 0)
    {
        printf("Invalid student count.\n");
        return EXIT_FAILURE;
    }

    Student *students = (Student *)malloc(student_count * sizeof(Student));
    if (students == NULL)
    {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    main_menu(students, &student_count);

    free(students);
    return EXIT_SUCCESS;
}

void main_menu(Student *students, int *count)
{
    int choice;
    do
    {
        print_line();
        printf("%30s\n", "RESULT MANAGEMENT SYSTEM");
        print_line();

        printf("| %-3s | %-45s |\n", "1", "Student Record Management");
        printf("| %-3s | %-45s |\n", "2", "File Operations");
        printf("| %-3s | %-45s |\n", "3", "Academic Insights");
        printf("| %-3s | %-45s |\n", "4", "Reports & Analytics");
        printf("| %-3s | %-45s |\n", "5", "Exit");
        print_line();

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: student_menu(students, count); break;
            case 2: file_menu(students, *count); break;
            case 3: insights_menu(students, *count); break;
            case 4: reports_menu(students, *count); break;
            case 5: printf("Exiting system...\n"); break;
            default: printf("Invalid option.\n");
        }

    } while (choice != 5);
}

void student_menu(Student *students, int *count)
{
    int choice;
    do
    {
        print_line();
        printf("%32s\n", "STUDENT RECORD MANAGEMENT");
        print_line();

        printf("| %-3s | %-45s |\n", "1", "Enter Student Details");
        printf("| %-3s | %-45s |\n", "2", "Update Student Record");
        printf("| %-3s | %-45s |\n", "3", "Delete Student Record");
        printf("| %-3s | %-45s |\n", "4", "Search Student");
        printf("| %-3s | %-45s |\n", "5", "Display All Students");
        printf("| %-3s | %-45s |\n", "6", "Calculate Results");
        printf("| %-3s | %-45s |\n", "7", "Back to Main Menu");
        print_line();

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: input_students(students, *count); break;
            case 2: update_students(students, *count); break;
            case 3: delete_student(students, count); break;
            case 4: search_student(students, *count); break;
            case 5: display_students(students, *count); break;
            case 6:
                calculate_results(students, *count);
                printf("Results calculated successfully.\n");
                break;
            case 7: break;
            default: printf("Invalid option.\n");
        }

    } while (choice != 7);
}

void file_menu(Student *students, int count)
{
    int choice;
    do
    {
        print_line();
        printf("%34s\n", "FILE OPERATIONS");
        print_line();

        printf("| %-3s | %-45s |\n", "1", "Save Records to CSV");
        printf("| %-3s | %-45s |\n", "2", "Load Records from CSV");
        printf("| %-3s | %-45s |\n", "3", "Export Sorted CSV");
        printf("| %-3s | %-45s |\n", "4", "Back to Main Menu");
        print_line();

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: save_to_file(students, count); break;
            case 2: load_from_file(students, count); break;
            case 3: saving_sorted_csv(students, count); break;
            case 4: break;
            default: printf("Invalid option.\n");
        }

    } while (choice != 4);
}

void insights_menu(Student *students, int count)
{
    int choice;
    do
    {
        print_line();
        printf("%34s\n", "ACADEMIC INSIGHTS");
        print_line();

        printf("| %-3s | %-45s |\n", "1", "Subject Wise Topper");
        printf("| %-3s | %-45s |\n", "2", "Overall Topper");
        printf("| %-3s | %-45s |\n", "3", "Distinction Students");
        printf("| %-3s | %-45s |\n", "4", "Failed Students");
        printf("| %-3s | %-45s |\n", "5", "Back to Main Menu");
        print_line();

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: subject_wise_topper(students, count); break;
            case 2: overall_topper(students, count); break;
            case 3: distinction_students(students, count); break;
            case 4: failed_students(students, count); break;
            case 5: break;
            default: printf("Invalid option.\n");
        }

    } while (choice != 5);
}


void reports_menu(Student *students, int count)
{
    int choice;
    do
    {
        print_line();
        printf("%34s\n", "REPORTS & ANALYTICS");
        print_line();

        printf("| %-3s | %-45s |\n", "1", "Generate Individual Report Card");
        printf("| %-3s | %-45s |\n", "2", "Class Performance Dashboard");
        printf("| %-3s | %-45s |\n", "3", "Back to Main Menu");
        print_line();

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: generate_report_card(students, count); break;
            case 2: class_analytics_dashboard(students, count); break;
            case 3: break;
            default: printf("Invalid option.\n");
        }

    } while (choice != 3);
}


void read_full_name(char *name, int size)
{
    fgets(name, size, stdin);

    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';
}

void input_students(Student *students, int count) 
{
    for (int i = 0; i < count; i++) 
	{
        printf("\nStudent %d\n", i + 1);
		
		printf("Roll number: ");
		while (1)
		{
		    if (scanf("%d", &students[i].roll_number) != 1)
		    {
		        clear_input_buffer();
		        printf("Invalid input. Enter roll number again: ");
		        continue;
		    }
		
		    if (roll_exists(students, i, students[i].roll_number, -1))
		    {
		        printf("Duplicate roll number detected. Enter a unique roll number: ");
		        continue;
		    }
		
		    break;
		}
	
		clear_input_buffer();
		printf("Name: ");
		read_full_name(students[i].name, NAME_LENGTH);
		
		for(int j=0;j<SUBJECT_COUNT;j++)
		{
			printf("Marks for %s: ", SUBJECT_NAMES[j]);
			
			while(scanf("%f", &students[i].marks[j]) !=1)
			{
			clear_input_buffer();
			printf("Invalid input, Enter marks again: ");
			}
		}
		
		students[i].total = 0.0f;
		students[i].percentage = 0.0f;
	}
}

void calculate_results(Student *students, int count) 
{
    for (int i = 0; i < count; i++)
	 {
        float sum = 0.0f;

        for (int j = 0; j < SUBJECT_COUNT; j++) 
		{
            sum += students[i].marks[j];
        }

        students[i].total = sum;
        students[i].percentage = sum / SUBJECT_COUNT;
    }
}

void display_students(Student students[], int count) 
{
    printf("\n----- STUDENT RESULTS -----\n");

    for (int i = 0; i < count; i++) 
	{
        printf("\nRoll Number : %d", students[i].roll_number);
        printf("\nName        : %s", students[i].name);
        printf("\nTotal       : %.2f", students[i].total);
        printf("\nPercentage  : %.2f%%", students[i].percentage);
    }
}

void update_students(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available to update.\n");
        return;
    }

    int roll;
    int found = 0;

    printf("Enter roll number to update: ");
    while (scanf("%d", &roll) != 1)
    {
        clear_input_buffer();
        printf("Invalid input. Enter roll number again: ");
    }

    for (int i = 0; i < count; i++)
    {
        if (students[i].roll_number == roll)
        {
            found = 1;

            printf("\nUpdating details for Roll Number %d\n", roll);

            // Update Roll Number, with duplicate protection

            int new_roll;

            printf("Enter new roll number: ");
            while (1)
            {
                if (scanf("%d", &new_roll) != 1)
                {
                    clear_input_buffer();
                    printf("Invalid input. Enter roll number again: ");
                    continue;
                }

                if (roll_exists(students, count, new_roll, i))
                {
                    printf("Duplicate roll number detected. Enter unique roll number: ");
                    continue;
                }

                break;
            }

            students[i].roll_number = new_roll;

            // Update Name

            clear_input_buffer();
			printf("New Name: ");
			read_full_name(students[i].name, NAME_LENGTH);


            // Marks updation and recalculation 

            float sum = 0.0f;

            for (int j = 0; j < SUBJECT_COUNT; j++)
            {
                printf("New marks for %s: ", SUBJECT_NAMES[j]);

                while (scanf("%f", &students[i].marks[j]) != 1)
                {
                    clear_input_buffer();
                    printf("Invalid input. Enter marks again: ");
                }

                sum += students[i].marks[j];
            }

            students[i].total = sum;
            students[i].percentage = sum / SUBJECT_COUNT;

            printf("Student details updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("No student found with roll number %d.\n", roll);
    }
}



void search_student(Student students[], int count) 
{
    int roll;
    int found = 0;

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll_number == roll) 
		{
            printf("\nStudent found:");
            printf("\nName       : %s", students[i].name);
            printf("\nTotal      : %.2f", students[i].total);
            printf("\nPercentage : %.2f%%\n", students[i].percentage);
            found = 1;
            break;
        }
    }

    if (!found) 
	{
        printf("No student found with roll number %d.\n", roll);
    }
}

void delete_student(Student students[], int *count)
{
    if (*count == 0)
    {
        printf("No records available to delete.\n");
        return;
    }

    int roll;
    int found = 0;

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < *count; i++)
    {
        if (students[i].roll_number == roll)
        {
            // Shifting remaining students left
            for (int j = i; j < *count - 1; j++)
            {
                students[j] = students[j + 1];
            }

            (*count)--;   // reducing total student count
            found = 1;

            printf("Student record deleted successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("No student found with roll number %d.\n", roll);
    }
}


void save_to_file(Student students[], int count)
{
    FILE *fp = fopen("students.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // Writing header
    fprintf(fp, "Roll,Name");

    for (int i = 0; i < SUBJECT_COUNT; i++)
        fprintf(fp, ",%s", SUBJECT_NAMES[i]);

    fprintf(fp, ",Total,Percentage,Grade\n");

    // Writing Students Grades
    for (int i = 0; i < count; i++)
    {
        char grade = calculate_grade(students[i].percentage);

        fprintf(fp, "%d,\"%s\"",
                students[i].roll_number,
                students[i].name);

        for (int j = 0; j < SUBJECT_COUNT; j++)
            fprintf(fp, ",%.2f", students[i].marks[j]);

        fprintf(fp, ",%.2f,%.2f,%c\n",
                students[i].total,
                students[i].percentage,
                grade);
    }

    fclose(fp);
    printf("Records saved successfully.\n");
}


void load_from_file(Student students[], int count)
{
    FILE *fp = fopen("students.csv", "r");
    if (fp == NULL)
    {
        printf("No CSV file found.\n");
        return;
    }

    char line[256];

    // Skipping Header
    fgets(line, sizeof(line), fp);

    int i = 0;

    while (fgets(line, sizeof(line), fp) != NULL && i < count)
    {
        sscanf(line,
               "%d,\"%31[^\"]\",%f,%f,%f,%f,%f,%f,%f,%*c",
               &students[i].roll_number,
               students[i].name,
               &students[i].marks[0],
               &students[i].marks[1],
               &students[i].marks[2],
               &students[i].marks[3],
               &students[i].marks[4],
               &students[i].total,
               &students[i].percentage);

        i++;
    }

    fclose(fp);
    printf("Records loaded successfully from CSV file.\n");
}


void saving_sorted_csv(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records to export.\n");
        return;
    }

    int option;

    printf("\nSelect sorting criteria:\n");
    printf("1. Roll Number (Ascending)\n");
    printf("2. Percentage (Highest First)\n");
    printf("3. Name (Alphabetical)\n");
    printf("Enter choice: ");

    if (scanf("%d", &option) != 1)
    {
        printf("Invalid input.\n");
        return;
    }

    // Creating a temporary copy 
    Student *temp =(Student *)malloc(count * sizeof(Student));
    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    memcpy(temp, students, count * sizeof(Student));

    //Selecting a comparator
    switch (option)
    {
        case 1:
            qsort(temp, count, sizeof(Student), roll_compare);
            break;

        case 2:
            qsort(temp, count, sizeof(Student), percentage_compare);
            break;

        case 3:
            qsort(temp, count, sizeof(Student), name_compare);
            break;

        default:
            printf("Invalid sorting option.\n");
            free(temp);
            return;
    }

    FILE *fp = fopen("students_sorted.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        free(temp);
        return;
    }

    // Writing header 
    fprintf(fp, "Roll,Name");
    
    for (int i = 0; i < SUBJECT_COUNT; i++)
        fprintf(fp, ",%s", SUBJECT_NAMES[i]);
        
    fprintf(fp, ",Total,Percentage,Grade\n");

    // Write sorted records
    
    for (int i = 0; i < count; i++)
    {
        char grade = calculate_grade(temp[i].percentage);

		fprintf(fp, "%d,\"%s\"",
		        temp[i].roll_number,
		        temp[i].name);
		
		for (int j = 0; j < SUBJECT_COUNT; j++)
		    fprintf(fp, ",%.2f", temp[i].marks[j]);
		
		fprintf(fp, ",%.2f,%.2f,%c\n", temp[i].total, temp[i].percentage, grade);
    }

    fclose(fp);
    free(temp);

    printf("Sorted CSV has been exported successfully.\n");
}

int roll_compare(const void *a, const void *b)
{
	const Student *s1 = (const Student *)a;
	const Student *s2 = (const Student *)b;
	
	return s1 ->roll_number - s2 ->roll_number;
}

int percentage_compare(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    if (s1->percentage < s2->percentage)
        return 1;
    else if (s1->percentage > s2->percentage)
        return -1;
    else
        return 0;
}

int name_compare(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    return strcmp(s1->name, s2->name);
}

int roll_exists(Student students[], int count, int roll, int ignore_index)
{
    for (int i = 0; i < count; i++)
    {
        if (i == ignore_index)
            continue;

        if (students[i].roll_number == roll)
            return 1;
    }
    return 0;
}

void clear_input_buffer(void)
{ 
	int c; 
	while ((c = getchar()) != '\n' && c!=EOF);
}

void subject_wise_topper(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available.\n");
        return;
    }

    for (int s = 0; s < SUBJECT_COUNT; s++)
    {
        int top_index = 0;

        for (int i = 1; i < count; i++)
        {
            if (students[i].marks[s] > students[top_index].marks[s])
                top_index = i;
        }

        printf("\n%s Topper:\n", SUBJECT_NAMES[s]);
        printf("Roll: %d\n", students[top_index].roll_number);
        printf("Name: %s\n", students[top_index].name);
        printf("Marks: %.2f\n", students[top_index].marks[s]);
    }
}


void overall_topper(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available.\n");
        return;
    }

    int top_index = 0;

    for (int i = 1; i < count; i++)
    {
        if (students[i].percentage > students[top_index].percentage)
            top_index = i;
    }

    printf("\nOverall Topper:\n");
    printf("Roll: %d\n", students[top_index].roll_number);
    printf("Name: %s\n", students[top_index].name);
    printf("Percentage: %.2f%%\n", students[top_index].percentage);
}

void distinction_students(Student students[], int count)
{
    int found = 0;

    printf("\nDistinction Students (>= 75%%):\n");

    for (int i = 0; i < count; i++)
    {
        if (students[i].percentage >= 75.0f)
        {
            printf("Roll: %d | Name: %s | %.2f%%\n",
                   students[i].roll_number,
                   students[i].name,
                   students[i].percentage);
            found = 1;
        }
    }

    if (!found)
        printf("No students with distinction.\n");
}

void failed_students(Student students[], int count)
{
    int found = 0;

    printf("\nFailed Students (Any subject < 40):\n");

    for (int i = 0; i < count; i++)
    {
        int failed = 0;

        for (int j = 0; j < SUBJECT_COUNT; j++)
        {
            if (students[i].marks[j] < 40.0f)
            {
                failed = 1;
                break;
            }
        }

        if (failed)
        {
            printf("Roll: %d | Name: %s\n",
                   students[i].roll_number,
                   students[i].name);
            found = 1;
        }
    }

    if (!found)
        printf("No failed students.\n");
}

char calculate_grade(float percentage)
{
    if (percentage >= 75.0f)
        return 'A';
    else if (percentage >= 60.0f)
        return 'B';
    else if (percentage >= 50.0f)
        return 'C';
    else
        return 'F';
}

void generate_report_card(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available.\n");
        return;
    }

    int roll;
    printf("Enter roll number to generate report card: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++)
    {
        if (students[i].roll_number == roll)
        {
            char grade = calculate_grade(students[i].percentage);

            int failed = 0;
            for (int j = 0; j < SUBJECT_COUNT; j++)
            {
                if (students[i].marks[j] < 40.0f)
                {
                    failed = 1;
                    break;
                }
            }

            printf("\n========================================\n");
            printf("           PERFORMANCE REPORT           \n");
            printf("========================================\n");
            printf("Name : %s\n", students[i].name);
            printf("Roll : %d\n", students[i].roll_number);
            printf("----------------------------------------\n");
            printf("| %-10s | %-10s |\n", "Subject", "Marks");
            printf("----------------------------------------\n");

            for (int j = 0; j < SUBJECT_COUNT; j++)
            {
                printf("| %-10s | %-10.2f |\n",
                       SUBJECT_NAMES[j],
                       students[i].marks[j]);
            }

            printf("----------------------------------------\n");
            printf("Total      : %.2f\n", students[i].total);
            printf("Percentage : %.2f%%\n", students[i].percentage);
            printf("Grade      : %c\n", grade);
            printf("Status     : %s\n", failed ? "FAIL" : "PASS");
            printf("========================================\n");

            return;
        }
    }

    printf("Student not found.\n");
}

void class_analytics_dashboard(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available.\n");
        return;
    }

    float total_percentage = 0.0f;
    float highest = students[0].percentage;
    float lowest = students[0].percentage;
    int pass_count = 0;

    int gradeA = 0, gradeB = 0, gradeC = 0, gradeF = 0;

    for (int i = 0; i < count; i++)
    {
        total_percentage += students[i].percentage;

        if (students[i].percentage > highest)
            highest = students[i].percentage;

        if (students[i].percentage < lowest)
            lowest = students[i].percentage;

        int failed = 0;
        for (int j = 0; j < SUBJECT_COUNT; j++)
        {
            if (students[i].marks[j] < 40.0f)
            {
                failed = 1;
                break;
            }
        }

        if (!failed)
            pass_count++;

        char grade = calculate_grade(students[i].percentage);

        if (grade == 'A') gradeA++;
        else if (grade == 'B') gradeB++;
        else if (grade == 'C') gradeC++;
        else gradeF++;
    }

    float class_avg = total_percentage / count;
    float pass_percentage = ((float)pass_count / count) * 100.0f;

    printf("\n========================================\n");
    printf("         CLASS ANALYTICS DASHBOARD      \n");
    printf("========================================\n");
    printf("Class Average Percentage : %.2f%%\n", class_avg);
    printf("Highest Percentage       : %.2f%%\n", highest);
    printf("Lowest Percentage        : %.2f%%\n", lowest);
    printf("Pass Percentage          : %.2f%%\n", pass_percentage);

    printf("\nGrade Distribution:\n");
    printf("A : %d\n", gradeA);
    printf("B : %d\n", gradeB);
    printf("C : %d\n", gradeC);
    printf("F : %d\n", gradeF);

    printf("\nSubject-wise Averages:\n");

    for (int s = 0; s < SUBJECT_COUNT; s++)
    {
        float sum = 0.0f;

        for (int i = 0; i < count; i++)
            sum += students[i].marks[s];

        printf("%s : %.2f\n", SUBJECT_NAMES[s], sum / count);
    }

    printf("========================================\n");
}







