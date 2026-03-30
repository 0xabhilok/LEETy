class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string ab(n, ')');
        char curr = 'a';

        for(int i = 0; i < n; i++) {
            if(ab[i] == ')') {
                for(int j = 0; j < n; j++) {
                    if(lcp[i][j] > 0) {
                        if(ab[j] == ')' || ab[j] == curr) {
                            ab[j] = curr;
                        } else {
                            return ""; 
                        }
                    }
                }
                if(curr>'z'){
                    return "";
                }
                curr++;
            }
        }

        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int k = 0;
                while(i + k < n && j + k < n && ab[i+k] == ab[j+k]) k++;
                if(k != lcp[i][j]) return "";
            }
        }

        return ab;
    }
};