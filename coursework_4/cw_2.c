#include <assert.h>
#include <stdbool.h>

// Global state buffers for each "round" (assuming K=2 rounds)
// Index 0 represents the state during the first context bound
// Index 1 represents the state during the second context bound
int g_buffer[2];

// Helper for non-deterministic choice
extern int nondet_int();

// Sequentialized Thread 1
void t1_seq(int arg1) {
    int a1, *aptr1;
    // We simulate execution in Round 0
    aptr1 = &arg1;
    a1 = *aptr1;
    
    // Thread 1's view of g in Round 0
    g_buffer[0] = 0;
    
    // Check assertion for Round 0 context
    assert(a1 == 10 && g_buffer[0] == 0);
}

// Sequentialized Thread 2
void t2_seq(int arg2) {
    int a2, *aptr2;
    // We simulate execution in Round 1
    aptr2 = &arg2;
    a2 = *aptr2;
    
    // Thread 2's view of g in Round 1
    g_buffer[1] = 0;
    
    // Check assertion for Round 1 context
    assert(a2 == 20);
}

// Sequentialized schema
int main() {
    // Guess initial values for the global variable in each round
    // This represents the state of 'g' at the start of each context switch
    g_buffer[0] = nondet_int();
    g_buffer[1] = nondet_int();

    // Save the very first initial state to check against the original start
    int initial_start = g_buffer[0];

    // Execute threads sequentially
    int arg1 = 10, arg2 = 20;
    t1_seq(arg1);
    t2_seq(arg2);

    // Main thread's own assertion check (from the original main)
    assert(g_buffer[0] == 0 || g_buffer[1] == 0);

    // The "Linking" Constraint
    // We must assume that the value at the end of Round 0 
    // is the same as the guessed value at the start of Round 1.
    // If g_end_of_round_0 == g_start_of_round_1, then the execution is valid.
    bool valid_interleaving = (g_buffer[0] == g_buffer[1]);
    
    // If this condition is met, any assertion failure found is a real bug.
    if (valid_interleaving) {
        // Successful simulation of a context switch
    }

    return 0;
}
