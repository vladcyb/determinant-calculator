#include "mymatrix.h"

void checkNext(){
    if (std::cin.peek() == '.'){
        std::cout << "Error! Only integer numbers are allowed!" << std::endl;
        std::exit(1);
    }
}

int inputInt(){
    int n;
    std::cin.clear();
    std::cin >> n;
    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error! Only integer numbers are allowed!" << std::endl;
        std::exit(1);
    }
    return n;
}

int det(matrix& v, int idx_from, int idx_to){
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
    for (int i = idx_from; i <= idx_to; ++i){
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
        x = det(det1, 0, det1.size() - 1);
        if(i % 2){
            s -= x * v[0][i];
        }else{
            s += x * v[0][i];
        }
    }
    return s;
}

void writeDeterminantToX (int& x, matrix& v, int idx_from, int idx_to){
    x = det(v, idx_from, idx_to);
}

void determ(){
    int n;
    std::cout << "Enter n: ";
    n = inputInt();
    checkNext();
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

    checkNext();
    std::cout << std::endl << "You entered: ";
    printMatrix(v);

    auto startTime = std::chrono::steady_clock::now();
    int answer = 0;
    if (v.size() > 3){
        int a[4];
        std::thread t1(writeDeterminantToX, std::ref(a[0]), std::ref(v), 0, v.size() / 4 - 1);
        std::thread t2(writeDeterminantToX, std::ref(a[1]), std::ref(v), v.size() / 4, v.size() / 2 - 1);
        std::thread t3(writeDeterminantToX, std::ref(a[2]), std::ref(v), v.size() / 2, v.size() * 3 / 4 - 1);
        std::thread t4(writeDeterminantToX, std::ref(a[3]), std::ref(v), v.size() * 3 / 4, v.size() - 1);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        for(int i = 0; i < 4; ++i){
            answer += a[i];
        }
    }else{
        answer = det(v, 0, v.size() - 1);
    }

    std::cout << std::endl << "Answer: " << answer << "\n\n";
    auto stopTime = std::chrono::steady_clock::now();
    std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>
                (stopTime - startTime).count() << " ms\n";
}

int len(int x){
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

int findMaxLength(matrix& a){
    int sgns;
    int max_len = 0;
    int n = a.size();
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            sgns = len(a[i][j]);
            if (sgns > max_len){
                max_len = sgns;
            }
        }
    }
    return max_len;
}

void printMatrix(matrix& a){
    int max_len = findMaxLength(a);
    std::cout << '\n';
    int n = a.size();
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << std::setw(max_len + 1) << a[i][j];
        }
        std::cout << '\n';
    }
}

void addRow(matrix& a, const int x, const int y){
    int count = 0;
    int n = a.size();
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

void addCol(matrix& a, const int x, const int y){
    int count = 0;
    int n = a.size();
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

void fillMatrix(matrix& mtrx, int n, int favorite){
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
        addRow(mtrx, n - i - 1, i);
        addCol(mtrx, i, n - i - 1);
    }
}

void randomMatrix(){
    matrix random_matrix;
    std::cout << "Enter your favorite number: ";
    int favorite = -1;
    while(true){
        favorite = inputInt();
        if (favorite <= 0){
            std::cout << "Error! Enter n > 0: ";
        }else{
            break;
        }
    }

    std::cout << "Enter number of rows and columns: ";
    int n = inputInt();
    if(n < 2){
        std::cout << "Error!" << std::endl;
        std::exit(1);
    }
    std::cout << "Enter number of determinants: ";
    int resN = inputInt();

    if (n < 2){
        return;
    }

    for(int i = 0; i < resN; ++i){
        fillMatrix(random_matrix, n, favorite);
        printMatrix(random_matrix);
    }

    std::cout << "\n\n";
}
