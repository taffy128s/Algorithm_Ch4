#include <cstdio>
#include <algorithm>
#include <ctime>
//#define BRUTE

struct Item {
    Item(int a, int b, int c) {
        left = a;
        right = b;
        max = c;
    }
    int left, right, max;
};

int arr[1000] = {0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
int temparr[1000], size = 40; //The new crossover point is near 40.

Item bruteForce(int l, int r) {
    temparr[l - 1] = 0;
    for (int i = l; i <= r; i++) {
        temparr[i] = arr[i];
        temparr[i] += temparr[i - 1];
    }
    int temp, lowerbound, upperbound, max = 1 << 31;
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            temp = temparr[j] - temparr[i - 1];
            if (temp >= max) {
                max = temp;
                lowerbound = i;
                upperbound = j;
            }
        }
    }
    return Item(lowerbound, upperbound, max);
}

Item recur(int l, int r) {
    if (l + 10 >= r) return bruteForce(l, r); // The crossover point is 12.
    //if (l == r) return Item(l, r, arr[l]); //The former code for finding crossover point.
    int mid = (l + r) / 2;
    int midmax_leftidx, midmax_rightidx, mid_leftmax = 1 << 31, mid_rightmax = 1 << 31;
    int temp = 0;
    for (int i = mid; i >= l; i--) {
        temp += arr[i];
        if (temp >= mid_leftmax) {
            mid_leftmax = temp;
            midmax_leftidx = i;
        }
    }
    temp = 0;
    for (int i = mid + 1; i <= r; i++) {
        temp += arr[i];
        if (temp >= mid_rightmax) {
            mid_rightmax = temp;
            midmax_rightidx = i;
        }
    }
    int midmax = mid_rightmax + mid_leftmax;
    Item left_item = recur(l, mid);
    Item right_item = recur(mid + 1, r);
    if (midmax == std::max(midmax, std::max(left_item.max, right_item.max))) {
        return Item(midmax_leftidx, midmax_rightidx, midmax);
    } else if (left_item.max == std::max(left_item.max, right_item.max)) {
        return left_item;
    } else return right_item;
}

int main() {
    clock_t begin = clock();
    #ifdef BRUTE
    Item ans = bruteForce(1, size);
    #else
    Item ans = recur(1, size);
    #endif
    clock_t end = clock();
    printf("max: %d left: %d right: %d time: %f\n", ans.max, ans.left, ans.right, (double) (end - begin) / CLOCKS_PER_SEC);
    return 0;
}
