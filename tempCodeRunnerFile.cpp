#include <bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[]) {
    double a=0;
    if (argc != 0 ) {
        for (int i=1;i<=argc;i++){
            a += atof(argv[i]);
        }
        cout << "---------------------------------\n";
        cout << "Average of " << argc-1 << " number = " << a/double(argc-1) << "\n";
        cout << "---------------------------------\n";
        return 0;
    }else {
        cout << "Please input numbers to find average.";
    }
    
}
