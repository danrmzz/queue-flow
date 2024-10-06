# Ticket Queue Simulation

This is a queue management system designed to handle customer assignments to multiple service booths, ensuring optimal performance with linked list data structures. The project dynamically allocates customers to booths, efficiently distributing the load, and processes customers based on their arrival time.

## Features

- **Linked List Queue Management**: Uses a linked list-based queue to minimize operational latency.
- **Optimized Enqueue and Dequeue Operations**: Processes customers with O(1) enqueue and dequeue operations.
- **Dynamic Queue Assignment**: Customers are dynamically assigned to the least occupied queue based on their name’s first letter.
- **Booth Assignment**: Evenly distributes customers across booths, allowing for optimal booth utilization and balanced queue lengths.
- **Output**: Prints the result of customer checkouts as they exit their booths.

## Purpose

This is designed to simulate the flow of customers through a theoretical ticketing system with multiple service booths. It handles dynamic customer assignments and optimizes processing efficiency using a linked list for queue management. This project ensures smooth customer flow, balanced resource utilization, and avoids memory leaks with proper dynamic memory management.

## Sample Output

```plaintext
Booth 1
John from line 3 checks out at time 155.
Alice from line 1 checks out at time 190.

Booth 2
Bob from line 2 checks out at time 200.

Booth 3
Eva from line 5 checks out at time 220.
```

## How It Works

1. **Customer Assignment**:
   - Customers are assigned to different queues based on the first letter of their names.
   - The queues are dynamically allocated using a linked list structure to optimize memory usage and operational efficiency.

2. **Booth Assignment**:
   - Queues are assigned to booths evenly based on the number of non-empty queues and operating booths.
   - Customers are processed based on their arrival time within each queue.

3. **Customer Processing**:
   - Each customer is processed based on their number of tickets and arrival time. 
   - The system outputs when each customer checks out of the assigned booth, keeping track of processing times.

## Technologies Used

- **C Language**: The core programming language used for the project.
- **Dynamic Memory Management**: Proper memory allocation and deallocation are used to prevent memory leaks.
- **Linked List**: Utilized for managing the queue to allow efficient insertion and removal of customers.

## Class Structure

1. **Customer Struct**:
   - Holds customer data including name, number of tickets, line number, and time of entry/exit.

2. **Queue Struct**:
   - Contains a linked list that manages the queue of customers, handling dynamic memory allocation.

3. **Node Struct**:
   - Represents each element in the queue, storing a pointer to the customer and the next node in the queue.

## How to Run

1. **Clone the repository**:
   ```bash
   git clone https://github.com/danrmzz/queue-flow.git
   cd queue-flow
   ```

2. **Compile and run the program**:
   ```bash
   gcc main.c -o queue_flow
   ./queue_flow
   ```
