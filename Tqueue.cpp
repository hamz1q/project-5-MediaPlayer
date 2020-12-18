#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

template <class T, int N> //T is the data type and N is the container's capacity
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //Name: Copy Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N>& x ); //Copy Constructor
  //Name: Destructor
  //Desc: Empties m_data
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: Enqueue
  //Desc: Adds item to the back of queue (checks for capacity)
  //Precondition: Existing Tqueue
  //Postcondition: Size is incremented if successful and m_back increases
  void Enqueue(T data); //Adds item to queue (to back)
  //Name: Dequeue
  //Desc: Removes item from queue (from front)
  //      **Automatically moves all data to start at index 0 (using loop**
  //Precondition: Existing Tqueue
  //Postcondition: Size is decremented if successful.
  //               Data in m_front is removed and remaining data is move to the front.
  void Dequeue();
  //Name: Sort
  //Desc: Sorts the contents of the Tqueue (any algorithm you like)
  //Precondition: Existing Tqueue
  //Postcondition: Contents of Tqueue is sorted (low to high)
  void Sort();
  //Name: IsEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int IsEmpty(); //Returns 1 if queue is empty else 0
  //Name: IsFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int IsFull(); //Returns 1 if queue is full else 0
  //Name: Size
  //Desc: Returns size of queue
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue (difference between m_back and m_front)
  int Size();
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=( Tqueue<T,N> y); //Overloaded assignment operator for queue
  //Name: At
  //Precondition: Existing Tqueue with index starting at 0
  //Postcondition: Returns object from Tqueue using At() 
  T& At(int x);//Returns data from queue at location
  //Name: DisplayAll()
  //Precondition: Existing Tqueue (not used in MediaPlayer)
  //Postcondition: Outputs all items in Tqueue (must be cout compatible -
  //               may require overloaded << in object)
  void DisplayAll();
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue (for this project should always remain at 0)
  int m_back; //Back of the queue (will increase as the size increases)
};

//**** Add class definition below ****

//Name: Tqueue - Default Constructor
//Precondition: None (Must be templated)
//Postcondition: Creates a queue using dynamic array
template <class T, int N>
Tqueue<T, N>::Tqueue()
  
{
  //dynamically allocating memory 
  m_data = new T[N];
  //m_front always is 0, m_back is -1 initially  
  m_front = 0;
  m_back = -1;
}

//Name: Copy Constructor
//Precondition: Existing Tqueue
//Postcondition: Copies an existing Tqueue
template <class T, int N>
Tqueue<T, N>::Tqueue( const Tqueue<T,N>& x )
{
  m_data = new T[N];
  //copying data from original
  m_front = x.m_front;
  m_back = x.m_back;

  for(int i = 0; i < N; i++)
    {
      m_data[i] = x.m_data[i];
    }
}

//Name: Destructor
//Desc: Empties m_data
//Precondition: Existing Tqueue
//Postcondition: Destructs existing Tqueue
template <class T, int N>
Tqueue<T, N>::~Tqueue()
{
  delete [] m_data;
}

//Name: Enqueue
//Desc: Adds item to the back of queue (checks for capacity)
//Precondition: Existing Tqueue
//Postcondition: Size is incremented if successful and m_back increases
template <class T, int N>
void Tqueue<T, N>::Enqueue(T data)
{ 
  if(IsFull())
    {
      cout << "Queue full! Cannot add anything else." << endl;
    }
  else
    {
      //incrementing back as items are added 
      m_back += 1;
      m_data[m_back] = data;
    }
}

//Name: Dequeue
//Desc: Removes item from queue (from front)
//      **Automatically moves all data to start at index 0 (using loop**
//Precondition: Existing Tqueue
//Postcondition: Size is decremented if successful.
//               Data in m_front is removed and remaining data is move to the front.
template <class T, int N>
void Tqueue<T,N>::Dequeue()
{
  if(IsEmpty())
    {
      cout << "Nothing to remove! Queue is empty" << endl;
    }
  else
    {
      //overwriting the elements 
      for(int i = 0; i < Size(); i++)
	{
	  m_data[i] = m_data[i+1];
	}
    }
  m_back -= 1;
}

//Name: Sort
//Desc: Sorts the contents of the Tqueue (any algorithm you like)
//Precondition: Existing Tqueue
//Postcondition: Contents of Tqueue is sorted (low to high)
template <class T, int N>
void Tqueue<T, N>::Sort()
{  
  bool swap;
  for (int i = 0; i < Size()-1; i++)
    {
      swap = false;
      for (int j = 0; j < Size()-i-1; j++)
	{
	  if(*m_data[j] < *m_data[j+1])
	    {
	      //bubble sort, comapring the first item with the next and swapping if <
	      T *first = &m_data[j];
	      T *second = &m_data[j+1];
	      T temp = *first; 
	      *first = *second;
	      *second = temp;
	      swap = true;
	    }
	}
      
      if (swap == false)
	break;
    }  
}

//Name: IsEmpty
//Precondition: Existing Tqueue
//Postcondition: Returns 1 if queue is empty else 0
template <class T, int N>
int Tqueue<T, N>::IsEmpty()
{
  if(m_back == -1)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

//Name: IsFull
//Precondition: Existing Tqueue
//Postcondition: Returns 1 if queue is full else 0
template <class T, int N>
int Tqueue<T, N>::IsFull()
{
  //N-1 is max index 
  if(m_back == N - 1)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

//Name: Size
//Desc: Returns size of queue
//Precondition: Existing Tqueue
//Postcondition: Returns size of queue (difference between m_back and m_front)
template <class T, int N>
int Tqueue<T, N>::Size()
{
  int size = m_back - m_front;
  return size + 1;
}

//Name: Overloaded assignment operator
//Precondition: Existing Tqueue
//Postcondition: Sets one Tqueue to same as a second Tqueue using =
template <class T, int N>
Tqueue<T,N>& Tqueue<T,N>::operator=( Tqueue<T,N> y)
{
  if(this != &y)
    {
      delete [] m_data;  
      m_data = new T[N];
      m_front = 0;
      m_back = y.m_back;
      
      for(int i = 0; i < N; i++)
	{
	  m_data[i] = y.m_data[i];
	}
    }
  return *this;
}

//Name: At
//Precondition: Existing Tqueue with index starting at 0
//Postcondition: Returns object from Tqueue using At()
template <class T, int N>
T& Tqueue<T, N>::At(int x)
{
  return m_data[x];
}

//Name: DisplayAll()
//Precondition: Existing Tqueue (not used in MediaPlayer)
//Postcondition: Outputs all items in Tqueue (must be cout compatible -
//               may require overloaded << in object)
template <class T, int N>
void Tqueue<T, N>::DisplayAll()
{
  if(IsEmpty())
    {
      cout << "No items to display!" << endl;
    }
  else
    {
      for(int i = 0; i < Size(); i++)
	{
	  cout << m_data[i] << endl;

	}
    }
}


#endif
