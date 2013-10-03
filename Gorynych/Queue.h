#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <exception>

class Queue_exceptin: std::exception
{
     const char* what() const throw ()
     {
         return "Read from empty queue!\n";
     };
};

template<typename T>
class Queue
{
public:
    Queue();
    ~Queue();
    void push_back(const T &new_data);
    void pop_front();
    T on_front() const;
    bool is_empty() const;
    void clear();
private:
    struct List
    {
        List(T new_data);
        ~List();
        T data;
        List *next;
    }*first,*end;
};

template<typename T>
Queue<T>::Queue():
    first(0),end(0)
{
}

template<typename T>
Queue<T>::~Queue()
{
    clear();
}

template<typename T>
Queue<T>::List::List(T new_data):
    data(new_data), next(0)
{
}

template<typename T>
Queue<T>::List::~List()
{
    next=0;
}

template<typename T>
void Queue<T>::push_back(const T &new_data)
{
    List *p = new List(new_data);

    if(first)
    {
        end->next=p;
        end=p;
    }
    else
    {
        end=first=p;
    }
    p = 0;
}

template<typename T>
void Queue<T>::pop_front()
{
    if(first)
    {
        List *p;
        p = first;
        first = first->next;
        if(!first)
            end=0;
        p->next = 0;
        delete p;
        p = 0;
    }
    else throw Queue_exceptin();
}

template<typename T>
T Queue<T>::on_front() const
{
    if(is_empty())
        throw Queue_exceptin();
    return first->data;
}

template<typename T>
bool Queue<T>::is_empty() const
{
    return first==0;
}

template<typename T>
void Queue<T>::clear()
{
    while(first)
    {
        List *p;
        p=first;
        first=first->next;
        delete p;
        p=0;
    }
}

#endif // QUEUE_H_INCLUDED
