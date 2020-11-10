// Challenge 04: kth smallest numbers
// Name: Logan Tillman
// Date: February 10 2020

/* This program will take an array, check if it's a max heap, 
 * and find the kth smallest element of the array and return it */

#include <iostream>
#include <vector>

using namespace std;

// Checks if the vector is a max heap
bool Is_Max_Heap(const vector <int> &numbers);

// Class to host the heap functions
class PQueueHeap
{
  public:
    int Pop();
    vector <int> h;
    void Percolate_Down(int index);
};

int main(int argc, char *argv[]) 
{
	PQueueHeap minheap;
	vector <int> numbers;
	unsigned int n, k; 
	int temp, rv;

	while(cin >> n >> k)
	{
		if (n < 0)
			return -1;
		if (k < 0)
			return -1;

		// Pushing elements into the vector (used for max heap
		for (unsigned int i = 0; i < n; i++)
		{
			cin >> temp;
			numbers.push_back(temp);
		}

		// Copying the vector into the class (used for min heap)
		minheap.h = numbers;

		// Traversing backwards through the vector and percolating down
		for (unsigned int i = 1; i <= minheap.h.size(); i++)
			minheap.Percolate_Down(minheap.h.size() - i);
	
		// Poping the vector k times, but saving the kth pop
		for (unsigned int i = 1; i <= k; i++)
		{
			if (i == k)
				rv = minheap.Pop();
			else
				minheap.Pop();
		}
	
		// Checking if the original vector is a max heap and printing the kth smallest element
		if (Is_Max_Heap(numbers) == true)
			cout << "Y  " << rv << '\n';
		else
			cout << "N  " << rv << '\n';

		// Clearing the vector
		numbers.clear();
	}
}

bool Is_Max_Heap(const vector <int> &numbers)
{
	unsigned int lc, rc;
	bool maxheap;

	// Initializing maxheap
	maxheap = true;

	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		lc = 2 * i + 1;
		rc = lc + 1;

		// Checking to see if both the lc and rc are less than the parent
		if (lc < numbers.size())
			if (numbers[i] < numbers[lc])
				maxheap = false;

		if (rc < numbers.size())
			if (numbers[i] < numbers[rc])
				maxheap = false;
		
		// Returning false if it's not a max heap
		if (maxheap == false)
			return false;
	}

	// Otherwise, it will return true
	return true;
}

int PQueueHeap::Pop() 
{
  int retval;
  
  if (h.empty()) {
    cerr << "Error: Called Pop on an empty PQueue\n";
    exit(1);
  }
  retval = h[0];
  h[0] = h[h.size()-1];
  h.pop_back();
  if (h.size() == 0) return retval;
  Percolate_Down(0);
  return retval;
}

void PQueueHeap::Percolate_Down(int index)
{
  int lc, rc;
  double tmp;

  /* lc is the left child, and
     rc is the right child. */

  while (1) {                
    lc = index*2+1;
    rc = lc+1;
   
    /* If index is on the bottom of the heap,
       then return, because we can't 
       percolate any more. */

    if (lc >= (int) h.size()) return;

    /* With this code, either there is no
       right child, or the left child is
       smaller than the right child.  In 
       this case, you need to compare the
       element at index with the left child. */

    if (rc == (int) h.size() || h[lc] <= h[rc]) {
      if (h[lc] < h[index]) {
        tmp = h[lc];
        h[lc] = h[index];
        h[index] = tmp;
        index = lc;
      } else {
        return;
      }

    /* Otherwise, we compare the element at
       index with the right child. */

    } else if (h[rc] < h[index]) {
      tmp = h[rc];
      h[rc] = h[index];
      h[index] = tmp;
      index = rc;
    } else {
      return;
    }
  }
}
