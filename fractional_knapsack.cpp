#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using std::vector;

class KnapsackItem {

  private:
    int itemValue;
    int itemWeight;
    double vpw;

  public:

    KnapsackItem(int value, int weight, double valuePerWeight) {
      itemValue = value;
      itemWeight = weight;
      vpw = valuePerWeight;
    }

    int getValue() {
      return itemValue;
    }
    int getWeight() {
      return itemWeight;
    }
    double getVPW() {
      return vpw;
    }
};

bool compare(KnapsackItem s1, KnapsackItem s2) {
  return s1.getVPW() > s2.getVPW();
}


double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  int numOfItems = weights.size();
  vector<KnapsackItem> items;
  double vpw = 0.00;


  // first, initialize a vector of KnapsackItem objects
  for (int i = 0; i < numOfItems; i++) {
    vpw = (double)values[i]/(double)weights[i];
    items.push_back(KnapsackItem(values[i], weights[i], vpw));
  }


  // order the items vector by value per weight unit
  std::sort(items.begin(), items.end(), compare);

  // then try to populate knapsack with each item
  // check each time if item must be split

  for (int i = 0; i < items.size(); i++) {
    std::cout << items[i].getVPW() << std::endl;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
