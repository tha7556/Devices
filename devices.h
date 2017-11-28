

/****************************************************************************/
/*                                                                          */
/* 			     Module DEVICES                                 */
/*			 External Declarations                              */
/*                                                                          */
/****************************************************************************/



/* external define constants */

#define PAGE_SIZE      512                /* size of a page in bytes        */
#define MAX_TRACK      60                 /* num of tracks on a devices     */
#define TRACK_SIZE     1024               /* track size on each device      */
#define MAX_BLOCK      MAX_TRACK * TRACK_SIZE / PAGE_SIZE
                                          /* num of blocks on a device      */
#define MAX_DEV        2                  /* size of the device table       */



/* external enumeration constants */

typedef enum {
    false, true                         /* the boolean data type            */
} BOOL;

typedef enum {
    read, write                         /* type of actions for I/O requests */
} IO_ACTION;

typedef enum { 
    running, ready, waiting, done       /* types of status                  */
} STATUS;

typedef enum {
    iosvc, devint,                      /* types of interrupt               */
    pagefault, startsvc,
    termsvc, killsvc,
    waitsvc, sigsvc, timeint
} INT_TYPE;



/* external type definitions */

typedef struct page_tbl_node PAGE_TBL;
typedef struct event_node EVENT;
typedef struct ofile_node OFILE;
typedef struct pcb_node PCB;
typedef struct iorb_node IORB;
typedef struct int_vector_node INT_VECTOR;
typedef struct dev_entry_node DEV_ENTRY;





/* external data structures */

extern struct pcb_node {
    int    pcb_id;         /* PCB id                                        */
    int    size;           /* process size in bytes; assigned by SIMCORE    */
    int    creation_time;  /* assigned by SIMCORE                           */
    int    last_dispatch;  /* last time the process was dispatched          */
    int    last_cpuburst;  /* length of the previous cpu burst              */
    int    this_cpuburst;  /* accumulated CPU time of this burst            */
    int    burst_estimate; /* estimate of next CPU burst                    */
    int    accumulated_cpu;/* accumulated CPU time                          */
    PAGE_TBL *page_tbl;    /* page table associated with the PCB            */
    STATUS status;         /* status of process                             */
    EVENT  *event;         /* event upon which process may be suspended     */
    int    priority;       /* user-defined priority; used for scheduling    */
    PCB    *next;          /* next pcb in whatever queue                    */
    PCB    *prev;          /* previous pcb in whatever queue                */
    int    *hook;          /* can hook up anything here                     */
};


struct event_node {
    int    event_id;    /* event id                                         */
    BOOL   happened;    /* indicates if the event has happebed (= true)     */
    PCB    *waiting_q;  /* queue of PCBs suspended on this event            */
    int    *hook;       /* can hook up anything here                        */
};

struct iorb_node {
    int    iorb_id;     /* iorb id                                          */
    int    dev_id;      /* associated device; index into the device table   */
    IO_ACTION action;   /* read/write                                       */
    int    block_id;    /* block involved in the I/O                        */
    int    page_id;     /* buffer page in the main memory                   */
    PCB    *pcb;        /* PCB of the process that issued the request       */
    EVENT  *event;      /* event used to synchronize processes with I/O     */
    OFILE  *file;       /* associated entry in the open files table         */
    IORB   *next;       /* next iorb in the device queue                    */
    IORB   *prev;       /* previous iorb in the device queue                */
    int    *hook;       /* can hook up anything here                        */
};

struct int_vector_node {
    INT_TYPE cause;           /* cause of interrupt                         */
    PCB    *pcb;              /* PCB to be started (if startsvc), or pcb    */
                              /* causing page fault (if pagefault interrupt)*/
    int    page_id;           /* page causing pagefault                     */
    int    dev_id;            /* device causing devint                      */
    EVENT  *event;            /* event involved in waitsvc and sigsvc calls */
    IORB   *iorb;             /* IORB involved in iosvc call                */
};


struct dev_entry_node {
    int    dev_id;      /* device id - index into Dev_Tbl                   */
    BOOL   busy;        /* the busy flag ("true", if busy)                  */
    BOOL   free_blocks[MAX_BLOCK];
                        /* block i is free: free_blocks[i] = true;          */
                        /* else: = false                                    */
    int    num_of_free_blocks;
    IORB   *iorb;       /* the iorb currently being processed by the device */
    int    *dev_queue;  /* optional: may point to the iorb queue to the dev */
    int    *hook;       /* can hook up anything here                        */
};



/* external variables */

extern INT_VECTOR Int_Vector;                   /* interrupt vector         */
extern DEV_ENTRY Dev_Tbl[MAX_DEV];              /* device table             */

extern int    ______trace_switch;


/* external routines */

extern siodev(/* iorb */);
extern lock_page(/* iorb */);
extern unlock_page(/* iorb */);
extern notify_files(/* iorb */);
/*  IORB   *iorb; */




/* end of module */
