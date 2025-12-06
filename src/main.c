#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif
#include "input.h"
#include "utils.h"
#include "arrayutils.h"
#include "arraysort.h"
#include "dllist.h"
#include "listsort.h"
#include "heap.h"
#include "maxsubarray.h"
#include "wqunion.h"

typedef enum main_menu_option {
    ARRAY_SORT = 0,
    LIST_SORT,
    MIN_HEAP,
    MAX_SUBARRAY,
    UNION_FIND,
    QUIT,
    NUM_MAIN_MENU_OPTIONS
} MENU_OPTION;

typedef enum heap_test_option {
    HEAP_PRINT = 0,
    HEAP_GET_MIN,
    HEAP_GET_MAX,
    HEAP_GET_IDX,
    HEAP_INSERT,
    HEAP_POP,
    HEAP_EXIT,
    NUM_HEAP_MENU_OPTIONS
} HEAP_TEST_OPTION;

typedef enum union_test_option {
    UNION_FIND_ROOT = 0,
    UNION_CHECK_CONNECTION,
    UNION_CONNECT,
    UNION_RETURN_MAIN,
    NUM_UNION_TEST_OPTIONS
} UNION_TEST_OPTION;

typedef struct array_sort_thread_vars {
    ARRAY_SORT_TYPE sort_type;
    int* array;
    size_t size;
#ifdef __APPLE__
    dispatch_semaphore_t print_sem;
#else
    sem_t print_sem;
#endif
} ARRAY_SORT_THREAD_VARS;

typedef struct list_sort_thread_vars {
    LIST_SORT_TYPE sort_type;
    struct dllist* original_list;
#ifdef __APPLE__
    uint64_t time_elapsed_ns;
#else
    struct timespec time_elapsed;
#endif
    bool was_successful;
} LIST_SORT_THREAD_VARS;

static const char* const sort_algorithm_names[NUM_ARRAY_SORTS] = {
    [SELECTION_SORT] = "Selection Sort",
    [INSERTION_SORT] = "Insertion Sort",
    [SHELLSORT]      = "Shellsort",
    [HEAPSORT]       = "Heapsort",
    [MERGE_SORT]     = "Merge Sort",
    [QUICKSORT]      = "Quicksort"
};

void array_sort_test(void);
void *array_sort_test_runner(void* arg);

void linked_list_sort_test(void);
void* list_sort_test_runner(void* arg);

void min_heap_test(void);
bool min_heap_test_helper(heap_t heap[const static 1], const HEAP_TEST_OPTION option);

void max_subarray_test(void);
void union_find_test(void);
bool union_find_test_helper(struct wqunion wqu[const static 1], const UNION_TEST_OPTION option);

size_t get_num_elements(void);
bool get_yes_or_no(void);
#ifdef __APPLE__
void print_time_elapsed(const uint64_t time_elapsed);
#endif

int main(void)
{
    initscr();
    if (keypad(stdscr, true) == ERR) {
        fputs("ERROR: Failed to enable the keypad.\n", stderr);
        return EXIT_FAILURE;
    }
    if (noecho() == ERR) {
        fputs("ERROR: Failed to disable echoing.\n", stderr);
        return EXIT_FAILURE;
    }
    if (curs_set(0) == ERR) {
        fputs("ERROR: Failed to make the cursor invisible.\n", stderr);
        return EXIT_FAILURE;
    }

    srand(time(0));

    static const char max_option_char = '0' + NUM_MAIN_MENU_OPTIONS;
    static const char* const menu_options[NUM_MAIN_MENU_OPTIONS] = {
        [ARRAY_SORT]   = "Array Sorting Algorithms",
        [LIST_SORT]    = "Linked List Sorting Algorithms",
        [MIN_HEAP]     = "Min Heap Test",
        [MAX_SUBARRAY] = "Maximum Subarray",
        [UNION_FIND]   = "Union Find",
        [QUIT]         = "Quit"
    };

    int key_input = 0;
    MENU_OPTION highlighted_option = ARRAY_SORT;
    bool exit_program = false;
    while (!exit_program)
    {
        erase();
        attron(A_BOLD);
        addstr("DATA STRUCTURES AND ALGORITHMS TEST SUITE\n\n");
        attroff(A_BOLD);
        for (size_t i = 0; i < NUM_MAIN_MENU_OPTIONS; i++) {
            if (i == highlighted_option) {
                attron(A_STANDOUT);
            }
            printw("%zu. %s\n", i + 1, menu_options[i]);
            if (i == highlighted_option) {
                attroff(A_STANDOUT);
            }
        }
        refresh();

        key_input = getch();
        if ((key_input == KEY_ENTER) || (key_input == 10)) {
            switch (highlighted_option) {
            case ARRAY_SORT:
                array_sort_test();
                break;
            case LIST_SORT:
                linked_list_sort_test();
                break;
            case MIN_HEAP:
                min_heap_test();
                break;
            case MAX_SUBARRAY:
                max_subarray_test();
                break;
            case UNION_FIND:
                union_find_test();
                break;
            case QUIT:
                exit_program = true;
                break;
            default:
                break;
            }
        } else if ((key_input == KEY_UP) && (highlighted_option > 0)) {
            highlighted_option--;
        } else if ((key_input == KEY_DOWN) && (highlighted_option < (NUM_MAIN_MENU_OPTIONS - 1))) {
            highlighted_option++;
        } else if ((key_input >= '1') && (key_input <= max_option_char)) {
            highlighted_option = (int)key_input - '1';
        }
    }

    endwin();
    return 0;
}

void array_sort_test(void)
{
    erase();
    attron(A_BOLD);
    addstr("Array Sorting Algorithms\n\n");
    attroff(A_BOLD);
    refresh();

    addstr("The array size will be a power of 2 (2^x).\n");
    int y;
    int x;
    getyx(stdscr, y, x);
    x = 0;
    size_t power = 0;
    static const size_t lower_limit = 4;
    static const size_t upper_limit = 22;
    while ((power < lower_limit) || (power > upper_limit)) {
        move(y, x);
        clrtoeol();
        printw("Enter an exponent between %zu and %zu: ", lower_limit, upper_limit);
        refresh();
        power = (size_t)get_int_input();
    }
    assert((power >= lower_limit) && (power <= upper_limit));
    const size_t num_elements = 1 << power;
    printw("Number of elements: 2^%zu = %zu (0x%zx)\n", power, num_elements, num_elements);
    const size_t array_size = num_elements * sizeof(int);
    printw("Array size: %zu (0x%zx) elements * %zu bytes/element = %zu (0x%zx) bytes\n", num_elements, num_elements, sizeof(int), array_size, array_size);
    refresh();
    
    addstr("\nSkip quadratic algorithms?\n");
    const size_t start_point = get_yes_or_no() ? 2 : 0;
    assert(start_point < NUM_ARRAY_SORTS);
    printw("Starting at: %s\n", sort_algorithm_names[start_point]);
    refresh();

    const size_t num_arrays = NUM_ARRAY_SORTS - start_point;
    const size_t alloc_size = num_arrays * array_size;
    printw("Arena size: %zu arrays * %zu bytes/array = %zu (0x%zx) bytes\n", num_arrays, array_size, alloc_size, alloc_size);

    refresh();
    int* const arena = malloc(alloc_size);
    if (arena == NULL) {
        fprintf(stderr, "%s: ERROR: malloc failed.\n", __func__);
        exit(EXIT_FAILURE);
    }
    printw("Arena location: %p to %p\n", arena, (const uint8_t*)arena + alloc_size);

    printw("\nCreating random pattern in array 0 (%p to %p).\n", arena, arena + num_elements);
    refresh();
    for (size_t i = 0; i < num_elements; i++) {
        arena[i] = get_random_num(-1000, 1000);
    }
    printw("Making %zu copies of the pattern.\n", num_arrays - 1);
    refresh();
    for (size_t i = 1; i < num_arrays; i++) {
        int* const dest = arena + (i * num_elements);
        printw("Copying pattern to array %zu (%p to %p).\n", i, dest, dest + num_elements);
        memcpy(dest, arena, num_elements);
    }

    addstr("Starting the threads. Please wait...\n\n");
    refresh();

    pthread_t threads[NUM_ARRAY_SORTS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    ARRAY_SORT_THREAD_VARS vars[NUM_ARRAY_SORTS];

#ifdef __APPLE__
    dispatch_semaphore_t print_sem = dispatch_semaphore_create(1);
    if (print_sem == NULL) {
        fprintf(stderr, "ERROR: dispatch_semaphore_create failed.\n");
        exit(EXIT_FAILURE);
    }
#else
    sem_t print_sem;
    const int sem_init_result = sem_init(&int_sem, 0, 1);
    if (sem_init_result != 0) {
        fprintf(stderr, "ERROR: sem_init failed: %d\n", sem_init_result);
        exit(EXIT_FAILURE);
    }
    int current_sem_value;
    const int getvalue_status = sem_getvalue(&int_sem, &current_sem_value);
    if (getvalue_status != 0) {
        fprintf(stderr, "ERROR: sem_getvalue failed: %d\n", getvalue_status);
        exit(EXIT_FAILURE);
    }
    if (current_sem_value != 1) {
        fprintf(stderr, "ERROR: Failed to initialize a binary semaphore.\n");
        exit(EXIT_FAILURE);
    }
#endif

    for (size_t i = start_point; i < NUM_ARRAY_SORTS; i++) {
        vars[i].sort_type = (ARRAY_SORT_TYPE)i;
        assert(i >= start_point);
        vars[i].array = arena + (i - start_point) * num_elements;
        vars[i].size = num_elements;
        vars[i].print_sem = print_sem;
        pthread_create(&threads[i], &attr, array_sort_test_runner, &vars[i]);
    }

    for (size_t i = start_point; i < NUM_ARRAY_SORTS; i++) {
        pthread_join(threads[i], NULL);
    }

    free(arena);
#if __APPLE__
    dispatch_release(print_sem);
#else
    const int sem_destroy_result = sem_destroy(&print_sem);
    if (sem_destroy_result != 0) {
        fprintf(stderr, "ERROR: sem_destroy failed: %d\n", sem_destroy_result);
        exit(EXIT_FAILURE);
    }
#endif

    addch('\n');
    refresh();
    wait_for_enter();
}

void* array_sort_test_runner(void* arg)
{
    ARRAY_SORT_THREAD_VARS* const vars = arg;

#ifdef __APPLE__
    const uint64_t start_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
#else
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
#endif

    switch (vars->sort_type) {
    case SELECTION_SORT:
        selection_sort(vars->size, vars->array);
        break;
    case INSERTION_SORT:
        insertion_sort(vars->size, vars->array);
        break;
    case SHELLSORT:
        shellsort(vars->size, vars->array);
        break;
    case HEAPSORT:
        heapsort_array(vars->array, 0, vars->size - 1);
        break;
    case MERGE_SORT:
        merge_sort_array(vars->size, vars->array);
        break;
    case QUICKSORT:
        quicksort(vars->array, 0, vars->size - 1);
        break;
    default:
        break;
    }

    assert(vars->sort_type < NUM_ARRAY_SORTS);
#ifdef __APPLE__
    const uint64_t time_elapsed_ns = clock_gettime_nsec_np(CLOCK_UPTIME_RAW) - start_time;
    dispatch_semaphore_wait(vars->print_sem, DISPATCH_TIME_FOREVER);
    printw("%-14s: ", sort_algorithm_names[vars->sort_type]);
    print_time_elapsed(time_elapsed_ns);
    printw(" (%s)\n", array_is_sorted(vars->size, vars->array) ? "OK" : "FAILED");
    refresh();
    dispatch_semaphore_signal(vars->print_sem);
#else
    struct timespec stop_time;
    clock_gettime(CLOCK_MONOTONIC, &stop_time);
    struct timespec time_elapsed;
    assert(get_time_diff(&start_time, &stop_time, &time_elapsed) == 0);
    sem_wait(&vars->print_sem);
    printw("%-14s: %ld.%09ld s", sort_algorithm_names[vars->sort_type], time_elapsed.tv_sec, time_elapsed.tv_nsec);
    printw(" (%s)\n", array_is_sorted(vars->size, vars->array) ? "OK" : "FAILED");
    refresh();
    sem_post(&vars->print_sem);
#endif

    return (void*)0;
}

void linked_list_sort_test(void)
{
    erase();
    attron(A_BOLD);
    addstr("Linked List Sorting Algorithms\n\n");
    attroff(A_BOLD);
    refresh();

    const size_t list_length = get_num_elements();
    printw("\nList will contain %zu elements.\n\n", list_length);
    dllist_t int_list = dllist_init();
    for (size_t i = 0; i < list_length; i++) {
        dlnode_t* const new_node = malloc(sizeof(struct dlnode));
        if (new_node == NULL) {
            fprintf(stderr, "%s: ERROR: malloc failed.\n", __func__);
            exit(EXIT_FAILURE);
        }
        new_node->data = get_random_num(-1000, 1000);
        dllist_append(&int_list, new_node);
    }

    static const char* const sort_algorithms[NUM_LIST_SORTS] = {
        [LIST_SELECTION_SORT]       = "Selection Sort",
        [LIST_SELECTION_SORT_SEDGE] = "Selection Sort (Sedgewick)",
        [LIST_INSERTION_SORT]       = "Insertion Sort",
        [LIST_INSERTION_SORT_SEDGE] = "Insertion Sort (Sedgewick)",
        [LIST_MERGE_SORT_SEDGE]     = "Merge Sort (Sedgewick)"
    };

    addstr("Skip quadratic algorithms?\n");
    const bool skip_quadratic = get_yes_or_no();
    addstr("\n\nPlease wait...");
    refresh();

    if (skip_quadratic) {
        dllist_t new_list = dllist_create_copy(&int_list);

#ifdef __APPLE__
        const uint64_t start_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
#else
        struct timespec start_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);
#endif

        new_list.first = dllist_merge_sort(new_list.first);

#ifdef __APPLE__
        const uint64_t stop_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
        addstr("Merge sort: ");
        print_time_elapsed(stop_time - start_time);
#else
        struct timespec stop_time;
        clock_gettime(CLOCK_MONOTONIC, &stop_time);
        struct timespec elapsed_time;
        assert(get_time_diff(&start_time, &stop_time, &elapsed_time) == 0);
        printw("Merge sort: %ld.%09ld s", elapsed_time.tv_sec, elapsed_time.tv_nsec);
#endif

        if (!dllist_is_sorted(&new_list)) {
            addstr(" (failed)");
        }
        addch('\n');
        refresh();
        dllist_destroy(&new_list);
    } else {
        pthread_t threads[NUM_LIST_SORTS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        LIST_SORT_THREAD_VARS vars[NUM_LIST_SORTS];

        for (size_t i = 0; i < NUM_LIST_SORTS; i++) {
            vars[i].sort_type = i;
            vars[i].original_list = &int_list;
            pthread_create(&threads[i], &attr, list_sort_test_runner, &vars[i]);
        }

        for (size_t i = 0; i < NUM_LIST_SORTS; i++) {
            pthread_join(threads[i], NULL);
        }
        
        clear();
        printw("When sorting %zu elements:\n\n", list_length);
        for (size_t i = 0; i < NUM_LIST_SORTS; i++) {
            printw("%-26s: ", sort_algorithms[i]);
#ifdef __APPLE__
            print_time_elapsed(vars[i].time_elapsed_ns);
#else
            printw("%ld.%09ld s", vars[i].time_elapsed.tv_sec, vars[i].time_elapsed.tv_nsec);
#endif
            if (!vars[i].was_successful) {
                addstr(" (failed)");
            }
            addch('\n');
        }
        refresh();
    }

    dllist_destroy(&int_list);
    addch('\n');
    wait_for_enter();
}

void* list_sort_test_runner(void* arg)
{
    LIST_SORT_THREAD_VARS* const vars = arg;
    dllist_t new_list = dllist_create_copy(vars->original_list);

#ifdef __APPLE__
    const uint64_t start_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
#else
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
#endif

    switch (vars->sort_type) {
    case LIST_SELECTION_SORT:
        dllist_selection_sort(&new_list);
        break;
    case LIST_SELECTION_SORT_SEDGE:
        new_list = dllist_selection_sort_sw(&new_list);
        break;
    case LIST_INSERTION_SORT:
        dllist_insertion_sort(&new_list);
        break;
    case LIST_INSERTION_SORT_SEDGE:
        dllist_insertion_sort_sw(&new_list);
        break;
    case LIST_MERGE_SORT_SEDGE:
        new_list.first = dllist_merge_sort(new_list.first);
        break;
    default:
        break;
    }

#ifdef __APPLE__
    vars->time_elapsed_ns = clock_gettime_nsec_np(CLOCK_UPTIME_RAW) - start_time;
#else
    struct timespec stop_time;
    clock_gettime(CLOCK_MONOTONIC, &stop_time);
    assert(get_time_diff(&start_time, &stop_time, &vars->time_elapsed) == 0);
#endif

    vars->was_successful = dllist_is_sorted(&new_list);
    
    dllist_destroy(&new_list);
    return (void*)0;
}

void min_heap_test(void)
{
    static const char* const menu_options[NUM_HEAP_MENU_OPTIONS] = {
        [HEAP_PRINT]   = "Print heap",
        [HEAP_GET_MIN] = "Get heap minimum value",
        [HEAP_GET_MAX] = "Get heap maximum value",
        [HEAP_GET_IDX] = "Get value at index",
        [HEAP_INSERT]  = "Add to heap",
        [HEAP_POP]     = "Pop top value from heap",
        [HEAP_EXIT]    = "Return to the main menu"
    };
    static const char MAX_CHAR = '0' + NUM_HEAP_MENU_OPTIONS;
    assert((MAX_CHAR >= '0') && (MAX_CHAR <= '9'));

    erase();
    attron(A_BOLD);
    addstr("MIN HEAP TEST\n\n");
    attroff(A_BOLD);
    refresh();

    heap_t heap = heap_init();

    int y;
    int x;
    getyx(stdscr, y, x);
    x = 0;
    int highlighted_option = 0;
    bool should_return_to_main = false;
    while (!should_return_to_main) {
        move(y, x);
        clrtobot();
        for (int i = 0; i < NUM_HEAP_MENU_OPTIONS; i++) {
            if (i == highlighted_option) {
                attron(A_STANDOUT);
            }
            printw("%zu. %s\n", i + 1, menu_options[i]);
            if (i == highlighted_option) {
                attroff(A_STANDOUT);
            }
        }
        refresh();

        int key_input = getch();
        switch (key_input) {
        case KEY_ENTER:
        case 10:
            should_return_to_main = min_heap_test_helper(&heap, highlighted_option);
            break;
        case KEY_UP:
            if (highlighted_option > 0) {
                highlighted_option--;
            }
            break;
        case KEY_DOWN:
            if (highlighted_option < NUM_HEAP_MENU_OPTIONS - 1) {
                highlighted_option++;
            }
            break;
        default:
            if ((key_input >= '1') && (key_input <= MAX_CHAR)) {
                highlighted_option = key_input - '1';
            }
            break;
        }
    }

    heap_free(&heap);
}

bool min_heap_test_helper(heap_t heap[const static 1], const HEAP_TEST_OPTION option)
{
    heap_key_t key;
    size_t idx;

    addch('\n');

    switch (option) {
    case HEAP_PRINT:
        heap_print(heap);
        break;
    case HEAP_GET_MIN:
        key = heap_get_min(heap);
        printw("Key: %d\n", key.value);
        break;
    case HEAP_GET_MAX:
        key = heap_get_max(heap);
        printw("Key: %d\n", key.value);
        break;
    case HEAP_GET_IDX:
        addstr("Enter index: ");
        idx = (size_t)get_int_input();
        addch('\n');
        key = heap_get_idx(heap, idx);
        printw("Key: %d\n", key.value);
        break;
    case HEAP_INSERT:
        addstr("Enter value to insert: ");
        key.value = get_int_input();
        printw("\nInserting %d.\n", key.value);
        heap_insert(heap, &key);
        break;
    case HEAP_POP:
        heap_pop(heap);
        break;
    case HEAP_EXIT:
        return true;
    default:
        break;
    }

    refresh();
    wait_for_enter();
    return false;
}

void max_subarray_test(void)
{
    erase();
    attron(A_BOLD);
    addstr("Max Subarray Test\n\n");
    attroff(A_BOLD);
    refresh();

    const size_t array_len = get_num_elements();
    int* const array = malloc(array_len * sizeof(int));
    for (size_t i = 0; i < array_len; i++) {
        array[i] = get_random_num(-100, 100);
    }

    addstr("Original Array:\n");
    print_int_array_curses(array_len, array);
    refresh();

#ifdef __APPLE__
    const uint64_t start_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
#else
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
#endif

    struct max_subarray ms = find_max_subarray(array, 0, array_len - 1);

#ifdef __APPLE__
    const uint64_t stop_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
#else
    struct timespec stop_time;
    clock_gettime(CLOCK_MONOTONIC, &stop_time);
#endif

    addstr("\n\nMax Subarray:\n");
    for (size_t i = ms.low_index; i <= ms.high_index; i++) {
        printw("%d ", array[i]);
    }
    printw("\n\nMax Subarray Sum: %d\n", ms.max_sum);

#ifdef __APPLE__
    const uint64_t time_elapsed = stop_time - start_time;
    print_time_elapsed(time_elapsed);
#else
    struct timespec elapsed_time;
    assert(get_time_diff(&start_time, &stop_time, &elapsed_time) == 0);
    printw("Time elapsed: %ld.%09ld s", elapsed_time.tv_sec, elapsed_time.tv_nsec);
#endif

    printw("\n\n");
    refresh();
    wait_for_enter();
}

void union_find_test(void)
{
    static const char* const menu_options[NUM_UNION_TEST_OPTIONS] = {
        [UNION_FIND_ROOT]        = "Find the root of a node",
        [UNION_CHECK_CONNECTION] = "Check whether two nodes are connected",
        [UNION_CONNECT]          = "Connect two nodes",
        [UNION_RETURN_MAIN]      = "Return to the main menu"
    };
    static const char MAX_CHAR = '0' + NUM_UNION_TEST_OPTIONS;
    assert((MAX_CHAR >= '0') && (MAX_CHAR <= '9'));

    erase();
    attron(A_BOLD);
    addstr("UNION FIND TEST\n\n");
    attroff(A_BOLD);
    refresh();

    const size_t size = get_num_elements();
    printw("\n%zu-element weighted quick UF\n\n", size);
    refresh();
    struct wqunion* const wqu = init_wqunion_of_size(size);

    int y;
    int x;
    getyx(stdscr, y, x);
    x = 0;
    int highlighted_option = 0;
    bool should_return_to_main = false;
    while (!should_return_to_main) {
        move(y, x);
        clrtobot();
        for (int i = 0; i < NUM_UNION_TEST_OPTIONS; i++) {
            if (i == highlighted_option) {
                attron(A_STANDOUT);
            }
            printw("%zu. %s\n", i + 1, menu_options[i]);
            if (i == highlighted_option) {
                attroff(A_STANDOUT);
            }
        }
        refresh();

        int key_input = getch();
        switch (key_input) {
        case KEY_ENTER:
        case 10:
            should_return_to_main = union_find_test_helper(wqu, highlighted_option);
            break;
        case KEY_UP:
            if (highlighted_option > 0) {
                highlighted_option--;
            }
            break;
        case KEY_DOWN:
            if (highlighted_option < (NUM_UNION_TEST_OPTIONS - 1)) {
                highlighted_option++;
            }
            break;
        default:
            if ((key_input >= '1') && (key_input <= MAX_CHAR)) {
                highlighted_option = key_input - '1';
            }
            break;
        }
    }

    delete_wqunion(wqu);
}

bool union_find_test_helper(struct wqunion wqu[const static 1], const UNION_TEST_OPTION option)
{
    size_t node1;
    size_t node2;
    size_t last_node;

    addch('\n');

    switch (option) {
    case UNION_FIND_ROOT: // Find root of a node
        addstr("Enter node number: ");
        refresh();
        node1 = (size_t)get_int_input();
        addch('\n');
        if (node1 > wqu->count - 1) {
            addstr("Invalid input.\n\n");
        } else {
            const int root = get_node_root(wqu, node1);
            printw("Root of %d: %d\n\n", node1, root);
        }
        break;
    case UNION_CHECK_CONNECTION: // Check if two nodes are connected
    case UNION_CONNECT: // Connect two nodes
        addstr("Enter number of first node:  ");
        node1 = (size_t)get_int_input();
        addstr("\nEnter number of second node: ");
        node2 = (size_t)get_int_input();
        addch('\n');
        // Validate input
        last_node = wqu->count - 1;
        if ((node1 > last_node) || (node2 > last_node)) {
            addstr("Invalid input.\n\n");
        } else if (option == UNION_CHECK_CONNECTION) {
            const bool are_connected = pair_is_connected(wqu, node1, node2);
            printw("Nodes %d and %d: %s\n\n", node1, node2, are_connected ? "connected" : "not connected");
        } else {
            unify_nodes(wqu, node1, node2);
            printw("Connected nodes %d and %d.\n\n", node1, node2);
        }
        break;
    case UNION_RETURN_MAIN:
        return true;
    default:
        break;
    }

    wait_for_enter();
    return false;
}

size_t get_num_elements(void)
{
    // Remember the coordinates so the cursor can be moved
    // back repeatedly in case of invalid user input
    int y;
    int x;
    getyx(stdscr, y, x);
    x = 0;
    
    int array_length = 0;
    while (array_length <= 0) {
        move(y,x);
        clrtobot();
        addstr("Enter desired number of elements: ");
        refresh();
        array_length = get_int_input();
    }

    return array_length;
}

bool get_yes_or_no(void)
{
    int y;
    int x;
    getyx(stdscr, y, x);
    x = 0;
    size_t highlighted_option = 0;
    bool user_pressed_enter = false;
    bool did_choose_yes;
    while (!user_pressed_enter) {
        move(y, x);
        clrtobot();

        if (highlighted_option == 0) {
            attron(A_STANDOUT);
        }
        addstr("Yes\n");
        if (highlighted_option == 0) {
            attroff(A_STANDOUT);
        }

        if (highlighted_option == 1) {
            attron(A_STANDOUT);
        }
        addstr("No\n");
        if (highlighted_option == 1) {
            attroff(A_STANDOUT);
        }

        refresh();

        const int key_input = getch();
        switch (key_input) {
        case KEY_ENTER:
        case 10:
            user_pressed_enter = true;
            did_choose_yes = highlighted_option == 0;
            break;
        case KEY_UP:
            if (highlighted_option > 0) {
                highlighted_option--;
            }
            break;
        case KEY_DOWN:
            if (highlighted_option < 1) {
                highlighted_option++;
            }
            break;
        case 'Y':
        case 'y':
            highlighted_option = 0;
            break;
        case 'N':
        case 'n':
            highlighted_option = 1;
            break;
        default:
            break;
        }
    }
    
    return did_choose_yes;
}

#ifdef __APPLE__
void print_time_elapsed(const uint64_t time_elapsed_ns)
{
    if (time_elapsed_ns >= NS_PER_S)
    {
        const uint64_t seconds = time_elapsed_ns / NS_PER_S;
        const uint64_t nanoseconds = time_elapsed_ns % NS_PER_S;
        printw("%" PRIu64 ".%09" PRIu64 " s", seconds, nanoseconds);
    }
    else if (time_elapsed_ns >= NS_PER_MS)
    {
        const uint64_t milliseconds = time_elapsed_ns / NS_PER_MS;
        const uint64_t nanoseconds = time_elapsed_ns % NS_PER_MS;
        printw("%" PRIu64 ".%06" PRIu64 " ms", milliseconds, nanoseconds);
    }
    else if (time_elapsed_ns >= NS_PER_US)
    {
        const uint64_t microseconds = time_elapsed_ns / NS_PER_US;
        const uint64_t nanoseconds = time_elapsed_ns % NS_PER_US;
        printw("%" PRIu64 ".%03" PRIu64 " us", microseconds, nanoseconds);
    }
    else
    {
        printw("%" PRIu64 " ns", time_elapsed_ns);
    }
}
#endif
