/****************************************************************************/
/* File: queue.h
 * Author: Clayton S. Ferner
 * Date: 9/23/05
 */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/*              Simple Queue ADT                                            */
/*                                                                          */
/*              Declarations                                                */
/*                                                                          */
/****************************************************************************/

#include <stdio.h>

typedef struct queueNode {
    struct queueNode *next, *prev;
    void *data;
} QueueNode;

typedef struct queueType {
    QueueNode *head;
    QueueNode *tail;
    QueueNode *current;
} Queue;

typedef QueueNode * QueueIterator;



/****************************************************************************/
/* Function: initQueue
 * Parameters: a pointer to a Queue
 * Return: none
 * Description: This function will initialize the Queue. A pointer
 *              to the queue should be provided by the user. It is
 *              up to the user to create or allocate the queue, as
 *              well as destroy it if necessary.
 */
/****************************************************************************/
void initQueue(Queue *self);



/****************************************************************************/
/* Function: isEmpty
 * Parameters: a pointer to a Queue
 * Return: true or false
 * Description: This function will true is the queue is empty, false otherwise.
 */
/****************************************************************************/
int isEmpty(Queue *self);



/****************************************************************************/
/* Function: enQueue
 * Parameters: a pointer to a Queue
 *             a pointer to the data to be inserted
 * Return: none
 * Description: This function will append a new QueueNode which contains
 *              the data to the end of the Queue.
 */
/****************************************************************************/
void enQueue(Queue *self, void *data);


/****************************************************************************/
/* Function: enQueueSorted
 * Parameters: a pointer to a Queue
 *             a pointer to the data to be inserted
 *             a function that can compare two data objects
 * Return: none
 * Description: This function will insert a new QueueNode which contains
 *              the data to the Queue. The data is inserted before the
 *              first node found (when searching from the front) that
 *              contains data greater than this data according to the
 *              compareTo function.  The compareTo function must be
 *              provided by the user and must take two data pointers as
 *              parameters.  It should return a
 *                 - negative integer if the first parameter is less than
 *                   the second parameters,
 *                 - positive integer if the first parameter is greater than
 *                   the second parameters,
 *                 - zero integer if the two parameter are equal
 *
 *              The queue should already be sorted for this to maintain a
 *              sorted queue.  In other words, the user should use EITHER
 *              enQueue() or enQueueSorted() BUT NOT BOTH.  The purpose
 *              is so that the queue can be used as a priority queue.
 *              NOTE: This is an inefficient way to implement a priority
 *              queue, because it is basically insertion sort, which is O(N^2).  
 *              It is used here because sometimes it is helpful to have the
 *              data in the queue actually be sorted, such as I/O management.  
 *              If one desires a O(logN) operation, then use a heap.
 */
/****************************************************************************/
void enQueueSorted(Queue *self, void *data, int (*compareTo)());


/****************************************************************************/
/* Function: frontValue
 * Parameters: a pointer to a Queue
 * Return:     a pointer to the data at the front of the Queue or 
 *             NULL if the Queue is empty
 * Description: This function return the data at the front of the Queue, 
 *              if it is not empty, but will not remove the data. If the 
 *              Queue is empty, then it will return NULL.
 */
/****************************************************************************/
void *frontValue(Queue *self);


/****************************************************************************/
/* Function: frontNode
 * Parameters: a pointer to a Queue
 * Return:     a pointer to the QueueNode at the front of the Queue or 
 *             NULL if the Queue is empty
 * Description: This function return the QueueNode at the front of the Queue, 
 *              if it is not empty, but will not remove the data. If the 
 *              Queue is empty, then it will return NULL.
 */
/****************************************************************************/
QueueNode *frontNode(Queue *self);


/****************************************************************************/
/* Function: backValue
 * Parameters: a pointer to a Queue
 * Return:     a pointer to the data at the back of the Queue or
 *             NULL if the Queue is empty
 * Description: This function return the data at the back of the Queue,
 *              if it is not empty, but will not remove the data. If the
 *              Queue is empty, then it will return NULL.
 */
/****************************************************************************/
void *backValue(Queue *self);


/****************************************************************************/
/* Function: backNode
 * Parameters: a pointer to a Queue
 * Return:     a pointer to the QueueNode at the back of the Queue or
 *             NULL if the Queue is empty
 * Description: This function return the QueueNode at the back of the Queue,
 *              if it is not empty, but will not remove the data. If the
 *              Queue is empty, then it will return NULL.
 */
/****************************************************************************/
QueueNode *backNode(Queue *self);


/****************************************************************************/
/* Function: deQueue
 * Parameters: a pointer to a Queue
 * Return:     a pointer to the data at the front of the Queue or 
 *             NULL if the Queue was empty
 * Description: This function return the data at the front of the Queue, 
 *              if it is not empty.  It will also remove the data, and
 *              free the corresponding QueueNode.  If the Queue is empty, 
 *              then it will return NULL.
 */
/****************************************************************************/
void *deQueue(Queue *self);


/****************************************************************************/
/* Function: removeNode
 * Parameters: a pointer to a Queue
 *             a pointer to a QueueNode
 * Return:     none
 * Description: This function will remove the QueueNode from the Queue, if it 
 *              is in the queue.  It will also free the QueueNode.  IT WOULD
 *              BE AN ERROR TO ATTEMPT TO USE THE QueueNode OR ITS POINTER
 *              AFTER CALLING THIS FUNCTION.
 */
/****************************************************************************/
void removeNode(Queue *self, QueueNode *p);



/****************************************************************************/
/* Function: findNode
 * Parameters: a pointer to a Queue
 *             a pointer to data
 *             a function that can compare two data objects
 * Return:     a pointer to a QueueNode that contains data that equals
 *             the data given as a parameter, or NULL if it is not found
 * Description: This function will return the QueueNode if it is found in 
 *              the queue, NULL if it is not. The compareTo function must be
 *              provided by the user and must take two data pointers as
 *              parameters.  It should return a
 *                 - negative integer if the first parameter is less than 
 *                   the second parameters,  
 *                 - positive integer if the first parameter is greater than
 *                   the second parameters,  
 *                 - zero integer if the two parameter are equal
 */
/****************************************************************************/
QueueNode *findNode(Queue *self, void *data, int (*compareTo)());


/****************************************************************************/
/* Function: findValue
 * Parameters: a pointer to a Queue
 *             a pointer to data
 *             a function that can compare two data objects
 * Return:     the data in the queue that equals the data given as a 
 *             parameter, or NULL if it is not found
 * Description: This function will return the data if it is found in 
 *              the queue, NULL if it is not. The compareTo function must be
 *              provided by the user and must take two data pointers as
 *              parameters.  It should return a
 *                 - negative integer if the first parameter is less than 
 *                   the second parameters,  
 *                 - positive integer if the first parameter is greater than
 *                   the second parameters,  
 *                 - zero integer if the two parameter are equal
 */
/****************************************************************************/
void *findValue(Queue *self, void *data, int (*compareTo)());


/****************************************************************************/
/* Function: purge 
 * Parameters: a pointer to a Queue
 *             a pointer to data
 *             a function that can compare two data objects
 * Return:     none
 * Description: This function will remove all data data from the queue that is
 *              equal to the given parameter. The compareTo function must be 
 *              provided by the user and must take two data pointers as
 *              parameters.  It should return a
 *                 - negative integer if the first parameter is less than 
 *                   the second parameters,  
 *                 - positive integer if the first parameter is greater than
 *                   the second parameters,  
 *                 - zero integer if the two parameter are equal
 */
/****************************************************************************/
void purge(Queue *self, void *data, int (*compareTo)());



/****************************************************************************/
/* Function: printQ
 * Parameters: a pointer to a Queue
 *             a string label
 *             a function that can convert the data to a string
 * Return:     none
 * Description: This function will print the label and the contents of 
 *              the queue to stdout.  Asterisks will surround
 *              the item that current points to (if it isn't pastEnd).
 *              The toString function must be provided and must take a 
 *              data pointer as a parameter.   It should return a string 
 *              that will be printed to the file.  It is assumed that the 
 *              string will be available briefly after the toString has 
 *              returned.  It is advisable that the toString function use 
 *              a static string for this purpose.  The contents of that 
 *              string will not be modified, and will no longer be 
 *              required after printing its contents.
 */
/****************************************************************************/
void printQ(Queue *self, char *label, char *(*toString)());


/****************************************************************************/
/* Function: fprintQ
 * Parameters: a file descriptor 
 *             a pointer to a Queue
 *             a string label
 *             a function that can convert the data to a string
 * Return:     none
 * Description: This function will print the label and the contents of 
 *              the queue to the file descriptor.  Asterisks will surround
 *              the item that current points to (if it isn't pastEnd).
 *              The toString function must be provided and must take a 
 *              data pointer as a parameter.   It should return a string 
 *              that will be printed to the file.  It is assumed that the 
 *              string will be available briefly after the toString has 
 *              returned.  It is advisable that the toString function use 
 *              a static string for this purpose.  The contents of that 
 *              string will not be modified, and will no longer be 
 *              required after printing its contents.
 */
/****************************************************************************/
void fprintQ(FILE *fd, Queue *self, char *label, char *(*toString)());
void fprintQN(FILE *fd, Queue *self, char *label, char *(*toString)());



/****************************************************************************/
/* Function: setCurrent
 * Parameters: a pointer to a Queue
 *             a poiner to a QueueNode
 * Return:     none
 * Description: This function will set the current pointer to point to the
 *              QueueNode given as an argument.  A current value of NULL is
 *              considered past the end of the queue.
 */
/****************************************************************************/
void setCurrent(Queue *self, QueueNode *c);


/****************************************************************************/
/* Function: advance
 * Parameters: a pointer to a Queue
 * Return:     none
 * Description: This function will set the current pointer to point to the
 *              next QueueNode.  A current value of NULL is
 *              considered past the end of the queue.
 */
/****************************************************************************/
void advance(Queue *self);


/****************************************************************************/
/* Function: retreat
 * Parameters: a pointer to a Queue
 *             a poiner to a QueueNode
 * Return:     none
 * Description: This function will set the current pointer to point to the
 *              previous QueueNode.  A current value of NULL is
 *              considered past the end of the queue.
 */
/****************************************************************************/
void retreat(Queue *self);


/****************************************************************************/
/* Function: isPastEnd 
 * Parameters: a pointer to a Queue
 * Return:     boolean 
 * Description: This function will return true if the current is NULL (i.e.
 *              past the end of the queue), else returns false (current is
 *              not NULL).
 */
/****************************************************************************/
int isPastEnd(Queue *self);


/****************************************************************************/
/* Function: getCurrentNode
 * Parameters: a pointer to a Queue
 * Return:     a pointer to the QueueNode that current points to or NULL
 * Description: This function will return a pointer to the QueueNode that
 *              current currently points to if current is not NULL.  If 
 *              is NULL, then it returns NULL.
 */
/****************************************************************************/
QueueNode *getCurrentNode(Queue *self);


/****************************************************************************/
/* Function: getCurrentValue
 * Parameters: a pointer to a Queue
 * Return:     the data that current points to or NULL
 * Description: This function will return a pointer to the data that
 *              current currently points to if current is not NULL.  If 
 *              is NULL, then it returns NULL.
 */
/****************************************************************************/
void *getCurrentValue(Queue *self);


/****************************************************************************/
/* Function: setIterator
 * Parameters: a pointer to a QueueIterator
 *             a poiner to a QueueNode
 * Return:     none
 * Description: This function will set the iterator to point to the
 *              QueueNode given as an argument.  
 */
/****************************************************************************/
void setIterator(QueueIterator *self, QueueNode *c);


/****************************************************************************/
/* Function: advanceIterator
 * Parameters: a pointer to a Queue
 * Return:     none
 * Description: This function will set the current pointer to point to the
 *              next QueueNode.  A current value of NULL is
 *              considered past the end of the queue.
 */
/****************************************************************************/
void advanceIterator(QueueIterator *self);


/****************************************************************************/
/* Function: retreatIterator
 * Parameters: a pointer to a QueueIterator
 *             a poiner to a QueueNode
 * Return:     none
 * Description: This function will set the current pointer to point to the
 *              previous QueueNode.  A current value of NULL is
 *              considered past the end of the queue.
 */
/****************************************************************************/
void retreatIterator(QueueIterator *self);


/****************************************************************************/
/* Function: isIteratorPastEnd 
 * Parameters: a pointer to a QueueIterator
 * Return:     boolean 
 * Description: This function will return true if the current is NULL (i.e.
 *              past the end of the queue), else returns false (current is
 *              not NULL).
 */
/****************************************************************************/
int isIteratorPastEnd(QueueIterator *self);


/****************************************************************************/
/* Function: getIteratorNode
 * Parameters: a pointer to a QueueIterator
 * Return:     a pointer to the QueueNode that current points to or NULL
 * Description: This function will return a pointer to the QueueNode that
 *              current currently points to if current is not NULL.  If 
 *              is NULL, then it returns NULL.
 */
/****************************************************************************/
QueueNode *getIteratorNode(QueueIterator *self);


/****************************************************************************/
/* Function: getIteratorValue
 * Parameters: a pointer to a QueueIterator
 * Return:     the data that current points to or NULL
 * Description: This function will return a pointer to the data that
 *              current currently points to if current is not NULL.  If 
 *              is NULL, then it returns NULL.
 */
/****************************************************************************/
void *getIteratorValue(QueueIterator *self);

