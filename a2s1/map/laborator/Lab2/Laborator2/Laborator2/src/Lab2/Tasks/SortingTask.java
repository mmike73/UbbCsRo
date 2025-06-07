package Lab2.Tasks;

import Lab2.Sorters.AbstractSorter;
import Lab2.Sorters.BubbleSorter;
import Lab2.Sorters.MergeSorter;
import Lab2.Sorters.SortingStrategies;

import java.util.Arrays;

public class SortingTask extends Task {
    private final int[] toSort;
    AbstractSorter sorter;

    public SortingTask(String taskId, String description, int[] toSort, SortingStrategies strategy) {
        super(taskId, description);
        this.toSort = toSort;

        switch (strategy) {
            case BUBBLESORT -> sorter = new BubbleSorter();
            case MERGESORT -> sorter = new MergeSorter();
        }
    }

    @Override
    public void execute() {
        sorter.sort(toSort);
        System.out.println("Sorted " + Arrays.toString(toSort) + " elements");
    }
}
