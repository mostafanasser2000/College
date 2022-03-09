#include <bits/stdc++.h>

using namespace std;

template<class typeName>

class MyList {
protected:
    // define a dynamic generic array of elems
    typeName *elems;
    int itsSize;
public:
    // Parametrized Constructor
    MyList(int s) {
        itsSize = s;
        elems = new typeName[itsSize];
    }

    // Destructor to free allocated memory
    virtual~MyList() {
        delete[] elems;
    }

    // return the size of the list
    int getSize() const {
        return itsSize;
    }

    // pure virtual functions
    virtual void addElem(typeName) = 0;

    virtual typeName getElem() = 0;

    virtual bool isEmpty() = 0;

    virtual bool isFull() = 0;

    virtual void clearItems() = 0;
};

//Stack class inherit from MyList class
template<class typeName>
class MyStack : public MyList<typeName> {
private:

    int currentIndex;

public:
    // Parametrized Constructor
    MyStack(int s) : MyList<typeName>::MyList(s) {
        currentIndex = 0; // start index to be last element in the list
    };
//    add an element to the end of the list
    void addElem(typeName val) {
        if (this->isFull()) {
            cout << "can't add current element your stack is full" << endl;
        } else {
            this->elems[currentIndex] = val;
            currentIndex++;
        }
    }
    // get element form the stack and remove it
    typeName getElem() {
        if (this->isEmpty()) {
            cout << "There is no elements in the stack" << endl;
            exit(0);
        } else {
            // return the last added element and the decrement the index
            return  this->elems[--currentIndex];
        }
    }

    // check if stack is empty
    bool isEmpty() {
        return (currentIndex == 0);
    }

    bool isFull() {
        return (currentIndex ==  this->getSize() );
    }

    void clearItems() {
        delete[]  this->elems;
    }
};

//Queue class
template<class typeName>

class MyQueue : public MyList<typeName> {
private:
    int currenIndex;
public:
    MyQueue(int s) : MyList<typeName>::MyList(s) {
        currenIndex = 0;
    };

    void addElem(typeName val) {
        if(this->isFull())
        {
            cout<<"Your queue is full\n";
            exit(0);
        }
        this->elems[currenIndex++] = val;

    }

    typeName getElem() {
        if(this->isEmpty())
        {
            cout<<"Your queue is empty\n";
            exit(0);
        }
        return  this->elems[this->getSize() - currenIndex--];
    }

    bool isEmpty() {
        return (currenIndex == 0);
    }

    bool isFull() {
        return(currenIndex == this->getSize());
    }

    void clearItems() {
        delete[] this->elems;
    }
};

//class rectangle
class Rectangle {
    int length;
    int width;
public:
    Rectangle();

    Rectangle(int, int);

    int getLength() const;

    int getWidth() const;

    int getArea() const;

    friend ostream &operator<<(ostream &, const Rectangle &);

    //exception class for avoid entering  wrong width values like -ve
    class WrongWidth {
    private:
        int wrongValue;
    public:
        WrongWidth(int w) {
            wrongValue = w;
        }
        // get the wrong value that the user enter
        int getVal() const {
            return wrongValue;
        }
    };

    //exception class for avoid entering  wrong length values like -ve
    class WrongLength {
    private:
        int wrongValue;
    public:
        WrongLength(int l) {
            wrongValue = l;
        }

        int getVal() const {
            return wrongValue;
        }
    };
};

Rectangle::Rectangle() {
    width = 0;
    length = 0;
}

Rectangle::Rectangle(int l, int w) {
    //if width is invalid
    if (w < 0)
        throw WrongWidth(w);
    //if length is invalid
    if (l < 0)
        throw WrongLength(l);
    width = w;
    length = l;
}
// return the length of the rectangle
int Rectangle::getLength() const {
    return length;
}

// return the width of the rectangle
int Rectangle::getWidth() const {
    return width;
}

// calculate the area
int Rectangle::getArea() const {
    return width * length;
}
// << operator to print rectangle objects
ostream &operator<<(ostream &output, const Rectangle &obj) {
    output << "Length = " << obj.getLength() << ", Width = " << obj.getWidth() << ", Area = " << obj.getArea() << endl;
    return output;
}



int numberOfElements, typeOfElements, length,width, num;
char choice;
string s;





//Main
int main() {
    cout << "Would you like to use a stack or a queue enter (S/Q)?" << endl;

    cin >> choice;
    choice = tolower(choice);
    if(choice != 'q' && choice !='s')
    {
        cout<<"Enter a valid character\n";
        return 0;
    }


        try {
            // ask user for size of list
            cout << "How many elements you want to store?" << endl;
            cin >> numberOfElements;
            if (numberOfElements <= 0) {
                throw "invalid number of inputs";
            }

            cout << "Would you like store integers, strings, or rectangles (1,2 or 3)?" << endl;
            cin >> typeOfElements;

            if (typeOfElements <= 0 || typeOfElements > 3) {
                throw "invalid choice";
            }
        }
           // catching  invalid number of elements
            catch (const char *msg) {
                cout << "Error: " << msg << endl;
            }

            // if user want to use queue
          if(choice == 'q') {
              // using queue of intgers
              if (typeOfElements == 1)
              {
                  MyQueue<int> M(numberOfElements);
                  bool check = true;

                  while (check)
                  {
                      for (int i = 0; i < M.getSize(); i++)
                      {
                          cout << "Enter num: ";
                          try
                          {
                              cin >> num;
                              // if user enter non intger value
                              if (std::cin.fail())
                              {
                                  std::cin.clear();
                                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                  M.addElem(0);
                                  throw "Input must be an integer will replaced by 0";
                              }

                              M.addElem(num);
                          }
                          // print error for values that are non intger
                          catch (const char *ptr)
                          {
                              cout << ptr << endl;
                          }
                      }
                        // print queue elements
                      cout << "All Elements" << endl;
                      for (int i = 0; i < M.getSize(); i++)
                      {
                          cout << "Element-->" << M.getElem() << endl;
                      }

                      check = false;
                  }
              }

              // using queue of strings
              else if (typeOfElements == 2)
              {
                  MyQueue<string> M(numberOfElements);
                  for (int i = 0; i < M.getSize(); i++)
                  {
                      cout << "Enter string: ";
                      cin >> s;
                      M.addElem(s);
                  }
                  // print queue elements
                  cout << "All Elements" << endl;
                  for (int i = 0; i < M.getSize(); i++)
                  {
                      cout << "Element-->" << M.getElem() << endl;
                  }
              }
              // using queue of rectangles
              else
              {
                  MyQueue<Rectangle> M(numberOfElements);
                  bool check = true;

                  while (check)
                  {
                      for (int i = 0; i < M.getSize(); i++)
                      {
                          cout << "Enter length and width space separated: ";
                          cin >> length >> width;
                          // check if user enter a valid length and width
                          try
                          {
                              M.addElem(Rectangle(length, width));
                          }

                           // print error for invalid length
                          catch (Rectangle::WrongLength &obj)
                          {
                              cout << "Error invalid value for length length will be 0 " << obj.getVal() << endl;
                              M.addElem(Rectangle(0, 0));
                          }
                          // print error for invalid width
                          catch (Rectangle::WrongWidth &obj)
                          {
                              cout << "Error invalid value for Width " << obj.getVal() << endl;
                              M.addElem(Rectangle(0, 0));
                          }
                      }

                      // print queue elements
                      cout << "All Elements" << endl;
                      for (int i = 0; i < M.getSize(); i++)
                      {
                          cout << "Element-->" << M.getElem() << endl;
                      }

                      check = false;
                  }
              }
          }

    // if user want to use stack
    if(choice == 's') {
        // using stack of intgers
        if (typeOfElements == 1)
        {
            MyStack<int> M(numberOfElements);
            bool check = true;

            while (check)
            {
                for (int i = 0; i < M.getSize(); i++)
                {
                    cout << "Enter num: ";
                    // check if user enter intger value
                    try
                    {
                        cin >> num;
                        if (std::cin.fail())
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            M.addElem(0);
                            throw "Input must be an integer";
                        }

                        M.addElem(num);
                    }
                    // print error for non intger values
                    catch (const char *ptr)
                    {
                        cout << ptr << endl;
                    }
                }
                // print stack elements
                cout << "All Elements" << endl;
                for (int i = 0; i < M.getSize(); i++)
                {
                    cout << "Element-->" << M.getElem() << endl;
                }

                check = false;
            }
        }

        // using stack of strings
        else if (typeOfElements == 2)
        {
            MyStack<string> M(numberOfElements);
            for (int i = 0; i < M.getSize(); i++)
            {
                cout << "Enter string: ";
                cin >> s;
                M.addElem(s);
            }

            cout << "All Elements" << endl;
            for (int i = 0; i < M.getSize(); i++)
            {
                cout << "Element-->" << M.getElem() << endl;
            }
        }
        // using stack of rectangles
        else
        {
            MyStack<Rectangle> M(numberOfElements);
            bool check = true;

            while (check)
            {
                for (int i = 0; i < M.getSize(); i++)
                {
                    cout << "Enter length and width space separated: ";
                    cin >> length >> width;

                    try
                    {
                        M.addElem(Rectangle(length, width));
                    }
                    // catching invalid length
                    catch (Rectangle::WrongLength &obj)
                    {
                        cout << "Error invalid value for length " << obj.getVal() << endl;
                        M.addElem(Rectangle(0, 0));
                    }
                    // catching invalid width
                    catch (Rectangle::WrongWidth &obj)
                    {
                        cout << "Error invalid value for Width " << obj.getVal() << endl;
                        M.addElem(Rectangle(0, 0));
                    }
                }

                // print stack elements
                cout << "All Elements" << endl;
                for (int i = 0; i < M.getSize(); i++)
                {
                    cout << "Element-->" << M.getElem() << endl;
                }

                check = false;
            }
        }
    }

       return 0;
}







