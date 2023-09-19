#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
// clear && gcc -o o PasswordManager.c && ./o
#define Exit 0
#define Create 1
#define Log 2
#define Delete 3
#define Change 4

char numbers[] = "0123456789";

char letter[] = "abcdefghijklmnoqprstuvwyzx";

char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";

char symbols[] = "!@#$^&*?";

static int encryptKey[100] = {+2, +2, +3, +8, +12};
static int encryptedValue[100], *pEncryptedValue = encryptedValue;

char *LoginSession;

typedef struct
{
    int age;
    char *Name;
    char *passWord;
    char *platform;
    char *platformPassWord;
} UserInfo;

UserInfo *user[100] = {0};

static int Login();
void executeMenuItem(int);
int displayMenu();
int subMenu();
static char *Encrypt(char *);
static UserInfo *utilityFunction();
static int createAccount();
static void viewAccount(char *);
static int AddPassword();
void ReadFile();
void WriteInfo();
static int AddPlatform();
void updatePlatformPassWord();
char *ecrypt();
int GetInfo();

int main()
{
    // system("touch files.txt");

    LoginSession = (char *)malloc(100);

    int choice = Exit;

    ReadFile();

    do
    {
        choice = displayMenu();
        executeMenuItem(choice);

        WriteInfo();

    } while (choice != Exit);
}

int displayMenu()
{
    int input = Exit;
    printf("Select one of the following:\n\n");
    printf("1. Create An Account\n2. Login\n");
    printf("%d. Exit Program\n> ", Exit);
    scanf("%d", &input);
    return input;
}

int subMenu()
{
    int input = Exit;
    printf("\n\tWhat would you like to do today\n\n");
    printf("1. Add Platform\n2. Update Platform Password\n3. Get PasswordFile\n");
    printf("4. Exit Program\n> ");
    scanf("%d", &input);
    return input;
}

void executeMenuItem(int menuOption)
{
    int pass;

    switch (menuOption)
    {
    case Exit:
        break;

    case Create:
        pass = createAccount();
        printf("Account created!\n");
        break;

    case Log:
        pass = Login();
        while (pass != 4 && pass > 0)
        {
            viewAccount(LoginSession);
            pass = subMenu();

            switch (pass)
            {
            case 1:
                AddPlatform();
                break;
            case 2:
                updatePlatformPassWord();
                break;
            case 3:
                GetInfo();
                break;
            }
        }

        break;
    }
}

int createAccount()
{
    UserInfo *ptr = utilityFunction();

    printf("Enter your name: ");
    scanf(" %[^\n]s", ptr->Name);

    printf("Enter platform Name: ");
    scanf(" %[^\n]s", ptr->platform);

    printf("Do you want a Generated password 1 = Y or 0 = N? ");
    int opt = 0;
    scanf("%d", &opt);

    if (opt)
    {
        ptr->platformPassWord = ecrypt();
    }
    else
    {
        printf("Enter your %s Password: ", ptr->platform);
        scanf(" %[^\n]s", ptr->platformPassWord);
    }

    printf("Do you want a Generated password 1 = Y or 0 = N? ");
    scanf("%d", &opt);

    if (opt)
    {
        ptr->passWord = ecrypt();
    }
    else
    {
        printf("Enter passWord: ");
        scanf(" %[^\n]s", ptr->passWord);
    }

    printf("Enter your age: ");
    scanf("%u", &ptr->age);

    return 1;
}

int Login()
{
    int pass = 0;
    int numOfPlatFrom;
    char *uName = (char *)malloc(50);
    char *pWord = (char *)malloc(50);

    printf("Enter UserName: ");
    scanf(" %[^\n]s", uName);

    for (UserInfo **start = user + 0; start < user + 100; start++)
    {
        if (*start != NULL && strcmp((*start)->Name, uName) == 0)
        {
            printf("Enter Password: ");
            scanf(" %[^\n]s", pWord);

            if (strcmp((*start)->passWord, pWord) == 0)
            {
                pass = 1;

                strcpy(LoginSession, uName);
                break;
            }
        }
    }

    if (pass == 0)
        printf("Could not login\n");

    free(uName);
    uName = NULL;

    free(pWord);
    pWord = NULL;

    return pass;
}

static void viewAccount(char *name)
{
    printf("\n\t     Welcome %s", name);
    printf("\n\t---------------------------\n");
    printf("\t| %-10s | %-10s |\n", "Platform", "Password");
    printf("\t---------------------------\n");

    for (UserInfo **start = user + 0; start < user + 100; start++)
        if (*start != NULL && strcmp((*start)->Name, name) == 0)
            printf("\t| %-10s | %-10s |\n", (*start)->platform, (*start)->platformPassWord);

    printf("\t---------------------------\n");
}

static int AddPlatform()
{
    for (UserInfo **start = user + 0; start < user + 100; start++)
    {
        if (*start != NULL && strcmp((*start)->Name, LoginSession) == 0)
        {
            UserInfo *ptr = utilityFunction();

            printf("Enter platform Name: ");
            scanf(" %[^\n]s", ptr->platform);

            printf("Enter your %s Password: ", ptr->platform);
            scanf(" %[^\n]s", ptr->platformPassWord);

            strcpy(ptr->passWord, (*start)->passWord);
            strcpy(ptr->Name, (*start)->Name);

            (*start)->age = ptr->age;

            break;
        }
    }
}

UserInfo *utilityFunction()
{
    for (UserInfo **start = user + 0; start < user + 100; start++)
    {
        if (*start == NULL)
        {
            *start = (UserInfo *)malloc(sizeof(UserInfo) * 30);

            (*start)->Name = (char *)malloc(50);
            (*start)->platform = (char *)malloc(50);
            (*start)->platformPassWord = (char *)malloc(50);
            (*start)->passWord = (char *)malloc(50);
            return *start;
        }
    }
}

void updatePlatformPassWord()
{
    char *pName = (char *)malloc(50);
    char *pWord;

    printf("Enter Platform name: ");
    scanf(" %[^\n]s", pName);

    for (UserInfo **start = user + 0; start < user + 100; start++)
    {
        if (*start != NULL && strcmp((*start)->Name, LoginSession) == 0 && strcmp((*start)->platform, pName) == 0)
        {
            pWord = (char *)malloc(50);

            printf("Enter the new password for your %s Account: ", pName);
            scanf(" %[^\n]s", pWord);

            strcpy((*start)->platformPassWord, pWord);

            return;
        }
    }

    printf("You do not have an %s Account", pName);

    free(pName);
    pName = NULL;

    free(pWord);
    pWord = NULL;
}

UserInfo **DeleteAccount()
{
    char *uName = (char *)malloc(50);
    printf("enter bus route to delete: ");
    scanf("%s", uName);

    for (UserInfo **start = user + 99; start >= user + 0; start--)
    {
        if (*start != NULL && strcmp((*start)->Name, uName) == 0)
        {
            free((*start)->Name);
            (*start)->Name = NULL;

            free((*start)->passWord);
            (*start)->passWord = NULL;

            free(*start);
            *start = NULL;

            return start;
        }
    }

    free(uName);
    uName = NULL;

    return NULL;
}

void ReadFile()
{
    FILE *file = fopen("info.csv", "r");
    if (file == NULL)
    {
        printf("File does not exist of file is emppyt\n");
        return;
    }

    do
    {
        UserInfo *ptr = utilityFunction();

        fscanf(file,
               "%49[^,],%49[^,],%49[^,],%49[^,],%d\n",
               ptr->Name,
               ptr->platform,
               ptr->platformPassWord,
               ptr->passWord,
               &ptr->age);

    } while (!feof(file));

    fclose(file);
}

void WriteInfo()
{
    FILE *fpt = fopen("info.csv", "w");

    for (UserInfo **start = user + 0; start < user + 100; start++)
    {
        if (*start != NULL)
        {

            fprintf(fpt, "%s,%s,%s,%s,%d\n", (*start)->Name, (*start)->platform, (*start)->platformPassWord, (*start)->passWord, (*start)->age);
        }
    }

    fclose(fpt);
}

char *ecrypt()
{
    int i = 0;

    int randomizer = 0;

    srand((unsigned int)(time(NULL)));

    randomizer = rand() % 4;

    char *password = (char *)malloc(50);

    for (i = 0; i < 10; i++)
    {

        if (randomizer == 1)
        {
            *(password + i) = numbers[rand() % 10];
            randomizer = rand() % 4;
        }
        else if (randomizer == 2)
        {
            *(password + i) = symbols[rand() % 8];
            randomizer = rand() % 4;
        }
        else if (randomizer == 3)
        {
            *(password + i) = LETTER[rand() % 26];
            randomizer = rand() % 4;
        }
        else
        {
            *(password + i) = letter[rand() % 26];
            randomizer = rand() % 4;
        }
    }

    printf("%s\n", password);

    return password;
}

int GetInfo()
{
    FILE *fpt = fopen(LoginSession, "w");
    fprintf(fpt, "%s,%s\n", "Platform", "PassWord");

    for (UserInfo **start = user + 0; start < user + 100; start++)
    {
        if (*start != NULL && strcmp((*start)->Name, LoginSession) == 0)
        {
            fprintf(fpt, "%s,%s\n", (*start)->platform, (*start)->platformPassWord);
        }
    }

    fclose(fpt);

    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("File written to: %s\n", cwd);
    }
}

void Admin()
{
    Login();
}