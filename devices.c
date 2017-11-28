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
char *toString(IORB *i);
Queue queues[MAX_DEV];
void devices_init()
{
    if (______trace_switch) printf("\tINITIALIZING ARRRRGGGH\n\n");
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
    if (______trace_switch) printf("\tENQ_IO ARRRRGGGH\n\n");
    enQueueSorted(&queues[iorb->dev_id],iorb,compareTo);

    if(Dev_Tbl[iorb->dev_id].busy == false) {
        lock_page(iorb);
        Dev_Tbl[iorb->dev_id].iorb = iorb;
        Dev_Tbl[iorb->dev_id].busy = true;
        siodev(iorb);
        //setCurrent(&queues[iorb->dev_id],findValue(&queues[iorb->dev_id],iorb,compareTo));
    }
}
void deq_io(IORB *iorb)
{
    if (______trace_switch) printf("\tDEQ_IO ARRRRGGGH\n\n");
    Queue *queue = &queues[iorb->dev_id];
    //QueueNode *node = getCurrentNode(queue);
    QueueNode *node = findNode(queue,iorb,compareTo);
    int devId = iorb->dev_id;
    if (______trace_switch) printf("\tparam: %s\n\n",toString(iorb));
    if(node == NULL)
        printQ(queue,"Queue:\n",toString);
    if (______trace_switch) printf("\tUNLOCKING PAGES\n\n");
    unlock_page(node->data);
    if (______trace_switch) printf("\tNOTIFY THE TROOPS\n\n");
    notify_files(node->data);
    if (______trace_switch) printf("\tADVANCE TROOPS\n\n");
    advance(queue);
    if (______trace_switch) printf("\tREMOVING\n\n");
    removeNode(queue,node);
    if(getCurrentNode(queue) == NULL) {
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
    if (______trace_switch) printf("\tTHE PURGE!!!\n\n");
    int i = 0;
    for(i = 0; i < MAX_DEV; i++) {
        QueueNode *node = frontNode(&queues[i]);
        printQ(&queues[i],"Queue:",toString);
        while(node != NULL) {
            QueueNode *nextNode = node->next;
            IORB *iorb = node->data;
            if(getCurrentNode(&queues[i]) == NULL)
                 printQ(&queues[i],"Current = NULL",toString);
            if(node != getCurrentValue && iorb->pcb == pcb) { //node not being serviced and contains the pcb
                if (______trace_switch) printf("\tremoving node: %s\n\n",toString(node->data));
                removeNode(&queues[i],node);
                notify_files(iorb);
            }
            node = nextNode;
        }
    }
}
int compareTo(IORB *i1, IORB *i2) {
    if (______trace_switch) printf("\tCOMPARETO ARRRRGGGH\n\n");
    int trackNum1 = (i1->block_id * PAGE_SIZE)/TRACK_SIZE;
    int trackNum2 = (i2->block_id * PAGE_SIZE)/TRACK_SIZE;
    return trackNum1 - trackNum2;
}
char *toString(IORB *i) {
    static char result[BUFSIZ];
    if (i == NULL) sprintf (result, "(null) ");
    else
        sprintf (result, "IORB %d(Track#-%d)\n", i->iorb_id,(i->block_id * PAGE_SIZE)/TRACK_SIZE);

    return result;
}


/* end of module */
