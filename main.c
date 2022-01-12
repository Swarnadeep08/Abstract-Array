#include <stdio.h>
#include <stdlib.h>

/*
List of operations -
1. Display()
2. Insert(index ,x)
3. Append(x)
4. Delete(x)
5. Pop()
6. i. Search(x)
6. ii. BinarySearch(x) for sorted array
7. Get(index)
8. Set(index, x)
9. Reverse()
10. Rotate()
11. Sumof()
12. i. Sort()
12. ii. Sorted() return a sorted array without changing the original, create the array in heap and return the base address
13. Is_sorted() return boolean value
14. Average()
15. Max()
16. Min()
17. Rearrange()
18. Merge(*arr) takes two sorted arrays and merges them as a sorted array
19. Union()
20. Intersection()
21. Difference()
*/

struct Array
{
    int *A;
    int size;
    int length;
};

void Display(struct Array arr)
{
    int i;
    printf("\nThe elements are -\n");
    for(i=0; i<arr.length; i++)
        printf("%d ", arr.A[i]);
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void Append(struct Array *arr, int x)
{
    if(arr->length < arr->size)
        arr->A[arr->length++] = x;
}

void Insert(struct Array *arr, int index, int x)
{
    int i = arr->length;

    if(arr->length < arr->size){
    // This conditions check whether the index is valid or not
        if(index >= 0 && index <= arr->length){
            for(; i > index ; i--)
                arr->A[i] = arr->A[i-1];
            arr->A[index] = x;
            arr->length++;
        }
    }
}

int Pop(struct Array *arr)
{
    int x = -999;
    // Check underflow condition i.e. array should not be empty
    if(arr->length != 0){
        x = arr->A[arr->length-1];
        arr->length--;
    }
    return x;
}

void Delete(struct Array *arr, int key)
{
    int i, j=0;
    for(i = 0; i < arr->length; i++)
    {
        if(key == arr->A[i])
            break;
    }

    // if the key is not found i = length and the next for loop will terminate in it's first comdition
    for(j = i; j < arr->length-1; j++)
        arr->A[j] = arr->A[j+1];

    // if the key is not found i = length-1 and the if statement will return 0
    if(i!=arr->length)
        arr->length--;
}

int Search(struct Array *arr, int x)
{
    for(int i=0; i<arr->length; i++)
    {
        if(arr->A[i] == x)
        {
            swap(&arr->A[i], &arr->A[0]);
            return 0;
        }
    }
    return -1;
}

int BinarySearch(struct Array arr, int x)
{
    int l, h, mid;
    l = 0;
    h = arr.length - 1;

    while(l<=h)
    {
        mid = (l+h)/2;
        if(arr.A[mid] == x)
            return mid;
        else if(x < arr.A[mid])
            h = mid-1;
        else
            l = mid+1;
    }
    return -1;
}

int Get(struct Array arr, int index)
{
    if(index >= 0 && index<arr.length)
        return arr.A[index];
    return -1;
}

void Set(struct Array *arr, int index, int x)
{
    if(index>=0 && index<arr->length)
        arr->A[index] = x;
}

int Max(struct Array arr)
{
    int max = arr.A[0];
    for(int i=1; i<arr.length; i++){
        if(arr.A[i]>max)
            max = arr.A[i];
    }
    return max;
}

int Min(struct Array arr)
{
    int min = arr.A[0];
    for(int i=1; i<arr.length; i++){
        if(arr.A[i]<min)
            min = arr.A[i];
    }
    return min;
}

int Sumof(struct Array arr)
{
    int sum = 0;
    for(int i = 0; i<arr.length; i++)
        sum += arr.A[i];
    return sum;
}

float Average(struct Array arr)
{
    return Sumof(arr)/arr.length;
}

void Reverse(struct Array *arr)
{
    int i, j;
    for(i=0,j=arr->length-1; i<j; i++,j--){
        swap(&arr->A[i], &arr->A[j]);
    }
}

void Rotate(struct Array *arr)
{
    int temp = arr->A[0];
    for(int i=1; i<arr->length; i++){
        arr->A[i-1] = arr->A[i];
    }
    arr->A[arr->length-1] = temp;
}

void InsertSort(struct Array *arr, int x)
{
    int i = arr->length-1;
    if(arr->length < arr->size){
        while(i>=0 && arr->A[i] > x){
            arr->A[i+1] = arr->A[i];
            i--;
        }
        arr->A[i+1] = x;
        arr->length++;
    }
}

int Is_Sorted(struct Array arr)
{
    int i;
    for(i=0; i<arr.length-1; i++){
        if(arr.A[i] > arr.A[i+1])
            return 0;
    }
    return 1;
}

void Rearrange(struct Array *arr)
{
    int i,j;
    i=0;
    j= arr->length-1;

    while(i<j){
        while(arr->A[i]<0)
            i++;
        while(arr->A[j]>=0)
            j--;
        if(i<j)
            swap(&arr->A[i], &arr->A[j]);
    }
}

struct Array* Merge(struct Array *arr1, struct Array *arr2)
{
    int i=0,j=0,k=0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    while(i<arr1->length && j<arr2->length){
        if(arr1->A[i] < arr2->A[j])
            arr3->A[k++] = arr1->A[i++];

        else
            arr3->A[k++] = arr2->A[j++];
    }

    while(i<arr1->length){
        arr3->A[k++] = arr1->A[i++];
    }

    while(j<arr2->length){
        arr3->A[k++] = arr2->A[j++];
    }

    arr3->length = arr1->length + arr2->length;
    arr3->size = 10;

    return arr3;
}

struct Array* Union(struct Array *arr1,struct Array *arr2)
{
    int i,j,k;
    i=j=k=0;
    struct Array *arr3=(struct Array *)malloc(sizeof(struct Array));

    while(i<arr1->length && j<arr2->length){
        if(arr1->A[i]<arr2->A[j])
            arr3->A[k++]=arr1->A[i++];
        else if(arr2->A[j]<arr1->A[i])
            arr3->A[k++]=arr2->A[j++];
        else{
            arr3->A[k++]=arr1->A[i++];
            j++;
        }
    }
    for(;i<arr1->length;i++)
        arr3->A[k++]=arr1->A[i];
    for(;j<arr2->length;j++)
        arr3->A[k++]=arr2->A[j];

    arr3->length=k;
    arr3->size=10;

    return arr3;
}

struct Array* Intersection(struct Array *arr1,struct Array *arr2)
{
    int i,j,k;
    i=j=k=0;
    struct Array *arr3=(struct Array *)malloc(sizeof(struct Array));

    while(i<arr1->length && j<arr2->length){
        if(arr1->A[i]<arr2->A[j])
            i++;
        else if(arr2->A[j]<arr1->A[i])
            j++;
        else if(arr1->A[i]==arr2->A[j]){
            arr3->A[k++]=arr1->A[i++];
            j++;
        }
    }

    arr3->length=k;
    arr3->size=10;

    return arr3;
}

struct Array* Difference(struct Array *arr1,struct Array *arr2)
{
    int i,j,k;
    i=j=k=0;
    struct Array *arr3=(struct Array *)malloc(sizeof(struct Array));

    while(i<arr1->length && j<arr2->length){
        if(arr1->A[i]<arr2->A[j])
            arr3->A[k++]=arr1->A[i++];
        else if(arr2->A[j]<arr1->A[i])
            j++;
        else{
            i++;
            j++;
        }
    }
    for(;i<arr1->length;i++)
        arr3->A[k++]=arr1->A[i];

    arr3->length=k;
    arr3->size=10;

    return arr3;
}

int main()
{
    struct Array arr;
    int ch;
    int x, index, res;

    printf("Enter the size of array: ");
    scanf("%d", &arr.size);
    arr.A = (int *)malloc(arr.size*sizeof(int));
    arr.length = 0;

    do{
        printf("\n-------------------------------------------------------------\n");
        printf("The Menu contains -\n");
        printf(" 1. Display()\n 2. Insert(index ,x)\n 3. Append(x)\n 4. Delete(x)\n 5. Pop()\n 6. Reverse()\n 7. Search(x)\n 8. Exit");
        printf("\n-------------------------------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: Display(arr); break;
            case 2: printf("Enter the index and the number: "); scanf("%d%d", &index, &x);
                    Insert(&arr, index, x); break;
            case 3: printf("Enter the number: "); scanf("%d", &x);
                    Append(&arr, x); break;
            case 4: printf("Enter the number you want to delete: ");
                    scanf("%d", &x);
                    Delete(&arr, x); break;
            case 5: res = Pop(&arr);
                    if(res==-999)
                        printf("There is no element in the array.");
                    else
                        printf("The deleted element is %d\n", res);
                    break;
            case 6: Reverse(&arr); break;
            case 7: printf("Enter the number to be searched: ");
                    scanf("%d", &x);
                    res = Search(&arr, x);
                    if(res==0)
                        printf("The number is found\n");
                    else
                        printf("The number is not found\n");
                    break;
        }
    }while(ch>0 && ch<8);

    free(arr.A);
    return 0;
}
