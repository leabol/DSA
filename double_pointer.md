# 双指针

## 快慢指针

#### 删除**有序**数组中的重复项
> 一个有序数组nums，原地删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度

```cpp
int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) {
            return n;
        }
        int slow = 2;
        for (int fast = 2; fast < n; ++fast){
            if (nums[fast] != nums[slow-2]){// fast 是读指针，不是写指针。我们无法知道前面已经写了多少个相同的值。只有 slow 才能记录我们已经保留了多少个相同的值。
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
```

#### 移除元素

> 在数组中,原地移除所有数值等于val的元素

```cpp
int removeElement(vector<int>& nums, int val) {
        int slow = 0;//可写入的下标
        int n = nums.size();
        for (int fast = 0; fast < n; fast++){
            if (nums[fast] != val){
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
```





## 相向指针

#### 移除元素
> 在数组中,原地移除所有数值等于val的元素, 相较于使用快慢指针的方法, 这种方法减少了元素的写入

```cpp
int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0){
            return 0;
        }
        int left = 0;//数组判断元素和可写入的下标
        int right = nums.size() - 1;//数组末尾的下标
        while (left <= right){
            if (nums[left] == val){
                nums[left] = nums[right--];
            }else{
                left++;
            }
        }

        return left;
    }
```

