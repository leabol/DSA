#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/**
 * 堆的最核心算法实现
 * 只保留两个核心调整算法：上浮(heapifyUp)和下沉(heapifyDown)
 */
template<typename T, typename Compare = std::greater<T>>
class CoreHeap
{
private:
    vector<T> heap_;
    Compare comp_;

    // ============ 核心辅助函数：索引计算 ============
    size_t getParent(size_t index) const {
        return (index - 1) / 2;  // 父节点索引 = (当前索引-1)/2
    }
    
    size_t getLeftChild(size_t index) const {
        return 2 * index + 1;    // 左子节点索引 = 当前索引*2+1
    }
    
    size_t getRightChild(size_t index) const {
        return 2 * index + 2;    // 右子节点索引 = 当前索引*2+2
    }

    // ============ 核心算法1：上浮调整(用于插入) ============
    void heapifyUp(size_t index)
    {
        // 从指定位置向上调整，直到满足堆性质或到达根节点
        while (index > 0)  // 当前不是根节点
        {
            size_t parent = getParent(index);
            
            // 核心判断：当前节点是否比父节点优先级更高
            if (comp_(heap_[index], heap_[parent]))
            {
                swap(heap_[index], heap_[parent]); // 交换父子节点
                index = parent;                     // 向上移动到父节点位置
            }
            else
            {
                break; // 堆性质已满足，结束调整
            }
        }
    }

    // ============ 核心算法2：下沉调整(用于删除) ============
    void heapifyDown(size_t index)
    {
        size_t size = heap_.size();
        
        while (true)
        {
            size_t left = getLeftChild(index);
            size_t right = getRightChild(index);
            size_t target = index; // 记录三个节点中优先级最高的节点
            
            // 核心逻辑：在父节点和两个子节点中找到优先级最高的
            if (left < size && comp_(heap_[left], heap_[target]))
            {
                target = left;  // 左子节点优先级更高
            }
            if (right < size && comp_(heap_[right], heap_[target]))
            {
                target = right; // 右子节点优先级更高
            }
            
            // 如果最高优先级不是当前节点，需要调整
            if (target != index)
            {
                swap(heap_[index], heap_[target]); // 交换
                index = target;                     // 向下移动到子节点位置
            }
            else
            {
                break; // 堆性质已满足，结束调整
            }
        }
    }

public:
    // ============ 核心操作：插入 ============
    void insert(const T& value)
    {
        heap_.push_back(value);         // 步骤1：添加到数组末尾
        heapifyUp(heap_.size() - 1);    // 步骤2：从末尾开始上浮调整
    }

    // ============ 核心操作：删除堆顶 ============
    T pop()
    {
        if (heap_.empty()) throw std::runtime_error("Heap is empty");

        T result = heap_[0];            // 步骤1：保存堆顶元素
        
        if (heap_.size() == 1)
        {
            heap_.pop_back();           // 特殊情况：只有一个元素
        }
        else
        {
            heap_[0] = heap_.back();    // 步骤2：用最后元素替换堆顶
            heap_.pop_back();           // 步骤3：删除最后元素
            heapifyDown(0);             // 步骤4：从堆顶开始下沉调整
        }

        return result;
    }

    // ============ 基础操作 ============
    const T& top() const { return heap_[0]; }
    bool empty() const { return heap_.empty(); }
    size_t size() const { return heap_.size(); }

    void print() const
    {
        cout << "[";
        for (size_t i = 0; i < heap_.size(); ++i)
        {
            cout << heap_[i];
            if (i < heap_.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// 类型别名
using MaxHeap = CoreHeap<int>;                    // 最大堆
using MinHeap = CoreHeap<int, std::less<int>>;    // 最小堆

int main()
{
    cout << "=== 堆的核心算法演示 ===" << endl;
    
    MaxHeap heap;
    vector<int> data = {4, 10, 3, 5, 1};
    
    cout << "\n插入过程（每次插入后上浮调整）：" << endl;
    for (int val : data)
    {
        cout << "插入 " << val << " -> ";
        heap.insert(val);
        heap.print();
    }
    
    cout << "\n删除过程（每次删除后下沉调整）：" << endl;
    while (!heap.empty())
    {
        cout << "删除 " << heap.pop() << " -> ";
        if (!heap.empty()) heap.print();
        else cout << "[]" << endl;
    }
    
    return 0;
}