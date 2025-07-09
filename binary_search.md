# 二分

## 二分查找

#### 二分查找的两种写法

```cpp
// 左闭右开
//更适合找边界、插入位置等复杂问题
int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();// !!
        while (left < right) {// !!
            int mid = left + ((right - left) >> 1);// >>运算的优先级低于+
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;// !!
            else
                right = mid;// !!
        }
        return left;
    }
```



```cpp
// 闭区间
//更适合标准查找、简单理解
int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;// !!
        while (left <= right) {// !!
            int mid = left + ((right - left) >> 1);
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;// !!
            else
                right = mid - 1;// !!
        }
        return left;
    }
```

