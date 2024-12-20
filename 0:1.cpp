// ---------------------------------------------Simple 0_1 Knapsack Code (prints maximum possible profit ---------------------------------------------------------------
#include <vector>
#include <iostream>
using namespace std;

int knapsack(int n, int W, vector<int> &prof, vector<int> &weig, vector<vector<int> > &v)
{
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j <= W; j++)
        {
            int inc = 0;
            if (j - weig[i] >= 0)
            {
                inc = v[i + 1][j - weig[i]] + prof[i];
            }
            int exc = v[i + 1][j];
            v[i][j] = max(inc, exc);
        }
    }
    return v[0][W];
}

int main()
{
    int n, W;
    cin >> n >> W;
    vector<int> profits(n), weights(n);
    for (int i = 0; i < n; i++)
        cin >> profits[i];
    for (int i = 0; i < n; i++)
        cin >> weights[i];
    vector<vector<int> > v(n + 1, vector<int>(W + 1, 0));
    int res = knapsack(n, W, profits, weights, v);
    cout << res << endl;
    return 0;
}


// ------------------------------------- Below Code prints maximum profit as well as items that are selected ------------------------------------------------- //

/*
#include <bits/stdc++.h>
using namespace std;

int knapsack(int n, int W, vector<int> &prof, vector<int> &weig, vector<vector<int>> &v)
{
    // Build the knapsack table from bottom to top
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j <= W; j++)
        {
            int inc = 0;
            if (j - weig[i] >= 0)
            {
                inc = v[i + 1][j - weig[i]] + prof[i]; // Include item i
            }
            int exc = v[i + 1][j];   // Exclude item i
            v[i][j] = max(inc, exc); // Choose the maximum of including or excluding
        }
    }
    return v[0][W]; // Return the maximum profit
}

// Function to find and display the items selected in the knapsack
void findSelectedItems(int n, int W, vector<int> &prof, vector<int> &weig, vector<vector<int>> &v)
{
    int remainingWeight = W;
    vector<int> selectedItems;

    for (int i = 0; i < n; i++)
    {
        // Check if including the item gives the same profit as the current cell
        if (remainingWeight >= weig[i] && v[i][remainingWeight] == v[i + 1][remainingWeight - weig[i]] + prof[i])
        {
            selectedItems.push_back(i + 1); // Store item index (1-based)
            remainingWeight -= weig[i];     // Reduce the weight capacity by the weight of the selected item
        }
    }

    cout << "Selected Items (1-based index): ";
    for (int item : selectedItems)
    {
        cout << "I" << item << " ";
    }
    cout << endl;
}

int main()
{
    int n, W;
    cout << "Enter the number of items and maximum weight capacity: ";
    cin >> n >> W;
    vector<int> profits(n), weights(n);

    cout << "Enter the profits of the items: ";
    for (int i = 0; i < n; i++)
        cin >> profits[i];

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++)
        cin >> weights[i];

    // Initialize the DP table with 0
    vector<vector<int>> v(n + 1, vector<int>(W + 1, 0));

    int res = knapsack(n, W, profits, weights, v);
    cout << "Maximum Profit: " << res << endl;

    // Find and display the selected items
    findSelectedItems(n, W, profits, weights, v);

    return 0;
}
*/

// ----------------------------------------Memoization ---------------------------------------------------------
// #include <iostream>
// #include <vector>
// #include <cstring>
// using namespace std;

// // Recursive function with memoization
// int knapsackUtil(int ind, int W, vector<int> &profit, vector<int> &weight,
//                  vector<vector<int>> &dp)
// {
//     // Base case
//     if (ind == 0)
//     {
//         if (weight[0] <= W)
//             return profit[0];
//         return 0;
//     }

//     // If result already calculated
//     if (dp[ind][W] != -1)
//         return dp[ind][W];

//     // Don't take current item
//     int notTake = knapsackUtil(ind - 1, W, profit, weight, dp);

//     // Take current item if possible
//     int take = 0;
//     if (weight[ind] <= W)
//     {
//         take = profit[ind] +
//                knapsackUtil(ind - 1, W - weight[ind], profit, weight, dp);
//     }

//     // Store and return the maximum
//     return dp[ind][W] = max(take, notTake);
// }

// int knapsack(int n, int W, vector<int> &profit, vector<int> &weight)
// {
//     // Initialize DP table with -1
//     vector<vector<int>> dp(n, vector<int>(W + 1, -1));
//     return knapsackUtil(n - 1, W, profit, weight, dp);
// }

// int main()
// {
//     int n, W;
//     cin >> n >> W;

//     vector<int> profit(n), weight(n);

//     // Input profits
//     for (int i = 0; i < n; i++)
//         cin >> profit[i];

//     // Input weights
//     for (int i = 0; i < n; i++)
//         cin >> weight[i];

//     cout << knapsack(n, W, profit, weight) << endl;
//     return 0;
// }
/*
 7 15
 20 5 10 40 15 25 30
 3 2 1 5 4 6 7
 95
 */
