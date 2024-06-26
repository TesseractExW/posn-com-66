// Merger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>

struct Station {
    int distance = 0;
    int count = 0;
};

struct StationList {
    Station* stations;
    int n;
    StationList(int N)
    { 
        n = N;
        stations = (Station*)malloc(sizeof(Station) * n);
    }
    void Read()
    {
        for (int i = 0;i < n;i++) {
            std::cin >> stations[i].distance;
        }
        for (int i = 0;i < n;i++) {
            std::cin >> stations[i].count;
        }
    }
    void Modify(int alpha,int beta)
    {
        for (int i = 0;i < n;i++)
        {
            stations[i].distance = alpha * stations[i].distance + beta;
        }
    }
    static StationList Copy(StationList a) {
        StationList b(a.n);
        for (int i = 0;i < a.n;i++) {
            b.stations[i] = a.stations[i];
        }
        return b;
    }
    static StationList Merge(StationList a, StationList b)
    {
        std::map<int, int> buffer; // distance and count
        for (int i = 0;i < a.n;i++) {
            Station _station = a.stations[i];
            buffer[_station.distance] = _station.count;
        }
        for (int i = 0;i < b.n;i++) {
            Station _station = b.stations[i];
            if (buffer.find(_station.distance) == buffer.end()) {
                buffer[_station.distance] = 0;
            }
            buffer[_station.distance] += _station.count;
        }
        
        int n = 0;

        for (std::map<int, int>::iterator i = buffer.begin(); i != buffer.end(); i++) {
            n++;
        }

        StationList c(n);
        int index = 0;
        for (auto i = buffer.begin(); i != buffer.end(); i++) {
            c.stations[index].distance = i->first;
            c.stations[index].count = i->second;
            index++;
        }
        return c;
    }
};

struct TestSet {
    int alpha = 0;
    int beta = 0;
    int k = 0;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m, q;
    std::cin >> n >> m >> q;
    StationList DC(n);
    StationList _AC(m);
    DC.Read();
    _AC.Read();

    TestSet* tests = (TestSet*)malloc(sizeof(TestSet) * q);
    for (int i = 0;i < q;i++)
    {
        std::cin >> tests[i].alpha >> tests[i].beta >> tests[i].k;
    }
    
    for (int i = 0;i < q;i++) {
        StationList AC = StationList::Copy(_AC);
        AC.Modify(tests[i].alpha, tests[i].beta);

        StationList res = StationList::Merge(DC, AC);
        int min_range = 1;
        int max_range = 1;
        bool stop = false;
        for (int j = 0;j < res.n && !stop;j++) {
            max_range = min_range + res.stations[j].count - 1;
            if (tests[i].k <= max_range && tests[i].k >= min_range) {
                std::cout << std::to_string(res.stations[j].distance) << std::endl;
                stop = true;
            }
            min_range = max_range + 1;
        }
    }

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
