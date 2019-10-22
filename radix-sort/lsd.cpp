#include <iostream>
#include <vector>
using namespace std;

int getmax(const vector<int> &a, int n) {
	int res = a[0];
	for(int x=1;x<n;x++) {
		res = (res < a[x]) ? a[x] : res;
	}
	return res;
}

void countsort(vector<int> &a, int n, int exp) {
	int result[n], i, count[10] = {0};

	for(int i=0;i<n;i++) {
		count[(a[i] / exp) % 10]++;	
	}

	for(i=1;i<10;i++) {
		count[i] += count[i-1];
	}

	for(i=n-1;i>=0;i--) {
		result[count[(a[i] / exp) % 10] - 1] = a[i];
		count[(a[i] / exp) % 10]--;
	}
	for(i=0;i<n;i++) {
		a[i] = result[i];
	}
}

void radix_sort(vector<int> &a, int n) {
	int exp, max;
	max = getmax(a, n);
	for(exp=1;max/exp>0;exp*=10) {
		countsort(a , n , exp);
	}
}

int main() {
	int n;
	cout << "Input the number of elements to be sorted: ";
	cin >> n;
	vector<int> vec(n);
	for(int i=0;i<n;i++) cin >> vec[i];
	cout << "Before sorting" << endl;
	for(int i=0;i<n;i++) {
		printf("%d%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
	radix_sort(vec, n);
	cout << "After sorting" << endl;
	for(int i=0;i<n;i++) {
		printf("%d%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
}
