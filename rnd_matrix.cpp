#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <chrono>

int inputInt(){
    int n;
    std::cin.clear();
    std::cin >> n;
    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error!" << std::endl;
        std::exit(1);
    }
    return n;
}

int favorite, n, max_signs, resN;
std::vector<std::vector<int>> a;

int signs(int x){
    int res = 0;
    if (x < 0){
        ++res;
    }
    while(x != 0){
        ++res;
        x /= 10;
    }
    if(!res){
        ++res;
    }
    return res;
}

void find_max_signs(){
    int sgns;
    max_signs = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            sgns = signs(a[i][j]);
            if (sgns > max_signs){
                max_signs = sgns;
            }
        }
    }

}

void print_matrix(){
    std::cout << '\n';
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << std::setw(max_signs+1) << a[i][j];
        }
        std::cout << '\n';
    }
}


void add_row(const int x, const int y){

    int count = 0;

    for(int i = 0; i < n; ++i){
        if (fabs(a[x][i] - a[y][i]) < fabs(a[x][i] + a[y][i])){
            ++count;
        }
    }

    if (count > n / 2){
        for(int i = 0; i < n; ++i){
            a[x][i] -= a[y][i];
        }
    }else{
        for(int i = 0; i < n; ++i){
            a[x][i] += a[y][i];
        }
    }

}

void add_col(const int x, const int y){

    int count = 0;

    for(int i = 0; i < n; ++i){
        if (fabs(a[i][x] - a[i][y]) > fabs(a[i][x] + a[i][y])){
            ++count;
        }
    }

    if (count > n / 2){
        for(int i = 0; i < n; ++i){
            a[i][x] -= a[i][y];
        }
    }else{
        for(int i = 0; i < n; ++i){
            a[i][x] += a[i][y];
        }
    }
}


void fill_matrix(){

    a = std::vector<std::vector<int> >(n);
    for(int i = 0; i < n; i++){
        a[i] = std::vector<int>(n);
        for(int j = 0; j < n; ++j){
            a[i][j] = 0;
        }
    }

    int x = favorite;
    int y = favorite;

    for(int i = 0; i < n - 1; ++i){

        x = ceil( pow(favorite, (double)1/n) );

        while(y % x){
            --x;
        }

        a[i][i] = x;
        y /= x;

    }
    a[n - 1][n - 1] = y;

    for(int i = 0; i < 10; ++i){
        for(int j = i + 1; j < n; ++j){
            a[i][j] = rand() % 10 + 1;
        }
    }

    for(int i = 0; i < n / 2; ++i){
        add_row(n - i - 1, i);
        add_col(i, n - i - 1);
    }
}

void randomMatrix(){

    std::cout << "Enter your favorite number: ";
    favorite = -1;
    while(true){
        favorite = inputInt();
        if (favorite <= 0){
            std::cout << "Error! Enter n > 0: ";
        }else{
            break;
        }
    }

    std::cout << "Enter number of rows and columns: ";
    n = inputInt();
    if(n < 2){
        std::cout << "Error!" << std::endl;
        std::exit(1);
    }
    std::cout << "Enter number of determinants: ";
    resN = inputInt();

    if (n < 2){
        return;
    }

    for(int i = 0; i < resN; ++i){
        fill_matrix();
        find_max_signs();
        print_matrix();
    }

    std::cout << "\n\n";
}
