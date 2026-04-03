
class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        
        // 1. Pair and sort robots by their positions
        vector<pair<long long, long long>> robot_data(n);
        for (int i = 0; i < n; ++i) {
            robot_data[i] = {robots[i], distance[i]};
        }
        sort(robot_data.begin(), robot_data.end());
        
        // 2. Extract walls sitting exactly on top of robots (guaranteed hits)
        sort(walls.begin(), walls.end());
        vector<long long> clean_walls;
        int base_count = 0;
        
        for (int w : walls) {
            // Binary search to check if a robot shares this exact coordinate
            auto it = lower_bound(robot_data.begin(), robot_data.end(), make_pair((long long)w, -1LL));
            if (it != robot_data.end() && it->first == w) {
                base_count++;
            } else {
                clean_walls.push_back(w);
            }
        }
        
        // Helper lambda for fast O(log M) interval queries using binary search
        auto count_walls = [&](long long start, long long end) -> int {
            if (start > end) return 0;
            auto left_it = lower_bound(clean_walls.begin(), clean_walls.end(), start);
            auto right_it = upper_bound(clean_walls.begin(), clean_walls.end(), end);
            return std::distance(left_it, right_it);
        };
        
        if (n == 0) return base_count;
        
        // 3. DP Initialization for Robot 0
        long long prev_L = count_walls(robot_data[0].first - robot_data[0].second, robot_data[0].first - 1);
        long long prev_R = 0;
        
        // 4. Process gap between Robot i-1 and Robot i
        for (int i = 1; i < n; ++i) {
            long long R_prev = robot_data[i-1].first;
            long long D_prev = robot_data[i-1].second;
            long long R_curr = robot_data[i].first;
            long long D_curr = robot_data[i].second;
            
            // Maximum effective reach into the current gap for both robots
            long long X_prev = min(R_prev + D_prev, R_curr - 1);
            long long Y_curr = max(R_curr - D_curr, R_prev + 1);
            
            // Scenario: Left - Left
            long long cost_LL = count_walls(Y_curr, R_curr - 1);
            
            // Scenario: Left - Right (Neither shoots into the gap)
            long long cost_LR = 0;
            
            // Scenario: Right - Left (Both shoot into the gap)
            long long c1 = count_walls(R_prev + 1, X_prev);
            long long c2 = count_walls(Y_curr, R_curr - 1);
            long long c12 = (Y_curr <= X_prev) ? count_walls(Y_curr, X_prev) : 0;
            long long cost_RL = c1 + c2 - c12; // Union of overlapping ranges
            
            // Scenario: Right - Right
            long long cost_RR = count_walls(R_prev + 1, X_prev);
            
            // Maximize current states
            long long curr_L = max(prev_L + cost_LL, prev_R + cost_RL);
            long long curr_R = max(prev_L + cost_LR, prev_R + cost_RR);
            
            prev_L = curr_L;
            prev_R = curr_R;
        }
        
        // 5. Add the walls hit by the final robot if it decides to shoot Right
        long long final_right_reach = count_walls(robot_data.back().first + 1, robot_data.back().first + robot_data.back().second);
        long long ans = max(prev_L, prev_R + final_right_reach);
        
        return ans + base_count;
    }
};