class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int n=moves.size();
        vector<int>m(3,0);
        for(int i=0;i<n;i++){
            if(moves[i]=='L'){
                m[0]++;
            }
            else if(moves[i]=='R'){
                m[1]++;
            }else{
                m[2]++;
            }
        }
        
        return abs(m[0]-m[1])+m[2];
        
    }
};