#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#include "input.h"
#include "utils.h"
#include "arrayutils.h"
#include "arraysort.h"
#include "dllist.h"
#include "listsort.h"
#include "maxsubarray.h"
#include "wqunion.h"

const unsigned long SI_h = 100;
const unsigned long SI_k = 1000;
const unsigned long SI_M = 1000000;
const unsigned long SI_G = 1000000000;
const unsigned long SI_hk = SI_h * SI_k;
const unsigned long SI_hM = SI_h * SI_M;
const unsigned long SI_hG = SI_h * SI_G;

struct array_sort_test_runner_vars {
    unsigned int sort_algo_num;
    int* original_array;
    int array_length;
    unsigned long time_elapsed_ns;
    bool was_successful;
};
void array_sort_test(void);
void *array_sort_test_runner(void* arg);

struct list_sort_test_runner_vars {
    unsigned int sort_algo_num;
    struct dllist* original_list;
    unsigned long time_elapsed_ns;
    bool was_successful;
};
void linked_list_sort_test(void);
void* list_sort_test_runner(void* arg);

void max_subarray_test(void);
void union_find_test(void);
void exercise_wqunion(struct wqunion* const wqu, const int option);

size_t get_num_elements(void);
bool get_yes_or_no(void);
void print_time_elapsed(const unsigned long time_elapsed);

enum main_menu_options {
    ARRAY_SORT = 0,
    LIST_SORT,
    MAX_SUBARRAY,
    UNION_FIND,
    QUIT,
    NUM_MAIN_MENU_OPTIONS
};

enum union_menu_options {
    UNION_FIND_ROOT,
    UNION_CHECK_CONNECTION,
    UNION_CONNECT,
    UNION_RETURN_MAIN,
    NUM_UNION_MENU_OPTIONS
};

int main(void)
{
    initscr();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    srand(time(0));

    static const char max_option_char = '0' + NUM_MAIN_MENU_OPTIONS;
    static const char* const menu_options[NUM_MAIN_MENU_OPTIONS] = {
        [ARRAY_SORT]   = "Array Sorting Algorithms",
        [LIST_SORT]    = "Linked List Sorting Algorithms",
        [MAX_SUBARRAY] = "Maximum Subarray",
        [UNION_FIND]   = "Union Find",
        [QUIT]         = "Quit"
    };

    int key_input = 0;
    size_t highlighted_option = 0;
    bool exit_program = false;
    while (!exit_program)
    {
        erase();
        attron(A_BOLD);
        printw("DATA STRUCTURES AND ALGORITHMS TEST SUITE\n\n");
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
        } else if ((key_input == KEY_DOWN) && (highlighted_option < NUM_MAIN_MENU_OPTIONS - 1)) {
            highlighted_option++;
        } else if ((key_input >= '1') && (key_input <= max_option_char)) {
            highlighted_option = ((int) key_input) - '1';
        }
    }

    endwin();
    return 0;
}

enum array_sorts {
    SELECTION_SORT = 0,
    INSERTION_SORT,
    SHELLSORT,
    HEAPSORT,
    MERGE_SORT,
    QUICKSORT,
    NUM_ARRAY_SORTS
};

void array_sort_test(void)
{
    erase();
    attron(A_BOLD);
    printw("Array Sorting Algorithms\n\n");
    attroff(A_BOLD);	

    size_t const array_length = get_num_elements();
    printw("\nArray will contain %zu elements.\n\n", array_length);
    int* const array = malloc(array_length * sizeof(int));
    for (size_t i = 0; i < array_length; i++) {
        array[i] = get_random_num(-1000, 1000);
    }

    static const char* const sort_algorithms[NUM_ARRAY_SORTS] = {
        [SELECTION_SORT] = "Selection Sort",
        [INSERTION_SORT] = "Insertion Sort",
        [SHELLSORT]      = "Shellsort",
        [HEAPSORT]       = "Heapsort",
        [MERGE_SORT]     = "Merge Sort",
        [QUICKSORT]      = "Quicksort"
    };
    
    printw("Skip quadratic algorithms?\n");
    const bool skip_quadratic = get_yes_or_no();
    printw("\n\n");
    const size_t start_point = skip_quadratic ? 2 : 0;
    printw("Please wait...");
    refresh();

    const size_t num_threads = NUM_ARRAY_SORTS - start_point;
    pthread_t threads[num_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    struct array_sort_test_runner_vars vars[num_threads];

    for (size_t i = 0; i < num_threads; i++) {
        vars[i].sort_algo_num = i + start_point;
        vars[i].original_array = array;
        vars[i].array_length = array_length;
        pthread_create(&threads[i], &attr, array_sort_test_runner, &vars[i]);
    }

    for (size_t i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clear();
    printw("When sorting %zu elements:\n\n", array_length);
    for (size_t i = 0; i < num_threads; i++) {
        printw("%-14s: ", sort_algorithms[i + start_point]);
        print_time_elapsed(vars[i].time_elapsed_ns);
        if (!vars[i].was_successful) {
            printw(" (failed)");
        }
        printw("\n");
    }
    refresh();

    printw("\n");
    wait_for_enter();
}


void *array_sort_test_runner(void* arg)
{	
    struct array_sort_test_runner_vars* const vars = arg;

    int* const new_array = copy_int_array(vars->array_length, vars->original_array);

    struct timespec start;
    struct timespec stop;
    clock_gettime(CLOCK_MONOTONIC, &start);
    switch (vars->sort_algo_num) {
    case SELECTION_SORT:
        selection_sort(vars->array_length, new_array);
        break;
    case INSERTION_SORT:
        insertion_sort(vars->array_length, new_array);
        break;
    case SHELLSORT:
        shellsort(vars->array_length, new_array);
        break;
    case HEAPSORT:
        heapsort_array(new_array, 0, vars->array_length - 1);
        break;
    case MERGE_SORT:
        merge_sort_array(vars->array_length, new_array);
        break;
    case QUICKSORT:
        quicksort(new_array, 0, vars->array_length - 1);
        break;
    default:
        break;
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);

    vars->time_elapsed_ns = get_time_diff(start, stop);
    vars->was_successful = array_is_sorted(vars->array_length, new_array);
    
    free(new_array);
    return 0;
}

enum list_sorts {
    LIST_SELECTION_SORT = 0,
    LIST_SELECTION_SORT_SEDGE,
    LIST_INSERTION_SORT,
    LIST_INSERTION_SORT_SEDGE,
    LIST_MERGE_SORT_SEDGE,
    NUM_LIST_SORTS
};

void linked_list_sort_test(void)
{
    erase();
    attron(A_BOLD);
    printw("Linked List Sorting Algorithms\n\n");
    attroff(A_BOLD);
    refresh();

    const size_t list_length = get_num_elements();
    printw("\nList will contain %zu elements.\n\n", list_length);
    dllist_t int_list = dllist_init();
    for (size_t i = 0; i < list_length; i++) {
        dlnode_t* const new_node = malloc(sizeof(struct dlnode));
        if (new_node == NULL) {
            fprintf(stderr, "%s: ERROR: malloc failed.\n", __func__);
            exit(1);
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

    printw("Skip quadratic algorithms?\n");
    const bool skip_quadratic = get_yes_or_no();
    printw("\n\nPlease wait...");
    refresh();

    if (skip_quadratic) {
        dllist_t new_list = dllist_create_copy(&int_list);
        struct timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);
        new_list.first = dllist_merge_sort(new_list.first);
        struct timespec stop;
        clock_gettime(CLOCK_MONOTONIC, &stop);
        const long time_elapsed_ns = get_time_diff(start, stop);
        printw("Merge sort: ");
        print_time_elapsed(time_elapsed_ns);
        if (!dllist_is_sorted(&new_list)) {
            printw(" (failed)");
        }
        printw("\n");
        refresh();
        dllist_destroy(&new_list);
    } else {
        pthread_t threads[NUM_LIST_SORTS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        struct list_sort_test_runner_vars vars[NUM_LIST_SORTS];

        for (size_t i = 0; i < NUM_LIST_SORTS; i++) {
            vars[i].sort_algo_num = i;
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
            print_time_elapsed(vars[i].time_elapsed_ns);
            if (!vars[i].was_successful) {
                printw(" (failed)");
            }
            printw("\n");
        }
        refresh();
    }

    dllist_destroy(&int_list);
    printw("\n");
    wait_for_enter();
}


void* list_sort_test_runner(void* arg)
{	
    struct list_sort_test_runner_vars* const vars = arg;
    dllist_t new_list = dllist_create_copy(vars->original_list);

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    switch (vars->sort_algo_num) {
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
    struct timespec stop;
    clock_gettime(CLOCK_MONOTONIC, &stop);

    vars->time_elapsed_ns = get_time_diff(start, stop);
    vars->was_successful = dllist_is_sorted(&new_list);
    
    dllist_destroy(&new_list);
    return (void*)0;
}


void max_subarray_test(void)
{
    erase();
    attron(A_BOLD);
    printw("Max Subarray Test\n\n");
    attroff(A_BOLD);
    refresh();

    const size_t array_len = get_num_elements();
    int* const array = malloc(array_len * sizeof(int));
    for (size_t i = 0; i < array_len; i++) {
        array[i] = get_random_num(-100, 100);
    }
    printw("Original Array:\n");
    print_int_array_curses(array_len, array);
    refresh();

    
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    struct max_subarray ms = find_max_subarray(array, 0, array_len - 1);
    struct timespec stop;
    clock_gettime(CLOCK_MONOTONIC, &stop);

    printw("\n\nMax Subarray:\n");
    for (size_t i = ms.low_index; i <= ms.high_index; i++) {
        printw("%d ", array[i]);
    }
    printw("\n\nMax Subarray Sum: %d\n", ms.max_sum);

    printw("Time elapsed: ");
    const long time_elapsed = get_time_diff(start, stop);
    print_time_elapsed(time_elapsed);
    printw("\n\n");
    refresh();
    wait_for_enter();
}

void union_find_test(void)
{
    erase();
    
    static const char* const menu_options[NUM_UNION_MENU_OPTIONS] = {
        [UNION_FIND_ROOT]        = "Find the root of a node",
        [UNION_CHECK_CONNECTION] = "Check whether two nodes are connected",
        [UNION_CONNECT]          = "Connect two nodes",
        [UNION_RETURN_MAIN]      = "Return to the main menu"
    };

    attron(A_BOLD);
    printw("UNION FIND TEST\n\n");
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
    size_t highlighted_option = 0;
    bool should_return_to_main = false;
    while (!should_return_to_main) {
        move(y, x);
        clrtobot();
        for (size_t i = 0; i < NUM_UNION_MENU_OPTIONS; i++) {
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
            if (highlighted_option == NUM_UNION_MENU_OPTIONS - 1) {
                should_return_to_main = true;
            } else {
                exercise_wqunion(wqu, highlighted_option);
            }
            break;
        case KEY_UP:
            if (highlighted_option > 0) {
                highlighted_option--;
            }
            break;
        case KEY_DOWN:
            if (highlighted_option < NUM_UNION_MENU_OPTIONS - 1) {
                highlighted_option++;
            }
            break;
        case '1':
        case '2':
        case '3':
        case '4':
            highlighted_option = (size_t)(key_input - '1');
            break;
        default:
            break;
        }
    }

    delete_wqunion(wqu);
}


void exercise_wqunion(struct wqunion* const wqu, const int option)
{
    switch (option) {
    case UNION_FIND_ROOT: // Find root of a node
        printw("\nEnter node number: ");
        refresh();
        const size_t node = get_size_t();
        if (node > wqu->count - 1) {
            printw("\nInvalid input.\n\n");
        } else {
            const int root = get_node_root(wqu, node);
            printw("\nRoot of %d: %d\n\n", node, root);
        }
        wait_for_enter();
        break;
    case UNION_CHECK_CONNECTION: // Check if two nodes are connected
    case UNION_CONNECT: // Connect two nodes
        printw("\nEnter number of first node:  ");
        const size_t node1 = get_size_t();
        printw("Enter number of second node: ");
        const size_t node2 = get_size_t();
        // Validate input
        const size_t last_node = wqu->count - 1;
        if ((node1 > last_node) || (node2 > last_node)) {
            printw("\nInvalid input.\n\n");
        } else if (option == UNION_CHECK_CONNECTION) {
            printw("\nNodes %d and %d: ", node1, node2);
            const bool connected = pair_is_connected(wqu, node1, node2);
            printw("%s\n\n", connected ? "connected" : "not connected");
        } else {
            unify_nodes(wqu, node1, node2);
            printw("\nConnected nodes %d and %d.\n\n", node1, node2);
        }
        wait_for_enter();
        break;
    default:
        break;
    }
}


size_t get_num_elements(void)
{
    // Remember the coordinates so the cursor can be moved
    // back repeatedly in case of invalid user input
    int y;
    int x;
    getyx(stdscr, y, x);
    x = 0;
    
    size_t array_length = 0;
    while (array_length <= 0) {
        move(y,x);
        clrtobot();
        printw("Enter desired number of elements: ");
        refresh();
        array_length = get_size_t();
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
        printw("Yes\n");
        if (highlighted_option == 0) {
            attroff(A_STANDOUT);
        }

        if (highlighted_option == 1) {
            attron(A_STANDOUT);
        }
        printw("No\n");
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


void print_time_elapsed(unsigned long const time_elapsed)
{
    if (time_elapsed < SI_hk) {
        printw("%10lu ns", time_elapsed);
    } else if (time_elapsed < SI_hM) {
        printw("%10lu us", time_elapsed / SI_k);
    } else if (time_elapsed < SI_hG) {
        printw("%10lu ms", time_elapsed / SI_M);
    } else {
        printw("%10lu  s", time_elapsed / SI_G);
    }
}

