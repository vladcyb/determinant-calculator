#include "rnd_matrix.cpp"

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
            if (s == strV[i]){
                cmdCode = i;
                break;
            }
        }

        switch(cmdCode){
            case 0:
                determ();
                break;
            case 1:
                randomMatrix();
                break;
        }
    }

    return 0;
}
