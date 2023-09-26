// File Name: assign3_fks7.cpp
//
// Author: Faith Shaffer
// Date: 3/5/2020
// Assignment Number: 3
// CS 2308.255 Spring 2020
// Instructor: Vladyslav Prokopenko
//

#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 8;                         // Constant array size of 8
const int SIZE2 = 10;                       // Constant array size of 10
const int SIZE3 = 5;                        // Constant array size of 5

// rightCircularShifts: Completes a right circular shift on array of integers,
// moves elements one position to the right and last element to the front.
void rightCircularShifts(int array[]) {
    int x, y;
    int *pntr;
    pntr = array;
    
    for (int i = SIZE - 1; i > 0; i--) {
        y = *(pntr + i);
        x = *(pntr + i - 1);
        *(pntr + i) = x;
        *(pntr + i - 1) = y;
    }
    
    for (int i = 0; i < SIZE; i++) {
        cout << *(pntr + i) << " ";
    }
    cout << endl;
}

// sort2withSum: changes the values of the variables passed into it, uses
// pointers as parameters.
// Returns sum of pointer variables.
int sort2withSum (int *x, int *y) {
    if (x > y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
    return *x + *y;
}

// resize: creates a new array that is twice the size of the argument array,
// copies the contents of the argument array to the new array, and
// initializes the unused elements of the new array with -1.
// Returns a pointer to the new array.
int *resize (int *arr, int SIZE2) {
    int *newArr = new int[2 * SIZE2];
    
    for (int i = 0; i < SIZE2; i++) {
        *(newArr + i) = *(arr + i);
    }
    for (int i = SIZE2; i < 2 * SIZE2; i++) {
        *(newArr + i) = -1;
    }
    return newArr;
}

// concatenate: creates a new array big enough to store both arrays,
// copies the contents of the first array to the new array,
// copies the contents of the second array to the new array in the
// remaining elements, and returns a pointer to the new array.
int *concatenate (int *arr2, int *arr3,int SIZE2, int SIZE3) {
    int *newArr = new int[SIZE2 + SIZE3];
    
    for (int i = 0; i < SIZE2; i++) {
        *(newArr + i) = *(arr2 + i);
    }
    for (int i = SIZE2, k = 0; i < SIZE2 +SIZE3; i++, k++) {
        *(newArr + i) = *(arr3 + k);
    }
        return newArr;
}

// duplicateArr: creates a new array that is a copy of the elements from the original array starting
// at the start index, and has length equal to the length argument.
// Takes an int array, a start index, and a length as arguments.
int *duplicateArr (int *arr, int size) {
    int *newArr;
    if (size <= 0)
        return NULL;
    
    newArr = new int [size];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}

// subArray: creates a new array that is a copy of the elements from the original array starting
// at the start index, and has length equal to the length argument.
// Takes an int array, a start index, and a length as arguments.
int *subArray (int *arr, int start, int length) {
    int *result = duplicateArr(arr + start, length);
    return result;
}

// printArr: prints array
void printArr (int *array, int SIZE){
    for (int i = 0; i < SIZE; i++){
        cout << *(array + i) << " ";
    }
    cout << endl;
}

// main: calls functions, outputs elements/results.
int main() {
    int arr[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr2[SIZE2] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int arr3[SIZE3] = {11, 22, 33, 44, 55};
    
    cout << "Testing RightCircularShift:" << endl;
    cout << "test data array: ";
    printArr(arr, SIZE);
    cout << "Expected Result: 8 1 2 3 4 5 6 7" << endl;
    cout << "Actual result: ";
    rightCircularShifts(arr);

    cout << "shift again:" << endl;
    cout << "2" << endl;
    cout << "Expected results: 7 8 1 2 3 4 5 6" << endl;
    cout << "Actual Results: ";
    rightCircularShifts(arr);

    int a = 8, b = 5, sum = 0;
    cout << "testing sort2withSum" << endl;
    cout << "test data: " << "a:" << a << " b:" << b << endl;
    cout << "Expected results: 13 a: 5 b: 8" << endl;
    cout << "Actual Results: ";
    sum = sort2withSum(&a, &b);
    cout << sum << " a: " << a << " b: " << b << endl;
    
    cout << "testing resize " << endl;
    cout << "test data: ";
    printArr(arr2, SIZE2);
    cout << "Expected Result: 1 2 3 4 5 6 7 8 9 0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1";
    cout << endl;
    int *resizeArr = resize(arr2, SIZE2);
    cout << "Actual results: ";
    printArr(resizeArr, SIZE2 * 2);
    
    cout << "testing concatenate " << endl;
    cout << "test data: ";
    printArr(arr2, SIZE2);
    cout << "and ";
    printArr(arr3, SIZE3);
    cout << "Expected result: 1 2 3 4 5 6 7 8 9 0 11 22 33 44 55" << endl;
    cout << "Actual Result: ";
    int *concatenateArr = concatenate(arr2, arr3, SIZE2, SIZE3);
    printArr(concatenateArr, SIZE2 + SIZE3);
    
    int start = 5, length = 4;
    cout << "testing subArray: " << endl;
    cout << "start: " << start << " length: " << length << endl;
    cout << "Expected Result: 6 7 8 9 " << endl;
    cout << "Actual Results: ";
    int *newArr = subArray(arr2, start, length);
    printArr(newArr, length);
    
    
    return 0;
}
