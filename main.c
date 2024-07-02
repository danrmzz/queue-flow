#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Struct declarations
typedef struct customer {
    char* name; 
    int numTickets;
    int lineNumber;
    int timeIn;
    int timeOut;
} customer;

typedef struct node {
    customer* cPtr;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* back;
    int nodeCount;
    int boothNumber;
} queue;


// Function signatures
customer* createCustomer(char* Cname, int CnumTickets, int CtimeIn);

void enQueue(queue* qPtr, int lineNum, customer* customer);

void deQueue(queue* queue, int index);

char* peek(queue* qPtr);

int empty(queue* qPtr);

int size(queue* qPtr);

int getP(char* customerName); 

int assignQueue(int position, queue* queues); 

int numOfnonEmptyQ(queue* queues); 


// Main function
int main (void) {

    // Declaring variables
    int totalCustomers, operatingBooths, i;
    int inputNumTickets, inputTimeIn;
    char inputName[51];
    queue lines[13];
    customer* newCustomer;
    int p;
    int lineNumber, numNonEmpty, queuesPerBooth;
    int queuesExtra;


    // Initialize values for queues
    for (i = 0; i < 13; i++) {

        lines[i].front = NULL;
        lines[i].back = NULL;
        lines[i].nodeCount = 0;
        lines[i].boothNumber = 0;
    }


    // Scan # of customers and # of booths
    scanf("%d %d", &totalCustomers, &operatingBooths);

    // Puts all customers in their assigned queues
    for (i = 0; i < totalCustomers; i++) {

        // Scan name, # of tix, and in time for each customer
        scanf("%s %d %d", inputName, &inputNumTickets, &inputTimeIn);


        // Create a customer struct and store their information in it
        newCustomer = createCustomer(inputName, inputNumTickets, inputTimeIn);

        // Get position of first letter in alphabet
        p = getP(inputName); 

        // Determine which queue customer struct goes in
        lineNumber = assignQueue(p, lines); 
    
        // Update customer line number and add customer to their assigned queue
        newCustomer->lineNumber = lineNumber;
        enQueue(lines, lineNumber, newCustomer);
    }


    // Calculate number of non-empty queues
    numNonEmpty = numOfnonEmptyQ(lines);

    queuesPerBooth  = numNonEmpty/operatingBooths;
    queuesExtra  = numNonEmpty%operatingBooths;


    // Initialize variables to keep track of current booth and current queue
    int boothIndex = 1;
    int queueIndex = 1; 

    // Loop through non-empty queues and assign them to booths
    for (int i = 1; i <= 12; i++) {

        // If the queue is non-empty
        if (lines[i].front != NULL) {

            // Update the queue.boothNumber
            lines[i].boothNumber = boothIndex; // Assign queues to booths

            // Check if this booth gets an extra queue
            if (queuesExtra > 0) {
                // If yes, assign an extra queue to this booth
                if (queueIndex <= queuesPerBooth) {
                    queueIndex++;
                } else {
                    boothIndex++;
                    queueIndex = 1;
                    queuesExtra--;
                }
            } 
            
            else {
                // If no extra queues, just assign queues evenly
                if (queueIndex < queuesPerBooth) {
                    queueIndex++;
                } else {
                    boothIndex++;
                    queueIndex = 1;
                }
            }
        }
    }


     int boothI, processTime;

     int boothTiming[operatingBooths + 1];

     for (i = 1; i <= operatingBooths; i++) {

        boothTiming[i] = 0;
     }

    for (boothI = 1; boothI <= operatingBooths; boothI++) {

        printf("Booth %d\n", boothI);

        while(1) {

            int queueNumberofEarliestCustomer = -1;
            int earliestArrivalTime = 1000000001;

            // Determine which customer should be taken first from queue if multiple queues are assigned one booth
            // Process customer and dequeue them from their queue
            // Final print statements
            for (i = 1; i <= 12; i++) {


                if (lines[i].front != NULL && lines[i].boothNumber == boothI && lines[i].front->cPtr->timeIn < earliestArrivalTime) {

                    earliestArrivalTime = lines[i].front->cPtr->timeIn;
                    queueNumberofEarliestCustomer = i;

                }
            }
                if (queueNumberofEarliestCustomer == -1) 
                    break;


                if (lines[queueNumberofEarliestCustomer].front != NULL) {

                    if (lines[queueNumberofEarliestCustomer].front->cPtr->timeIn > boothTiming[boothI])
                        boothTiming[boothI] = lines[queueNumberofEarliestCustomer].front->cPtr->timeIn;
                    // Process Customer
                    processTime = 30 + lines[queueNumberofEarliestCustomer].front->cPtr->numTickets * 5;
                    lines[queueNumberofEarliestCustomer].front->cPtr->timeOut = processTime + boothTiming[boothI];


                    boothTiming[boothI] += processTime;
                    

                    printf("%s from line %d checks out at time %d.\n", lines[queueNumberofEarliestCustomer].front->cPtr->name,
                    lines[queueNumberofEarliestCustomer].front->cPtr->lineNumber, lines[queueNumberofEarliestCustomer].front->cPtr->timeOut);
                    
                    deQueue(lines, queueNumberofEarliestCustomer);
                }
        }
        printf("\n");
    }

    return 0;
}

// Function definitions:
// DMA create a customer struct and store their information
customer* createCustomer(char* Cname, int CnumTickets, int CtimeIn) {

    // DMA create a customer struct
    customer* c = (customer*)malloc(sizeof(customer));

    // DMA create an array for name inside of customer struct
    // and store customer name into customer struct
    c->name = (char*)malloc((strlen(Cname) + 1) * sizeof(char));
    strcpy(c->name, Cname);

    c->numTickets = CnumTickets;
    c->lineNumber = -1;
    c->timeIn = CtimeIn;

    return c;
}


// Gets the position in alphambet of the first letter of customer name 
int getP(char* customerName) {

    return (customerName[0] - 'A');
}


// Calculates which queue is assigned to each customer
int assignQueue(int position, queue* queues) {

    // If position % 13 equals 0
    if (position % 13 == 0) {

        int minQueueIndex = -1;
        int minQueueSize = 999999;

        // Iterate through all queues to find the one with the minimum number of customers
        for (int i = 1; i <= 12; i++) {
            // Check if the queue is non-empty and has fewer customers than the current minimum
            if (queues[i].nodeCount > 0 && queues[i].nodeCount < minQueueSize) {
                minQueueIndex = i;
                minQueueSize = queues[i].nodeCount;
            }
        }
        
        // If all queues are empty, assign the customer to the first queue
        if (minQueueIndex == -1) 
            minQueueIndex = 1;

        return minQueueIndex;
    }

    // If position % 13 is not equal to 0
    else
        return position % 13;
}


// Add a customer to their assigned queue WORKS
void enQueue(queue* qPtr, int lineNum, customer* customer) {

    // Create a new node
    node* newNode = (node*)malloc(sizeof(node));
    newNode->cPtr = customer;
    newNode->next = NULL;

    // If the queue is empty, make front and back the new node
    if (empty(&qPtr[lineNum]) == 1) {
        qPtr[lineNum].front = newNode;
        qPtr[lineNum].back = newNode;
    } else { // Link the new node to the back of the linked list and update back
        qPtr[lineNum].back->next = newNode;
        qPtr[lineNum].back = newNode;
    }

    // Increase nodeCount by 1
    qPtr[lineNum].nodeCount++;
}


// Calculate number of non-empty booths
int numOfnonEmptyQ(queue* queues) {

    int num = 0;

    for (int i = 1; i <= 12; i++) {

        if (queues[i].front != NULL)
            num ++;
    }

    return num;
}


// Check if a queue is empty
int empty(queue* qPtr) {
    return (qPtr->front == NULL);
}


// Remove a customer from their queue
void deQueue(queue* lines, int index) {

    // Check if the queue at the given index is empty
    if (empty(&lines[index])) {
        printf("Error: Attempting to dequeue from an empty queue.\n");
        return;
    }

    // Store a pointer to the front node to be dequeued
    node* temp = lines[index].front;

    // Move the front pointer to the next node
    lines[index].front = lines[index].front->next;

    // If there are no more nodes in the queue, update the back pointer as well
    if (lines[index].front == NULL) {
        lines[index].back = NULL;
    }

    // Free the memory allocated for the customer struct inside the dequeued node
    if (temp != NULL) {
        free(temp->cPtr->name);
        free(temp->cPtr);
    }

    // Free the memory allocated for the dequeued node itself
    free(temp);

}


// Peek the queue and get who is in the front
char* peek(queue* qPtr) {

    // Check if the queue is empty
    if (empty(qPtr)) {
        printf("Error: Queue is empty.\n");
        return NULL;
    }
    // Return the name of the customer at the front of the queue
    return qPtr->front->cPtr->name;
}


// Get the number of customers in a queue
int size(queue* qPtr) {
    return qPtr->nodeCount;
}
