// Total memory addresses
#define TOTAL 100
// Free memory address indicator
#define EMPTY 0

/**
 * Relocate jobs in the memory dynamically
 * @param int* memory
 * @author mavyfaby (Maverick Fabroa)
 *
 * The function will fill the free addressed in the memory by
 * computing the number of empty addresses using the relocation register
 * 
 *          Memory before and after
 * 
 * +-----------+                 +-----------+
 * |  0 (free) |                 |    1      |
 * +-----------+                 +-----------+
 * |    1      |                 |    2      |
 * +-----------+ It will become: +-----------+ 
 * |  0 (free) |                 |  0 (free) |
 * +-----------+                 +-----------+
 * |    2      |                 |  0 (free) |
 * +-----------+                 +-----------+
 * 
 */
void compact_and_relocate(int* memory) {
    // Initialize the bound registers
    int bound_start_register = 0; // (Bound Lowest Address)
    int bound_end_register = TOTAL; // (Bound Highest Address)
    // Initialize the relocation register
    // The relocation register will be used as a counter to count
    // how many steps the addresses will be relocated
    int relocation_register = 0;

    // A flag whether the counter doesn't visited an empty address yet
    unsigned short int isVisitedEmpty = 0;

    // Loop through the memory addresses
    for (int i = bound_start_register; i < bound_end_register; i++) {
        // If the current memory address is empty
        if (memory[i] == EMPTY) {
            // Set the {isVisitedEmpty} flag to 1
            isVisitedEmpty = 1;
            // Increment the relocation register
            // By incrementing the relocation register, we will know how many empty addresses
            // are there, so we can relocate the jobs in the memory
            relocation_register += 1;
            // Continue to the next memory address
            continue;
        }

        // If the counter doesn't visited an empty address yet
        if (!isVisitedEmpty) {
            // Don't do anything, just continue to the next memory address
            continue;
        }

        /**
         * This code will below will be executed if:
         * If the counter visited an empty address and the current memory address is not empty
         */
        
        // Set the current memory address to the empty address
        // We subtract the current address to the relocation register
        // to get where the empty address is located and set the current memory address to it
        memory[i - relocation_register] = memory[i];
        // Set the current memory address to empty (meaning it's now free)
        memory[i] = EMPTY;
    }
}