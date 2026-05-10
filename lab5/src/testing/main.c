#include "main.h"

int main (int argc, char *argv [])
{
    if (argc != 3) return incorrect_number_args_error;
    if (strlen (argv [2]) >= INIT_PATH_LEN) return path_length_exceeded_error;

    interface_t *interface = NULL;

    if (!strcmp (argv [1], "--B"))        interface = B_interface    (BIG_FROM, BIG_TO, BIG_STEP, argv [2]);    
    if (!strcmp (argv [1], "--RB"))       interface = RB_interface   (BIG_FROM, BIG_TO, BIG_STEP, argv [2]);    
    if (!strcmp (argv [1], "--AVL"))      interface = AVL_interface  (BIG_FROM, BIG_TO, BIG_STEP, argv [2]);    
    if (!strcmp (argv [1], "--CRT"))      interface = CRT_interface  (BIG_FROM, BIG_TO, BIG_STEP, argv [2]);    
    if (!strcmp (argv [1], "--SPL"))      interface = SPL_interface  (BIG_FROM, BIG_TO, BIG_STEP, argv [2]);
    if (!strcmp (argv [1], "--SKIP"))     interface = SKIP_interface (BIG_FROM, BIG_TO, BIG_STEP, argv [2]);    
    if (!strcmp (argv [1], "--BST_RAND")) interface = BST_interface  (BST_RAND_ALL, BST_RAND_ALL, BST_RAND_ALL, argv [2]); 
    if (!strcmp (argv [1], "--BST_SORT")) interface = BST_interface  (BST_SORTED_ALL, BST_SORTED_ALL, BST_SORTED_ALL, argv [2]); 

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


interface_t *AVL_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = AVL_add;
    interface->init_f     = AVL_init;
    interface->delete_f   = AVL_delete;
    interface->destruct_f = AVL_destructor;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}



interface_t *B_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = B_add;
    interface->init_f     = B_init;
    interface->delete_f   = B_delete;
    interface->destruct_f = B_free_tree;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}



interface_t *BST_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = BST_add;
    interface->init_f     = BST_init;
    interface->delete_f   = BST_delete;
    interface->destruct_f = BST_destructor;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}

interface_t *CRT_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = CRT_add;
    interface->init_f     = CRT_init;
    interface->delete_f   = CRT_delete;
    interface->destruct_f = CRT_destroy_tree;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}


interface_t *RB_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = RB_add;
    interface->init_f     = RB_init;
    interface->delete_f   = RB_delete;
    interface->destruct_f = RB_destroy_tree;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}


interface_t *SKIP_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = SKIP_add;
    interface->init_f     = SKIP_init;
    interface->delete_f   = SKIP_delete;
    interface->destruct_f = SKIP_destructor;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);
    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}


interface_t *SPL_interface (unsigned from, unsigned to, unsigned step, char path [])
{
    interface_t *interface = (interface_t *) malloc (1 * sizeof (interface_t));
    if (!interface) return NULL;

    interface->add_f      = SPL_add;
    interface->delete_f   = SPL_delete;
    interface->init_f     = SPL_ctr_tree;
    interface->destruct_f = SPL_destructor;
    interface->test_gen_f = rand_unsigned_arr;
    interface->from       = from;
    interface->to         = to;
    interface->step       = step;
    strncpy (interface->_path, path, INIT_PATH_LEN - 1);

    interface->_path [INIT_PATH_LEN - 1] = '\0';
    return interface;
}

