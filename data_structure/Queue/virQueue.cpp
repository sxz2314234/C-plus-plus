template<class T>
class queue
{
    public:
    virtual ~queue(){};
    virtual int size()const=0;
    virtual bool empty()const=0;
    virtual bool full()const=0;
    virtual void pop(T&)=0;
    virtual void push(const T&)=0;
};