#include "queue.h"
#include "devices.h"



/****************************************************************************/
/*									    */
/*									    */
/*				Module DEVICES				    */
/*                             Internal Routines                            */
/*									    */
/*									    */
/****************************************************************************/

int compareTo(IORB *i1, IORB *i2);
Queue queues[MAX_DEV];
void devices_init()
{
    int i;
    for(i = 0; i < MAX_DEV; i++) {
        Queue queue;
        initQueue(&queue);
        queues[i] = queue;

        Dev_Tbl[i].busy = false;
        Dev_Tbl[i].iorb = NULL;
    }

}
void enq_io(IORB *iorb) {
    enQueueSorted(&queues[iorb->dev_id],iorb,compareTo);

    lock_page(iorb);
    Dev_Tbl[iorb->dev_id].iorb = iorb;
    Dev_Tbl[iorb->dev_id].busy = true;
    siodev(iorb);
}
void deq_io(IORB *iorb)
{
    Queue *queue = &queues[iorb->dev_id];
    QueueNode *node = getCurrentNode(queue);
    int devId = iorb->dev_id;

    unlock_page(node->data);
    notify_files(node->data);

    advance(queue);
    removeNode(queue,node);
    if(isPastEnd(queue)) {
        setCurrent(queue,frontNode(queue));
    }

    if(frontNode(queue) != NULL) {
        IORB *newIorb = getCurrentValue(queue);
        lock_page(newIorb);
        Dev_Tbl[newIorb->dev_id].iorb = newIorb;
        Dev_Tbl[newIorb->dev_id].busy = true;
        siodev(newIorb);
    }
    else {
        Dev_Tbl[devId].busy = false;
        Dev_Tbl[devId].iorb = NULL;
    }

}
void purge_iorbs(PCB *pcb)
{
    int i = 0;
    for(i = 0; i < MAX_DEV; i++) {
        QueueNode *node = frontNode(&queues[i]);
        while(node != NULL) {
            QueueNode *nextNode = node->next;
            IORB *iorb = node->data;
            if(node != getCurrentValue && iorb->pcb == pcb) { //node not being serviced and contains the pcb
                removeNode(&queues[i],node);
                notify_files(iorb);
            }
            node = nextNode;
        }
    }
}
int compareTo(IORB *i1, IORB *i2) {
    int trackNum1 = (i1->block_id * PAGE_SIZE)/TRACK_SIZE;
    int trackNum2 = (i2->block_id * PAGE_SIZE)/TRACK_SIZE;
    return trackNum1 - trackNum2;
}


/* end of module */
