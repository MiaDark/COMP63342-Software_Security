#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char** commands;
    int num_commands;
    int pc;        // program counter
} Process;

void explore(Process* procs, int num_procs, char** current_path, int path_len, int* count) {
    // Check if all processes are finished
    int finished = 1;
    for (int i = 0; i < num_procs; i++) {
        if (procs[i].pc < procs[i].num_commands) {
            finished = 0;
            break;
        }
    }

    if (finished) {
        (*count)++;
        for (int i = 0; i < path_len; i++) {
            printf("%s ", current_path[i]);
        }
        printf("\n");
        return;
    }

    // Try to execute next command from each process that is not finished
    for (int i = 0; i < num_procs; i++) {
        if (procs[i].pc < procs[i].num_commands) {
            // Execute command
            current_path[path_len] = procs[i].commands[procs[i].pc];
            procs[i].pc++;

            // Recurse
            explore(procs, num_procs, current_path, path_len + 1, count);

            // Backtrack
            procs[i].pc--;
        }
    }
}

int main() {
    // Define the commands for each process
    char* cmds1[] = {"a1", "b1"};
    char* cmds2[] = {"a2", "b2"};
    char* cmds3[] = {"a3", "b3"};

    Process procs[3] = {
        {1, cmds1, 2, 0},
        {2, cmds2, 2, 0},
        {3, cmds3, 2, 0}
    };

    // Allocate space for the current path (max 6 steps)
    char** current_path = (char**)malloc(6 * sizeof(char*));

    int count = 0;

    explore(procs, 3, current_path, 0, &count);

    printf("Total interleavings: %d\n", count);

    free(current_path);
    return 0;
}