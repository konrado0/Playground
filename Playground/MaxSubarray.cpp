#include "stdafx.h"

struct MaxSubarrayDesc {
	size_t l;
	size_t r;
	int sum;

	MaxSubarrayDesc(size_t l, size_t r, int sum) : l(l), r(r), sum(sum) {}

	bool operator<(MaxSubarrayDesc& a) {
		return this->sum < a.sum;
	}

	inline void Update(size_t l, size_t r, int sum) {
		this->l = l;
		this->r = r;
		this->sum = sum;
	}
};

MaxSubarrayDesc BruteMaxSubarray(std::vector<int>& array)
{
	size_t l=0, r=0;
	int max_sum = INT_MIN;

	for (size_t i = 0; i < array.size(); i++) {
		int sum = 0;
		for (size_t j = i; j < array.size(); j++) {
			sum += array[j];
			if (sum > max_sum) {
				max_sum = sum;
				l = i;
				r = j;
			}
		}
	}

	return MaxSubarrayDesc(l, r, max_sum);
}

MaxSubarrayDesc MaxCrossingArray(std::vector<int>& array, size_t l, size_t mid, size_t r)
{
	int suml = array[mid], ml=mid;
	int sum = suml;
	for(int i=mid-1; i>=0; i--) {
		sum += array[i];
		if(sum >= suml) {
			suml = sum;
			ml = i;
		}
	}

	int sumr = array[mid+1], mr = mid+1;
	sum = sumr;
	for (size_t i = mid + 2; i <= r; i++) {
		sum += array[i];
		if (sum >= sumr) {
			sumr = sum;
			mr = i;
		}
	}

	return MaxSubarrayDesc(ml, mr, suml+sumr);
}

MaxSubarrayDesc DCMaxSubarray(std::vector<int>& array, size_t l, size_t r)
{
	if (l == r)
		return MaxSubarrayDesc(l, r, array[l]);

	size_t mid = (l + r) / 2;

	MaxSubarrayDesc rl = DCMaxSubarray(array, l, mid);
	MaxSubarrayDesc rr = DCMaxSubarray(array, mid+1, r);
	MaxSubarrayDesc rm = MaxCrossingArray(array, l, mid, r);

	if (rr < rl)
		if(rm < rl) return rl;
		else return rm;
	if (rm < rr) return rr;
	return rm;
}

MaxSubarrayDesc LinearMaxSubarray(std::vector<int>& array)
{
	MaxSubarrayDesc max_ending_here(0, 0, array[0]);
	MaxSubarrayDesc max_so_far(0, 0, array[0]);

	for (size_t i = 1; i < array.size(); i++) {
		if (array[i] > max_ending_here.sum + array[i])
			max_ending_here.Update(i, i, array[i]);
		else
			max_ending_here.Update(max_ending_here.l, i, max_ending_here.sum+array[i]);
		
		if (max_so_far < max_ending_here)
			max_so_far = max_ending_here;
	}
	return max_so_far;
}

void TestMaxSubarray()
{
	std::vector<int> v1 = { 1, 2, 3, 4 };
	std::vector<int> v2 = { -1, -2, -3, -4 };
	std::vector<int> v3 = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	std::vector<int> v4 = { 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };


	MaxSubarrayDesc res = BruteMaxSubarray(v1);
	assert(res.l == 0 && res.r == 3 && res.sum == 10);
	res = DCMaxSubarray(v1, 0, v1.size()-1);
	assert(res.l == 0 && res.r == 3 && res.sum == 10);

	res = BruteMaxSubarray(v2);
	assert(res.l == 0 && res.r == 0 && res.sum == -1);
	res = LinearMaxSubarray(v2);
	assert(res.l == 0 && res.r == 0 && res.sum == -1);
	res = DCMaxSubarray(v2, 0, v2.size() - 1);
	assert(res.l == 0 && res.r == 0 && res.sum == -1);

	res = BruteMaxSubarray(v3);
	assert(res.l == 7 && res.r == 10 && res.sum == 43);
	res = LinearMaxSubarray(v3);
	assert(res.l == 7 && res.r == 10 && res.sum == 43);
	res = DCMaxSubarray(v3, 0, v3.size() - 1);
	assert(res.l == 7 && res.r == 10 && res.sum == 43);

	res = LinearMaxSubarray(v4);
	assert(res.l == 0 && res.r == 10);
}