int x1_array[5]; // Declaration with specified size

int x2_array[5] = {10,20,30,40,50}; // Declaration with initialization

// Size inferred from initializer
int x3_array[] = {10,20,30,40,50};  // Size is 5

// Partial initialization (remaining elements become 0)
int x4_array[10] = {10,20,30,40,50};  // First 5 are 10,20,30,40,50; rest are 0

int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};