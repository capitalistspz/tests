using System;

namespace starter
{
    //Queue structure. Can only be modified by 'popping' the first object in the queue
    class queue<T>
    {
        //Creates a queue of size q_size
        public queue(UInt32 q_size) {
            realLast = (q_size == 0) ? 10 : q_size * 2;
            last = q_size;
            arr = new T[realLast];
            start = 0;
        }
        private UInt32 realLast, last, start;
        private T[] arr;
        public UInt32 Size { get => last-start; }
        public T peek_front() { return arr[0]; }
        public T peak_back() { return arr[last-1]; }
        public void enqueue(T element) { 
            if (last < realLast-1)
                // End position assigned to new element and end incremented;
                arr[last++] = element;
                // Time complexity: n + 1 + 1 + 1 - O(n) // Space complexity: O(1)
            else if (start > 0)                     
            {
                // If the beginning of the accessible part of the array is not default (and the end pos == real end pos), 
                // all elements are moved forward (toward 0) so that the first element is at arr[0]
                // new element is put at the last indexable position of the array, and the last position is incremented
                // avoids allocating more memory through array creation

                for (uint i = 0; i < (last - start); ++i)
                    arr[i] = arr[i + start];
                last -= start; start = 0;
                arr[last++] = element;
            } // Time complexity: n + 1 + 1 + 1 - O(n) // Space complexity: O(1)
            else
            {
                //  Array is expanded by creating a new, larger array containing all the old values and assigning to the original array.
                realLast = last + 1 * 2;
                T[] newArr = new T[realLast];
                for (uint i = 0; i < last; ++i)
                    newArr[i] = arr[i];
                newArr[last++] = element;
                arr = newArr;
            } // Time complexity: 1 + 1 + 1 + n + 1 + 1 - O(n)
              // Space complexity: n * 2 + 1 - O(n)
        }
        //  If the first position is the same as the last position, there are obviously no elements between them.
        public bool isEmpty { get => last == start; }
        public T dequeue()
        {
            if (isEmpty) {Console.WriteLine("Queue is empty!"); return default(T); }
            T front = arr[start++];
            return front;
        }
        //  Normal indexer
        /*public T this[int i]
        {
            get {
                if (i > -1 && i < (last - start))
                    return arr[start + i];
                else
                    throw new ArgumentException("Index is out of range:" + i.ToString());
            }
        }*/


    }

    class Program
    {
        static void Main(string[] args)
        {
            queue<int> Q = new queue<int>(0);
            Console.WriteLine(Q.Size);
            Q.enqueue(1);
            Q.enqueue(2);
            Q.enqueue(8);
            Q.enqueue(4);
            Q.enqueue(1);
            Q.enqueue(2);
            Q.enqueue(8);
            Q.enqueue(4);
            Q.enqueue(1);
            Q.enqueue(2);
            Q.enqueue(8);
            Q.enqueue(4);

            Console.WriteLine("==========================");
            while (!Q.isEmpty)
                Console.WriteLine(Q.dequeue());
            Q.enqueue(1);
            Q.enqueue(2);
            Q.enqueue(8);
            Q.enqueue(4);
            Q.enqueue(1);
            Q.enqueue(2);
            Q.enqueue(8);
            Q.enqueue(4);
            Q.enqueue(1);
            Q.enqueue(2);
            Q.enqueue(8);
            Q.enqueue(4);
            Console.ReadKey();

        }
    }
}
