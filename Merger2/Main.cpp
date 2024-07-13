#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Station {
	int distance;
	int count;
};

int main()
{
	// input n ,m & q
	int n, m, q;
	std::cin >> n >> m >> q;

	// input DC AC (distance,count)
	Station* DC_Stations = new Station[n];
	Station* AC_Stations = new Station[m];
	// for dc
	for (int i = 0;i < n;i++) {
		std::cin >> DC_Stations[i].distance;
	}
	for (int i = 0;i < n;i++) {
		std::cin >> DC_Stations[i].count;
	}
	// for ac
	for (int i = 0;i < m;i++) {
		std::cin >> AC_Stations[i].distance;
	}
	for (int i = 0;i < m;i++) {
		std::cin >> AC_Stations[i].count;
	}
	// input question
	std::vector<int*> question;
	for (int i = 0;i < q;i++) {
		int* alpha_beta = new int[3];
		std::cin >> alpha_beta[0] >> alpha_beta[1] >> alpha_beta[2];
		
		question.push_back(alpha_beta);
	}
	// loop through each question
	for (int o = 0;o < q;o++) {
		int alpha = *(question[o]);
		int beta = *(question[o] + 1);
		int slotK = *(question[o] + 2);

		// transform AC_Station to NAC_Station;
		Station* NAC_Stations = new Station[m];
		for (int i = 0;i < m;i++) {
			int new_distance = alpha * AC_Stations[i].distance + beta;

			NAC_Stations[i].distance = new_distance;
			NAC_Stations[i].count = AC_Stations[i].count;
		}
		// merging to R_Map (distance,count);
		std::map<int, int> R_Map;
		for (int i = 0;i < n;i++) {
			int distance = DC_Stations[i].distance;
			R_Map[distance] = DC_Stations[i].count;
		}
		for (int i = 0;i < m;i++) {
			int distance = NAC_Stations[i].distance;
			if (R_Map.find(distance) != R_Map.end()) {
				R_Map[distance] += NAC_Stations[i].count;
			}
			else {
				R_Map[distance] = NAC_Stations[i].count;
			}
		}
		// find the slot k
		int min_range = 1;
		int max_range = 0;
		for (auto const& p : R_Map) {
			max_range += p.second;
			if (min_range <= slotK && slotK <= max_range) {
				std::cout << p.first << std::endl;
				break;
			}
			min_range += p.second;
		}
		// clear for new question
		R_Map.clear();
		delete[] NAC_Stations;
	}
	
	return 0;
}