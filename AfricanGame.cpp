#include <string>
#include <algorithm>
#include <numeric>
#include <utility>
#include <climits>
#include <iostream>

int MAX(int a, int b){
	return a > b ? a : b;
}
int MIN(int a, int b){
	return a > b ? b : a;
}

using namespace std;

typedef string Board;

int dps(bool getMax, Board state, int opp, int u, int depth){
	cout<<depth<<endl;
	bool opp_done = true, u_done = true;
	for(int i = 0; i < 6; ++i){
		if(state[i] != 0){
			opp_done = false;
			break;
		}
	}
	for(int i = 6; i < 12; ++i){
		if(state[i] != 0){
			u_done = false;
			break;
		}
	}
	if(opp_done){
		return u + accumulate(state.begin()+6,state.end(),0);
	}
	else if(u_done){
		return u;
	}

	int start;
	decltype(&MIN) compair;
	int best;

	if(getMax){
		start = 6;
		compair = MAX;
		best = INT_MIN;
	}
	else{
		start = 0;
		compair = MIN;
		best = INT_MAX;
	}

	int opp_e;
	int u_e;

	for(int i = start; i < start + 6; ++i){
		if(state[i] > 0){
			opp_e = 0;
			u_e = 0;
			Board newState = state;
			int balls = newState[i];
			newState[i] = 0;

			newState.insert(newState.begin()+start+6,0);
			for(int j = i+1; j <= i + balls; ++j){
				newState[j%13]++;
			}
			if(start == 0){
				opp_e = newState[start+6];
			}
			else{
				u_e = newState[start+6];
			}
			newState.erase(newState.begin()+start+6);
			best = compair(best,dps(getMax+1,newState,opp+opp_e,u+u_e,depth+1));
		}
	}
	return best;
}

int main(){
	Board start_state = {4,4,4,4,4,4,4,4,4,4,4,4};
	cout<<dps(true,start_state,0,0,0)<<endl;

	return 0;
}