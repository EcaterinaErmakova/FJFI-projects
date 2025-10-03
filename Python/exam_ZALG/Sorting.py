# Python3 program for Bubble Sort Algorithm Implementation
def bubbleSort(arr):
    n = len(arr)
    # For loop to traverse through all 
    # element in an array
    for i in range(n):
        for j in range(0, n - i - 1):
            # Range of the array is from 0 to n-i-1
            # Swap the elements if the element found 
            #is greater than the adjacent element
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def selectionSort(array, size):
    for s in range(size):
        min_idx = s
        for i in range(s + 1, size):
            # For sorting in descending order
            # for minimum element in each loop
            if array[i] < array[min_idx]:
                min_idx = i
        # Arranging min at the correct position
        (array[s], array[min_idx]) = (array[min_idx], array[s])

# Function to sort array using insertion sort
def insertionSort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        # Move elements of arr[0..i-1], that are
        # greater than key, to one position ahead
        # of their current position
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# function for Sorting the Array
def bingoSort(arr, size):
    # Finding the smallest element From the Array
    bingo = min(arr) 
    # Finding the largest element from the Array
    largest = max(arr)
    nextBingo = largest
    nextPos = 0
    while bingo < nextBingo:      
        # Will keep the track of the element position to
        # shifted to their correct position
        startPos = nextPos
        for i in range(startPos, size):
            if arr[i] == bingo:
                arr[i], arr[nextPos] = arr[nextPos], arr[i]
                nextPos += 1          
            #  Here we are finding the next Bingo Element
            #  for the next pass
            elif arr[i] < nextBingo:
                nextBingo = arr[i]
        bingo = nextBingo
        nextBingo = largest

# Python3 program for implementation of Shell Sort
def shellSort(arr, n):
    gap=n//2
    while gap>0:
        j=gap
        # Check the array in from left to right
        # Till the last possible index of j
        while j<n:
            i=j-gap # This will keep help in maintain gap value
            while i>=0:
                # If value on right side is already greater than left side value
                # We don't do swap else we swap
                if arr[i+gap]>arr[i]:
                    break
                else:
                    arr[i+gap],arr[i]=arr[i],arr[i+gap]
                i=i-gap # To check left side also
                            # If the element present is greater than current element 
            j+=1
        gap=gap//2

def cocktailSort(a):
    n = len(a)
    swapped = True
    start = 0
    end = n-1
    while (swapped == True):
        # reset the swapped flag on entering the loop,
        # because it might be true from a previous
        # iteration.
        swapped = False
        # loop from left to right same as the bubble
        # sort
        for i in range(start, end):
            if (a[i] > a[i + 1]):
                a[i], a[i + 1] = a[i + 1], a[i]
                swapped = True
        # if nothing moved, then array is sorted.
        if (swapped == False):
            break
        # otherwise, reset the swapped flag so that it
        # can be used in the next stage
        swapped = False
        # move the end point back by one, because
        # item at the end is in its rightful spot
        end = end-1
        # from right to left, doing the same
        # comparison as in the previous stage
        for i in range(end-1, start-1, -1):
            if (a[i] > a[i + 1]):
                a[i], a[i + 1] = a[i + 1], a[i]
                swapped = True
        # increase the starting point, because
        # the last stage would have moved the next
        # smallest number to its rightful spot.
        start = start + 1


def heapify(arr, N, i):
    largest = i  # Initialize largest as root
    l= 2*i + 1     # left = 2*i + 1
    r= 2*i + 2     # right = 2*i + 2
    # See if left child of root exists and is
    # greater than root
    if l < N and arr[largest] < arr[l]:
        largest = l
    # See if right child of root exists and is
    # greater than root
    if r < N and arr[largest] < arr[r]:
        largest = r
    # Change root, if needed
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # swap
        # Heapify the root.
        heapify(arr, N, largest)
# The main function to sort an array of given size
def heapSort(arr):
    N = len(arr)
    # Build a maxheap.
    for i in range(N//2 - 1, -1, -1):
        heapify(arr, N, i)
    # One by one extract elements
    for i in range(N-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # swap
        heapify(arr, i, 0)


def partition(arr, low, high): #rozdeleni
    # Choose the pivot
    pivot = arr[high]
    i = low - 1
    # Traverse arr[low..high] and move all smaller
    # elements on the left side. Elements from low to 
    # i are smaller after every iteration
    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    # Move pivot after smaller elements and
    # return its position
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1
# The QuickSort function implementation
def quick_sort(arr, low, high):
    if low < high:
        # pi is the partition return index of pivot
        pi = partition(arr, low, high) 
        '''Hoar_partition'''
        # Recursion calls for smaller elements
        # and greater or equals elements
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)

''' This function takes first element as pivot, and places
      all the elements smaller than the pivot on the left side
      and all the elements greater than the pivot on
      the right side. It returns the index of the last element
      on the smaller side '''
def Hoar_partition(arr, low, high):
    pivot = arr[low]
    i = low - 1
    j = high + 1
    while (True):
        # Find leftmost element greater than
        # or equal to pivot
        i += 1
        while (arr[i] < pivot):
            i += 1
        # Find rightmost element smaller than
        # or equal to pivot
        j -= 1
        while (arr[j] > pivot):
            j -= 1
        # If two pointers met.
        if (i >= j):
            return j
        arr[i], arr[j] = arr[j], arr[i]


def merge(arr, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid
    # Create temp arrays
    L = [0] * n1
    R = [0] * n2
    # Copy data to temp arrays L[] and R[]
    for i in range(n1):
        L[i] = arr[left + i]
    for j in range(n2):
        R[j] = arr[mid + 1 + j]
    i = 0  # Initial index of first subarray
    j = 0  # Initial index of second subarray
    k = left  # Initial index of merged subarray
    # Merge the temp arrays back
    # into arr[left..right]
    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1
    # Copy the remaining elements of L[],
    # if there are any
    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1
    # Copy the remaining elements of R[], 
    # if there are any
    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1

def merge_sort(arr, left, right):
    if left < right:
        mid = (left + right) // 2
        merge_sort(arr, left, mid)
        merge_sort(arr, mid + 1, right)
        merge(arr, left, mid, right)
