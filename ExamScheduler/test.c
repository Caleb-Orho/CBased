#include <stdio.h>
 
void decToBinary(unsigned long long int n)
{
    // array to store binary number
    unsigned long long int binaryNum[32];
  
    // counter for binary array
    unsigned long long int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
  
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        printf("%llu", binaryNum[j]);
}
  
// Driver program to test above function
int main()
{
    unsigned long long int n = 13835058055282163712;
    //decToBinary(n);
    return 0;
}