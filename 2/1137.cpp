#include <vector>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int BMAX = 1001, NMAX = 101;
int N, X, Y, B, mdp[BMAX][NMAX], fdp[BMAX][NMAX];
vector<pair<int, int>> males, females;
vector<int> mI, fI, mIndex[BMAX][NMAX], fIndex[BMAX][NMAX];

int main(){
    scanf("%d%d%d%d", &N, &X, &Y, &B);
    for(int i = 1; i <= N; ++i){
        char ch[2]; int a, b;
        scanf("%s%d%d", ch, &a, &b);
        if(ch[0] == 'M'){
            males.push_back(make_pair(a, b));
            mI.push_back(i);
        }else{
            females.push_back(make_pair(a, b));
            fI.push_back(i);
        }
    }
    memset(mdp, 0, sizeof(mdp));
    for(int i = 0; i <= B; ++i){
        for(int j = 1; j <= X; ++j) mdp[i][j] = INT_MIN;
    }
    for(int i = 0; i < males.size(); ++i){
        for(int j = B; j >= males[i].second; --j){
            for(int k = X; k > 0; --k){
                int temp = j - males[i].second;
                if(mdp[temp][k - 1] != INT_MIN){
                    int t = mdp[temp][k - 1] + males[i].first;
                    if(mdp[j][k] < t){
                        mIndex[j][k].clear();
                        mdp[j][k] = t;
                        copy(mIndex[temp][k - 1].begin(), mIndex[temp][k - 1].end(), back_inserter(mIndex[j][k]));
                        mIndex[j][k].push_back(mI[i]);
                    }else if(mdp[j][k] == t){
                        bool flag = false;
                        int d;
                        for(d = 0; d < k - 1; ++d){
                            if(mIndex[j][k][d] > mIndex[temp][k - 1][d]){
                                flag = true;
                                break;
                            }
                        }
                        if(!flag && d == k - 1 && mIndex[j][k][k - 1] > mI[i]) flag = true;
                        if(flag){
                            mIndex[j][k].clear();
                            copy(mIndex[temp][k - 1].begin(), mIndex[temp][k - 1].end(), back_inserter(mIndex[j][k]));
                            mIndex[j][k].push_back(mI[i]);
                        }
                    }
                }
            }
        }
    }
    memset(fdp, 0, sizeof(fdp));
    for(int i = 0; i <= B; ++i){
        for(int j = 1; j <= Y; ++j) fdp[i][j] = INT_MIN;
    }
    for(int i = 0; i < females.size(); ++i){
        for(int j = B; j >= females[i].second; --j){
            for(int k = Y; k > 0; --k){
                int temp = j - females[i].second;
                if(fdp[temp][k - 1] != INT_MIN){
                    int t = fdp[temp][k - 1] + females[i].first;
                    if(fdp[j][k] < t){
                        fIndex[j][k].clear();
                        fdp[j][k] = t;
                        copy(fIndex[temp][k - 1].begin(), fIndex[temp][k - 1].end(), back_inserter(fIndex[j][k]));
                        fIndex[j][k].push_back(fI[i]);
                    }else if(fdp[j][k] == t){
                        bool flag = false;
                        int d;
                        for(int d = 0; d < k - 1; ++d){
                            if(fIndex[j][k][d] > fIndex[temp][k - 1][d]){
                                flag = true;
                                break;
                            }
                        }
                        if(flag && d == k - 1 && fIndex[j][k][k - 1] > fI[i]) flag = true;
                        if(flag){
                            fIndex[j][k].clear();
                            copy(fIndex[temp][k - 1].begin(), fIndex[temp][k - 1].end(), back_inserter(fIndex[j][k]));
                            fIndex[j][k].push_back(fI[i]);
                        }
                    }
                }
            }
        }
    }
    int ansV = INT_MIN, ansB;
    vector<pair<int, int>> ansI;
    for(int i = 0; i <= B; ++i){
        for(int j = 0; i + j <= B; ++j){
            if(mdp[i][X] != INT_MIN && fdp[j][Y] != INT_MIN){
                int temp = mdp[i][X] + fdp[j][Y];
                if(temp > ansV){
                    ansV = temp;
                    ansI.clear();
                    ansI.push_back(make_pair(i, j));
                    ansB = i + j;
                }else if(temp == ansV){
                    if(i + j < ansB){
                        ansI.clear();
                        ansI.push_back(make_pair(i, j));
                        ansB = i + j;
                    }else if(i + j == ansB){
                        ansI.push_back(make_pair(i, j));
                    }
                }
            }
        }
    }
    vector<int> ind(X + Y, N);
    for(int i = 0; i < ansI.size(); ++i){
        vector<int> temp;
        for(int j = 0; j < X; ++j) temp.push_back(mIndex[ansI[i].first][X][j]);
        for(int j = 0; j < Y; ++j) temp.push_back(fIndex[ansI[i].second][Y][j]);
        sort(temp.begin(), temp.end());
        bool flag = false;
        for(int j = 0; j < ind.size(); ++j){
            if(ind[j] > temp[j]){
                flag = true;
                break;
            }else if(ind[j] < temp[j]){
                break;
            }
        }
        if(flag) for(int i = 0; i < X + Y; ++i) ind[i] = temp[i];
    }
    printf("%d %d\n", ansV, ansB);
    printf("%d", ind[0]);
    for(int i = 1; i < ind.size(); ++i){
        printf(" %d", ind[i]);
    }
    printf("\n");
    return 0;
}
