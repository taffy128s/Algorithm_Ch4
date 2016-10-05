#include <cstdio>

struct Item {
    Item(int a, int b, int c) {
        left = a;
        right = b;
        max = c;
    }
    int left, right, max;
};

int arr[1000] = {0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
int size = 16;
Item ans = Item(0, 0, 0);

int main() {
    ans.max = 1 << 31;
    int sum = 0, templeftbound = 0;
    for (int i = 1; i <= size; i++) {
        if (sum > 0) sum += arr[i];
        else {
            sum = arr[i];
            templeftbound = i;
        }
        if (sum > ans.max) {
            ans.max = sum;
            ans.left = templeftbound;
            ans.right = i;
        }
    }
    printf("max: %d left: %d right: %d\n", ans.max, ans.left, ans.right);
    return 0;
}
