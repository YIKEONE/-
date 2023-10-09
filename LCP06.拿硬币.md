#### [LCP 06. 拿硬币](https://leetcode.cn/problems/na-ying-bi/)

桌上有 `n` 堆力扣币，每堆的数量保存在数组 `coins` 中。我们每次可以选择任意一堆，拿走其中的一枚或者两枚，求拿完所有力扣币的最少次数。

~~~c++
//一个点:对于这道题无论对于偶数还是奇数,++后>>1,和直接>>1是一样的,因为如果硬币数是奇数,一次最多拿两个,最后剩余的一个,还是会浪费一次拿的次数
class Solution {
public:
    int minCount(vector<int>& coins) {
        int ans = 0;
        for (auto coin : coins) 
            ans += (coin + 1) >> 1;
        return ans;
    }
};
~~~

