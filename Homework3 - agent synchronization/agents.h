/* ________________________________________________________________________

    Header File: agent.h
      of the program AGENTS.C.  part 1 of 3.

      Related Files:           1. agents.h   -  Global Constants.
                               2. agents.c   -  Agent actions.
                               3. agents.doc -  Doc file.

      Description:         Here are all the Constants needed to
                           initiate the work of the agents program.

      Note:                You may change some for expermintal use.
__________________________________________________________________________ */

#ifndef __AGENT_H
#define __AGENT_H


#define OPERATIONS  20       /* Number of Operation for each Agent      */
                             /* Change it to 30 to check your solution. */

#define MAX_OPER    50       /* Maximum absolute order of one operation */

#define START_SUM  500
#define ACCOUNT  "account"   /* Name of Account File */

#define ERROR    999999 /* smth very unlogical for sum to get upto this limit*/
#define SUCCESS     0

#define BUF_LENGTH  64       /* buffer size used by read */
#define NAMES_LEN   3        /* Agent's Name length + 1 */
#define MAX_AGENTS  8        /* Maximum number of agents */
#define AGENTS {"A1","A2","A3","A4","A5","A6","A7","A8"} /*Depends upon MAX_AGENTS!*/

#define RETRY      10        /* Number of retries for system calls */
#define MAX_SLEEP  2         /* Maximum seconds of rest for agent + 1 */
#define SLEEP      1         /* Sleeping time before retry of system call */


#endif

