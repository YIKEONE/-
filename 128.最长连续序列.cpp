#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
/*  QUESTION:
    给定一个未排序的整数数组 nums
   ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
    请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/
/*  思路:
    1. 首先使用哈希表把nums元素都装进去, 1.去重, 2. 查找元素是O(1)
    2. 遍历哈希表k,如果k-1元素存在,说明他有连续项,就跳过
    3. 如果k-1元素不存在的话, 就说明他是作为一个子序列起点位置,开始一次遍历k++,直到k++不存在时
    4. 求出子序列的长度, max比较一下算出最大子连续序列长度
*/
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> hashtable;
        int ans = 1;
        for (auto x : nums) hashtable.emplace(x);
        for (auto k : hashtable) {
            //前一个元素存在,说明就不是子序列的头,跳过
            if (hashtable.count(k - 1)) continue;
            //不存在,为子序列的后,开始遍历他的每后一项,cnt++
            //当没有后一项的时候,也就说明该子序列走到头了,cnt与ans更新最大值
            int cnt = 1;
            while (hashtable.count(++k)) cnt++;
            ans = max(cnt, ans);
        }
        return ans;
    }
};