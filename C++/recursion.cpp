#include <iostream>

#define length 13

int recursiveFunction(int* nums, int index, int count, bool matched) {
        std::cout << index << std::endl;
        if (index == length -1) return count;
        if (index <= length -2 && nums[index] == nums[index+1] && !matched) {
            count++;
            matched = true;
        } else if (nums[index] != nums[index+1])
            matched = false;
        return recursiveFunction(nums, index+1, count, matched);
}

int timeRequired(char[] request, int index) {
    
}


int main() {
        int nums[] = {1, 1, 1, 1, 3, 3, 5, 5, 4, 1, 1, 4, 4};
        int* numsPtr = nums;
        std::cout << recursiveFunction(numsPtr, 0, 0, false);

        return 0;
}