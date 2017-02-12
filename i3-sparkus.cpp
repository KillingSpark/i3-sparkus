#include "JSON-Builder.h"
#include <iostream>
#include "modules.h"

using namespace std;

int main(){
    JSONArray output;

    //given by the i3bar protocol
    cout << "{\"version\":1}" << endl;
    cout << "[" << endl;
    
    while(true){
        //need reset because im not streaming but building an array each loop and printing it
        output.reset();
        output.add(myDate().toString());
        output.add(myVolume().toString());
        output.add(myBat().toString());
        output.add(myWifi().toString());
        cout << output.toString() << "," << endl;
        sleep(1);
    }

    return 0;
}