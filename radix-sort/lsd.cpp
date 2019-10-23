#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
using ll = long long;
const ll MAX_N = 1e9;
#define KEY 16
ll vec[MAX_N];

ll getmax(ll *a, ll n) {
	ll res = a[0];
	for(ll x=1;x<n;x++) {
		res = (res < a[x]) ? a[x] : res;
	}
	return res;
}

void countsort(ll *a, ll n, ll exp) {
	ll result[n], i, count[KEY] = {0};

	for(ll i=0;i<n;i++) {
		count[(a[i] / exp) % KEY]++;	
	}

	for(i=1;i<KEY;i++) {
		count[i] += count[i-1];
	}

	for(i=n-1;i>=0;i--) {
		result[count[(a[i] / exp) % KEY] - 1] = a[i];
		count[(a[i] / exp) % KEY]--;
	}
	for(i=0;i<n;i++) {
		a[i] = result[i];
	}
}

void radix_sort(ll *a, ll n) {
	ll exp, max;
	max = getmax(a, n);
	for(exp=1;max/exp>0;exp*=KEY) {
		countsort(a , n , exp);
	}
}

int main() {
	ll n;
	cout << "Input the number of elements to be sorted: ";
	cin >> n;

	random_device rnd;
	mt19937 mt(rnd());

	for(ll i=0;i<n;i++) vec[i] = mt();
	cout << "Before sorting (quick sort)" << endl;
	for(ll i=0;i<n;i++) {
		printf("%lld%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
	sort(vec, vec+n);
	cout << "finished" << endl;
	for(ll i=0;i<n;i++) {
		printf("%lld%c", vec[i], (i==n-1) ? '\n' : ' ');
	}

	for(ll i=0;i<n;i++) vec[i] = mt();
	cout << "Before sorting (lsd radix sort)" << endl;
	for(ll i=0;i<n;i++) {
		printf("%lld%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
	radix_sort(vec, n);
	cout << "finished" << endl;
	for(ll i=0;i<n;i++) {
		printf("%lld%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
}

