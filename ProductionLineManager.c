/* 
    Author: Clarence Navarro

    Date: 21/03/2024

    Program Description: Program takes record of a Company that manufactures aeronautical equipment. More specifically, the program takes record of the production lines' information such as product ID, time and date of the batch etc. 
    The program contains 4 tasks, however before executing these 4 tasks, the program displays all the information in each production line. Task 1 sorts the data in order of product ID, issue code, and date and time per production line,
    task 2 combines all four production lines into one single list using linked-lists, task 3 provides a feature to search for the earliest occurrence of a specified product ID and issue code combination, and finally task 4 counts the 
    number of issues reported for every product ID.

*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Symbolic Names
#define LINE_SIZE 4
#define SIZE 15
#define DESC_SIZE 100
#define PROD_SIZE 20
#define ISSUE_SIZE 7

// Structure Templates
struct batchTime // Nested Structure- Holds the time information
{
    int day;
    int hr;
    int min;
};

struct issData // Nested - Holds information on the issues relating to manufacturing
{
    int issCode;
    char issDesc[DESC_SIZE];
};

struct resData // Nested - Holds information on the the solution given in relation to the issue
{
    int resCode;
    char resDesc[DESC_SIZE];
};

struct manuData // Main structure - contains the information of everything about the manufacturing including the other structures
{
    int lineCodeNo;
    int batchCode;
    struct batchTime timeInfo; 
    int prodID;
    struct issData issueInfo;
    struct resData resoInfo;
    int employID;
};

struct node // Node structure - Node used for the single-list needed for task 2
{
    struct manuData linkedList;
    struct node *link;
};


// Function Signatures
//  Task Functions
void lineCodeSort(struct manuData[], struct manuData[], struct manuData[], struct manuData[]); // Task 1
struct node* listCreate(struct node*,struct node*, struct manuData[], struct manuData[], struct manuData[], struct manuData[]); // Task 2
void prodIssueFinder(struct manuData[], struct manuData[], struct manuData[], struct manuData[]); // Task 3
void issueReport(struct node*);

// Display lineCode
void originalDisplay(struct manuData[]);
void lineCodeDisplay(struct manuData[]);

//  Product ID sorting
void prodMergeSort(struct manuData[], int, int); 
void prodMerge(struct manuData[], int, int, int); 

//  Issue sorting 
void issueSort(struct manuData[]); 
void issueMergeSort(struct manuData[], int, int); 
void issueMerge(struct manuData[], int, int, int); 

//  Time sorting 
void timeSort(struct manuData[]); 
void timeMergeSort(struct manuData[], int, int);
void timeMerge(struct manuData[], int, int, int);

// Single-List
void listReport(struct node*);

// Search
int binarySearch(struct manuData[], int, int, int, int);
void linearSearch(struct manuData[], int, int, int);



int main(void)
{
    // Initialise Production Line Data - struct manuData lineCode#NO[SIZE] = {lineCode, batchCode, timeInfo(Day, Hours, Minutes), productID, issueInfo(Code, Description), resoInfo(Code, Description), employeeID} 
    // Production line 1
    struct manuData lineCode1[SIZE] = 
    {
        {1, 234567, {7, 4, 33}, 60824, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 22345670},
        {1, 298076, {19, 12, 55}, 66201, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 22789010},
        {1, 298076, {14, 23, 10}, 66201, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 22345670},
        {1, 234589, {25, 8, 42}, 60928, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 22234560},
        {1, 234589, {3, 17, 26}, 60928, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 22098760},
        {1, 234567, {3, 6, 18}, 60824, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 22456780},
        {1, 290123, {11, 20, 47}, 62106, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 22987650},
        {1, 276543, {22, 14, 14}, 67490, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 22543210},
        {1, 298076, {14, 23, 39}, 66201, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 22678920},
        {1, 234589, {6, 1, 21}, 60928, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 22234560},
        {1, 206319, {30, 19, 50}, 62935, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 22345670},
        {1, 234567, {11, 9, 7}, 60824, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 22123450},
        {1, 298765, {2, 15, 28}, 61670, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 22345670},
        {1, 234589, {20, 22, 59}, 60928, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 22012340},
        {1, 298076, {12, 7, 15}, 66201, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 22123450}
    };

    // Production line 2
    struct manuData lineCode2[SIZE] = 
    {
        {2, 234589, {19, 15, 14}, 60928, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2036320},
        {2, 206319, {21, 6, 6}, 62935, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 2831360},
        {2, 234589, {25, 2, 56}, 60928, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 2981410},
        {2, 206319, {27, 10, 4}, 62935, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 2416990},
        {2, 234589, {19, 3, 40}, 60928, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2988260},
        {2, 298076, {20, 9, 28}, 66201, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 2967430},
        {2, 298076, {9, 12, 12}, 66201, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 2089830},
        {2, 276543, {12, 6, 43}, 67490, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2691560},
        {2, 206319, {9, 3, 42}, 62935, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 2041390},
        {2, 298076, {14, 14, 58}, 66201, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 2954000},
        {2, 234589, {21, 19, 13}, 60928, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 2128340},
        {2, 298076, {28, 6, 36}, 66201, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2363030},
        {2, 234589, {11, 12, 3}, 60928, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 2206010},
        {2, 298076, {29, 18, 6}, 66201, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 2575740},
        {2, 276543, {18, 0, 31}, 67490, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2547870}
    };

    // Production line 3
    struct manuData lineCode3[SIZE] = 
    {
        {3, 202450, {28, 1, 40}, 61847, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2689060 },
        {3, 202450, {30, 19, 25}, 61847, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2701190 },
        {3, 218025, {18, 5, 47}, 65833, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 2880550 },
        {3, 220054, {11, 22, 57}, 64033, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 2655590 },
        {3, 225227, {2, 0, 21}, 66395, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 2640460 },
        {3, 236609, {4, 22, 36}, 63342, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 2013900 },
        {3, 236609, {25, 11, 43}, 63342, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 2140430 },
        {3, 220054, {8, 16, 43}, 64033, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2386060 },
        {3, 248297, {2, 14, 5}, 67733, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2575570 },
        {3, 220054, {8, 18, 2}, 64033, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 2019570 },
        {3, 275352, {20, 0, 56}, 61746, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 2976180 },
        {3, 248297, {1, 18, 55}, 67733, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 2310100 },
        {3, 202450, {28, 2, 2}, 61847, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 2734040 },
        {3, 275352, {1, 0, 11}, 61746, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 2812280 },
        {3, 236609, {2, 11, 56}, 63342, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2943390 }
    };

    // Production line 4
    struct manuData lineCode4[SIZE] = 
    {
        {4, 213720, {24, 3, 44}, 64843, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2701120 },
        {4, 216861, {16, 14, 44}, 68931, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 2299520 },
        {4, 218725, {21, 6, 17}, 65460, {70123, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 2889120 },
        {4, 221581, {28, 17, 48}, 68868, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 2531100 },
        {4, 222760, {6, 0, 23}, 62026, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2397830 },
        {4, 202450, {17, 3, 49}, 61847, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 2938440 },
        {4, 213720, {9, 21, 18}, 64843, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 2125900 },
        {4, 222760, {27, 4, 20}, 62026, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2006830 },
        {4, 218725, {19, 15, 28}, 65460, {71234, "Dents observed on the surface of the product."}, {81234, "Straighten dents and apply protective coatings."}, 2876120 },
        {4, 222760, {24, 19, 1}, 62026, {79601, "Scratched product affecting overall appearance."}, {89601, "Buff out scratches and restore surface integrity."}, 2379250 },
        {4, 236609, {18, 1, 24}, 63342, {74592, "Oil leaks found in critical components."}, {84592, "Repair and seal affected areas to prevent further leaks."}, 2273940 },
        {4, 213720, {18, 18, 12}, 64843, {76210, "Faulty sensors leading to inaccurate readings."}, {86210, "Replace malfunctioning sensors and recalibrate."}, 2128280 },
        {4, 202450, {2, 0, 32}, 61847, {70123, "Electrical faults disrupting system performance."}, {80123, "Replace faulty electrical components and conduct tests."}, 2847930 },
        {4, 202450, {7, 19, 12}, 61847, {71495, "Cracked components identified during inspection."}, {81495, "Replace cracked components with new ones."}, 2247260 },
        {4, 288610, {18, 21, 34}, 64516, {79820, "Excessive noise levels during operation."}, {89820, "Investigate and mitigate sources of excessive noise."}, 2352830 }
    };

    // Initialise single-list structures
    struct node *head = NULL;
    struct node *ptr = NULL;

    // Display Original Structures
    originalDisplay(lineCode1);
    originalDisplay(lineCode2);
    originalDisplay(lineCode3);
    originalDisplay(lineCode4);

    // Task 1 - Sorting the Product ID, Issue Code, Date and Time
    lineCodeSort(lineCode1, lineCode2, lineCode3, lineCode4);

    // Task 2 - Copying production line data into a single linked list and displaying the content
    head = listCreate(head, ptr, lineCode1, lineCode2, lineCode3, lineCode4);

    // Task 3 - Binary Searching the earliest occurrence of a given product id and issue code
    prodIssueFinder(lineCode1, lineCode2, lineCode3, lineCode4);

    // Task 4 - Counts the number of issue codes per product ID
    issueReport(head);
   
    return 0;

} // End main



// originalDisplay() - displays the original order of all 4 production lines, along with all their data
void originalDisplay(struct manuData lineCode[])
{
    // Initialise Variables
    int i = 0;


    // Prints out all of the data from the production lines
    printf("\n\n- Production Line %d -", lineCode[i].lineCodeNo);

    // Shows the order of which the data is output
    printf("\nLine Code - Batch Code - Date and Time - Product ID - Issue Code - Issue Description - Resolution Code - Resolution Description - Employee ID");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    for (i = 0; i < SIZE; i++)
    {
        printf("\n%d | %d | %d - %d:%d\t| %d | %d - %s | %d - %s | %d ", lineCode[i].lineCodeNo, lineCode[i].batchCode, lineCode[i].timeInfo.day,
        lineCode[i].timeInfo.hr, lineCode[i].timeInfo.min,lineCode[i].prodID, lineCode[i].issueInfo.issCode, lineCode[i].issueInfo.issDesc,
        lineCode[i].resoInfo.resCode, lineCode[i].resoInfo.resDesc, lineCode[i].employID);
    } // End For
    
} // End originalDisplay()



// lineCodeSort() - Holds the functions that will be used for task 1
void lineCodeSort(struct manuData lc1[], struct manuData lc2[], struct manuData lc3[], struct manuData lc4[])
{
    // Initialise Variables
    int i;
    int low = 0;
    int high = SIZE - 1;


    // lineCode1 Sorting
    prodMergeSort(lc1, low, high); // Calls prodMergeSort -> prodMerge
    issueSort(lc1); // Calls issueSort -> issueMergeSort -> issueMerge
    timeSort(lc1); // Calls timeSort -> timeMergeSort -> timeMerge

    // lineCode2 Sorting
    prodMergeSort(lc2, low, high); // Calls prodMergeSort -> prodMerge
    issueSort(lc2); // Calls issueSort -> issueMergeSort -> issueMerge
    timeSort(lc2); // Calls timeSort -> timeMergeSort -> timeMerge

    // lineCode3 Sorting
    prodMergeSort(lc3, low, high); // Calls prodMergeSort -> prodMerge
    issueSort(lc3); // Calls issueSort -> issueMergeSort -> issueMerge
    timeSort(lc3); // Calls timeSort -> timeMergeSort -> timeMerge

    // lineCode4 Sorting
    prodMergeSort(lc4, low, high); // Calls prodMergeSort -> prodMerge
    issueSort(lc4); // Calls issueSort -> issueMergeSort -> issueMerge
    timeSort(lc4); // Calls timeSort -> timeMergeSort -> timeMerge

    printf("\n\n\n\nTask 1 - Sorting the Production Lines by Product ID, Issue Code, and Date and Time");

    // Display lineCode data
    printf("\n\n- Production Line 1 -");
    lineCodeDisplay(lc1);

    printf("\n\n- Production Line 2 -");
    lineCodeDisplay(lc2);

    printf("\n\n- Production Line 3 -");
    lineCodeDisplay(lc3);

    printf("\n\n- Production Line 4 -");
    lineCodeDisplay(lc4);

} // End lineCodeSort()



// lineCodeDisplay() - Displays the Product ID, Issue Codes and Date and Time
void lineCodeDisplay(struct manuData lineCode[])
{
    // Initialise Variables
    int i;


    printf("\nLine Code - Batch Code - Date and Time - Product ID - Issue Code - Issue Description - Resolution Code - Resolution Description - Employee ID");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------");

    // Displays the prod ID, issue code, and time and date of the lineCode being put into the function.
    for (i = 0; i < SIZE; i++)
    {
        printf("\n%d | %d | %d - %d:%d\t| %d | %d - %s | %d - %s | %d ", 
        lineCode[i].lineCodeNo, lineCode[i].batchCode, lineCode[i].timeInfo.day,
        lineCode[i].timeInfo.hr, lineCode[i].timeInfo.min,lineCode[i].prodID, lineCode[i].issueInfo.issCode,
        lineCode[i].issueInfo.issDesc, lineCode[i].resoInfo.resCode, lineCode[i].resoInfo.resDesc, lineCode[i].employID);
    } // End for

} // End lineCodeDisplay()



// prodMergeSort() - Divides the structure until the elements are fully separated
void prodMergeSort(struct manuData lineCode[], int l, int h)
{
    // Initialise Variables
    int mid = 0;


    // Recursive - divides the array until the elements are fully individuals
    if (l >= h)
    {
        // Causes the pop
        return;
    } // End Inner If
    else
    {
        mid = (h + l) / 2;
        // Divides structure into a left section and a right section
        prodMergeSort(lineCode, l, mid); 
        prodMergeSort(lineCode, mid + 1, h); 

        // Re-joins the divided sub-structures back into one structure
        prodMerge(lineCode, l, mid, h);
    } // End Inner Else    
    
} // End prodMergeSort()



// prodMerge() - This will merge the separated elements and sort them into their respected order
void prodMerge(struct manuData lineCode[], int l, int m, int h)
{
    // Initialise Variables
    struct manuData transferStruct[SIZE];
    int i, j, k; 
    

    i = l; // Start index for transfer structure
    j = l; // Start index for left sub-structure
    k = m + 1; // Start Index for right sub-structure

    // While loop ensures that all elements within the structure are used
    while (j <= m && k <= h )
    {
        // Filling the transferStruct in non-descending order 
        if (lineCode[j].prodID <= lineCode[k].prodID)
        {
            transferStruct[i] = lineCode[j];
            j++;
        } // End Inner If
        else
        {
            transferStruct[i] = lineCode[k];
            k++;
        } // End Inner Else
        i++;
    } // End While

    // While deals with unused elements
    while (j <= m) // Fill rest using lineCode[j]
    {
        transferStruct[i] = lineCode[j];
        i++;
        j++;
    } // End While

    while (k <= h) // Fill rest using lineCode[k]
    {
        transferStruct[i] = lineCode[k];
        i++;
        k++;
    } // End While 

    // Copies sorted data back into the original structure
    for (j = l; j < i; j++)
    {
        lineCode[j] = transferStruct[j];
    } // End For
    
} // End prodMerge()



// issueSort() - Function will sort the issue codes within the product ID's that share the same number
void issueSort(struct manuData lineCode[])
{
    // Initialise Variables
    int start = 0; // Marks the start of the current member
    int end = 0; // Marks the end of the current member
    int i;
    int curr = 0; // Number that the index i is currently on

    
    // Within this for loop - the start and end of the current prod ID are found
    for (i = 0; i < SIZE; i++)
    {
        start = i; // Marks the start, before i gets
        curr = i; // Indicates what is the current prodID

        while (lineCode[curr].prodID == lineCode[i].prodID)
        {
            i++;
        }
        i--; // Decremented so that the proper start is found 
        end = i; // i in this case finds the end of the occurrences of the current prodID

        // Using the start and end calculated, mergeSort() called, only if the start and end are not the same number
        if (start < end)
        {
            issueMergeSort(lineCode, start, end);
        } // End If
    } // End for

} // End issueSort()



// issueMergeSort() - Divides the structure until the elements are fully separated
void issueMergeSort(struct manuData lineCode[], int l, int h)
{
    // Initialise Variables
    int mid = 0;


    // Recursive - divides the array until the elements are fully individuals
    if (l >= h)
    {
        // Causes the pop
        return;
    } // End Inner If
    else
    {
        mid = (h + l) / 2;

        // Divides structure into a left section and a right section
        issueMergeSort(lineCode, l, mid);
        issueMergeSort(lineCode, mid + 1, h);

        // Re-joins the divided sub-structures back into one structure
        issueMerge(lineCode, l, mid, h);
    } // End Inner Else    
    
} // End issueMergeSort()



// issueMerge() - This will merge the separated elements and sort them into their respected order
void issueMerge(struct manuData lineCode[], int l, int m, int h)
{
    // Initialise Variables
    struct manuData transferStruct[SIZE];
    int i, j, k; 
    

    i = l; // Start index for transfer structure
    j = l; // Start index for left sub-structure
    k = m + 1; // Start Index for right sub-structure

    // While loop ensures that all elements within the structure are used
    while (j <= m && k <= h )
    {
        // If compares the two structures, if a[j] is bigger than a[k] then a[k] will be put into the transferStruct[i] first. Then the k++ indicates the sorted part of the structure
        if (lineCode[j].issueInfo.issCode <= lineCode[k].issueInfo.issCode)
        {
            transferStruct[i] = lineCode[j];
            j++;
        } // End Inner If
        else
        {
            transferStruct[i] = lineCode[k];
            k++;
        } // End Inner Else
        i++;
    } // End While

    // While will take care of the rest of the elements within the structure that are not dealt with
    while (j <= m)
    {
        transferStruct[i] = lineCode[j];
        i++;
        j++;
    } // End While

    while (k <= h)
    {
        transferStruct[i] = lineCode[k];
        i++;
        k++;
    } // End While 

    // This will transfer sorted elements and only sorted elements back into the original structure
    for (j = l; j < i; j++)
    {
        lineCode[j] = transferStruct[j];
    } // End For
    
} // End issueMerge()



// timeSort() - Function will sort the times codes within the duplicate times
void timeSort(struct manuData lineCode[])
{
    // Initialise Variables
    int start = 0; // Marks the end of the current member
    int end = 0; // Marks the end of the current member
    int i;
    int curr = 0; // Number that the index i is currently on

    
    // Within this for loop - the start and end of the current issue codes are first found - while(currProdID == prodID[i]) - these will be used to tell where the merge sorting will start and end
    for (i = 0; i < SIZE; i++)
    {
        start = i; // Marks the start
        curr = i; // Indicates what is the current prodID

        while (lineCode[curr].issueInfo.issCode == lineCode[i].issueInfo.issCode)
        {
            i++;
        } // End While
        i--; // Decremented so that the proper start is found. Because once the current Issue Code != [i] issue code it will stop the loop, but it will still go through with the increment
        end = i; // i in this case finds the end of the occurrences of the current issue code

        // Using the start and end calculated, mergeSort() called, only if the start and end are not the same size
        if (start < end)
        {
            timeMergeSort(lineCode, start, end);
        } // End If
    } // End For

} // End TimeSort



// timeMergeSort() - Divides the structure until the elements are fully separated
void timeMergeSort(struct manuData lineCode[], int l, int h)
{
    // Initialise Variables
    int mid = 0;


    // Recursive - divides the structure until the elements are fully individuals
    if (l >= h)
    {
        // Causes the pop
        return;
    } // End If
    else
    {
        mid = (h + l) / 2;

        // Divides structure into a left section and a right section
        timeMergeSort(lineCode, l, mid);
        timeMergeSort(lineCode, mid + 1, h);

        // Re-joins the divided sub-structures back into one structure
        timeMerge(lineCode, l, mid, h);
    } // End Else    
    
} // End timeMergeSort()



// timeMerge() - This will merge the separated elements and sort them into their respected order
void timeMerge(struct manuData lineCode[], int l, int m, int h)
{
    // Initialise Variables
    struct manuData transferStruct[SIZE];
    int i, j, k; 
    

    i = l; // Start index for transfer structure
    j = l; // Start index for left sub-structure
    k = m + 1; // Start Index for right sub-structure

    // While loop ensures that all elements within the structure are used
    while (j <= m && k <= h )
    {
        // If compares the two structures, if a[j] is bigger than a[k] then a[k] will be put into the transferStruct[i] first. Then the k++ indicates the sorted part of the structure
        if (lineCode[j].timeInfo.day < lineCode[k].timeInfo.day)
        {
            transferStruct[i] = lineCode[j];
            j++;
        } // End Inner If
        else if (lineCode[j].timeInfo.day > lineCode[k].timeInfo.day)
        {
            transferStruct[i] = lineCode[k];
            k++;
        } // End Inner Else If
        else // If the two variables are equal - then hours are now compared
        {
            if (lineCode[j].timeInfo.hr < lineCode[k].timeInfo.hr)
            {
                transferStruct[i] = lineCode[j];
                j++;
            } // End Inner If
            else if (lineCode[j].timeInfo.hr > lineCode[k].timeInfo.hr)
            {
                transferStruct[i] = lineCode[k];
                k++;
            } // End Inner Else If
            else // If the two variables are equal - then minutes are now compared
            {
                if (lineCode[j].timeInfo.min <= lineCode[k].timeInfo.min)
                {
                    transferStruct[i] = lineCode[j];
                    j++;
                } // End Inner If
                else
                {
                    transferStruct[i] = lineCode[k];
                    k++;
                } // End Inner Else
            } // End Inner Else
        } // End Inner Else
        i++;
    } // End While

    // While will take care of the rest of the elements within the structure that are not dealt with.
    while (j <= m)
    {
        transferStruct[i] = lineCode[j];
        i++;
        j++;
    } // End While

    while (k <= h)
    {
        transferStruct[i] = lineCode[k];
        i++;
        k++;
    } // End While 

    // This will transfer sorted elements and only sorted elements back into the original structure.
    for (j = l; j < i; j++)
    {
        lineCode[j] = transferStruct[j];
    } // End For
    
} // End timeMerge()



// listCreate() - Creates the whole list of all 4 production lines. Since not asked in the task, this is NOT in order of issue code, production ID, and production line
struct node* listCreate(struct node *head, struct node *ptr, struct manuData lc1[], struct manuData lc2[], struct manuData lc3[], struct manuData lc4[])
{
    // Initialise Variables
    struct node *temp; // temp will be the node being added in per iteration
    int i;


    // This creates the first node of the list
    head = malloc(sizeof(struct node));
    head->linkedList = lc1[0];
    head->link = NULL;
    ptr = head; // Ensures both the head and the tail pointer are pointing to the first node while the list is empty

    // For loop adds all of lineCode1 to the single list - i = 1 for this loop because lineCode1[0] is already added
    for (i = 1; i < SIZE; i++)
    {
        // New node created
        temp = malloc(sizeof(struct node));
        temp->linkedList = lc1[i];
        temp->link = NULL;

        // New node being assigned as the new tail end of the list
        ptr->link = temp;
        ptr = temp;
    } // End For

    // For loop adds all of lineCode2 to the single list
    for (i = 0; i < SIZE; i++)
    {
        // New node created
        temp = malloc(sizeof(struct node));
        temp->linkedList = lc2[i];
        temp->link = NULL;

        // New node being assigned as the new tail end of the list
        ptr->link = temp;
        ptr = temp;
    } // End For

    // For loop adds all of lineCode3 to the single list
    for (i = 0; i < SIZE; i++)
    {
        // New node created
        temp = malloc(sizeof(struct node));
        temp->linkedList = lc3[i];
        temp->link = NULL;

        // New node being assigned as the new tail end of the list
        ptr->link = temp;
        ptr = temp;
    } // End For

    // For loop adds all of lineCode4 to the single list
    for (i = 0; i < SIZE; i++)
    {
       // New node created
        temp = malloc(sizeof(struct node));
        temp->linkedList = lc4[i];
        temp->link = NULL;

        // New node being assigned as the new tail end of the list
        ptr->link = temp;
        ptr = temp;
    } // End For
    
    // Call function to display the new data
    listReport(head);

    return head; // For task 4

} // End listCreate()



// listReport() - Displays the whole single-list containing all 4 production lines
void listReport(struct node *head)
{
    // Initialise Variables
    struct node *ptr = NULL;


    // If list is empty, displays message saying nothing is present
    if (head == NULL)
    {
        printf("\n\nList is empty\n");
    } // End If

    // ptr will be used to navigate through the list - pointing at head to start
    ptr = head;
    printf("\n\n\n\nTask 2 - Copying the data structures from all 4 Production Lines into a Single Linked-List");
    printf("\n\nLine ID | Product ID | Issue Code");
    printf("\n----------------------------------");

    // ptr will continue to go through the list until NULL is found
    while (ptr != NULL)
    {
        printf("\n%d\t| %d      | %d ",ptr->linkedList.lineCodeNo, ptr->linkedList.prodID, ptr->linkedList.issueInfo.issCode);
        ptr = ptr->link; // ptr navigation, this is how ptr moves from node to node
    } // End While

} // End listReport()



// prodIssueFinder() - contains the functions for task 3 to find earliest occurrence of a specified product id and issue code
void prodIssueFinder(struct manuData lc1[], struct manuData lc2[], struct manuData lc3[], struct manuData lc4[])
{
    // Initialise Variables
    struct manuData temporaryStruct[4]; // Stores the variable from each production line called the 'earliestOccur'
    int low = 0;
    int high = SIZE - 1;
    int targetProdID = 0;
    int targetIssCode = 0;
    int location = 0;
    int i = 0; // Used to determine where the occurrences are stored, as well as determining the size of the loop for linear search


    printf("\n\n\n\nTask 3 - Locating the earliest occurrence of a specified product ID and issue code");
    printf("\n\nProduct Manual:\t\t60824, 60928, 61670, 61746, 61847, 62026, 62106, 62935, 63342, 64033, 64516, 64843, 65460, 65833, 66201, 66395, 67490, 67733, 68868, 68931");
    printf("\nIssue Code Manual:\t70123, 71234, 71495, 74592, 76210, 79601, 79820");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n\nPlease enter the Product ID and Issue Code you wish to find");
    printf("\nEnter Product ID: ");
    scanf("%d", &targetProdID);
    printf("Enter Issue Code: ");
    scanf("%d", &targetIssCode);
    

    // LineCode1
    location = binarySearch(lc1, low, high, targetProdID, targetIssCode); 

    if(location > -1)
    {
        temporaryStruct[i] = lc1[location];
        i++; // Increment i to set up the temporaryStruct for the next location
    } // End If


    // LineCode2
    location = binarySearch(lc2, low, high, targetProdID, targetIssCode); 

    if(location > -1)
    {
        temporaryStruct[i] = lc2[location];
        i++; // Increment i to set up the temporaryStruct for the next location
    } // End If


    // LineCode3
    location = binarySearch(lc3, low, high, targetProdID, targetIssCode); 

    if(location > -1)
    {
        temporaryStruct[i] = lc3[location];
        i++; // Increment i to set up the temporaryStruct for the next location
    } // End If


    // LineCode4
    location = binarySearch(lc4, low, high, targetProdID, targetIssCode);

    if(location > -1)
    {
        temporaryStruct[i] = lc4[location];
        i++; // Increment i to set up the temporaryStruct for the size of the temporary Structure
    } // End If


    // Tells user if the product ID and Issue Code pair exists or not
    if (i == 0)
    {
        printf("\nProduct ID: %d, Issue Code: %d does not exist within the Production Lines", targetProdID, targetIssCode);
    } // End If
    else
    {
        linearSearch(temporaryStruct, targetProdID, targetIssCode, i);
    } // End Else

} // End prodIssueFinder()



// binarySearch() - Halves the list continuously until product ID and issue code are found
int binarySearch(struct manuData lineCode[], int low, int high, int targetProdID, int targetIssCode) 
{
    // Initialise Variables
    int mid = 0;
    int earliestOccur = -1; // Initialize to -1 indicating not found


    // While loop does not end until one variable is left, or until the target product and issue code is found
    while (low <= high) 
    {
        mid = (low + high) / 2; // New mid reassigned after every iteration

        // Move Left
        if (lineCode[mid].prodID > targetProdID || (lineCode[mid].prodID == targetProdID && lineCode[mid].issueInfo.issCode > targetIssCode)) 
        {
            high = mid - 1;
        } // End If
        // Move Right 
        else if (lineCode[mid].prodID < targetProdID || (lineCode[mid].prodID == targetProdID && lineCode[mid].issueInfo.issCode < targetIssCode)) 
        {
            low = mid + 1;
        } // End Else If
        else 
        {
            earliestOccur = mid; // Match Found, so check if there are earlier occurrences
            while (mid > 0 && lineCode[mid - 1].prodID == targetProdID && lineCode[mid - 1].issueInfo.issCode == targetIssCode) 
            {
                earliestOccur = --mid; // Pre-Decrementing to check earlier occurrences
            } // End While
            break; // Break out of loop once earliest occurrence is found
        } // End Else
    } // End While

    return earliestOccur; // This will be returned is no value is found

} // End binarySearch()



// linearSearch() - Linear Search finds the earliest occurrence of the specified Product ID and Issue Code from the 4 Production Lines
void linearSearch(struct manuData tempStruct[], int targetProdID, int targetIssCode, int size)
{
    // Initialising Variables
    int i;
    struct manuData earliestOccur = tempStruct[0];


    // For loop will start from 1 since 0 is already assigned as the smallest
    for (i = 1; i < size; i++)
    {
        // If tempStruct[i].timeInfo.day is smaller than the earliestOccur.day, tempStruct will be reassigned as the earliest 
        if (earliestOccur.timeInfo.day > tempStruct[i].timeInfo.day)
        {
            earliestOccur = tempStruct[i];
        } // End Inner If
        // If tempStruct[i].timeInfo.day is equal to the earliestOccur.day, compare the hours
        else if (earliestOccur.timeInfo.day == tempStruct[i].timeInfo.day)
        {
            // If tempStruct[i].timeInfo.hr is smaller than the earliestOccur.hr, tempStruct will be reassigned as the earliest 
            if (earliestOccur.timeInfo.hr > tempStruct[i].timeInfo.hr)
            {
                earliestOccur = tempStruct[i];
            } // End Inner If
            // If tempStruct[i].timeInfo.hr is equal to the earliestOccur.hr, compare the mins
            else if (tempStruct[i].timeInfo.hr == earliestOccur.timeInfo.hr && tempStruct[i].timeInfo.min < earliestOccur.timeInfo.min)
            {
                    earliestOccur = tempStruct[i];
            } // End Inner Else If
        } // End Inner Else If
    } // End For

    // Display the found product ID and Issue Code
    printf("\nEarliest Occurrence for Product ID: %d, Issue Code: %d found", targetProdID, targetIssCode);
    printf("\nProduction Line | Product ID | Issue Code | Date and Time (Day and Time)");
    printf("\n-----------------------------------------------------------------------------");
    printf("\n%d\t\t| %d\t     | %d\t  | %d  %d: %d", earliestOccur.lineCodeNo, earliestOccur.prodID, earliestOccur.issueInfo.issCode, earliestOccur.timeInfo.day, earliestOccur.timeInfo.hr, earliestOccur.timeInfo.min);
    
} // End linearSearch()



// issueReport() - Summarises the number of issues reported for each product ID
void issueReport(struct node *head)
{
    // Initialise Variables
    struct node *ptr = NULL;
    int i = 0;


    // Task 4 - Initialise Variables
    int productIDMan[PROD_SIZE] = {60824, 60928, 61670, 61746, 61847, 62026, 62106, 62935, 63342, 64033, 64516, 64843, 65460, 65833, 66201, 66395, 67490, 67733, 68868, 68931};
    int issueQuantity[PROD_SIZE] = {0}; // Used to count the quantity of each issue code


    // If list is empty, displays message saying nothing is present
    if (head == NULL)
    {
        printf("\n\nList is empty\n");
    } // End If

    // ptr will be used to navigate through the list - pointing at head to start
    ptr = head;


    // ptr will continue to go through the list until i < PROD_SIZE
    while (i < PROD_SIZE)
    {   
        // Checks for the current product ID - this also means that another issue for that product ID is found
        if (ptr->linkedList.prodID == productIDMan[i])
        {
            issueQuantity[i]++; // Counter for the quantity of issues per product 
        } // End If

        ptr = ptr->link; // ptr navigation, this is how ptr moves from node to node

        if (ptr == NULL)
        {
            ptr = head;
            i++;
        } // End Inner If
    } // End While

    printf("\n\n\n\nTask 4 - Calculates the number of issues reported per product ID");
    printf("\n\nProduct ID | Number of Issue Reports");
    printf("\n--------------------------------------------");
    
    // Display the data of product IDs and Quantity of issue codes found per product ID
    for (i = 0; i < PROD_SIZE; i++)
    {
        printf("\n%d\t   | \t%d", productIDMan[i], issueQuantity[i]);
    } // End For

} // End listReport()


