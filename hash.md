# Hash

## 两数之和

``` cpp
 vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); i++){
            auto it  = hashtable.find(target - nums[i]);//判断是否存在
            if (it != hashtable.end()){
                return {i, it->second};
            }
            hashtable[nums[i]] = i;// 添加元素,  这里的添加顺序不可提前,因为我想做的是先查找,如果先添加会影响这一次查找
        }
        return {};
    }
```

