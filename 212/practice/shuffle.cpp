#include <iostream>
using namespace std;

const int N = 16;
int A[N];

void shuffle(int *A, int start, int end)
{
  if(end == start + 1) return;
  int mid = (start + end) / 2;
  int quarter = (mid + start) / 2 + 1;
  mid++;
  for (int i = 0; i < (end - start + 1) / 4; i++)
`	{
	swap(A[quarter + i], A[mid + i]);
	}
  shuffle(A, start, mid - 1);
  shuffle(A, mid, end);
}

int main (void)
{
  for (int i = 0; i < N; i++)
	{
	cin >> A[i];
	}
  shuffle(A, 0, N-1);

  for(i = 0; i < N; i++)
	{
	cout << A[i] << "\n";
	}
  return 0;
}
