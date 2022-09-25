#include "MathCode/interface/MathematicsInterface.h"
using namespace std;




int main(){

    MathematicsInterface mathInterface("PDS1","PDS1.txt");
    mathInterface.standartPrologue();
    mathInterface.taskSelection();
    mathInterface.standartEpilogue();
    system("pause");
    return 0;

}

