#include <iostream>
#include <vector>
#include <cmath>
const int MAX_N = 1e9;
using namespace std;

int vec[MAX_N];

int getmax(int *a, int *en, int n) {
	int res = a[0];
	for(int *ptr = a;ptr != en; ptr++) {
		if(res < *ptr)
			res = *ptr;
	}
	return res;
}

int getmaxradix(int key) {
	int res = 1;
	while(1) {
		if(key / 10 == 0) {
			break;
		}else {
			key /= 10;
			res++;
		}
	}
	return res;
}

void countsort(int *a, int *en, int n, int exp) {
	if(exp <= 0 || n <= 1) return;
	int result[n], counter[11] = {0}, counter_cpy[11] = {0};
	for(int i=0;i<n;i++) {
		counter[(a[i]/exp)%10]++;
	}

	vector<int> wid;
	for(int i=0;i<10;i++) {
		if(counter[i] != counter[i+1])
			wid.push_back(i);
	}
	for(int i=1;i<10;i++) {
		counter[i] += counter[i-1];
	}
	for(int i=0;i<10;i++) {
		counter_cpy[i] = counter[i];
	}

	for(int i=n-1;i>=0;i--) {
		result[counter[(a[i]/exp)%10] - 1] = a[i];
		counter[(a[i]/exp)%10]--;
	}

	for(int i=0;i<n;i++) {
		a[i] = result[i];
	}
	
	int before = 0;
	int now = counter_cpy[wid[0]];
	for(int i=0;i<wid.size();i++) {
		countsort(a+before, a+now, now - before, exp/10);
		if(i+1==wid.size()) break;
		before = counter_cpy[wid[i]];
		now = counter_cpy[wid[i+1]];
	}
}

void radix_sort(int *a, int *en, int n) {
	int max = getmax(a, en, n);
	int maxradix = getmaxradix(max);
	countsort(a, en, n, pow(10, maxradix-1));
}

int main() {
	int n;
	cout << "Input the number of elements to be sorted: ";
	cin >> n;
	for(int i=0;i<n;i++) cin >> vec[i];
	cout << "Before sorting" << endl;
	for(int i=0;i<n;i++) {
		printf("%d%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
	radix_sort(vec, vec+n, n);
	cout << "After sorting" << endl;
	for(int i=0;i<n;i++) {
		printf("%d%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
}
