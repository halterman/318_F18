// Adapted from https://msdn.microsoft.com/en-us/library/hh873179.aspx

#include <ppl.h>          // Parallel Patterns Library
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <unordered_map>

using std::unordered_map, std::string, std::vector, std::pair;
using concurrency::parallel_transform, concurrency::parallel_reduce;

class MapFunc {
public:
	unordered_map<string, size_t> operator()(vector<string>& elements) const {
		unordered_map<string, size_t> m;
		for_each(begin(elements), end(elements),
			[&m](const string& elem) { m[elem]++; });
		return m;
	}
};


struct ReduceFunc {
	unordered_map<string, size_t> operator() (
		const unordered_map<string, size_t>& x,
		const unordered_map<string, size_t>& y) const {
		unordered_map<string, size_t> ret(x);
		for_each(begin(y), end(y), [&ret](const std::pair<string, size_t>& pr) {
			auto key = pr.first;
			auto val = pr.second;
			ret[key] += val;
		});
		return ret;
	}
};


int main() {
	// File 1 
	vector<string> v1;
	v1.push_back("word1"); //1 
	v1.push_back("word1"); //2 
	v1.push_back("word2");
	v1.push_back("word3");
	v1.push_back("word4");

	// File 2 
	vector<string> v2;
	v2.push_back("word5");
	v2.push_back("word6");
	v2.push_back("word7");
	v2.push_back("word8");
	v2.push_back("word1"); //3 

	vector<vector<string>> v;
	v.push_back(v1);
	v.push_back(v2);

	vector<unordered_map<string, size_t>> map(v.size());

	// The Map operation
	MapFunc mapper;
	parallel_transform(begin(v), end(v), begin(map), mapper);

	// The Reduce operation 
	ReduceFunc reducer;
	unordered_map<string, size_t> result = parallel_reduce(
		begin(map), end(map), unordered_map<string, size_t>(), reducer);

	std::cout << "\"word1\" occurs " << result["word1"] << " times. \n";
}
/* Output:
"word1" occurs 3 times.
*/
