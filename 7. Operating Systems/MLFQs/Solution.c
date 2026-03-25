#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Process Info
typedef struct
{
	char pid[20];
	int arrival;
	int burst;
	int remaining;
	int disrupt_flag;
	int queue_level;
	int time_in_q;    // units executed so far in current queue slot
	int interrupt_ct; // total interruptions for rule 8
	int quantum_rem;  // quantum remaining for this slot (used with disrupt_flag=1)
	int completion;
	int finished;
} Process;

// Queue
typedef struct
{
	Process **data;
	int capacity;
	int size;
	int front;
	int rear;
} Queue;

Queue *queue_create(int cap)
{
	Queue *q = (Queue *) malloc(sizeof(Queue));
	q->data = (Process **) malloc(cap * sizeof(Process *));
	q->capacity = cap;
	q->size = 0;
	q->front = 0;
	q->rear = 0;
	return q;
}

void enqueue(Queue *q, Process *p)
{
	if (q->size == q->capacity)
		return;
	q->data[q->rear] = p;
	q->rear = (q->rear + 1) % q->capacity;
	q->size++;
}

Process *dequeue(Queue *q)
{
	if (q->size == 0)
		return NULL;
	Process *p = q->data[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return p;
}

Process *peek(Queue *q)
{
	if (q->size == 0)
		return NULL;
	return q->data[q->front];
}

// Gantt Chart entry
typedef struct
{
	char pid[20];
	int start;
	int end;
} GanttEntry;

// Read processes from file
Process *read_processes(const char *filename, int *count)
{
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "Cannot open %s\n", filename);
		exit(1);
	}

	// count lines
	int n = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF)
		if (ch == '\n')
			n++;

	rewind(fp);

	Process *procs = (Process *) malloc((n + 1) * sizeof(Process));
	int i = 0;
	while (fscanf(fp, "%s %d %d %d", procs[i].pid, &procs[i].arrival, &procs[i].burst, &procs[i].disrupt_flag) == 4)
	{
		procs[i].remaining = procs[i].burst;
		procs[i].queue_level = 1;
		procs[i].time_in_q = 0;
		procs[i].interrupt_ct = 0;
		procs[i].quantum_rem = 2; // starts in Q1
		procs[i].completion = 0;
		procs[i].finished = 0;
		i++;
	}
	fclose(fp);
	*count = i;
	return procs;
}

int quantum_for_level(int level)
{
	if (level == 1)
		return 2;
	if (level == 2)
		return 4;
	return 999999; // Q3 FCFS
}

// Push process into a queue, resetting its slot tracking
void push_to_queue(Queue *q, Process *p, int level)
{
	p->queue_level = level;
	p->time_in_q = 0;
	p->quantum_rem = quantum_for_level(level);
	enqueue(q, p);
}

// Print Gantt Chart
void print_gantt(GanttEntry *gantt, int g_size)
{
	int i;
	printf("\n");
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║                      GANTT CHART                         ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n\n");

	// top border
	printf(" ");
	for (i = 0; i < g_size; i++)
	{
		int width = gantt[i].end - gantt[i].start;
		if (width < 3)
			width = 3;
		printf("+");
		for (int k = 0; k < width + 2; k++)
			printf("-");
	}
	printf("+\n");

	// process names (centered in each cell)
	printf(" ");
	for (i = 0; i < g_size; i++)
	{
		int width = gantt[i].end - gantt[i].start;
		if (width < 3)
			width = 3;
		int pad_left = (width + 2 - (int) strlen(gantt[i].pid)) / 2;
		int pad_right = width + 2 - (int) strlen(gantt[i].pid) - pad_left;
		printf("|");
		for (int k = 0; k < pad_left; k++)
			printf(" ");
		printf("%s", gantt[i].pid);
		for (int k = 0; k < pad_right; k++)
			printf(" ");
	}
	printf("|\n");

	// bottom border
	printf(" ");
	for (i = 0; i < g_size; i++)
	{
		int width = gantt[i].end - gantt[i].start;
		if (width < 3)
			width = 3;
		printf("+");
		for (int k = 0; k < width + 2; k++)
			printf("-");
	}
	printf("+\n");

	// time markers
	printf(" ");
	for (i = 0; i < g_size; i++)
	{
		int width = gantt[i].end - gantt[i].start;
		if (width < 3)
			width = 3;
		printf("%-*d", width + 3, gantt[i].start);
	}
	printf("%d\n\n", gantt[g_size - 1].end);
}

int main(void)
{
	int count;
	Process *procs = read_processes("processes.txt", &count);

	printf("╔══════════════════════════════════════════════════════════════╗\n");
	printf("║              OS ASSIGNMENT 2 - ASJAD RAZA                    ║\n");
	printf("╚══════════════════════════════════════════════════════════════╝\n\n");

	printf("Scheduling Queues:\n");
	printf("  Q1 -> Round Robin  (Quantum = 2)\n");
	printf("  Q2 -> Round Robin  (Quantum = 4)\n");
	printf("  Q3 -> FCFS         (No quantum)\n\n");

	printf("Processes read from processes.txt:\n");
	printf("  %-6s %-10s %-12s %-12s\n", "PID", "Arrival", "Burst", "Disrupt");
	printf("  %-6s %-10s %-12s %-12s\n", "---", "-------", "-----", "-------");
	for (int i = 0; i < count; i++)
		printf("  %-6s %-10d %-12d %-12d\n", procs[i].pid, procs[i].arrival, procs[i].burst, procs[i].disrupt_flag);
	printf("\n");

	Queue *q1 = queue_create(count);
	Queue *q2 = queue_create(count);
	Queue *q3 = queue_create(count);

	// Gantt: worst case one entry per quantum slice
	int max_time = 0;
	for (int i = 0; i < count; i++)
		max_time += procs[i].burst + 1;
	GanttEntry *gantt = (GanttEntry *) malloc(max_time * sizeof(GanttEntry));
	int g_size = 0;

	int clock = 0;
	int next_proc = 0; // index of next unqueued process
	int done_count = 0;

	// Enqueue all processes whose arrival time <= clock into Q1
#define ENQUEUE_ARRIVALS()                                                                                             \
	while (next_proc < count && procs[next_proc].arrival <= clock)                                                     \
	{                                                                                                                  \
		push_to_queue(q1, &procs[next_proc], 1);                                                                       \
		next_proc++;                                                                                                   \
	}

	printf("Simulation Log:\n");

	while (done_count < count)
	{
		ENQUEUE_ARRIVALS();

		// Pick highest priority non-empty queue
		Queue *active_q = NULL;
		int cur_level = 0;

		if (q1->size > 0)
		{
			active_q = q1;
			cur_level = 1;
		}
		else if (q2->size > 0)
		{
			active_q = q2;
			cur_level = 2;
		}
		else if (q3->size > 0)
		{
			active_q = q3;
			cur_level = 3;
		}

		if (active_q == NULL)
		{
			// CPU idle: jump clock to next arrival
			if (next_proc < count)
				clock = procs[next_proc].arrival;
			else
				break;
			continue;
		}

		Process *p = dequeue(active_q);
		int quantum = quantum_for_level(cur_level);

		// How much does this process run this slice?
		// disrupt_flag=1 -> uses quantum_rem (may be reduced from a previous interrupt)
		// disrupt_flag=0 -> always gets full quantum
		int allotted = (p->disrupt_flag == 1) ? p->quantum_rem : quantum;

		int slice_start = clock;
		int interrupted = 0;
		int units_run = 0;

		// Run process for up to 'allotted' ticks
		// Check each tick for: new arrivals that interrupt, and process completion
		for (int t = 0; t < allotted; t++)
		{
			// Before each tick, check if a higher-priority process just arrived
			// (interrupts only apply if we're in Q2 or Q3)
			if (cur_level > 1)
			{
				while (next_proc < count && procs[next_proc].arrival <= clock)
				{
					push_to_queue(q1, &procs[next_proc], 1);
					next_proc++;
				}
				if (q1->size > 0)
				{
					interrupted = 1;
					break;
				}
			}

			// Run one unit
			p->remaining--;
			units_run++;
			clock++;

			// Enqueue any processes that arrived at this new clock value
			ENQUEUE_ARRIVALS();

			// Process finished mid-quantum
			if (p->remaining == 0)
				break;
		}

		// Record this slice in the Gantt chart
		strcpy(gantt[g_size].pid, p->pid);
		gantt[g_size].start = slice_start;
		gantt[g_size].end = clock;
		g_size++;

		if (p->remaining == 0)
		{
			// Process completed
			p->finished = 1;
			p->completion = clock;
			done_count++;
			printf("  [t=%3d] %-4s FINISHED  (Q%d)\n", clock, p->pid, cur_level);
		}
		else if (interrupted)
		{
			// A higher-priority process arrived, cutting this slice short
			p->interrupt_ct++;
			printf("  [t=%3d] %-4s INTERRUPTED (Q%d, interrupts=%d)\n", clock, p->pid, cur_level, p->interrupt_ct);

			// Rule 8: every 3rd interruption promotes the process (unless already Q1)
			if (p->interrupt_ct % 3 == 0 && cur_level > 1)
			{
				int new_level = cur_level - 1;
				Queue *dest = (new_level == 1) ? q1 : q2;
				push_to_queue(dest, p, new_level);
				printf("  [t=%3d] %-4s PROMOTED  Q%d -> Q%d\n", clock, p->pid, cur_level, new_level);
			}
			else
			{
				// Rule 9: re-queue at end of same queue
				p->queue_level = cur_level;
				if (p->disrupt_flag == 0)
				{
					// Gets full quantum again next time (executed time ignored)
					p->quantum_rem = quantum;
					p->time_in_q = 0;
				}
				else
				{
					// Gets only the leftover quantum next time
					p->quantum_rem = allotted - units_run;
					p->time_in_q = units_run;
				}
				enqueue(active_q, p);
			}
		}
		else
		{
			// Ran full quantum without finishing → demote
			if (cur_level < 3)
			{
				int new_level = cur_level + 1;
				Queue *dest = (new_level == 2) ? q2 : q3;
				push_to_queue(dest, p, new_level);
				printf("  [t=%3d] %-4s DEMOTED   Q%d -> Q%d\n", clock, p->pid, cur_level, new_level);
			}
			else
			{
				// Already Q3 (FCFS): keep running in Q3 until done
				enqueue(active_q, p);
			}
		}
	}

	print_gantt(gantt, g_size);

	// Performance Metrics
	printf("╔══════════════════════════════════════════════════════════════════════╗\n");
	printf("║                       PERFORMANCE METRICS                            ║\n");
	printf("╚══════════════════════════════════════════════════════════════════════╝\n\n");
	printf("  %-8s %-8s %-8s %-8s %-8s %-8s\n", "Process", "AT", "BT", "CT", "TAT", "WT");
	printf("  %-8s %-8s %-8s %-8s %-8s %-8s\n", "-------", "--", "--", "--", "---", "--");

	double total_tat = 0, total_wt = 0;
	for (int i = 0; i < count; i++)
	{
		int tat = procs[i].completion - procs[i].arrival;
		int wt = tat - procs[i].burst;
		total_tat += tat;
		total_wt += wt;
		printf("  %-8s %-8d %-8d %-8d %-8d %-8d\n", procs[i].pid, procs[i].arrival, procs[i].burst, procs[i].completion,
		       tat, wt);
	}

	printf("\n  Average Turnaround Time : %.2f\n", total_tat / count);
	printf("  Average Waiting Time    : %.2f\n\n", total_wt / count);

	// Cleanup
	free(gantt);
	free(procs);
	free(q1->data);
	free(q1);
	free(q2->data);
	free(q2);
	free(q3->data);
	free(q3);

	return 0;
}