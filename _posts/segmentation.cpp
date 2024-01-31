#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// the index of root is 1 intead of 0

struct Info
{
    int sum;
    int val;
    int right_dist;
    int lazy_right_dist_add = 0;
    int lazy_val_add = 0;
    Info()
    {
        sum = 0;
        val = 0;
    }
};
// reload + operator for Info
Info operator+(const Info &a, const Info &b)
{
    // this function define how to combine to Info
    // left_node + right_node = father_node
    Info ret;
    ret.sum = a.sum + b.sum;
    // ret.val = a.val + b.val;
    // ret.right_dist = a.right_dist + b.right_dist;
    return ret;
}
Info operator-(const Info &a, const Info &b)
{
    // this functoin define how to update the value to current nodes.
    // current_node = current_node - bJJJJJ
    Info ret;
    ret.sum = a.sum - b.sum;
    // ret.val = a.val - b.val;
    // ret.right_dist = a.right_dist - b.right_dist;
    return ret;
}

class segment_tree_node
{
public:
    Info val;
    bool push_down = false;
    unsigned int left, right;
    segment_tree_node()
    {
        val = Info();
        left = right = 0;
    }
    segment_tree_node(unsigned int _left, unsigned int _right) : left(_left), right(_right)
    {
        val = Info();
    }
};

class segment_tree
{

public:
    int n; // number of elements
    vector<segment_tree_node> tree;
    segment_tree(int n)
    {
        this->n = n;
        tree.resize(2 * n + 10);
    }
    void build(int root, int l, int r, vector<T> &arr)
    {
        if (l == r)
        {
            tree[root].val = arr[l];
            tree[root].left = tree[root].right = l;
            return;
        }
        int mid = (l + r) / 2;
        build(root << 1, l, mid, arr);
        build(root << 1 | 1, mid + 1, r, arr);
        tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
        tree[root].left = l;
        tree[root].right = r;
    }
    void update_node(int root, int l, int r, int i, Info val)
    {
        // change the value of the i-th element to `val`
        if (l == r)
        {
            tree[root].val = tree[root].val - val;
            return;
        }
        int mid = (l + r) / 2;
        if (i <= mid)
            update_node(root << 1, l, mid, i, val);
        else
            update_node(root << 1 | 1, mid + 1, r, i, val);
        tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
    }
    Info query(int root, int l, int r)
    {
        if (l == r)
            return tree[root].val;
        if (l > tree[root].right || r < tree[root].left)
            return Info();
        if (l <= tree[root].left && tree[root].right <= r)
        {
            return tree[root].val;
        }
        Info left_val = query(root << 1, l, r);
        Info right_val = query(root << 1 | 1, l, r);
        return left_val + right_val;
    }
    void update_segment(int root, int l, int r, int i, int j, Info val)
    {
        // change the value of the from i to j-th element to `val`
        if (l > tree[root].right || r < tree[root].left)
            return;
        if (l <= tree[root].left && tree[root].right <= r)
        {
            tree[root].val = tree[root].val - val;
            tree[root].push_down = true;
            return;
        }
        // push_down(root);
        int mid = (l + r) / 2;
        update_segment(root << 1, l, mid, i, j, val);         // push down
        update_segment(root << 1 | 1, mid + 1, r, i, j, val); // push down
        tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
    }
    Info lazy_query(int root, int l, int r)
    {
        if (l == r)
            return tree[root].val;
        if (l > tree[root].right || r < tree[root].left)
            return Info();
        if (l <= tree[root].left && tree[root].right <= r)
        {
            return tree[root].val;
        }
        // push_down(root);
        int mid = (l + r) / 2;
        Info left_val = lazy_query(root << 1, l, mid);
        Info right_val = lazy_query(root << 1 | 1, mid + 1, r);
        return left_val + right_val;
    }
    // void push_down(int root)
    // {
    //     if (tree[root].left == tree[root].right)
    //         return;
    //     if (tree[root].push_down)
    //     {
    //         tree[root << 1].val = tree[root << 1].val - tree[root].val;
    //         tree[root << 1 | 1].val = tree[root].val;
    //         tree[root << 1].push_down = tree[root << 1 | 1].push_down = true;
    //         tree[root].push_down = false;
    //     }
    // }
};
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    // segment_tree<int> st(n);
    // st.build(1, 0, n - 1, arr);

    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
    {
        int l = i, r = n - 1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            int tmp = st.query(1, i, mid);
            if (tmp == mid - i + 1)
            {
                q.push(make_pair(i, mid));
                break;
            }
            else if (tmp < mid - i + 1)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
    }
    int ret = 0;
    int pos = 0;
    while (!q.empty())
    {
        auto a = q.front();
        q.pop();
        while (pos < a.second)
        {
            cout << ret << " ";
            pos++;
        }
        ret++;
        while (!q.empty() && q.front().first <= a.second)
            q.pop();
    }
    while (pos < n)
    {
        cout << ret << " ";
        pos++;
    }

    return 0;
}