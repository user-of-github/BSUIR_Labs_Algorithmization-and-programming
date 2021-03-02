/* https://bsuir.irunner.by/courses/165/problems/4120/
Необходимо реализовать бинарный поиск на отсортированном в неубывающем порядке
массиве чисел.
Использование готовых функций бинарного поиска из стандартных библиотек запрещается.*/

#include <cstdio>

int BinarySearchLeft (const int *arr, const unsigned int &length, const int &desiredElement);
int BinarySearchRight (const int *arr, const unsigned int &length, const int &desiredElement);

int main()
{

    unsigned int length = 10;
    scanf("%d", &length);
    int *numbers = new int [length];

    for (unsigned int counter = 0; counter < length; counter ++)
        scanf("%d", &numbers[counter]);

    unsigned int numberOfRequests = 0;
    scanf("%d", &numberOfRequests);

    int query;

    for (unsigned int counter = 0; counter < numberOfRequests; counter ++)
    {
        scanf("%d", &query);
        unsigned int leftIndex = BinarySearchLeft(numbers, length, query);
        unsigned int rightIndex = BinarySearchRight(numbers, length, query);

        if (numbers[leftIndex] == query || numbers[rightIndex] == query)
            printf("1 ");
        else
            printf("0 ");

        // ДЛЯ БОЛЬШЕГО ИЛИ РАВНОГО
        if (numbers[leftIndex] >= query)
        {
            //cout<<"numbers[leftIndex] >= query";
            while (leftIndex > 0 && numbers[leftIndex - 1] >= query)
                leftIndex --;

        }
        else
        {
            while (leftIndex < length && numbers[leftIndex] < query)
                leftIndex ++;
        }

        // для БОЛЬШЕГО:
        if (numbers[rightIndex] > query)
        {
            while (rightIndex > 0 && numbers[rightIndex - 1] > query)
                rightIndex --;

        }
        else
        {
            while (rightIndex < length && numbers[rightIndex] <= query)
                rightIndex ++;
        }


        printf("%d %d", leftIndex, rightIndex);
        printf(counter != numberOfRequests - 1 ? "\n" : "");
    }

    return 0;
}

int BinarySearchLeft (const int *arr, const unsigned int &length, const int &desiredElement)
{
    int left = 0,
        right = length - 1;
    int middle = (left + right) / 2;

    while (left <= right)
    {
        middle = (left + right) / 2;
        if (left == middle)
            break;

        if (arr[middle] < desiredElement)
            left = middle;
        else
            right = middle;
    }

    return right;
}

int BinarySearchRight (const int *arr, const unsigned int &length, const int &desiredElement)
{
    int left = 0,
        right = length - 1;
    int middle = (left + right) / 2;

    while (left <= right)
    {
        middle = (left + right) / 2;

        if (left == middle)
            break;

        if (arr[middle] <= desiredElement)
            left = middle;
        else
            right = middle;
    }

    return left;
}

