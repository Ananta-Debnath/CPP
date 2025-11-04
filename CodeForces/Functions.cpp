#include <bits/stdc++.h>
using namespace std;
 
vector<int>* coordinateCompression(vector<int>& unic)
{
    vector<int>* a = new vector<int>(unic);
    vector<int>& f = *a;
    sort(unic.begin(),unic.end());
    unic.resize(unique(unic.begin(),unic.end())-unic.begin());
    for(int i = 0;i < f.size(); i++){
        f[i] = lower_bound(unic.begin(),unic.end(),f[i])-unic.begin();
    }

    return a;
}