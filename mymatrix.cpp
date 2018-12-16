#include "mtrx.h"

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

int favorite, n, resN;

int det(matrix& v){
    int n = v.size();
    if (n == 1){
        return v[0][0];
    }else if (n == 2){
        return v[0][0] * v[1][1] - v[0][1] * v[1][0];
    }

    matrix det1(n - 1);
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

matrix minor1(matrix& v, int i, int j){
    int N = v.size();
    int n = N - 1;
    matrix v1(n);
    for(int i = 0; i < n; ++i){
        v1[i].resize(n);
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

            v1[y][x] = v[k][l];
            ++x;
            ++l;
        }
        ++y;
        ++k;

    }
    return v1;
}

matrix complement(matrix& v){
    int n = v.size();
    matrix v1(n);
    for(int i = 0; i < n; ++i){
        v1[i].resize(n);
    }

    matrix v2;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            v2 = minor1(v, i, j);
            v1[i][j] = (i + j) % 2 ? -det(v2) : det(v2);
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
    matrix v(n);


    for(int i = 0; i < n; ++i){
        v[i].resize(n);
        for(int j = 0; j < n; ++j){
            v[i][j] = inputInt();
        }
    }

    auto startTime = std::chrono::steady_clock::now();

    std::cout << std::endl << "Answer: " << det(v) << "\n\n";
    auto stopTime = std::chrono::steady_clock::now();
    std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count() << " ms\n";

}

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

int findMaxSigns(matrix& a){
    int sgns;
    int max_signs = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            sgns = signs(a[i][j]);
            if (sgns > max_signs){
                max_signs = sgns;
            }
        }
    }
    return max_signs;
}

void printMatrix(matrix& a){
    fillMatrix(a);
    int max_signs = findMaxSigns(a);
    std::cout << '\n';
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << std::setw(max_signs + 1) << a[i][j];
        }
        std::cout << '\n';
    }
}


void add_row(matrix& a, const int x, const int y){

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

void add_col(matrix& a, const int x, const int y){

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


void fillMatrix(matrix& mtrx){
    mtrx = matrix(n);
    for(int i = 0; i < n; i++){
        mtrx[i] = std::vector<int>(n);
        for(int j = 0; j < n; ++j){
            mtrx[i][j] = 0;
        }
    }

    int x = favorite;
    int y = favorite;

    for(int i = 0; i < n - 1; ++i){

        x = ceil( pow(favorite, (double)1/n) );

        while(y % x){
            --x;
        }

        mtrx[i][i] = x;
        y /= x;

    }
    mtrx[n - 1][n - 1] = y;

    for(int i = 0; i < 10; ++i){
        for(int j = i + 1; j < n; ++j){
            mtrx[i][j] = rand() % 10 + 1;
        }
    }

    for(int i = 0; i < n / 2; ++i){
        add_row(mtrx, n - i - 1, i);
        add_col(mtrx, i, n - i - 1);
    }
}

void randomMatrix(){
    matrix random_matrix;
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
        fillMatrix(random_matrix);
        findMaxSigns(random_matrix);
        printMatrix(random_matrix);
    }

    std::cout << "\n\n";
}
