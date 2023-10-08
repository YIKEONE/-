# 算法

#### 求数组最小次数

桌上有 `n` 堆力扣币，每堆的数量保存在数组 `coins` 中。我们每次可以选择任意一堆，拿走其中的一枚或者两枚，求拿完所有力扣币的最少次数。

~~~c++
//思路:因为求拿最少的次数且拿的方式只有1个和2个,肯定是一次拿2个是最少的次数。所以当一堆是偶数就+1再除2结果还是本身/2,而奇数+1 /2。
class Solution {
public:

    int minCount(vector<int>& coins) {
        int cnt = 0;
        for(auto& i : coins)
        {
            cnt += (i + 1) / 2;
        }
        return cnt;
    }
};
~~~

#### [1. 两数之和](https://leetcode.cn/problems/two-sum/)

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`* 的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

~~~c++
//思路:创建哈希表hm,key是num的val,value是索引。遍历数组,只要是hm[targe - num[i]],targe - num[i]这个val值在hm中,就可以返回hm的value值(下标),没有的话就加入到hm中
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int ,int> hm;
        for(int i = 0; i < nums.size(); i++)
        {
          if(hm.find(target - nums[i]) != hm.end())
            return {hm[target - nums[i]], i};
          hm[nums[i]] = i;
        }
        return {};
    }
};
~~~

#### [2. 两数相加](https://leetcode.cn/problems/add-two-numbers/)

![1695258936165](D:\桌面\算法\1695258936165.jpg)

~~~c++
//思路:两个链表相加(0 <= x <= 9),有int carry,他是0 1。当和sum >= 0,carry = 1，->val = sum % 10。9 % 10 = 9,当l1、l2存在,n1、n2就是l1->val,不存在就是0。且若l1、l2存在,在操作后,就后移。
//怎么添加节点? 初始head、tail = nullptr。若!head,也就是没有头,就head = tail,都指向第一个节点,若存在了,tail添加节点,再tail后移。
//当l1、l2都添加后,看carry,若carry>0,就在添加一个节点
class Solution {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
    ListNode *head = nullptr, *tail = nullptr;
    int carry = 0;
    while(l1 || l2)
    {
      int n1 = l1 ? l1->val : 0;
      int n2 = l2 ? l2->val : 0;
      int sum = n1 + n2 + carry;
      if(!head)
        head = tail = new ListNode(sum % 10);
      else 
      {
        tail->next = new ListNode(sum % 10);
        tail = tail->next;
      }
      carry = sum / 10;
      if(l1) l1 = l1->next;
      if(l2) l2 = l2->next;
    }
    if(carry > 0)
      tail->next = new ListNode(carry);
    return head;
  }
};
~~~

~~~c++
//使用递归
//边界条件就是l1和l2都到了最后nullptr,int carry为总和。
//以l1或者l2为要操作的链条(l1),
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry = 0)
    {	//base case,当l1、l2都为null时,就结束了
        if(l1 == nullptr && l2 == nullptr)
            return carry > 0 ? new ListNode(carry) : nullptr;
        if(l1 == nullptr)//确保l1比l2长
            swap(l1, l2);
        carry += l1->val + (l2 ? l1->val : 0); 
        l1->val = carry % 10;
        l1->next = addTwoNumbers(l1->next, l2 ? l2->next : nullptr, carry / 10);
        return l1;
  	}
};
~~~

#### [2591. 将钱分给最多的儿童](https://leetcode.cn/problems/distribute-money-to-maximum-children/)

![1695385062331](D:\桌面\算法\1695385062331.jpg)

~~~c++
//思路:就是满足条件,children个小孩,最低要求children元,而算出(money - children) / 7,是拿八元的最大人数。
class Solution {
public:
    int distMoney(int money, int children) {
        if(money < children)
            return -1;
        //算出最大人数,如果100元2人分,那res>children,就出错了,所以min取最小值
        int res = min(children, (money - children) / 7);
        //剩余的人、钱(刨除每人1元和拿8元的人)
        money -= (children + 7 * res);
        children -= res;
        //特殊情况:1.当剩余人为0,且还有剩钱的情况(人:0, 钱:20)
        //2.剩余钱为3且剩余人为1时,一定 res-1(人:1, 钱:3)
        if((children == 0 && money > 0) || (children == 1 && money == 3))
            res--;
        return res;
    }
};
~~~

#### [1031. 两个非重叠子数组的最大和](https://leetcode.cn/problems/maximum-sum-of-two-non-overlapping-subarrays/)

给你一个整数数组 `nums` 和两个整数 `firstLen` 和 `secondLen`，请你找出并返回两个非重叠 **子数组** 中元素的最大和*，*长度分别为 `firstLen` 和 `secondLen` 。长度为 `firstLen` 的子数组可以出现在长为 `secondLen` 的子数组之前或之后，但二者必须是不重叠的。子数组是数组的一个 **连续** 部分。

![1695395155055](D:\桌面\算法\1695395155055.jpg)

~~~c++
//思路:求子数组和v[i, j],就使用前缀合sum[i, j],sum[j]-sum[i]就是子数组的和,子数组的元素和转换成两个前缀和的差
//再使用滑动窗口,假设A在左,B在右。一直滑动A,B,用max保存A,B滑动时合的最大值,A,B反过来在求一遍(B在左,A在右)。
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size(), sum[n + 1];
        sum[0] = 0;
        partial_sum(nums.begin(), nums.end(), sum + 1); //求前缀合
        int ans = 0, maxSumL = 0, maxSumR = 0;
        for(int i = firstLen + secondLen; i <= n; ++i){
            maxSumL = max(maxSumL, sum[i - secondLen] - sum[i - secondLen - firstLen]);
            maxSumR = max(maxSumR, sum[i - firstLen] - sum[i - firstLen - secondLen]);
            ans = max(ans, max(maxSumL + sum[i] - sum[i - secondLen], //firstLen在左
                               maxSumR + sum[i] - sum[i - firstLen]));//firstLen在右
        }
        return ans;
    }
};
~~~

#### 206.反转链表

![1695432640731](D:\桌面\算法\1695432640731.png)

~~~C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = nullptr, *next = nullptr;
        while(head){
            next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        return pre;
    }
};
//递归
使用递归函数，一直递归到链表的最后一个结点，该结点就是反转后的头结点，记作 retret .
此后，每次函数在返回的过程中，让当前结点的下一个结点的 next 指针指向当前节点。
同时让当前结点的 next 指针指向NULL ，从而实现从链表尾部开始的局部反转
当递归函数全部出栈后，链表反转完成。

ListNode* reverseList(ListNode* head){
    if(head == nullptr || head->next ==nullptr){
        return head;
    }
    //要的是递归遍历所有节点,而且是从后往前开始遍历,
    ListNode* ret = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return ret;
}
~~~

#### [234. 回文链表](https://leetcode.cn/problems/palindrome-linked-list/)

~~~c++
//1.把链表先放出数组中,再用两个指针头尾,判断
//2.使用快慢指针,把右区链表反转,再比较,再反转回来
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return true;
        vector<int> v;
        while(head){
            v.push_back(head->val);
            head = head->next;
        }
        for(int i = 0, j = v.size() - 1; i < j; ++i, --j){
            if(v[i] != v[j])
                return false;
        }
        return true;
    }
};
~~~

#### [147. 对链表进行插入排序](https://leetcode.cn/problems/insertion-sort-list/)

~~~c++
//插入排序的思路:先是第一个节点有序,对比值,满足条件就把第二个点插入,一次类推,保证0~n有序,把第n+1节点插入进去
//对于链表的插入排序,lastSorted就是前i有序的最后一个节点i,cur就是要操作的节点在,lastSorted的后面
//dummyHead指向头节点,保证插入在头节点,依旧可以返回,
//pre就是要插入位置的前一个节点,默认值是dummyHead->next也就是头节点,因为有序了,循环找到cur->val > pre->next->val。就是遍历链表。
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *lastSorted = head, *cur = head->next;
        while(cur != nullptr){
            //小到大排序,如果操作的值大于已排好的序前i,那就直接有序
            if(cur->val >= lastSorted->val){
                lastSorted = lastSorted->next;//后移
            }else{
                //cur点就是要插入到前i有序的链表中
                ListNode *pre = dummyHead;
                while(pre->next->val <= cur->val){
                    pre = pre->next;//找到要插入的位置
                }
                //把cur点插入对应的位置
                lastSorted->next = cur->next;
                cur->next = pre->next;
                pre->next = cur;
                //插完后,lastSorted的最后一个节点还是那个,只是长度+1
            }
            cur = lastSorted->next;
        }
        return dummyHead->next;   
    }
};
//数组插入排序
void test(vector<int>& v){
    int len = v.size();
    for(int i = 1; i < len; i++){//要插入的点
        for(int j = i - 1; j >= 0 && v[j + 1] < v[j]; j--){
            //如果操作的i值,大于等于j值,就直接跳过循环,进入一个i
            //若不是的话
           | j - 1 = i - 2 | j = i -1 | i | 
            //i和j交换,
            //交换后,j就后移了,比较 j和j-1,若交换了
            //再比较j-1和j-2, 以此类推
            swap(v[j], v[j - 1]);
            //类似冒泡,
        }
    }
}
~~~

#### [21. 合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/)

![1695566751682](D:\桌面\算法\1695566751682.jpg)

~~~c++
//思路:使用一个指针pre来贯穿这两个链表,preHead就是pre贯穿后的头节点
//pre = preHead; 遍历两个链表,判断值,值小的话,就使用pre开始穿线,pre->next=*samll; small的指针都后移
//最后有可能有一个链表为空,当一个为空的时候,把pre->next穿不空的链表
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *preHead = new ListNode(-1);
        ListNode *pre = preHead;
		//pre是用于操作的节点
        while(list1 != nullptr && list2 != nullptr){
            //修改pre->next指针,指向值小的节点(穿节点)
            if(list1->val < list2->val){
                pre->next = list1;
                list1 = list1->next;
            }else{
                pre->next = list2;
                list2 = list2->next;
            }
            pre = pre->next;//后移
        }
        pre->next = list1 == nullptr ? list2 : list1;
        return preHead->next;
    }
};
//使用递归
//相当于自己穿线,
//而递归返回的值就是小的值
//因为是自穿,一定要有穿线的动作,也就是要有->next的操作
ListNode* merge(ListNode* l1, ListNode* l2){
    if(l1 == nullptr){
        return l2;
    }else(l2 == nullptr){
        return l1;
    }else if(l1->val < l2->val){
        l1->next = merge(l1->next, l2);
        return l1;
    }else{
        l2->next = merge(l1, l2->next);
        return l2;
    }
    //递归,递归的操作=basecase;依次从后往前获得答案,最后面也就是base
};
~~~

#### [88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)

给你两个按 **非递减顺序** 排列的整数数组 `nums1` 和 `nums2`，另有两个整数 `m` 和 `n` ，分别表示 `nums1` 和 `nums2` 中的元素数目。

请你 **合并** `nums2` 到 `nums1` 中，使合并后的数组同样按 **非递减顺序** 排列。

**注意：**最终，合并后数组不应由函数返回，而是存储在数组 `nums1` 中。为了应对这种情况，`nums1` 的初始长度为 `m + n`，其中前 `m` 个元素表示应合并的元素，后 `n` 个元素为 `0` ，应忽略。`nums2` 的长度为 `n` 。

~~~c++
//1.两个数组融合在一起,再排序
//2.p1,p2双指针,使用一个tmp数组,小的入组,当某一个指针空了,把另外一个指针的元素入组
//3.逆序双指针,因为num1的长度m+n,后n个元素空,所以可以p1,p2双指针,指针指的是数组的后边,谁大谁入num1[tail],这样无需使用额外空间。
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1, p2 = n - 1, tail = m + n - 1;
        int cur = 0;
        while(p1 != -1 || p2 != -1){
            if(p1 == -1){
                cur = nums2[p2--];
            }else if(p2 == -1){
                cur = nums1[p1--];
            }else if(nums1[p1] <= nums2[p2]){
                cur = nums2[p2--];
            }else{
                cur = nums1[p1--];
            }
            nums1[tail--] = cur;
        }
    }
};
~~~

#### [27. 移除元素](https://leetcode.cn/problems/remove-element/)

![1695631113008](D:\桌面\算法\1695631113008.png)

给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 `O(1)` 额外空间并 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组**。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

~~~c++
//1.有点类似快慢指针,快指针就是遍历数组中的每一个元素, 慢指针就是不是val值的指针
//如果不是val的话,idx位置就写入快指针指向的值,如果是的话,idx就不变
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        for(auto x : nums)
            if(x != val) nums[idx++] = x;
        return idx;
    }
};
~~~

~~~c++
//2.把数组分为两份,作部分都不是val的值,右部分都是val值
//两个指针分别指向头尾,头指针遍历数组,如果头指针是val,交换头尾指针,尾指针前移,头指针前移,下一个循环判断与尾节点交换值是否为val。
int l = 0, r = nums.size() - 1;
for(; l <= r; l++){
    if(nums[l] == val){
        nums[l--] = nums[r--];//回到上一个位置,判断上一次和尾部交换的值
    }
}
return r + 1;
~~~

#### [26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)

![1695632370024](D:\桌面\算法\1695632370024.jpg)

~~~c++
//使用双指针,slow,fast,
//fast就是遍历数组,默认位置就是1
//slow是不是重复值的最后一个元素的下标,默认值0
//如果fast!=slow,也就不是重复值,slow的下一个位置赋值
//因为返回是个数,也就是slow+1
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, fast = 1;
        for(; fast < nums.size(); fast++) {
            if(nums[fast] != nums[slow]){
                nums[++slow] = nums[fast];
            }
        }
        return slow + 1;
    }
};
~~~

#### [80. 删除有序数组中的重复项 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/)

给你一个有序数组 `nums` ，请你**[ 原地](http://baike.baidu.com/item/原地算法)** 删除重复出现的元素，使得出现次数超过两次的元素**只出现两次** ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组** 并在使用 O(1) 额外空间的条件下完成。

~~~c++
只删除超过三位的元素(保留两位)。
//思路:
//所以要点就是如何判断相同元素超过两次
//使用双指针,指slow、fast指针开始的位置就是数组第三位,小于就可以直接返回
//slow就是要添加元素的位置,fast是遍历数组所有元素,
//数组是有序的,就是看fast是否和slow-2的位置是否相同(slow - 2, slow - 1, slow,三个元素,),如果fast和slow - 2 相同,也就是和slow - 1也相同,所以不添加,fast后移
//不同的话就是直接添加,slow后移,fast后移
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if(len < 3){
            return len;
        }
        int slow = 2, fast = 2;
        while(fast < len){
            if(nums[slow - 2] != nums[fast]) {
                //只有不超过三个相同元素,才添加,超过就不添加
                nums[slow++] = nums[fast];
            }
            ++fast;
        }
        return slow;
    }
};
//所以如果删除超过三位元素的多余元素时,也是同思路
//slow表示符合要求,添加元素的位置,fast表示遍历数组的指针
//判断slow - 3 和 fast(正在遍历的点)
//相等的话,也就是slow-3,slow-2,slow-1,这三个点也是和fast点相等,此时就不把fast赋值给slow,也就是slow保持不动,而是fast直接后移
//不相等的话,对于最坏的情况也是slow-2,slow-1相等,此时也才只有两个元素相等,所以fast赋值给slow,
~~~

#### [169. 多数元素](https://leetcode.cn/problems/majority-element/)

给定一个大小为 `n` 的数组 `nums` ，返回其中的多数元素。多数元素是指在数组中出现次数 **大于** `⌊ n/2 ⌋` 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

~~~c++
//哈希法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> hm;//<element, cnt>
        int majority = 0, cnt = 0;
        for(int num : nums){
            ++hm[num];
            //谁比cnt大谁当majority
            if(hm[num] > cnt){
                majority = num;
                cnt = hm[majority];
            }
        }
        return majority;
    }
};
//2.排序,因为是超过一半的数,所以排序后的数组的中位数一定是出现元素最多次的
~~~

![1695730417012](D:\桌面\算法\1695730417012.jpg)

![1695730462458](D:\桌面\算法\1695730462458.jpg)

~~~c++
//摩尔投票
//有两个特点:1.如果是众数,投票结果一定是>0
//2.如果前面和为0,就可以约掉,那么众数还会出现在剩下的元素里,且votes>0
//先假设第一个元素为maj,遇到相同+1,不同-1,votes为0了,就把下一个元素当maj,依次类推。最后的maj就是众数
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majority = 0, votes = 0;
        for(int num : nums){
            if(votes == 0)//为0了,就把下一个元素假设为majority
                majority = num;
            //判断, 相同+1, 不同-1
            votes += num == majority ? 1 : -1;
        }
        return majority;
    }
};
~~~

#### [189. 轮转数组](https://leetcode.cn/problems/rotate-array/)

![1695738479352](D:\桌面\算法\1695738479352.jpg)

~~~c++
//使用额外空间
//因为右转k个位置,也就是每个元素都向右移动k个位置,所以第i位置移动到的位置是i+k,要考虑到过界,所以是(i+k) % n,i位置+k后,若是超过n了,就mod一下,就循环了
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        vector<int> tmp(len);
        //nums每一个元素都移动k位置到tmp中,移动到tmp(i+k)%n上
        for(int i = 0; i < len; i++){
            tmp[(i + k) % len] = nums[i];
        }
        //把tmp赋值给nums
        nums.assign(tmp.begin(), tmp.end());
        //nums.swap(tmp);,交换容器也行
    }
};
~~~

![1695739786486](D:\桌面\算法\1695739786486.jpg)

~~~c++
//环状替换,不需要使用额外空间
//因为nums所有元素都要移动到(i+k)%n位置上
//所以可以用从第一个元素开始,把(i+k)%n记录,pos=(i+k)%n应该移动到(pos+k)%n,再记录下来,再把这个位置移动到下一个位置,依次类推,直到回到最初开始的位置
//但是这个过程中,有可能不会遍历所有元素,目的是遍历所有元素修改
//这样再从第二个元素开始,重复上述过程

//但是重复多少次呢？
//因为回到原来元素,所以一定是整数圈an,在这次过程中,假设经历的元素为b,an=bk。
//因为是第一次回到原来元素,所以a一定要小,也就是an一定是n,k的最小公倍数,lcm(n,k) = bk,b=lcm(n,k)/k, b是经历的元素,
//所以要经历的次数len/b = nk/lcm(n,k),为nk的最大公约数gcd(n,k)

void rotate(vector<int>& nums, int k) {
    int count = gcd(n, k);
    for(int start = 0; start < count; ++start) {
        int cur = start;//index
        int cur_data = nums[start];
        do {
            int next = (cur + k) % n;//index
            swap(cur_data, nums[next]);//交换
            cur = next;//交换后,操作的元素就后移
        }while(cur != start);
    }
}
//不使用最大公约数,可以使用cnt,交换一次就cnt++,cnt<=n
~~~

#### [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)

~~~c++
//思路:
//如果在第i天买入,在之后卖出
//只有在i天之后的价值比i的价值低,才有可能出现,差值最大的情况

//案例:1.如果在i天买入,之后价格都比i高,那么i不就是最低点么,所以在i天之后无论哪一天买入max都不会比在i天买入大
//2.所以只有i天之后有买入price小于第i天时,才有可能出现maxprofit的情况,是有可能。所以就计算以那天(比i买入价格低)买入,计算以哪天买入之后的差值,如果比前的maxprofit大。就是以这天买入合适,没有比maxprofit大,就在i天买入合适

//然而，暴力法会产生许多冗余计算。例如，若第 1 天价格低于第 2 天价格，即第 1 天成本更低，那么我们一定不会选择在第 2 天买入。进一步的，若在前 i 天选择买入，若想达到最高利润，则一定选择价格最低的交易日买入。考虑根据此贪心思想，遍历价格列表 prices 并执行两步：

//遍历一遍数组，计算每次 到当天为止 的最小股票价格和最大利润。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxprofit = 0;
        int minprice = int(1e9);
        for(int price : prices){
            maxprofit = max(maxprofit, price - minprice);
            minprice = min(minprice, price);
        }
        return maxprofit;
    }
};
~~~

[122. 买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)

~~~c++
//我的思路:同一天可以买卖,所以只要是计算两个差值大于0即可,这种方法只做两天的股票买卖,第一天买,第二天卖。
//prices[i] > prices[i -1]满足这个条件,prices[i]就买入,prices[i - 1]就卖出
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(prices.empty()|| n <= 1) return 0;

        int maxprofit = 0;
        for(int i = 1; i < n; i++) {
            maxprofit += max(0, prices[i] - prices[i -1]);
        }
        return maxprofit;
    }
};
~~~

[55. 跳跃游戏](https://leetcode.cn/problems/jump-game/)

给你一个非负整数数组 `nums` ，你最初位于数组的 **第一个下标** 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 `true` ；否则，返回 `false` 。

~~~C++
//最重要的思路就是贪心算法,
我们依次遍历数组中的每一个位置，并实时维护 最远可以到达的位置rightmost。对于当前遍历到的位置 x，如果它在 rightmost 的范围内，那么我们就可以从起点通过若干次跳跃到达该位置，因此我们可以用 x+nums[x] 更新 rightmost。

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int rightmost = 0;//表示能达到的最远位置下标

        for(int i = 0; i < n; i++) {
            //遍历的点必须得能达到最远点的范围内,若超过了,没有点跳到那里,那么肯定也跳不到边界,直接返回false即可
            if(i <= rightmost) {
                rightmost = max(nums[i] + i, rightmost); 
                if(rightmost >= n - 1) {
                    return true;
                }
            }else {
                return false;
            }
        } 
        return false;
    }
};
~~~

[45. 跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/)

![1695799030011](D:\桌面\算法\1695799030011.jpg)

~~~c++
//问最少跳几次？
//start, end初始值0,先看第一个点最远能跳到哪里
//如果第一个元素是2,那么第一个元素可以跳到下标1和跳到下标2两种选择
//分别求下标1和下标2的最远元素,求最值maxPos,start=1, end=2
//如果这个时候end还在下标n - 1以内,说明最远举例还是走不到终点,需要再走
class Solution {
public:
    int jump(vector<int>& nums) {
        
        int n = nums.size();
        int cnt = 0;
        int start = 0, end = 0;

        while(end < n - 1) {
            int maxPos = 0;
            for(int i = start; i <= end; i++) {
                maxPos = max(nums[i] + i, maxPos);
            }
            //下一步的范围
            start = end + 1;
            end = maxPos;
            cnt++;
        }
        return cnt;
    }
};
//看每一步最远能到哪里,如果这步超过了边界,不就可以了么
//第一步,如果第一步可以跳5步,这是有5种选择,跳到第1个...跳到第5个。
//如果跳完第一步,还没有跳到边界,就继续跳
//第一步没有跳到位,那么第二步就得从这5个点选择一个开始跳,这个点怎么选择呢？
//遍历每个可以选择的点,求这个5个点哪个点跳的远,以此类推
~~~

#### [274. H 指数](https://leetcode.cn/problems/h-index/)

一名科研人员的 `h` **指数** 是指他（她）至少发表了 `h` 篇论文，并且每篇论文 **至少** 被引用 `h` 次。如果 `h` 有多种可能的值，**`h` 指数** 是其中最大的那个。

~~~c++
//1. 从大到小遍历数组,h的默认值是0,如果[i] > h, h++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        //大到小排序
        sort(citations.begin(), citations.end(), greater<int>());
        int h = 0;
        for(auto x : citations) {
            h += x > h ? 1 : 0;
        }
        return h;
    }
};
//为什么要从大到小遍历呢？
//如果i后面的都满足h的标准了([i] > h),那么i之前也一定满足

//h表示的就是论文个数,x表示引用个数,
//大到小遍历,x引用个数要>=h论文个数,
//但是在这种情况不能=,因为x=h,后h++,就会x<h,引用少于论文个数,不符合情况
~~~

~~~c++
//计数排序
//因为上面的时间复杂度和排序算法的时间复杂度有关,选一个低的排序算法
//思路:使用counter[n + 1]数组,下标表示这发的论文数,值表示引用数,遍历原数组,值大于长度的在counter的下标n的值+1,在范围内的,就在counter[citations[i]]++,是引用多少就在对应下标里面的值+1
//最后从后遍历counter数组,int tol,当tol引用数>=论文数时,return,因为返回的是最大值
//tol呢,因为引用数大的论文也给可以充当引用数小的论文,所以tol是+=counter[i], i1=n。
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> counter(n + 1);
        //计数排序
        for(int i = 0; i < n; i++) {
            if(citations[i] >= n) {
                counter[n] += 1;
            }else {
                counter[citations[i]] += 1;
            }
        }
        int tol = 0;
        for(int i = n; i >= 0; i--){
            tol += counter[i];
            if(tol >= i) {
                return i;
            }
        }
        return 0;
    }
};
~~~

#### [238. 除自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/)

![1695885597203](D:\桌面\算法\1695885597203.jpg)

前缀积

![1695885526570](D:\桌面\算法\1695885526570.jpg)

后缀积

![image-20230928151924535](C:\Users\YK\AppData\Roaming\Typora\typora-user-images\image-20230928151924535.png)

~~~c++
//思路:
//需要求一个数组,除i之外剩下元素的乘积
// = 这个数左边所有数乘积 * 右边所有数乘积
//所以运用到的技巧就类似前缀和,前缀积,表示ans[i]表示i之前的乘积
//还因为是左右边的乘积,再引入一个后缀积sufMul
//所以ans[i] = preMul[i] * sufMul[i];
//用到的是双指针,preMul[0] = 1, sufMul[n - 1] = 1;
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int preMul = 1, sufMul = 1;//前缀和后缀积
        vector<int> ans(n, 1);//默认值1
        for(int i = 0, j = n - 1; i < n; i++, j--) {
            //如果算单向的话,其实等于可以,因为算的是两个方向,所以是 *=。当i=1,算完后,等到j=1,再算一次
            ans[i] *= preMul;
            ans[j] *= sufMul;

            preMul *= nums[i];
            sufMul *= nums[j];
        }
        return ans;
    }
};
~~~

#### [605. 种花问题](https://leetcode.cn/problems/can-place-flowers/)

假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给你一个整数数组 `flowerbed` 表示花坛，由若干 `0` 和 `1` 组成，其中 `0` 表示没种植花，`1` 表示种植了花。另有一个数 `n` ，能否在不打破种植规则的情况下种入 `n` 朵花？能则返回 `true` ，不能则返回 `false` 。

~~~c++
//思路:跳格子,看位置是否可以种花
//规则就是[i] = 1, 那么左右都为0,
//如果[i] = 1,说明这个位置不能种花,就直接跳2个位置,(这个位置下一个必定为0)
//如果[i] = 0,因为规则存在,这个位置前一个位置一定为0,所以就判断下一个位置如果是0就可以种花,所以n--,这个位置就变为1了,再跳2格,如果恰巧走到了最后一个位置,就一定可以种花
//如果下一个位置是1,说明这个位置不能种花,跳到这个为1的位置
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size();
        int i = 0;
        while(i < len && n > 0) {
            if(flowerbed[i] == 1) {//为1,不能种花,跳2个格子,
                i += 2;
            //为0,有可能可以种花,两个情况,
            //恰巧走到最后一个位置,可以种。下一位置0,可以种
            }else if(i == len - 1 || flowerbed[i + 1] == 0) {//同样表示了flowerbed[i]不等于1
                //跳到这个位置,判断可以种花,种花[i]=1,变为1了就跳两格
                n--;
                i += 2;
            }else {//下一个位置(i+1)不是最后一个位置,并且为1,不能种,从1的位置跳两个,
                //下一个位置为1,再跳两格,i += 3, 一共跳三格
                i += 3;
            }
        }
        //最后一次循环n == 1,进入下一个循环,则n==0,表示可以种,若提前结束循环,表示n > 0,表示不能种
        return n == 0;
    }
};
//无论是跳到哪里(跳的位置就是表示可以种花的位置),这个位置的前一个位置一定为0。
~~~

~~~c++
//还有就是三个指针,同时指向当前位置,前一个位置,后一个位置都为0,就是表示可以种花
//当这个位置是第一个位置就不用判断前一个位置, 这个位置是最后一个位置,就不用判断最后一个位置
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size();
        for(int i = 0; i < len; ++i) {
            //自身,前一个,后移位置都为0,才可以种
            if((i == 0 || flowerbed[i - 1] == 0) && flowerbed[i] == 0 && 
                                                    (flowerbed[i + 1] == 0 || i == len - 1)) {
                //可以种花,那么下一个位置一定不能种花                                        
                n--;
                i++;                                         
            }
        }
        return n == 0;
    }
};
//判断前一个位置(i == 0 || flowerbed[i - 1] == 0),前一个位置为0,或者当前位置是第一个位置就不用判断前一个位置
//判断后一个位置(flowerbed[i + 1] == 0 || i == len - 1)),后一个位置为0,或者当前位置是最后一个位置就不用判断后一个位置
~~~

#### [134. 加油站](https://leetcode.cn/problems/gas-station/)

![1695981198312](D:\桌面\算法\1695981198312.png)

~~~c++
//思路:index遍历数组index表示开始出发的位置
//最开始pos == index,pos表示着到的位置(到哪里了),计数器cnt = 0,求total = gas[pos] - cost[pos],若total < 0,就表示着从这里出发不行,index后移,
//total >= 0,表示着从index出发,到pos这个位置,还有油可以继续往下走,pos后移,index保持不变,pos每走一步cnt+++
//当pos走到了total < 0的位置, 没有油了,如果想走完一圈,必须得从后面的位置获取多余的汽油,所以index应该更新到pos后面的位置,代码用的更新位置是通过cnt计数器,pos走了一步就++,index = inedx + cnt,的后一步,index = index + cnt +1;
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int pos = 0, index = 0, total = 0, cnt = 0;
        while(index < n) {
            //pos的初始位置是index
            total += gas[pos] - cost[pos];
            //如果<0,就表示着从index出发不行,表示着从0 ~ pos,汽油差为负,如果想走完,一定是从后面开始出发,
            //先从后面的第一个开始尝试
            if(total < 0) {
                total = 0;
                index = index + cnt + 1;//更新index,到pos的后面
                cnt = 0;//表示这pos离index的距离
                pos = index;
            }else {//表示这pos这个位置可以走,
                cnt++;//离距离index的位置
                pos = (pos + 1) % n;
            }
            if(cnt == n) {//若移动的距离等于n就表示
                return index;
            }
        }
        return -1;
    }
};
~~~

[125. 验证回文串](https://leetcode.cn/problems/valid-palindrome/)

~~~c++
//思路就是通过 std::isalnum(ch),判断是否为数字和字母,是的话再把字母改成小写tolower(ch)
//得到的字符串数组tmp,反转数组,string tmp_rev(tmp.rbegin(), tmp.rend());
class Solution {
public:
    bool isPalindrome(string s) {
        string tmp;
        for(auto ch : s) {
            if(isalnum(ch)) //判断是否为字母和数字
                tmp += tolower(ch);//添加
        }
        string tmp_res(tmp.rbegin(), tmp.rend());

        return tmp_res == tmp;
    }
};
~~~

#### [135. 分发糖果](https://leetcode.cn/problems/candy/)

`n` 个孩子站成一排。给你一个整数数组 `ratings` 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

- 每个孩子至少分配到 `1` 个糖果。
- 相邻两个孩子评分更高的孩子会获得更多的糖果。

请你给每个孩子分发糖果，计算并返回需要准备的 **最少糖果数目** 。

~~~c++
//思路:相邻孩子,评分高的必须获得多的糖果,可以拆分成左右两个规则
//左规则: ratings[i] > ratings[i-1],那么i的糖果,必须比i-1的糖果多
//右规则: ratings[i] > ratings[i+1],那么i的糖果,必须比i+1的糖果多
//所有遍历两次,从头开始执行左规则,从尾开始执行右规则
//但是在执行右规则的时候,当[i] > [i + 1]时,i的糖果比i+1的糖果多,max([i], [i + 1] + 1);+
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> candys(n);
        if( n == 1) {
            return 1;
        }
        //比较i 和 i - 1
        for(int i = 0; i < n; i++) {
            if(i > 0 && ratings[i] > ratings[i - 1]) {
                candys[i] = candys[i - 1] + 1;
            } else {
                candys[i] = 1;
            }
        }
        //比较i 和 i + 1
        for(int i = n - 1; i >= 0; i--) {
            if(i < n - 1 && ratings[i] > ratings[i + 1]) 
                candys[i] = max(candys[i + 1] + 1, candys[i]);
        }
        int res;
        for(auto x : candys) {
            res += x;
        }
        return res;
    }
};
~~~

#### [167. 两数之和 II - 输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/)

~~~c++
//思路:因为是有序数组,这一个条件一定是帮助减少时间复杂度的,就考虑这个条件有什么特点
//特点就是头的最小的,尾是最大的,
//设置双指针,一个指向头,一个指向尾,
//若sum>target,数大了,如果p1前移就会越来越大,那么一定是p2后移,使得p2变小,总体变小去逼近target
//同理sum<target,数小了,若p2后移,数就会越来越小,要逼近target就得使p1前移
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        //可以使用哈希, 但是空间是O(n)
        
        //双指针
        int p1 = 0, p2 = numbers.size() - 1;
        vector<int> ret(2);
        while(p1 < p2) {
            int sum = numbers[p1] + numbers[p2];
            if(sum > target) {
                --p2;
            }else if(sum < target) {
                ++p1;
            }else {
                return vector<int> {p1 + 1, p2 + 1};
            }
        }
        return vector<int> {-1, -1};
    }
};
~~~

~~~c++
//因为是有序数组,可以使用二分查找
//二分查找是找一个数,问题要找两个数,所以就固定一个数,去找另外一个数,i从0开始遍历,找mid
for (int i = 0; i < numbers.size(); ++i) {
            int low = i + 1, high = numbers.size() - 1;
            while (low <= high) {
                int mid = (high - low) / 2 + low;
                if (numbers[mid] == target - numbers[i]) {
                    return {i + 1, mid + 1};
                } else if (numbers[mid] > target - numbers[i]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return {-1, -1};

~~~

#### [15. 三数之和](https://leetcode.cn/problems/3sum/)

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请

你返回所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。

~~~c++
//和两数之和是一类提醒,两数之和目标是target,而这个三数之和目标就是nums[i]
//先给nums数组排序sort(iterator, iterator, cmp);
//i遍历数组,到n - 2, 因为n-2位置给j,n-1的位置给k
//while(j < k), 双指针j = n + 1, k = n - 1,三个数之和sum,如果sum>0,就表示数字太大,需要右指针k左移数减小,反之如果sum<0表示数太小了,需要左指针j右移数增大
//如果sum==0,就表示复合要求就把ijk,push进去，同时j右移,k左移继续循环判断

//tips1:但是题目中要求不要有重复的三元组,例如nums{-1, -1 , 0 , 1},其中i=0时的三元组是{-1, 0, 1}，i=1的三元组也是这个,这样ans中就出现了重复的三元组,所以要判断上一个的num[i] 是否 等于现在的num[i],如果相同的话就直接跳过这个i
//tips2:在sum==0时,需要push,ijk,同时要需要左右指针移动,但是前一个nums[j-1]和现在的nums[j]相同的话,会出现重复的三元组,这样的j就不考虑,j后移,同理k,如果后一个nums[k+1]== nums[k],也会出现相同的三元组,也是不考虑,k直接前移
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            int x = nums [i];
            //去除重复的nums[i],tips1
            if (i && nums[i - 1] == x) continue;
            //优化1:数组有序,如果nums[i]加上最小的两个数都要>0,说明任意的三个数相加都>0,直接break掉
            if (x + nums[i + 1] + nums[i + 2] > 0) break;
            //优化2:当nums[i]加上最大的两个数都<0,说明nums[i]不符合要求,i需要后移,所以就continue掉
            if (x + nums[n - 1] + nums[n - 2] < 0) continue;
            int j = i + 1, k = n - 1;
            while (j < k) {
                int sum = x + nums[j] + nums[k];
                if (sum > 0) --k;
                else if (sum < 0) ++j;
                else {
                    ans.push_back({x, nums[j], nums[k]});
                    //因为此时的jk,符合要求,j,k需要同时移动,移动后考虑nums[j\k]和上一个的nums[j\k]是否相同,相同的就++j或--k,tips2
                    for (++j; j < k && nums[j] == nums[j - 1]; ++j);
                    for (--k; k > j && nums[k] == nums[k + 1]; --k);
                }
            }
        }
        return ans;
    }
};
~~~

