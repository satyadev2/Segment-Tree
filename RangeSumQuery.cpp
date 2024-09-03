#include <bits/stdc++.h>
using namespace std;

void buildTree(int i, int l, int r, vector<int> &v, vector<int> &segTree)
{
    if (l == r)
    {
        segTree[i] = v[l];
        return;
    }

    int mid = (l + r) / 2;
    buildTree(2 * i + 1, l, mid, v, segTree);     // left node
    buildTree(2 * i + 2, mid + 1, r, v, segTree); // right node
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

int findSum(int i, int l, int r, int queryL, int queryR, vector<int> &segTree)
{
    // Completely outside the range
    if (l > queryR || r < queryL)
        return 0;

    // Completely inside the range
    if (l >= queryL && r <= queryR)
        return segTree[i];

    // Partially inside and outside the range
    int mid = (l + r) / 2;
    int leftSum = findSum(2 * i + 1, l, mid, queryL, queryR, segTree);
    int rightSum = findSum(2 * i + 2, mid + 1, r, queryL, queryR, segTree);
    return leftSum + rightSum;
}

void update(int i, int l, int r, int idx, int value, vector<int> &segTree)
{
    if (l == r) // we will always reach the correct leaf because of conditional recursive call
    {
        segTree[i] = value;
        return;
    }

    int mid = (l + r) / 2;
    if (idx <= mid)
    {
        update(2 * i + 1, l, mid, idx, value, segTree);
    }
    else
    {
        update(2 * i + 2, mid + 1, r, idx, value, segTree);
    }

    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

int main()
{
    cout << "Number of Elements\n";
    int n;
    cin >> n;
    vector<int> v(n);
    cout << "Input elements\n";
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    vector<int> segTree(4 * n, 0);
    buildTree(0, 0, n - 1, v, segTree);

    while (true)
    {
        cout << "------------------------------\n";
        cout << "1. QUERY\n";
        cout << "2. UPDATE\n";
        cout << "0. View Segment Tree\n";
        cout << "Enter your choice-\n";

        cout << "--------------------------------\n";

        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            cout << "Number of queries\n";
            int q;
            cin >> q;
            while (q--)
            {
                cout << "Give indices between which you want to find sum (0-based)\n";
                int queryL, queryR;
                cin >> queryL >> queryR;
                cout << findSum(0, 0, n - 1, queryL, queryR, segTree) << "\n";
            }
            break;
        }
        case 2:
        {
            cout << "Give index and its corresponding value to update (0-based)\n";
            int idx, val;
            cin >> idx >> val;
            if (idx < 0 || idx >= n)
            {
                cout << "Invalid index.\n";
                break;
            }
            update(0, 0, n - 1, idx, val, segTree);
            break;
        }
        case 0:
        {
            cout << "----------------------------\n";
            cout << "Elements in segment Tree\n";
            for (auto i : segTree)
            {
                cout << i << " ";
            }
            cout << "\n--------------------------------\n";
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
