#ifndef Stack_h
#define Stack_h

#define MaxStackLength 5
#define debug false

#include "Arduino.h"

template <class T>
class Stack {
  private:
    int top;
    byte count;
    T slist[MaxStackLength];
  public:
    //constructor
    Stack(void) {
      top = -1;
      count = 0;
    }

    //operators
    //test
    bool SEmpty(void) {return count == 0;}
    
    //modify
    void Spush(T& item) {
      if (top>MaxStackLength-1) {
        Serial.println("Stack Owerflow");
        return;
      }
      top++;
      slist[top] = item;
      count++;
    }

    T Spop(void) {
      T temp;
      if (SEmpty()) {
        Serial.println("Deleting from empty Stack");
        return NULL;
      }
      temp = slist[top];
      count--;
      top--;
      return  temp;
    }
};

#endif
