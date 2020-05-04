#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;


class TimeDifference
{
    void timp (string s, int &h1, int &mn1)
    {
        mn1=0;
        h1=0;
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]==':')
            {
                for (int j=i+1; j<s.size(); j++)
                {
                    mn1=mn1*10+s[j]-'0';
                }
                break;
            }
            else
                h1=h1*10+s[i]-'0';
        }
    }
    public:
    string calculate(string s, string e)
    {
        stringstream ss;
        int mn1=0, h1=0;
        timp (s, h1, mn1);
        int mn2=0, h2=0;
        timp (e, h2, mn2);
        int h, mn;
        if (h1<h2 || (h1==h2 && mn1<=mn2))
        {
            if (mn1>mn2)
            {
                mn=60+mn2-mn1;
                h=h2-h1-1;
            }
            else
            {
                mn=mn2-mn1;
                h=h2-h1;
            }

        }
        else
        {
            ss << '-';
            if (mn1<mn2)
            {
                mn=60+mn1-mn2;
                h=h1-h2-1;
            }
            else
            {
                mn=mn1-mn2;
                h=h1-h2;
            }
        }
        if (mn<=9)
            ss << h << ':' << '0' << mn;
        else
            ss << h << ':' << mn;
        return ss.str();
    }
};

// CUT begin
ifstream data("TimeDifference.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string startTime, string endTime, string __expected) {
    time_t startClock = clock();
    TimeDifference *instance = new TimeDifference();
    string __result = instance->calculate(startTime, endTime);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string startTime;
        from_stream(startTime);
        string endTime;
        from_stream(endTime);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(startTime, endTime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1587025394;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "TimeDifference (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
