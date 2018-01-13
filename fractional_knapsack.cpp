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
  int allValues = 0;
  int allWeights = 0;

  // first, initialize a vector of KnapsackItem objects
  for (int i = 0; i < numOfItems; i++) {
    items.push_back(KnapsackItem(values[i], weights[i], (double)values[i]/(double)weights[i]));
    allValues += values[i];
    allWeights += weights[i];
  }

  // if there is more capacity than total item weights, you can fit all items
  if (allWeights <= capacity) {
    return allValues;
  }

  // order the items vector by value per weight unit
  std::sort(items.begin(), items.end(), compare);

  // then try to populate knapsack with each item
  // check each time if item must be split

  int weightSoFar = 0;

  for (int i = 0; i < items.size(); i++) {
    if (weightSoFar + items[i].getWeight() < capacity) {
      weightSoFar += items[i].getWeight();
      value += items[i].getValue();
    } else if (weightSoFar + items[i].getWeight() == capacity) {
      value += items[i].getValue();
      break;
    } else {  // if it's greater, figure out how to fraction the difference and add it
      int weightDelta = capacity - weightSoFar;
      value += items[i].getVPW() * (double)weightDelta;
      break;
    }
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

  std::cout.precision(4);
  std::cout << std::fixed << optimal_value << std::endl;
//  std::cout << std::fixed << std::setprecision(4) << optimal_value << std::endl;
  return 0;
}
