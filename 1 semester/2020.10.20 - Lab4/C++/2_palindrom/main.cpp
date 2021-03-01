#include <stdio.h>
#include <vector>

using std::vector, std::swap;

void reverseArray(vector<char> &arr);
void arrayOfNumbers(vector<char> &nums, long long number);
void makePalindrom(vector<char> &arr);
void numberFromArray(vector<char> nums, long long &number);

int main()
{
    long long input;
    scanf("%lld", &input);

    vector<char> nums;

    arrayOfNumbers(nums, input);
    makePalindrom(nums);

    long long newNumber = 0;

    numberFromArray(nums, newNumber);

    if (newNumber <= input)
    {

        arrayOfNumbers(nums, input);
        char position = ((nums.size() % 2) == 0 ? (nums.size() / 2 - 1) : (nums.size()/2));
        nums[position] = (nums[position] + 1) % 10;
        if (nums[position] == 0)
        {
            position--;
            while (nums[position] == 9 && position >= 0)
            {
                nums[position] = 0;
                position --;
            }

            if (position <= 0 && nums[0] == 0)
            {
                nums.push_back(0);
                for (int i = 0; i < nums.size() - 1; i ++)
                    nums[i + 1] = nums[i];

                nums[0] = 1;
            }
            else
            {
                nums[position] += 1;
            }
        }
        makePalindrom(nums);
        numberFromArray(nums, newNumber);
    }

    printf("%lld", newNumber);

    return 0;
}
void reverseArray(vector<char> &arr)
{
    for (int counter = 0; counter < (arr.size() / 2); counter ++)
    {
        swap(arr[counter], arr[arr.size() - counter - 1]);
    }
    return;
}
void arrayOfNumbers(vector<char> &nums, long long number)
{
    nums.clear();
    while (number > 0)
    {
        nums.push_back(number % 10);
        number /= 10;
    }
    reverseArray(nums);
    return;
}
void makePalindrom(vector<char> &arr)
{
    for (char counter = 0; counter < (arr.size() / 2); counter ++)
    {
        arr[arr.size() - counter - 1] = arr[counter];
    }
    return;
}
void numberFromArray(vector<char> nums, long long &number)
{
    number = 0;
    for (char counter = 0; counter < nums.size(); counter ++)
    {
        number = number * 10 + nums[counter];
    }
    return;
}
