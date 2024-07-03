// Explorer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

template<typename T>
bool isVectorContain(vector<T> vec, T val)
{
    return !vec.empty() && find(vec.begin(), vec.end(), val) != vec.end();
}

void Permute(vector<int>* rooms, int n_room, int& res, vector<int> pass, int focused_room, int recent_list)
{
    vector<int> room = *(rooms+focused_room);
    if (!isVectorContain<int>(pass,focused_room)) {
        pass.push_back(focused_room);
    }
    if (pass.size() >= n_room) {
        res++;
        return;
    }
    if (room.size() > 1) {
        int isFail = true;
        for (int i = 0;i < room.size();i++) {
            int foo = distance(pass.begin(), find(pass.begin(), pass.end(), room[i])) - 1;
            if ((recent_list == -1 || room[i] != pass[recent_list]) 
                && !isVectorContain<int>(pass, room[i])) {
                    Permute(rooms, n_room, res, pass, room[i], foo);
                isFail = false;
            }
        }
        if (isFail)
        {
            Permute(rooms, n_room, res, pass, pass[recent_list], recent_list - 1);
        }
    }else if (room.size() == 1) {
        Permute(rooms, n_room, res, pass, pass[recent_list], recent_list - 1);
    }
}
int main()
{
    int n;
    cin >> n;
    
    int* old_list = new int[2*n-1];

    for (int i = 0;i < 2 * n - 1;i++) // input the acient method list
        cin >> *(old_list + i);
    
    vector<int>* rooms = new vector<int>[n+1]; // (1 : {1 ,3 ,4}) room 1 is connected to 1 3 and 4
    for (int i = 0;i < 2 * n - 2;i++) {
        int r1 = old_list[i];
        int r2 = old_list[i + 1];
        if (!isVectorContain<int>(rooms[r1],r2))
            rooms[r1].push_back(r2);
        if (!isVectorContain<int>(rooms[r2], r1))
            rooms[r2].push_back(r1);

    }
    for (int i = 1;i < n + 1;i++) {
        cout << i << ' ' << ':' << ' '; // 1 : 2 3 4 room 1 is connected to 2 3 4
        vector<int>* curr = rooms + i;
        for (int j = 0; j < curr->size();j++) {
            cout << (*curr)[j] << ' ';
        }
        cout << endl;
    }

    int res = 0;
    Permute(rooms, n, res, {}, *old_list, -1);

    cout << res % 1000000007 << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
