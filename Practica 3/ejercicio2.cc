#include <sched.h>
#include <stdio.h>

int main (int argc, char **argv)
{
   int max_priority;
   int min_priority;
   struct sched_param param;
   
   int pid = atoi(argv[1]);
   
   int schedule = sched_getscheduler(pid);
   
   switch(sched_getscheduler(pid)) {
	case SCHED_OTHER:
		printf("Politica de planificación: SCHEDULE OTHER\n");
		break;
	case SCHED_FIFO:
		printf("Politica de planificación: SCHEDULE FIFO\n");
		break;
	case SCHED_RR:
		printf("Politica de planificación: SCHEDULE ROUND ROBIN\n");
		break;
   }
   
   max_priority = sched_get_priority_max(schedule);
   
   min_priority = sched_get_priority_min(schedule);
   
   printf("La prioridad maxima es: %d\n", max_priority);
   printf("La prioridad minima es: %d\n", min_priority);

   sched_getparam(pid, &param);

   printf("La prioridad asiganda es: %d\n", param.sched_priority);

   return(0);
}