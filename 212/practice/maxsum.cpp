#include<iostream>
using namespace std;

const int N = 1000000;
int A[N];

//return max sum of any aubarray in A[start...end]
int solve(int *A, int start, int end)
{
  if (start == end)
	{
	return A[start];
  	}
  int mid = (start + end) / 2;
  int sol1 = solve(A, start, mid);
  int sol2 = solve(A, mid+1, end);
  int prefix = A[mid + 1];
  int runningsum = A[mid + 1];
  for(int i = mid+2; i <= end; i++)
	{
	runningsum += A[i];
	if(runningsum > prefix)
		{
		prefix = running_sum;
		}
	}
  int suffix = A[mid];
  runningsum = A[mid + 1];
  for(i = mid-1; i >= start; i--)
        {
        runningsum += A[i];
        if(runningsum > suffix)
                {
                suffix = runningsum;
                }
        }
  int sol3 = prefix + suffix;
  return max(sol1, max(sol2, sol3);
}

int main(void)
{
  for (int i = 0; i < N; i++) cin >> A[i];
  cout << solve(A, 0, N-1) << "\n";
  return 0;
}
