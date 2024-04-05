#### [LCR 010. 和为 K 的子数组](https://leetcode.cn/problems/QTMn0o/)

![1712312078935](D:\桌面\leetcode算法题\算法配图\1712312078935.jpg)

~~~c++
//利用前缀和技巧
//使用哈希表来实现前缀和，k为前缀和，v表示该前缀和出现的频次
pre来记录前缀和，目标hash[pre - j] == k时，表明此时可以，pre的前缀和数组和j的前缀和数组之间的数组可以使内的和等于目标值
所以此时count,应该加上构成pre的前缀和的频次

说白了，就是利用hash中的k作为前缀和，v来记录次数，这样的好处就是，当出现 1 0 0 这种情况，在前缀合不变的情况下，子数组的可能性++

// num:    1 2 5 3 5
// index : 0 1 2 3 4
//           j   pre
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> hash; // k->sum, v->count
        hash[0] = 1;
        int count = 0, pre = 0;
        for (auto& num : nums) {
            pre += num;
            if (hash.count(pre - k)) {
                count += hash[pre - k];
            }
            hash[pre]++;
        }
        return count;
    }
};
~~~

