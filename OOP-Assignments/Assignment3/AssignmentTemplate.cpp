
template<class typeName>
class MyList{
private:
    typeName *elems;
    int itsSize;
public:
    MyList(int s){
        itsSize = s;
        elems = new typeName[itsSize];
    }
    virtual ~MyList(){
        delete []elems;
    }
    int getSize()const{
        return itsSize;
    }
    // pure virtual functions
    virtual void addElem(typeName) = 0;
    virtual typeName getElem() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void clearItems() = 0;


};


