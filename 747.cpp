#include <iostream>
#include <vector>
#include <utility>
using namespace std;
typedef int data;
typedef int index_num;
int main(){
    int T = 0;
    cin >> T;
    for (int i = 0;i!=T;++i){
        int N;
        int K;
        cin >> N;
        cin >> K;
        int number;
        vector<pair<data,index_num>> initial_seq;
        for (int i = 0;i!=N;++i){
            cin >> number;
            initial_seq.push_back(make_pair(number,i+1));
        }
        vector<pair<data,index_num>> current_seq(initial_seq);
        while(!current_seq.empty()) {
            //Step1
            vector<pair<data, index_num>> temp_seq;
            if (current_seq.size()>=K) {
                temp_seq.insert(temp_seq.end(), current_seq.begin(), current_seq.begin() + K);
            }
            else{
                temp_seq.insert(temp_seq.end(), current_seq.begin(), current_seq.end());
            }
            vector<pair<data, index_num>>::iterator vmax = temp_seq.begin();
            for (vector<pair<data, index_num>>::iterator iter = temp_seq.begin(); iter != temp_seq.end(); ++iter) {
                if (iter->first > vmax->first)
                    vmax = iter;
            }
            for (vector<pair<data, index_num>>::iterator iter = temp_seq.begin(); iter != vmax; ++iter) {
                iter->first -= 1;
            }
            for (vector<pair<data, index_num>>::iterator iter = vmax + 1; iter != temp_seq.end(); ++iter) {
                iter->first -= 1;
            }
            //Step2
            cout << vmax->second;
            if (vmax == temp_seq.begin()) {
                current_seq.insert(current_seq.end(), temp_seq.begin() + 1, temp_seq.end());
            } else if (vmax == temp_seq.end() - 1) {
                current_seq.insert(current_seq.end(), temp_seq.begin(), temp_seq.end() - 1);
            } else {
                current_seq.insert(current_seq.end(), temp_seq.begin(), vmax);
                current_seq.insert(current_seq.end(), vmax + 1, temp_seq.end());
            }
        }




    }
    return 0;

}
