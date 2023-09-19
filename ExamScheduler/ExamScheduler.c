
#include <stdio.h>
#include <stdlib.h>
#include "041040764.h"

// define statement to print out the menu option.
#define MENU(Num, action) printf("%d. %s\n", Num, action);

typedef unsigned long long int uLLInt;

// This variable hold the 64 bit binary value of the schedules.
uLLInt binaryReservations[2][64] = {0};

// This is a temporary variable hold the 64 bit binary value of the schedules.
uLLInt binaryReservations_temp[2][64] = {0};

// Temporary array that holds the | result of binaryReservations1(temp variable) and binaryReservations array. More on this variable in convertToBiary() method.
uLLInt temp[2][64] = {0};

// This is a temporary exam booking array.
int temp_examBookings[3000][5] = {0};

int lengthOfExamBookingArray = 2715;

/*
These two variable hold the weeks and days of the exam, it is only used when printing out students exam schedules and finding unbooked time.
*/
char Week[][200] = {{"Week 1"}, {"Week 2"}};
char Day[][200] = {{"Monday"}, {"Tuesday"}, {"Wednesday"}, {"Thursday"}, {"Friday"}, {"Saturday"}, {"Sunday"}};

// Required forwared declarations
void displayUnbookedTime(int time, char *day, char *week);
void setExamBookingTime();
void convertuLLIntToArray();
int convertToBinary(int value[3000][5]);
int displayMenu();
void executeMenuItem(int menuItem);
void displayStudentExamSchedule();

/*
This is the main method that calls the display menu option method and calls the execute menu option method.
*/
int main(void)
{

    convertToBinary(examBookings);

    int option = 0;
    do
    {
        option = displayMenu();
        executeMenuItem(option);

    } while (option != 4);

    printf("Exiting Exam Booking Software\n");
}

/*
This method prints out the menu option to screen.
This method also gets the user menu choice.
*/
int displayMenu()
{
    int input = 0;
    printf("Select one of the following:\n\n");
    MENU(1, "display a student's exam schedule");
    MENU(2, "load a new exam booking");
    MENU(3, "find unbooked times");
    MENU(4, "exit");
    printf("> ");
    scanf("%d", &input);
    return input;
}

void executeMenuItem(int menuItem)
{

    switch (menuItem)
    {
    case 1:
        displayStudentExamSchedule();
        break;
    case 2:
        setExamBookingTime();
        break;
    case 3:
        convertuLLIntToArray();
        break;
    default:
        break;
    }
}

/*
  This method displays a given students exam shedule by by looping through the examBookings array
  and pulling out the requied information(which is the student exam schedule).
*/
void displayStudentExamSchedule()
{
    // variable that holds the student number
    int stuNum;

    printf("Enter Student Number: ");
    scanf("%d", &stuNum);

    // Looping through the array to find exam shedule.
    for (int i = 0; i < lengthOfExamBookingArray; i++)
    {
        // Checking to see if the element at the specified examBookings index is equal to the student number
        if (examBookings[i][0] == stuNum)
        {
            // printing out required information
            printf("%s: %s \t%d:00 - %d:00\n", Week[examBookings[i][1]], Day[examBookings[i][2]],
                   examBookings[i][3], examBookings[i][3] + examBookings[i][4]);
        }
    }
}

/*
This method prints out the information passed in the parameter.
This method is used to print unbooked time.
*/
void displayUnbookedTime(int time, char *day, char *week)
{
    printf("%s \t %s \t %d:00\n", week, day, time);
}

/*
This method sets the exam booking time by getting the shcedule information form keyboard, converting that into binary then &ing the binary form of schedules that already exist to make sure there are no duplicates.
*/
void setExamBookingTime()
{
    int examWeek = 0; // This variable stores the week of the exam the user will input.
    int examDay = 0;  // This variable stores the day of the exam the user will input.

    // Getting requied information from line "141" to line "156".
    printf("Enter Student Number: ");
    scanf("%d", &temp_examBookings[0][0]);

    printf("Enter exam week(1 or 2): ");
    scanf("%d", &examWeek);
    examWeek = examWeek - 1;
    temp_examBookings[0][1] = examWeek;

    printf("Enter exam day(M = 0; T = 1...): ");
    scanf("%d", &temp_examBookings[0][2]);

    printf("Enter exam start time(9 - 16): ");
    scanf("%d", &temp_examBookings[0][3]);

    printf("Enter number of hours: ");
    scanf("%d", &temp_examBookings[0][4]);

    /*
    Calling the convert to binary method to convert the given shcedule to binary and then making sure there are not duplicate schedule.
    The convert to binary method return a "1" if the shcedule inputed by the user matches a schedule that already exist i.e duplicate schedule and "0" if it dosent.
    */
    int test = convertToBinary(temp_examBookings);

    // Checking if the conversion and comparison of the schedules was sucessful.
    if (test != 1)
    {
        // This for loop copies the information from the temporary examBooking array into the original exam booking array.
        for (int i = 0; i < 5; i++)
        {
            examBookings[lengthOfExamBookingArray][i] = temp_examBookings[0][i];
        }

        // Incrementing the lenth of the array, to create space for more values.
        lengthOfExamBookingArray++;
        printf("Timeblock was successfully booked\n");
    }
}

/*
This method is used by the displayUnbookeTime method, this method converts the binary schedules into a readable format by looping through the binaryReservations array and finding the 0's bits and calculating
the correct week, day , and time that corresponds to the 0 value.
*/
void convertuLLIntToArray()
{
    // Outter for loop to specify the week.
    for (int i = 0; i < 2; i++)
    {
        // The time is used to determine the time of the binary value.
        // The variable dayNum is used to determine the day.
        int time = 9, dayNum = 0;

        for (int t = 64 - 1; t >= 8; t--)
        {
            /* Checking for 1's in the binaryReservation array and calling the displayUnbookedTime method to print out the information of that binary bit
             in readable form e.g Monday, week 1.......
             */
            if (binaryReservations[i][t] == 0)
            {

                displayUnbookedTime(time, Day[dayNum], Week[i]);
            }

            /*
            The block of code from line "204" to line "211" is used to control the day and time variable e.g.
            If the time is > 16:00, we will need to change the time back to 9:00 and increment the day by one which tells us that the next 0 binary values to encounter will be in day e.g Tuesday and time 9:00.....
            */
            time++;

            (time > 16) ? dayNum++ : 0;
            (dayNum > 6) ? dayNum = 0 : 0;
            (time > 16) ? time = 9 : 0;
        }
    }
}

/*
This method converts an array into binary and receives the array e.g binaryReservations as a parameter.
This method shifts a 64 bit bitmask value by the hours extracted from the array, then inverse it, then shift it again by 8 * the day extracted form the array.
After that, it then converts the value gotten from the shifts into a binary form. And the binary (of the shifted value) is then &ed(&) by the existing binary reservations to ensure no ducplicate schedules is made. e.g
1 & 1 = 1 which mean duplicate schedule, 1 & 0 = 0 which mean not a duplicate schedule.
After the &ing is done and ensured there are no duplicate schedules, the values are then |(ored) with the binaryReservations array, which then holds the binary value of all the schedules.

Note: The binary "&" results are held in a temp array called "binaryReservations_temp", and the binary | results are held in a temp arrray called "temp", when no duplicate schedules are ensured the binary values in the "temp" array
are then copied to binaryReservations array.
e.g if there are duplicate schedules it will be held in the temp array, therefore not affecting binaryReservations (which holds the correct schedules). and if there are no duplicate scheules, the binary values are copied into binaryReservations.
*/
int convertToBinary(int value[3000][5])
{
    uLLInt bitmask = 0xFFFFFFFFFFFFFFFF;
    uLLInt binaryReservations1[2][64] = {0}; // Temporary array that holds the binary result of the schedules i.e the shifting and inverting result converted to binary.
    int x = 0;                               // just the index of the binary array. e.g binaryReservations1[1][x], binaryReservations1[2][x].....

    for (int i = 0; i < lengthOfExamBookingArray; i++)
    {
        int hour = value[i][4];                                                // This variable holds the duration of the exam, hours.
        uLLInt shiftBit = bitmask >> hour;                                     // This line of code right shifts the bitmask value by the hours.
        shiftBit = ~shiftBit;                                                  // This line of code inverses the result of the left shift.
        uLLInt dayShift = shiftBit >> ((8 * value[i][2]) + (value[i][3] - 9)); // This line of code shifts the result of the inverse by the day of the exam + the start time.

        // This block of code just converts the result of dayShift into an array.
        while (dayShift > 0)
        {
            binaryReservations1[value[i][1]][x] = dayShift % 2;
            x++;
            dayShift = dayShift / 2;
        }

        x = 0;

        // This for loop is used to & and | the binary values.
        // for (int j = 64 - 1; j >= 0; j--)
        for (int j = 64 - 1; j >= 8; j--)
        {
            //|ing the binary values of temp and binaryReservations1 and saving them in the temp array.
            temp[value[i][1]][j] = temp[value[i][1]][j] | binaryReservations1[value[i][1]][j];

            //&ing the binary values of binaryReservations and binaryReservations1 and saving them in the binaryReservations_temp array.
            binaryReservations_temp[value[i][1]][j] = binaryReservations[value[i][1]][j] & binaryReservations1[value[i][1]][j];

            // This if statement checks if the & result is of the current index is equls 1 (Which mean there is a duplicate).
            // If the condition is met the method is terminated.
            if (binaryReservations_temp[value[i][1]][j] == 1)
            {
                printf("That time is not available :)\n");
                return 1;
            }
        }
    }

    /*
    If the process of this code reaches here that mean there where no duplicate schedules. So it would be safe to copy the values for the
    temp(holds the result of |) array to the binaryReservation array.
    */
    for (int i = 0; i < lengthOfExamBookingArray; i++)
    {
        for (int j = 64 - 1; j >= 0; j--)
        {
            binaryReservations[examBookings[i][1]][j] = temp[examBookings[i][1]][j];
        }
    }

    return 0;
}
