#include "mymatrix.cpp"

int main (){
    srand( unsigned ( time(0) ) );
    char c ='a';

    while(c != '0'){
        std::cout << "1 - calculate determinant\n";
        std::cout << "2 - random matrix by determinant\n";
        std::cout << "0 - exit\n\n";
        std::cin >> c;

        switch(c){
            case '0':
                std::cout << "exiting...";
                break;
            case '1':
                determ();
                break;
            case '2':
                randomMatrix();
                break;
            default:
                std::cout << "incorrect option\n";
        }
    }

    return 0;
}
