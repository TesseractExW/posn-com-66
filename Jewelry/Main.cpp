#include <iostream>
int main()
{
	int n;
	std::cin >> n;
	char* str = new char[n];
	std::cin >> str;

	unsigned long int sum = 0;
	// O(n^4) :skull:
	for (int low = 0;low < n;low++) {
		for (int high = low;high < n;high++) {
			int max_ = 0;
			int count = 0;
			for (int i = low;i <= high;i++) {
				if (str[i] == 'T') {
					count++;
				}
				else {
					count = 0;
				}
				max_ = std::max(max_, count);
			}
			sum += max_;
		}
	}
	std::cout << sum << std::endl;
	return 0;
}