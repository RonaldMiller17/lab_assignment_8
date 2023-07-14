#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void maxHeap(int arr[], int n, int i) {
	int left = 2*i + 1, right = 2*i + 2;
    int large = i;
    
    if(left < n && arr[left] > arr[large])
		large = left;
    if(right < n && arr[right] > arr[large])
		large = right;

    if(large != i)
    {
		int temp = arr[i];
		arr[i] = arr[large];
		arr[large] = temp;
        maxHeap(arr, n, large);
    }
}

void heapSort(int arr[], int n)
{
	int i;
	for (i = (n - 2) / 2; i >= 0; i--) {
		maxHeap(arr, n, i);
	}
	for (i = 0; i < n; i++) {
		// swap
		int temp = arr[n - i - 1];
		arr[n - i - 1] = arr[0];
		arr[0] = temp;
		maxHeap(arr, n - i - 1, 0);
	}
}


void mergeSort(int pData[], int l, int r) {
    if (l >= r)
		return;

	int mid = l + (r - l) / 2;

	mergeSort(pData, l, mid);
	mergeSort(pData, mid + 1, r);

	int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int* left = malloc(n1 * sizeof(int));
	int* right = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        left[i] = pData[l + i];
    for (j = 0; j < n2; j++)
        right[j] = pData[mid + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            pData[k++] = left[i++];
        else
            pData[k++] = right[j++];
    }

    while (i < n1)
        pData[k++] = left[i++];

    while (j < n2)
        pData[k++] = right[j++];
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

void printArray(int pData[], int dataSz)
{
	printf("\tData:\n\t");
	for (int i = 0; i < dataSz; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i = 0; i < 4; ++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n", dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.9lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}