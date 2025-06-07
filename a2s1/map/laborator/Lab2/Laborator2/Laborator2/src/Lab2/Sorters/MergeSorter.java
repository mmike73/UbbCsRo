package Lab2.Sorters;

public class MergeSorter extends AbstractSorter {

    private void mergeSort(int[] arr, int st, int dr) {
        if(st < dr) {
            int mid = st + (dr - st) / 2;
            mergeSort(arr, st, mid);
            mergeSort(arr, mid + 1, dr);

            int a = st, b = mid + 1, c = 0;
            int[] tmp = new int[dr - st + 1];

            while(a <= mid && b <= dr) {
                if(arr[a] - arr[b] < 0) {
                    tmp[c++] = arr[a++];
                } else {
                    tmp[c++] = arr[b++];
                }
            }

            while(a <= mid) {
                tmp[c++] = arr[a++];
            }

            while(b <= dr) {
                tmp[c++] = arr[b++];
            }

            for (int i = 0; i < c; ++i) {
                arr[st + i] = tmp[i];
            }
        }
    }

    @Override
    public void sort(int[] arr) {
        mergeSort(arr, 0, arr.length - 1);
    }
}
