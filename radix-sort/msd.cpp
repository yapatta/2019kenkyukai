#include <iostream>
#include <vector>
#include <cmath>
#include <random>
using namespace std;
using ll = long long;
const ll MAX_N = 1e9;

ll vec[MAX_N];

ll getmax(ll *a, ll *en, ll n) {
	ll res = a[0];
	for(ll *ptr = a;ptr != en; ptr++) {
		if(res < *ptr)
			res = *ptr;
	}
	return res;
}

ll getmaxradix(ll key) {
	ll res = 1;
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

void countsort(ll *a, ll *en, ll n, ll exp) {
	if(exp <= 0 || n <= 1) return;
	ll result[n], counter[11] = {0}, counter_cpy[11] = {0};
	for(ll i=0;i<n;i++) {
		counter[(a[i]/exp)%10]++;
	}

	vector<ll> wid;
	for(ll i=0;i<10;i++) {
		if(counter[i] != counter[i+1])
			wid.push_back(i);
	}
	for(ll i=1;i<10;i++) {
		counter[i] += counter[i-1];
	}
	for(ll i=0;i<10;i++) {
		counter_cpy[i] = counter[i];
	}

	for(ll i=n-1;i>=0;i--) {
		result[counter[(a[i]/exp)%10] - 1] = a[i];
		counter[(a[i]/exp)%10]--;
	}

	for(ll i=0;i<n;i++) {
		a[i] = result[i];
	}
	
	ll before = 0;
	ll now = counter_cpy[wid[0]];
	for(ll i=0;i<wid.size();i++) {
		countsort(a+before, a+now, now - before, exp/10);
		if(i+1==wid.size()) break;
		before = counter_cpy[wid[i]];
		now = counter_cpy[wid[i+1]];
	}
}

void radix_sort(ll *a, ll *en, ll n) {
	ll max = getmax(a, en, n);
	ll maxradix = getmaxradix(max);
	countsort(a, en, n, pow(10, maxradix-1));
}

int main() {
	ll n;
	cout << "Input the number of elements to be sorted: ";
	cin >> n;
	
	random_device rnd;
	mt19937 mt(rnd());
	for(ll i=0;i<n;i++) vec[i] = mt();
	cout << "Before sorting (msd radix sort)" << endl;
	/*
	for(ll i=0;i<n;i++) {
		printf("%lld%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
	*/

	radix_sort(vec, vec+n, n);
	cout << "finished" << endl;

	for(ll i=0;i<n;i++) vec[i] = mt();
	cout << "Before sorting (quick sort)" << endl;
	sort(vec, vec+n);
	cout << "finished" << endl;

	/*
	cout << "After sorting" << endl;
	for(ll i=0;i<n;i++) {
		printf("%lld%c", vec[i], (i==n-1) ? '\n' : ' ');
	}
	*/
}
