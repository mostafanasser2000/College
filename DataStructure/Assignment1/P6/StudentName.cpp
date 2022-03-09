#include "StudentName.h"
StudentName::StudentName(string name) {
    this->name = name;
    int num_spaces = 0;
    int L = name.size();
    int index_OF_space = -1;

    for(int i = 0; i < L; ++i)
    {
        if(name[i] == ' ')
        {
            num_spaces++;
        }
    }

    if(num_spaces < 2)
    {
        for(int i = 0; i < L ; ++i)
        {
            if(name[i] == ' ')
            {
                index_OF_space = i;
            }
        }

        for(int i = num_spaces ; i < 2; ++i)
        {
            if(num_spaces == 0 )
            {
                string text  = name;
                this->name += " " + text;
            }
            else if(num_spaces == 1)
            {
                string text = name.substr(index_OF_space+1,L);
                this->name += " " + text;
            }
        }
    }
}
//Implement Print to display detailed name
void  StudentName::printName()
{
    int part = 1;
    cout<<part<<")"<<" ";
    for(int i = 0; i < name.size(); ++i)
    {
        if(name[i] == ' ')
        {
            cout<<endl;
            part++;
            cout<<part<<")"<<" ";
        }
        else
        {
            cout<<name[i];
        }
    }
    cout<<endl;
}


//Implement replace
bool StudentName::replace(int i, int j) {
    stringstream str(name);
    vector<string>v;
    string namePart;
    while(str>>namePart)
    {
        v.push_back(namePart);
    }
    if(i < 0 || j < 0 || i > (int)v.size() || j > (int)v.size() )
    {
        return false;
    }
    else
    {


        swap(v[i-1],v[j-1]);
        name = "";
        for(int i = 0; i < (int) v.size(); ++i)
        {
            name += v[i];
            if(i != v.size() - 1)
            {
                name += " ";
            }
        }
        return true;
    }

}