class Solution {
public:
    bool dfs(vector<int>& arr, int i, vector<int>& vis) {
        
        // Out of bounds
        if(i < 0 || i >= arr.size())
            return false;

        // Already visited
        if(vis[i])
            return false;

        // Found zero
        if(arr[i] == 0)
            return true;

        vis[i] = 1;

        // Jump forward or backward
        return dfs(arr, i + arr[i], vis) ||
               dfs(arr, i - arr[i], vis);
    }

    bool canReach(vector<int>& arr, int start) {
        vector<int> vis(arr.size(), 0);

        return dfs(arr, start, vis);
    }
};