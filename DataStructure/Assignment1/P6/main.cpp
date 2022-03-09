# include "StudentName.cpp"





int main(){

    StudentName sn("Mostafa AHMED");
    sn.printName();
    if(sn.replace(2,1)){
        cout<<"after replace"<<endl;
        sn.printName();
    }
    else{
        cout<<"index are out of range"<<endl;
    }



}

