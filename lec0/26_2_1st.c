#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// --------------------------------------------------------
// 1. 병합 정렬 (Merge Sort) - O(n log n)
// --------------------------------------------------------
void merge(int arr[], int left, int mid, int right) {
int i = left, j = mid + 1, k = 0;
int *temp = (int *)malloc(sizeof(int) * (right - left + 1));

while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) temp[k++] = arr[i++];
    else temp[k++] = arr[j++];
}
while (i <= mid) temp[k++] = arr[i++];
while (j <= right) temp[k++] = arr[j++];

for (i = left, k = 0; i <= right; i++, k++) {
    arr[i] = temp[k];
}
free(temp);


}

void mergeSort(int arr[], int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;
mergeSort(arr, left, mid);
mergeSort(arr, mid + 1, right);
merge(arr, left, mid, right);
}
}

// --------------------------------------------------------
// 2. 버블 정렬 (Bubble Sort) - O(n^2)
// --------------------------------------------------------
void bubbleSort(int arr[], int n) {
for (int i = 0; i < n - 1; i++) {
bool swapped = false;
for (int j = 0; j < n - 1 - i; j++) {
if (arr[j] > arr[j + 1]) {
int temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;
swapped = true;
}
}
// 교환이 한 번도 없으면 이미 정렬된 상태이므로 조기 종료
if (!swapped) break;
}
}

// --------------------------------------------------------
// 3. 칵테일 셰이커 정렬 (Cocktail Shaker Sort) - O(n^2)
// --------------------------------------------------------
void cocktailShakerSort(int arr[], int n) {
bool swapped = true;
int start = 0;
int end = n - 1;

while (swapped) {
    swapped = false;

    // 왼쪽에서 오른쪽으로 (일반 버블 정렬 방향)
    for (int i = start; i < end; ++i) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
            swapped = true;
        }
    }
    if (!swapped) break;
    
    swapped = false;
    end--; // 가장 큰 값이 맨 끝에 자리 잡았으므로 범위 축소

    // 오른쪽에서 왼쪽으로 (역방향)
    for (int i = end - 1; i >= start; --i) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
            swapped = true;
        }
    }
    start++; // 가장 작은 값이 맨 앞에 자리 잡았으므로 범위 축소
}


}

// --------------------------------------------------------
// 벤치마크 및 유틸리티 함수
// --------------------------------------------------------
void generateRandomArray(int arr[], int n) {
for (int i = 0; i < n; i++) {
arr[i] = rand() % 100000;
}
}

void copyArray(int src[], int dest[], int n) {
for (int i = 0; i < n; i++) {
dest[i] = src[i];
}
}

void measurePerformance(int n) {
int *original = (int *)malloc(sizeof(int) * n);
int *arr = (int *)malloc(sizeof(int) * n);
clock_t start, end;
double cpu_time_used; // 이제 이 변수를 아래에서 정상적으로 사용합니다.

generateRandomArray(original, n);
printf("데이터 크기 (n = %d)\n", n);
printf("----------------------------------------\n");

// 1. Merge Sort
copyArray(original, arr, n);
start = clock();
mergeSort(arr, 0, n - 1);
end = clock();
cpu_time_used = ((double) (end - start) / CLOCKS_PER_SEC) * 1000.0;
printf("1. Merge Sort      : %.2f ms\n", cpu_time_used);

// 2. Bubble Sort
copyArray(original, arr, n);
start = clock();
bubbleSort(arr, n);
end = clock();
cpu_time_used = ((double) (end - start) / CLOCKS_PER_SEC) * 1000.0;
printf("2. Bubble Sort     : %.2f ms\n", cpu_time_used);

// 3. Cocktail Shaker Sort
copyArray(original, arr, n);
start = clock();
cocktailShakerSort(arr, n);
end = clock();
cpu_time_used = ((double) (end - start) / CLOCKS_PER_SEC) * 1000.0;
printf("3. Cocktail Shaker : %.2f ms\n", cpu_time_used);

printf("========================================\n\n");

free(original);
free(arr);


}

int main() {
// 랜덤 시드 설정
srand(time(NULL));

printf("========================================\n");
printf("       정렬 알고리즘 성능 비교\n");
printf("========================================\n\n");

// 다양한 배열 크기에 대해 성능 측정
measurePerformance(1000);
measurePerformance(10000);
measurePerformance(30000);

return 0;


}
