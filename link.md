# 链表

## 删除特定节点

```cpp
ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0, head);
        ListNode* cur = &dummy;
        while (cur->next) {//
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;//比条件可以多一个next
                delete tmp;
            } else
                cur = cur->next;
        }
        return dummy.next;
    }
```



## 两两交换相邻节点

​	在改变单链表时,**优先改变上游的指针**

```cpp
ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next)
            return head;

        ListNode dummy(0, head);
        ListNode* cur = &dummy;

        while (cur->next && cur->next->next) {
            ListNode* p1 = cur->next;
            ListNode* p2 = cur->next->next;
            cur->next = p2;//先改头->p2  cur-->p1-->p2-->other
            p1->next = p2->next;//在改p1->other
            p2->next = p1;//最后在p2->p1;
            cur = p1;
        }
        return dummy.next;
    }
```



## 合并有序链表

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // 创建一个哑节点作为新链表的起点
        ListNode dummy(0);
        ListNode* curr = &dummy;  // 当前指针用于构建新链表

        // 同时遍历两个链表
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;  // 移动当前指针
        }

        // 将剩余部分直接连接到新链表末尾
        curr->next = (l1 != nullptr) ? l1 : l2;

        // 返回合并后的头节点
        return dummy.next;
    }
};
```



## 环形链表

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        // 边界情况：空链表或只有一个节点且无环
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        // 初始化快慢指针
        ListNode *slow = head;
        ListNode *fast = head;

        // 快指针及其下一个节点都非空时继续循环
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;                  // 慢指针每次走一步
            fast = fast->next->next;            // 快指针每次走两步

            if (slow == fast) {
                // 快慢指针相遇，说明存在环
                return true;
            }
        }

        // 遍历结束未相遇，说明没有环
        return false;
    }
};
```



## 在有序链表中删除相同元素

​	在链表的循环中, 判断条件一般是所有指针中最前面的指针

```cpp
ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }
        ListNode* cur = head;
        while (cur->next){
            if (cur->val == cur->next->val){
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }else{
                cur = cur->next;
            }
        }
        return head;
    }
```

