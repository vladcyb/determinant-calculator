#include <iostream>
#include <vector>
#include <chrono>
#include "rnd_matrix.cpp"

int det(std::vector< std::vector<int> >& v){
    int n = v.size();
    if (n == 1){
        return v[0][0];
    }else if (n == 2){
        return v[0][0] * v[1][1] - v[0][1] * v[1][0];
    }

    std::vector<std::vector<int> > det1(n - 1);
    for (std::vector<int>& el : det1){
        el.resize(n - 1);
    }

    std::vector<int> vect1;

    int s = 0;
    int x;
    for (int i = 0; i < n; ++i){
        x = 0;
        for(int j = 1; j < n; ++j){
            vect1.clear();
            for(int k = 0; k < n; ++k){
                if (k == i){
                    continue;
                }
                vect1.push_back(v[j][k]);
            }
            det1[j - 1] = vect1;
        }
        x = det(det1);
        if(i % 2){
            s -= x * v[0][i];
        }else{
            s += x * v[0][i];
        }
    }

    return s;

}

std::vector< std::vector<int> > minor1(std::vector< std::vector<int> >& v, int i, int j){
    int N = v.size();
    int n = N - 1;
    std::vector< std::vector<int> > v1(n);
    for(int i = 0; i < n; ++i){
        v1.at(i).resize(n);
    }
    int k = 0, l, y = 0, x;
    while(k < N){
        if (k == i){
            ++k;
            if (k == N){
                break;
            }
        }

        l = 0;
        x = 0;
        while(l < N){
            if (l == j){
                ++l;
                if (l == N){
                    break;
                }
            }

            v1.at(y).at(x) = v.at(k).at(l);
            ++x;
            ++l;
        }
        ++y;
        ++k;

    }
    return v1;
}

std::vector< std::vector<int> > complement(std::vector< std::vector<int> >& v){
    int n = v.size();
    std::vector< std::vector<int> > v1(n);
    for(int i = 0; i < n; ++i){
        v1.at(i).resize(n);
    }

    std::vector< std::vector<int> > v2;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            v2 = minor1(v, i, j);
            v1.at(i).at(j) = (i + j) % 2 ? -det(v2) : det(v2);
        }
    }
    return v1;
}

void determ(){
    int n;
    std::cout << "Enter n: ";
    n = inputInt();

    if (n < 2){
        std::cout << "Error: n < 2\n";
        return;
    }

    std::cout << "Enter the elements:\n\n";
    std::vector<std::vector<int> > v(n);


    for(int i = 0; i < n; ++i){
        v.at(i).resize(n);
        for(int j = 0; j < n; ++j){
            v.at(i).at(j) = inputInt();
        }
    }

    auto startTime = std::chrono::steady_clock::now();

    std::cout << std::endl << "Answer: " << det(v) << "\n\n";
    auto stopTime = std::chrono::steady_clock::now();
    std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count() << " ms\n";

}

int main (){
    srand( unsigned ( time(0) ) );
    std::string s;
    int cmdCode;

    while(true){
        std::cout << "1 - calculate determinant\n";
        std::cout << "2 - random matrix by determinant\n";
        std::cout << "0 - exit\n\n";
        cmdCode = -1;
        std::cin >> s;

        if (s == "0"){
            break;
        }

        std::vector<std::string> strV = { "1", "2" };
        for(unsigned int i = 0; i < strV.size(); ++i){
            if (s == strV.at(i)){
                cmdCode = i;
                break;
            }
        }

        switch(cmdCode){
            case 0:
                determ();
                break;
            case 1:
                rnd_matrix::init();
                break;
        }
    }

    return 0;
}
