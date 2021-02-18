#ifndef Queue_h
#define Queue_h

#define MaxQueueLength 35
#define debug false

#include "Arduino.h"

template <class T>
class Queue {
  private:
    int front1, rear, count1;
    T qlist[MaxQueueLength];
  public:
    //constructor
    Queue(void) {
      front1 = 0;
      rear = 0;
      count1 = 0;
      //qlist = nullptr;
    }

    //operators
    //test
    bool QLenght(void) {
      return count1;
    }
    bool QEmpty(void) {
      return (count1 == 0);
    }
    bool QFull(void) {
      return (count1 == MaxQueueLength);
    }
    //modify
    void Qinsert(const T& item) {
      if (QFull()) {
        Serial.println("Queue Owerflow");
        return;
      }
      count1++;
      qlist[rear] = item;
      rear = (rear + 1) % MaxQueueLength;
    }

    T Qdelete(void) {
      T temp;
      if (QEmpty()) {
        Serial.println("Deleting from empty queue");
        return NULL;
      }
      temp = qlist[front1];
      count1--;
      front1 = (front1 + 1) % MaxQueueLength;
      return temp;
    }
    void ClearQueue(void) {
      while (!this->QEmpty()) {
        if (this->QFront() != NULL) {
          (this->Qdelete()).~T();//destruct
        }
        else {
          count1--;
          front1 = (front1 + 1) % MaxQueueLength;
        }
      }

    };
    //access
    T QFront(void) const {
      return qlist[front1];
    }
};

#endif
