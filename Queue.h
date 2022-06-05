#ifndef Queue_h
#define Queue_h
#include <iostream>
using namespace std;

const int n = 100;

template <typename T>
class Queue {
private:
    T queue[n];
    int front = -1, rear = -1;
public:
    void insert(T value) {
        if (rear == n - 1) {
            cout << "Overflow" << endl;
            return;
        }
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = value;
    }
    void del() {
        if (front == -1 || front > rear) {
            cout << "Underflow" << endl;
            return;
        }
        else {
            front++;
        }
    }
    void display() {
        if (front == -1) {
            return;
        }
        for (int i = front; i <= rear; i++) {
            cout << queue[i] << " ";
        }
        cout << endl;
    }
    
    T firstElement() { //will always have at least one element in queue 
        return queue[front];
    }
    bool isEmpty() {
        return (front == -1 || front > rear);
    }
};

#endif
