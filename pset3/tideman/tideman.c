#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(int array[], int left, int right);
void merge_both(int array[], int left, int middle, int right);
bool all_true_rows(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    printf("candidate_count: %i", candidate_count);
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // updating the ranks array with the candidates number based on the rank provided. i.e. rank_array = [2,0,1] this would be a user's vote.
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks. We are given an array [4,2,1,3,0] where candidate 4 is preferred over 2,1,3,0 and candidate 2 is preferred over 1,3,0 ...
// Using a nested for loop since we want to update the 2D preferences array where the i is the pointer of the ith candidate and j is the pointer of the candidates that was not preferred in the rank array
void record_preferences(int ranks[])
{
    // TODO

    for(int i = 0; i < candidate_count; i++)
    {
        if (i != candidate_count - 1)
        {
            for (int j = i + 1; j < candidate_count; j++)
            {
                preferences[ranks[i]][ranks[j]] += 1;

            }
        }


    }
    return;
}

// Record pairs of candidates where one is preferred over the other
//The preferences is always a square matrix using i + 1 so that i!=j. The sum will calculate the difference between i and j candidates. If positive then i is the winner and j is the loser
// else if it is negative then i -> loser and j -> winner. Otherwise we continue.
void add_pairs(void)
{
    // TODO
    int sum, m, n;
    int pairs_index = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(i > j)
            {
                continue;
            }

            m = i;
            n = j;
            printf("i: %i j: %i\n", m,n);
            sum = preferences[i][j] - preferences[j][i];
            printf("sum[%i][%i] = %i\n", i,j,sum);
            if (sum > 0)
            {
                pairs[pairs_index].winner = i;
                printf("pairs[%i].winner = %i\n", pairs_index, i);
                pairs[pairs_index].loser = j;
                printf("pairs[%i].loser = %i\n", pairs_index, j);
                pair_count += 1;
                pairs_index++;
            }
            else if (sum < 0)
            {
                pairs[pairs_index].winner = j;
                printf("pairs[%i].winner = %i\n", pairs_index, j);
                pairs[pairs_index].loser = i;
                printf("pairs[%i].loser = %i\n", pairs_index, i);
                pair_count += 1;
                pairs_index++;
            }
            else
            {
                continue;
            }

        }

    }

    printf("\n");
    for(int i = 0; i < pair_count; i++)
    {
        printf("winner[%i]: %i ", i,pairs[i].winner);
        printf("loser[%i]: %i ", i,pairs[i].loser);
        printf("\n");
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// We create an array to hold the values of the strength of victory and another pairs struct to copy the values of the pairs.
// The values of the strength of victories are stored in the array_sort to be sorted using the merge sort algorithm.
// Once the array is sorted we then use these values to find the same values from the strength of victories in the pairs_copy and replace them at positions in the global pairs variable.
void sort_pairs(void)
{
    // TODO
    int array_sort[pair_count];
    pair pairs_copy[pair_count];

    for(int i = 0; i < pair_count; i++)
    {
        pairs_copy[i].winner = pairs[i].winner;
        pairs_copy[i].loser = pairs[i].loser;
    }
    int sum;
    for (int i = 0; i < pair_count; i++)
    {
        sum = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        if (sum < 0)
        {
            sum *= -1;
        }
        array_sort[i] = sum;
    }

    merge_sort(array_sort, 0, pair_count - 1);
    for(int i = 0; i < pair_count; i++)
    {
        printf("%i ", array_sort[i]);
    }
    printf("\n");

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            sum = preferences[pairs_copy[j].winner][pairs_copy[j].loser] - preferences[pairs_copy[j].loser][pairs_copy[j].winner];
            if (sum < 0)
            {
                sum *= -1;
            }

            if (sum == array_sort[i])
            {
                pairs[i].winner = pairs_copy[j].winner;
                pairs[i].loser = pairs_copy[j].loser;
            }

        }
    }



    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// If every row contains a True that means it becomes a cycle. The same goes for every column so need to either verify if a column/row is free of True values.
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        //if all the rows are true then we need to undo the change of making it false and break from the for loop as we are not going to update the locked array anymore.
        if (all_true_rows())
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            break;
        }

    }

    return;
}

// Print the winner of the election
// Need to find a column with all false values that will prove that it has no edge towards it.
void print_winner(void)
{
    // TODO
    int winner = 0;
    bool check_column_true = false;
    for (int j = 0; j < candidate_count; j++)
    {
        check_column_true = false;
        for (int i = 0; i < candidate_count; i++)
        {
            if(locked[i][j] == true)
            {
                check_column_true = true;
                break;
            }
        }

        if(!check_column_true)
        {
            printf("%s\n\n", candidates[winner]);
            break;
        }

        winner++;
    }

    printf("preferences: \n");
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    printf("pairs: \n");
    for(int i = 0; i < pair_count; i++)
    {
        printf("winner[%i]: %i ", i,pairs[i].winner);
        printf("loser[%i]: %i ", i,pairs[i].loser);
        printf("\n");
    }

    printf("locked: \n");
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            printf("%d ", locked[i][j]);
        }
        printf("\n");
    }

    return;
}


void merge_sort(int array[], int left, int right)
{
    if(left < right)
    {
        int middle = left + (right - left) / 2; // finds the middle point of an array

        merge_sort(array, left, middle); //recursively calling until left < right from [l....m]
        merge_sort(array, middle + 1, right); //recursively calling from [m+1...r]

        merge_both(array, left, middle, right); // Once sorted then this is called.
    }

}

//When two arrays need to be merged. Create three pointers i,j,k
// i-> pointer of the first subarray i.e. subarray1
// j -> pointer of the second subarray i.e subarray2
// k -> pointer of the original array
void merge_both(int array[], int left, int middle, int right) //0,2,5
{
    int left_bound = middle - left + 1; //[left...middle] Number of elements for the first subarray
    int right_bound = right - middle; // [middle + 1...right] No. of elements for the second subarray

    //creating temporary arrays to store the elements of the first and second subarrays.
    int sub_array1[left_bound], sub_array2[right_bound];

    // copying the elements from the array's left point to and including the middle element
    for (int i = 0; i < left_bound; i++)
    {
        sub_array1[i] = array[left + i];
    }

    //copying the elements from the array's middle + 1 's element to the right
    for (int j = 0; j < right_bound; j++)
    {
        sub_array2[j] = array[middle + 1 + j];
    }

    //Creating the 3 pointers.
    int i,j,k;
    i = 0;
    j = 0;
    k = left;

    //Merging the two arrays and comparing which is lesser/greater and placing it in the left position of the original array
    while (i < left_bound && j < right_bound)
    {
        if (sub_array1[i] >= sub_array2[j])
        {
            array[k] = sub_array1[i];
            i++;
        }
        else
        {
            array[k] = sub_array2[j];
            j++;
        }

        k++;
    }

    //Since EITHER one of the subarrays might be larger we have to include the rest of the elements.
    // Notice that we exited the previous while loop because either i or j has reached the end of its respective subarray.

    while (i < left_bound)
    {
        array[k] = sub_array1[i];
        i++;
        k++;
    }

    while (j < right_bound)
    {
        array[k] = sub_array2[j];
        j++;
        k++;
    }

}

//Returns true if locked array consists of at least one true value in each row else it returns false.
bool all_true_rows(void)
{
    int sum_all_rows_true = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        // Finds atleast one occurrence of the true value in a row and the breaks from it moving to the next row.
        for (int j = 0; j < candidate_count; j++)
        {
            if(locked[i][j])
            {
                sum_all_rows_true += 1;
                break;
            }
        }
    }

    // If the no. of rows with true match the number of candidates then return true in which a cycle has formed else return false.
    if(sum_all_rows_true == candidate_count)
    {
        return true;
    }
    return false;
}
