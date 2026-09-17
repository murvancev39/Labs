#include "main.h"


int main (int argc, char *argv [])
{
    if (argc != 3) return incorrect_number_args_error;
    if (strlen (argv [2]) >= INIT_PATH_LEN) return path_length_exceeded_error;

    interface_t *interface = NULL;

    if (!strcmp (argv [1], "--RSQ_FENW"))   interface = RSQ_FENW_interface          (FROM, TO, STEP, argv [2]);
    if (!strcmp (argv [1], "--RMQ_N_LOGN")) interface = RMQ_N_LOGN_interface        (FROM, TO, STEP, argv [2]);
    if (!strcmp (argv [1], "--RMQ_LOGN_N")) interface = RMQ_LOGN_N_interface        (FROM, TO, STEP, argv [2]);    
    if (!strcmp (argv [1], "--RSQ_SEG"))    interface = RSQ_SEG_interface_interface (FROM, TO, STEP, argv [2]);
    error_code_t error_code = all_okey;

    if (!interface) return 0;

    error_code = run (*interface);
    
    free (interface);

#ifndef NDEBUG
    if (error_code) error_code_handling (error_code);
#endif

    return error_code;
}

void error_code_handling (error_code_t error_code)
{
    if (error_code == all_okey) return;

    fprintf (stderr, ANSI_COLOR_RED "\n[FATAL ERROR] Code: %d\n" ANSI_COLOR_RESET, error_code);

    switch (error_code)
    {
    case alloc_error:
        fprintf (stderr, "Message: Memory allocation failed.\n"
                        "Possible reason: System is out of memory or heap is corrupted.\n");
        break;

    case fopen_error:
        fprintf (stderr, "Message: File open error.\n"
                        "Possible reason: Path doesn't exist or insufficient permissions.\n");
        break;

    case output_error:
        fprintf (stderr, "Message: Writing to file failed.\n"
                        "Possible reason: Disk full or broken pipe.\n");
        break;

    case func_ptr_error:
        fprintf (stderr, "Message: Invalid function pointer.\n"
                        "Possible reason: One of the interface functions (add/delete/init) is NULL.\n");
        break;

    case test_gen_error:
        fprintf (stderr, "Message: Test generation failed.\n"
                        "Possible reason: Randomizer error or size overflow.\n");
        break;

    case make_path_error:
        fprintf (stderr, "Message: Path creation failed.\n"
                        "Possible reason: String concatenation logic error.\n");
        break;

    case path_intit_error:
        fprintf (stderr, "Message: Path initialization error.\n"
                        "Possible reason: Target path pointer is NULL or empty.\n");
        break;

    case null_argument_error:
        fprintf (stderr, "Message: Null pointer passed as argument.\n"
                        "Possible reason: Core logic received NULL where data was expected.\n");
        break;

    case func_name_init_error:
        fprintf (stderr, "Message: Failed to identify the function name.\n"
                        "Possible reason: The string with the tree name (e.g., 'AVL') is empty or NULL.\n");
        break;

    case snprintf_overflow_error:
        fprintf (stderr, "Message: snprintf buffer overflow.\n"
                        "Possible reason: Resulting string is longer than MAX_PATH_LEN.\n");
        break;

    case path_length_exceeded_error:
        fprintf (stderr, "Message: Input path is too long.\n"
                        "Possible reason: Provided directory path exceeds INIT_PATH_LEN.\n");
        break;

    case incorrect_number_args_error:
        fprintf (stderr, "Message: Invalid CLI arguments.\n"
                        "Possible reason: Check 'from', 'to' and 'step' parameters.\n");
        break;

    default:
        fprintf (stderr, "Message: Unknown error occurred.\n"
                        "Possible reason: Error code is not defined in system enum.\n");
        break;
    }
    
    fprintf (stderr, ANSI_COLOR_BLUE "Advice: Check logs above for file:line info.\n\n" ANSI_COLOR_RESET);
    return;
}


interface_t *RMQ_N_LOGN_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->to         = to;
    interface->from       = from;
    interface->step       = step;
    interface->update_f   = NULL;
    interface->destruct_f = destruct_v_n_wrapp;
    interface->init_with_feel_f    = create_v_n;
    interface->search_f   = rmq_search_v_n_wrapp;
    interface->test_pairs_gen_f    = test_pairs_gen;
    interface->test_sequence_gen_f = test_sequence_gen;

    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}

void destruct_v_n_wrapp (void *table)
{
    destruct_v_n (table);
    return;
}

error_code_t rmq_search_v_n_wrapp (void *table, unsigned int left, unsigned int right)
{
    if (!table) return null_argument_error;
    rmq_v_n (table, left, right);
    return all_okey;
}


interface_t *RMQ_LOGN_N_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->to         = to;
    interface->from       = from;
    interface->step       = step;
    interface->update_f   = NULL;
    interface->destruct_f = destruct_v_logn_wrapp;
    interface->init_with_feel_f    = create_v_logn;
    interface->search_f   = rmq_search_v_logn_wrapp;
    interface->test_pairs_gen_f    = test_pairs_gen;
    interface->test_sequence_gen_f = test_sequence_gen;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}

void destruct_v_logn_wrapp (void *table)
{
    destruct_v_logn (table);
    return;
}

error_code_t rmq_search_v_logn_wrapp (void *table, unsigned int left, unsigned int right)
{
    if (!table) return null_argument_error;
    rmq_v_logn (table, left, right);
    return all_okey;
}

interface_t *RSQ_FENW_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->to         = to;
    interface->from       = from;
    interface->step       = step;
    interface->destruct_f = fenw_destructor_wrapp;
    interface->update_f   = fenw_update_wrapp;
    interface->search_f   = fenw_search_wrapp;
    interface->init_with_feel_f = fenwik_init;
    interface->test_pairs_gen_f = test_pairs_gen;
    interface->test_sequence_gen_f = test_sequence_gen;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}

void fenw_destructor_wrapp (void *table)
{
    fenw_destructor (table);
    return;
}

error_code_t fenw_search_wrapp (void *table, unsigned int left, unsigned int right)
{
    if (!table) return null_argument_error;
    fenw_query (table, left, right);
    return all_okey;
}

error_code_t fenw_update_wrapp (void *table, unsigned int left, unsigned int right)
{
    if (!table) return null_argument_error;
    fenw_update (table, left, right);
    return all_okey;
}

interface_t *RSQ_SEG_interface_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->to       = to;
    interface->from     = from;
    interface->step     = step;
    interface->update_f = seg_tree_update_wrapp;
    interface->search_f = seg_tree_search_wrapp;
    interface->init_with_feel_f    = seg_tree_init;
    interface->test_pairs_gen_f    = test_pairs_gen;
    interface->destruct_f          = seg_tree_destructor_wrapp;
    interface->test_sequence_gen_f = test_sequence_gen;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}

void seg_tree_destructor_wrapp (void *table)
{
    seg_tree_destructor (table);
    return;
}

error_code_t seg_tree_search_wrapp (void *table, unsigned int left, unsigned int right)
{
    if (!table) return null_argument_error;
    seg_tree_query (table, left, right);
    return all_okey;
}

error_code_t seg_tree_update_wrapp (void *table, unsigned int left, unsigned int right)
{
    if (!table) return null_argument_error;
    seg_tree_update (table, left, right);
    return all_okey;
}
