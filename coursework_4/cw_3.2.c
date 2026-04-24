#include <stdio.h>

void run_optimized_exploration(int num_procs, int cmds_per_proc) {
    int x = 0; // Global variable
    int total_commands = 0;

    printf("Initial x = %d\n\n", x);

    // Instead of backtracking through 90 paths, we execute 
    // a single canonical path.
    for (int i = 1; i <= num_procs; i++) {
        printf("Process P%d sequence:\n", i);
        
        for (int j = 1; j <= cmds_per_proc; j++) {
            x++;
            total_commands++;
            
            // Label commands as a or b for the specific process
            char label = (j == 1) ? 'a' : 'b';
            printf("  Command %c%d executed: x = %d\n", label, i, x);
        }
        printf("\n");
    }

    printf("Final value of x: %d\n", x);
    printf("Total commands processed: %d\n", total_commands);
}

int main() {
    // 3 Processes, 2 Commands each
    int P = 3;
    int K = 2;

    run_optimized_exploration(P, K);

    return 0;
}