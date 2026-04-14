#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int>nums = {2,1,3};
    vector<int>nums1 = {3,4,5};
    vector<int>nums3;
    
    for(int i = 0; i < nums.size();i++){
        nums3.push_back(nums[i]);
        
    }
    for(int i = 0; i < nums1.size();i++){
        nums3.push_back(nums1[i]);
    }
    int n = nums3.size();
    if(n % 2 != 0){
        cout << nums3[n / 2];
    }else {
        cout << (nums[n / 2-1] + nums[n/2]) / 2.0;
    }


    
    return 0;
}
