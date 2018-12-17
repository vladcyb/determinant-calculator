#include "mymatrix.cpp"

int main (){
    srand( unsigned ( time(0) ) );
    char c ='a';

    while(c != 'q'){
        std::cout << "1 - calculate determinant\n";
        std::cout << "2 - random matrix by determinant\n";
        std::cout << "q - exit\n\n";
        std::cin >> c;

        switch(c){
            case 'q':
                std::cout << "exiting..." << std::endl;
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
