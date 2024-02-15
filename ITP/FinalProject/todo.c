#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "lib/clui.h"

#define _TO_STR(x) #x
#define TO_STR(x) _TO_STR(x)

// -- Program name --

#define PROGRAM_NAME "Simple Todo List"

// -- Terminal sizes --

#define TERMINAL_MIN_ROWS 10
#define TERMINAL_MIN_COLS 50
#define PRIORITY_COMLUMN_WIDTH 10
#define DEADLINE_COMLUMN_WIDTH 12

// -- Footer texts --

#define MAIN_WINDOW_FOOTER "<N> New task  <D> Delete task  <J> Down  <K> Up  <Return> View task  <S> Sort By  <Q> Quit"
#define TASK_DETAILS_FOOTER "<Q> Return to main menu  <T> Edit title  <D> Edit description  <P> Edit priority  <L> Edit deadline"

// -- Formatted texts --

#define USER_FRIENDLY_INPUT_FORMAT " ==> Enter %s (leave blank to cancel): "
#define MAX_LEN_EXCEEDED_ERROR_FORMAT " ==> %s cannot be more than %d characters."
#define NOT_A_NUMBER_ERROR_FORMAT " ==> %s should be a number."
#define INVALID_RANGE_ERROR_FORMAT " ==> %s should be between %lld and %lld."
#define SMALL_TERMINAL_ERROR_FORMAT PROGRAM_NAME " needs at least " TO_STR(TERMINAL_MIN_ROWS) " * " TO_STR(TERMINAL_MIN_COLS) " terminal window. Please resize the terminal."

// -- Texts about deadline --

#define DEADLINE_PASSED_STATUS_TEXT "Passed"
#define LESS_THAN_A_DAY_STATUS_TEXT "< 1 day"

// -- Window titles --

#define TITLE_PREFIX " -- " PROGRAM_NAME " - %s --"
#define MAIN_WINDOW_TITLE_TEXT "All Tasks"
#define NEW_TASK_WINDOW_TITLE_TEXT "New Task"
#define TASK_DETAILS_WINDOW_TITLE_TEXT "Task Details"
#define EDIT_TASK_WINDOW_TITLE_TEXT "Edit Task"

// -- User input names --

#define INPUT_TITLE_TASK_TITLE "task title"
#define INPUT_TITLE_TASK_DESCRIPTION "task description"
#define INPUT_TITLE_TASK_PRIORITY "task priority"
#define INPUT_TITLE_TASK_DEADLINE "days to task deadline"

// -- Column title texts --

#define MAIN_WINDOW_TITLE_COLUMN_TEXT "Title"
#define MAIN_WINDOW_PRIORITY_COLUMN_TEXT "Priority"
#define MAIN_WINDOW_DEADLINE_COLUMN_TEXT "Deadline"

#define TASKS_EMPTY_MESSAGE "  So Empty here... Press <N> to add a new task."

// -- Colors --

#define WINDOW_TITLE_R 52
#define WINDOW_TITLE_G 192
#define WINDOW_TITLE_B 235

#define DESCRIPTION_R 150
#define DESCRIPTION_G 150
#define DESCRIPTION_B 150

#define MENU_CURSOR_R 173
#define MENU_CURSOR_G 121
#define MENU_CURSOR_B 0

#define PRIORITY_VERY_HIGH_R 235
#define PRIORITY_VERY_HIGH_G 64
#define PRIORITY_VERY_HIGH_B 52

#define PRIORITY_HIGH_R 235
#define PRIORITY_HIGH_G 155
#define PRIORITY_HIGH_B 52

#define PRIORITY_MEDIUM_R 235
#define PRIORITY_MEDIUM_G 216
#define PRIORITY_MEDIUM_B 235


#define PRIORITY_LOW_R 103
#define PRIORITY_LOW_G 235
#define PRIORITY_LOW_B 52

#define PRIORITY_VERY_LOW_R 52
#define PRIORITY_VERY_LOW_G 189
#define PRIORITY_VERY_LOW_B 235

void m_str_trim(char* input_str, int max_size, char* dst) {
    const int input_str_len = strlen(input_str);

    if (input_str_len <= max_size) {
        strcpy(dst, input_str);
        return;
    }

    for (int i = 0; i < max_size - 3; i++) {
        dst[i] = input_str[i];
    }
    for (int i = max_size - 3; i < max_size; i++) {
        dst[i] = '.';
    }
    dst[max_size] = '\0';
}

// Works only for positive integer
char* mstr_int_to_str(int n) {
    if (n < 0) {
        return NULL;
    }
    if (n == 0) {
        char* result = malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';

        return result;
    }

    int buffer_size = 1;
    char* result_buffer = malloc(buffer_size * sizeof(char));

    while (n > 0) {
        buffer_size++;
        result_buffer = realloc(result_buffer, buffer_size * sizeof(char));

        char cur_char = (n % 10) + '0';

        if (buffer_size > 2) {
            for (int i = buffer_size - 3; i >= 0; i--){
                result_buffer[i + 1] = result_buffer[i];
            }
        }
        result_buffer[0] = cur_char;

        n /= 10; // Shift to right
    }

    // Null-terminate result string
    result_buffer[buffer_size - 1] = '\0';

    return result_buffer;
}

#define MAX_TITLE_LEN 100
#define MAX_DESCRIPTION_LEN 400
#define MIN_PRIORITY 1
#define MAX_PRIORITY 10
#define MIN_DEADLINE 0
#define MAX_DEADLINE 4611686018427387904ll

// Main struct for storing task information
typedef struct task{
    char* title_s;
    char* description_s;
    int priority_i;
    long long int deadline_ll;
} task_t;

// Struct for storing an array of task_t
typedef struct task_list{
    task_t** tasks;
    int size;
} task_list_t;

enum sort_types {
    SORT_TYPE_TITLE = 0,
    SORT_TYPE_PRIORITY = 1,
    SORT_TYPE_DEADLINE = 2
};

int _cmp_by_priority(const void* task_a, const void* task_b) {

    const int priority_a = (*(task_t**)task_a)->priority_i;
    const int priority_b = (*(task_t**)task_b)->priority_i;

    if (priority_a < priority_b) {
        return +1;
    } else if (priority_a > priority_b) {
        return -1;
    } else {
        return 0;
    }
}

int _cmp_by_title(const void* task_a, const void* task_b) {
    const char* title_a = (*((task_t**)task_a))->title_s;
    const char* title_b = (*((task_t**)task_b))->title_s;

    return -strcmp(title_b, title_a);
}

int _cmp_by_deadline(const void* task_a, const void* task_b) {
    const int deadline_a = (*(task_t**)task_a)->deadline_ll;
    const int deadline_b = (*(task_t**)task_b)->deadline_ll;

    if (deadline_a < deadline_b) {
        return -1;
    } else if (deadline_a > deadline_b) {
        return +1;
    } else {
        return 0;
    }
}

task_list_t* tasks_init() {
    task_list_t* new_task_list = malloc(sizeof(task_list_t));

    new_task_list->tasks = NULL;
    new_task_list->size = 0;

    return new_task_list;
}

task_t* tasks_create(task_list_t* task_list, char* title, char* description, int priority, long long int deadline) {

    const int title_len = strlen(title);
    const int desc_len = strlen(description);

    // Check input
    if (title_len == 0 || title_len > MAX_TITLE_LEN) {
        return NULL;
    }
    if (desc_len == 0 || desc_len > MAX_DESCRIPTION_LEN) {
        return NULL;
    }
    if (priority < 1 || priority > 10) {
        return NULL;
    }

    // Create task_t object
    task_t* new_task = malloc(sizeof(task_t));

    new_task->title_s = malloc((title_len + 1) * sizeof(char));
    new_task->description_s = malloc((desc_len + 1) * sizeof(char));

    // Store title and description
    strcpy(new_task->title_s, title);
    strcpy(new_task->description_s, description);

    // Store priority and deadline
    new_task->priority_i = priority;
    new_task->deadline_ll = deadline;

    // Insert new task into tasks array
    task_list->size = task_list->size + 1;
    task_list->tasks = realloc(task_list->tasks, task_list->size * sizeof(task_t*));
    (task_list->tasks)[task_list->size - 1] = new_task;

    return new_task;
}

void tasks_delete(task_list_t* task_list, int index) {
    if (index >= task_list->size) {
        return;
    }

    // Clean up
    free(task_list->tasks[index]->title_s);
    free(task_list->tasks[index]->description_s);
    free(task_list->tasks[index]);

    if (task_list->size == 1) {
        task_list->tasks = NULL;
    } else {
        for (int i = index + 1; i < task_list->size; i++) {
            task_list->tasks[i - 1] = task_list->tasks[i];
        }
    }

    task_list->size = task_list->size - 1;
    task_list->tasks = realloc(task_list->tasks, task_list->size * sizeof(task_t*));
}

void tasks_sort(task_list_t* task_list, enum sort_types sort_type) {
    if (sort_type == SORT_TYPE_PRIORITY) {
        qsort(task_list->tasks, task_list->size, sizeof(task_t*), _cmp_by_priority);
    } else if (sort_type == SORT_TYPE_TITLE) {
        qsort(task_list->tasks, task_list->size, sizeof(task_t*), _cmp_by_title);
    } else if (sort_type == SORT_TYPE_DEADLINE) {
        qsort(task_list->tasks, task_list->size, sizeof(task_t*), _cmp_by_deadline);
    }
}

void tasks_edit_title(task_t* task, const char* new_title) {
    const int new_title_len = strlen(new_title);
    
    if (new_title_len == 0 || new_title_len > MAX_TITLE_LEN) {
        return;
    }

    task->title_s = realloc(task->title_s, (new_title_len + 1) * sizeof(char));
    strcpy(task->title_s, new_title);
}

void tasks_edit_description(task_t* task, char* new_description) {
    const int new_description_len = strlen(new_description);
    
    if (new_description_len == 0 || new_description_len > MAX_TITLE_LEN) {
        return;
    }

    task->description_s = realloc(task->description_s, (new_description_len + 1) * sizeof(char));
    strcpy(task->description_s, new_description);
}

void tasks_edit_priority(task_t* task, int new_priority) {
    if (new_priority < MIN_PRIORITY || new_priority > MAX_PRIORITY) {
        return;
    }

    task->priority_i = new_priority;
}

void tasks_edit_deadline(task_t* task, long long int new_deadline) {
    if (new_deadline < MIN_DEADLINE || new_deadline > MAX_DEADLINE) {
        return;
    }

    task->deadline_ll = new_deadline;
}

enum window_state{
    WINDOW_STATE_MAIN,
    WINDOW_STATE_NEW_TASK,
    WINDOW_STATE_TASK_DETAILS,
    WINDOW_STATE_EDIT_TASK_TITLE,
    WINDOW_STATE_EDIT_TASK_DESCRIPTION,
    WINDOW_STATE_EDIT_TASK_PRIORITY,
    WINDOW_STATE_EDIT_TASK_DEADLINE
};

typedef struct {
    int cur_position;
    enum window_state cur_window_state;
    enum sort_types sort_type;
} menu_state_t;

bool window_is_size_ok() {
    return (get_window_rows() >= TERMINAL_MIN_ROWS && get_window_cols() >= TERMINAL_MIN_COLS);
}

char* _get_str_input_user_friendly(const char* input_name, int max_len) {

    char* input = NULL;

    while (1) {
        printf(USER_FRIENDLY_INPUT_FORMAT, input_name);

        int i;
        for (i = 0; i < max_len; i++) {
            char next_char = fgetc(stdin);
            if (next_char == EOF || next_char == '\n') {
                break;
            }
            input = realloc(input, (i + 2) * sizeof(char));
            input[i] = next_char;
        }

        if (i >= max_len - 1 && fgetc(stdin) != EOF) {
            // Max length exceeded
            printf(MAX_LEN_EXCEEDED_ERROR_FORMAT "\n\n", input_name, max_len);
            continue;
        } else if (i == 0){
            // Cancel
            free(input);
            return NULL;
        } else {
            input[i] = '\0';
            break;
        }
    }

    return input;
}

long long int _get_ll_input_user_friendly(const char* input_name, long long int min_value, long long int max_value) {

    long long int input;

    while (1) {
        char* input_str = _get_str_input_user_friendly(input_name, 64);
        if (input_str == NULL) {
            // Insertion of new task is canceled.
            return -1;
        }
        int scanf_result = sscanf(input_str, "%lld", &input);

        if (scanf_result <= 0) {
            printf(NOT_A_NUMBER_ERROR_FORMAT "\n\n", input_name);
            continue;
        } else if (input < min_value || input > max_value) {
            printf(INVALID_RANGE_ERROR_FORMAT "\n\n", input_name, min_value, max_value);
            continue;
        } else {
            return input;
        }

    }
}

void _print_title_bar(const char* title) {
    change_color_rgb(WINDOW_TITLE_R, WINDOW_TITLE_G, WINDOW_TITLE_B);
    printf(TITLE_PREFIX "\n", title);
    reset_color();
}

char* _get_human_readable_eta(long long int timestamp) {
    const long long int end_of_today = ((time(NULL) / (24 * 3600)) + 1) * (24 * 3600);
    const long long int end_of_timestamp_day = ((timestamp / (24 * 3600)) + 1) * (24 * 3600);

    const long long int days_diff = (end_of_timestamp_day - end_of_today) / (24 * 3600);

    char* result = malloc((12 + 1) * sizeof(char));

    if (days_diff < 0) {
        snprintf(result, 12 * sizeof(char), DEADLINE_PASSED_STATUS_TEXT);
    } else if (days_diff == 0) {
        snprintf(result, 12 * sizeof(char), LESS_THAN_A_DAY_STATUS_TEXT);
    } else if (days_diff == 1) {
        snprintf(result, 12 * sizeof(char), "%lld day", days_diff);
    } else {
        snprintf(result, 12 * sizeof(char), "%lld days", days_diff);
    }

    return result;
}

void _update_for_main(task_list_t* task_list, menu_state_t cur_menu_state) {

    const int cur_window_cols = get_window_cols();
    const int cur_window_rows = get_window_rows();

    _print_title_bar(MAIN_WINDOW_TITLE_TEXT);

    const int title_width = cur_window_cols - (DEADLINE_COMLUMN_WIDTH + PRIORITY_COMLUMN_WIDTH);

    if (cur_menu_state.sort_type == SORT_TYPE_TITLE) {
        change_color_rgb(WINDOW_TITLE_R, WINDOW_TITLE_G, WINDOW_TITLE_B);
    }
    printf("%-*s", title_width, MAIN_WINDOW_TITLE_COLUMN_TEXT);
    reset_color();

    if (cur_menu_state.sort_type == SORT_TYPE_PRIORITY) {
        change_color_rgb(WINDOW_TITLE_R, WINDOW_TITLE_G, WINDOW_TITLE_B);
    }
    printf("%-*s", PRIORITY_COMLUMN_WIDTH, MAIN_WINDOW_PRIORITY_COLUMN_TEXT);
    reset_color();

    if (cur_menu_state.sort_type == SORT_TYPE_DEADLINE) {
        change_color_rgb(WINDOW_TITLE_R, WINDOW_TITLE_G, WINDOW_TITLE_B);
    }
    printf("%-*s", DEADLINE_COMLUMN_WIDTH, MAIN_WINDOW_DEADLINE_COLUMN_TEXT);
    reset_color();

    if (task_list->size == 0) {
        printf("\n\n" TASKS_EMPTY_MESSAGE);
    }

    char* trimmed_task_title = malloc(title_width * sizeof(char) + 1);

    for (int i = 0; i < task_list->size; i++) {
        task_t* cur_task = (task_list->tasks)[i];

        m_str_trim(cur_task->title_s, title_width - 1, trimmed_task_title);

        if (i == cur_menu_state.cur_position) {
            change_color_rgb(MENU_CURSOR_R, MENU_CURSOR_G, MENU_CURSOR_B);
        }
        printf("%-*s", title_width, trimmed_task_title);

        if (i == cur_menu_state.cur_position) {
            change_color_rgb(MENU_CURSOR_R, MENU_CURSOR_G, MENU_CURSOR_B);
        } else if (cur_task->priority_i <= 2) {
            change_color_rgb(PRIORITY_VERY_LOW_R, PRIORITY_VERY_LOW_G, PRIORITY_VERY_LOW_B);
        } else if (cur_task->priority_i <= 4) {
            change_color_rgb(PRIORITY_LOW_R, PRIORITY_LOW_G, PRIORITY_LOW_B);
        } else if (cur_task->priority_i <= 6) {
            change_color_rgb(PRIORITY_MEDIUM_R, PRIORITY_MEDIUM_G, PRIORITY_MEDIUM_B);
        } else if (cur_task->priority_i <= 8) {
            change_color_rgb(PRIORITY_HIGH_R, PRIORITY_HIGH_G, PRIORITY_HIGH_B);
        } else {
            change_color_rgb(PRIORITY_VERY_HIGH_R, PRIORITY_VERY_HIGH_G, PRIORITY_VERY_HIGH_B);
        }
        printf("%-*d", PRIORITY_COMLUMN_WIDTH, cur_task->priority_i);
        reset_color();


        char* human_readable_eta = _get_human_readable_eta(cur_task->deadline_ll);

        if (i == cur_menu_state.cur_position) {
            change_color_rgb(MENU_CURSOR_R, MENU_CURSOR_G, MENU_CURSOR_B);
        }
        printf("%-*s", DEADLINE_COMLUMN_WIDTH, human_readable_eta);
        reset_color();

        free(human_readable_eta);
    }

    free(trimmed_task_title);

    cursor_to_pos(cur_window_rows - 1, 2);

    change_color_rgb(WINDOW_TITLE_R, WINDOW_TITLE_G, WINDOW_TITLE_B);
    printf(MAIN_WINDOW_FOOTER);
    reset_color();
}

void _update_for_new_task(task_list_t* task_list) {

    _print_title_bar(NEW_TASK_WINDOW_TITLE_TEXT);

    char* new_task_title = _get_str_input_user_friendly(INPUT_TITLE_TASK_TITLE, MAX_TITLE_LEN);
    if (new_task_title == NULL) {
        // Insertion of new task is canceled.
        return;
    }
    clear_screen();

    _print_title_bar(NEW_TASK_WINDOW_TITLE_TEXT);
    char* new_task_description = _get_str_input_user_friendly(INPUT_TITLE_TASK_DESCRIPTION, MAX_DESCRIPTION_LEN);
    if (new_task_description == NULL) {
        // Insertion of new task is canceled.
        return;
    }
    clear_screen();

    _print_title_bar(NEW_TASK_WINDOW_TITLE_TEXT);
    int priority = _get_ll_input_user_friendly(INPUT_TITLE_TASK_PRIORITY, MIN_PRIORITY, MAX_PRIORITY);
    if (priority < 0) {
        // Insertion of new task is canceled.
        return;
    }
    clear_screen();

    _print_title_bar(NEW_TASK_WINDOW_TITLE_TEXT);

    int days_to_deadline = _get_ll_input_user_friendly(INPUT_TITLE_TASK_DEADLINE, MIN_DEADLINE, MAX_DEADLINE);
    if (days_to_deadline < 0) {
        // Insertion of new task is canceled.
        return;
    }

    long long int deadline = time(NULL) + (24ll * 3600 * days_to_deadline);

    clear_screen();

    tasks_create(task_list, new_task_title, new_task_description, priority, deadline);

    free(new_task_title);
    free(new_task_description);
}

void _update_for_task_details(task_list_t* task_list, menu_state_t cur_menu_state) {

    const int cur_window_rows = get_window_rows();

    _print_title_bar(TASK_DETAILS_WINDOW_TITLE_TEXT);

    task_t* cur_task = (task_list->tasks)[cur_menu_state.cur_position];

    printf("> %s\n", cur_task->title_s);
    printf("> " MAIN_WINDOW_PRIORITY_COLUMN_TEXT ": %d\n", cur_task->priority_i);

    char formatted_time_str[21];
    time_t deadline_time = cur_task->deadline_ll;
    struct tm* tm_info = localtime(&deadline_time);

    strftime(formatted_time_str, sizeof(formatted_time_str), "%Y-%m-%d", tm_info);

    printf("> " MAIN_WINDOW_DEADLINE_COLUMN_TEXT ": %s\n", formatted_time_str);

    printf("\n");

    change_color_rgb(DESCRIPTION_R, DESCRIPTION_G, DESCRIPTION_B);
    printf(">> %s", cur_task->description_s);
    reset_color();

    cursor_to_pos(cur_window_rows - 1, 2);
    change_color_rgb(WINDOW_TITLE_R, WINDOW_TITLE_G, WINDOW_TITLE_B);
    printf(TASK_DETAILS_FOOTER);
    reset_color();
}

void _update_for_edit_task(task_list_t* task_list, menu_state_t cur_menu_state) {

    task_t* cur_task = task_list->tasks[cur_menu_state.cur_position];

    _print_title_bar(EDIT_TASK_WINDOW_TITLE_TEXT);

    if (cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_TITLE) {
        char* new_title = _get_str_input_user_friendly("new " INPUT_TITLE_TASK_TITLE, MAX_TITLE_LEN);
        if (new_title == NULL) {
            // Cancelled
            return;
        }
        tasks_edit_title(cur_task, new_title);
    } else if (cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_DESCRIPTION) {
        char* new_description = _get_str_input_user_friendly("new " INPUT_TITLE_TASK_DESCRIPTION, MAX_DESCRIPTION_LEN);
        if (new_description == NULL) {
            // Cancelled
            return;
        }
        tasks_edit_description(cur_task, new_description);
    } else if (cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_PRIORITY) {
        int new_priority = _get_ll_input_user_friendly("new " INPUT_TITLE_TASK_PRIORITY, MIN_PRIORITY, MAX_PRIORITY);
        if (new_priority == -1) {
            // Cancelled
            return;
        }
        tasks_edit_priority(cur_task, new_priority);
    } else if (cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_DEADLINE) {
        long long new_deadline = _get_ll_input_user_friendly("new " INPUT_TITLE_TASK_DEADLINE, MIN_DEADLINE, MAX_DEADLINE);
        if (new_deadline == -1) {
            // Cancelled
            return;
        }
        tasks_edit_deadline(cur_task, new_deadline);
    }
}

void window_update(task_list_t* task_list, menu_state_t cur_menu_state) {

    clear_screen();

    if (!window_is_size_ok()) {
        printf(SMALL_TERMINAL_ERROR_FORMAT);
        flush();
        return;
    }

    if (cur_menu_state.cur_window_state == WINDOW_STATE_MAIN) {
        _update_for_main(task_list, cur_menu_state);
    } else if (cur_menu_state.cur_window_state == WINDOW_STATE_NEW_TASK) {
        _update_for_new_task(task_list);
    } else if (cur_menu_state.cur_window_state == WINDOW_STATE_TASK_DETAILS) {
        _update_for_task_details(task_list, cur_menu_state);
    } else if (
        cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_TITLE ||
        cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_DESCRIPTION ||
        cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_PRIORITY ||
        cur_menu_state.cur_window_state == WINDOW_STATE_EDIT_TASK_DEADLINE
    ) {
        _update_for_edit_task(task_list, cur_menu_state);
    }

    flush();
}

int calc_new_menu_position(int old_pos, int menu_size, int shift_amount) {
    return (old_pos + menu_size + shift_amount) % menu_size;
    //                    |
    //                    |
    //   <This is for when left side of % is negative>
}

int main() {

    task_list_t* main_task_list = tasks_init();
    menu_state_t main_menu_state = {
        0, // cur_position
        WINDOW_STATE_MAIN, // cur_menu_state
        SORT_TYPE_TITLE
    };

    init_clui();
    window_update(main_task_list, main_menu_state);

    while (1) { // Main program loop
        window_update(main_task_list, main_menu_state);
        if (!window_is_size_ok()) {
            delay(10);
            continue;
        }

        char cur_key = getch();

        if (main_menu_state.cur_window_state == WINDOW_STATE_MAIN){
            if (cur_key == 'n') {
                main_menu_state.cur_window_state = WINDOW_STATE_NEW_TASK;
                window_update(main_task_list, main_menu_state);
                tasks_sort(main_task_list, main_menu_state.sort_type);
                main_menu_state.cur_window_state = WINDOW_STATE_MAIN;

            } else if (cur_key == 'q') {
                quit();
                return 0;
            } else if (cur_key == 'j') {
                if (main_task_list->size > 0) { 
                    main_menu_state.cur_position = calc_new_menu_position(main_menu_state.cur_position, main_task_list->size, +1); // Move down
                } else {
                    continue;
                }
            } else if (cur_key == 'k') {
                if (main_task_list->size > 0) { 
                    main_menu_state.cur_position = calc_new_menu_position(main_menu_state.cur_position, main_task_list->size, -1); // Move up
                } else {
                    continue;
                }
            } else if (cur_key == '\n') {
                if (main_task_list->size > 0) {
                    main_menu_state.cur_window_state = WINDOW_STATE_TASK_DETAILS;
                } else {
                    continue;
                }
            } else if (cur_key == 'd') {
                if (main_task_list->size > 0){
                    tasks_delete(main_task_list, main_menu_state.cur_position);
                    if (main_task_list->size != 0 && main_menu_state.cur_position == main_task_list->size) {
                        // Move up by 1
                        main_menu_state.cur_position = calc_new_menu_position(main_menu_state.cur_position, main_task_list->size, -1);
                    }
                    tasks_sort(main_task_list, main_menu_state.sort_type);
                } else {
                    continue;
                }
            } else if (cur_key == 's') {
                main_menu_state.sort_type = (main_menu_state.sort_type + 1) % 3;
                tasks_sort(main_task_list, main_menu_state.sort_type);
            }
        } else if (main_menu_state.cur_window_state == WINDOW_STATE_TASK_DETAILS) {
            if (cur_key == 'q') {
                main_menu_state.cur_window_state = WINDOW_STATE_MAIN;
            } else if (cur_key == 't') {
                // Edit task title
                main_menu_state.cur_window_state = WINDOW_STATE_EDIT_TASK_TITLE;
                window_update(main_task_list, main_menu_state);
                tasks_sort(main_task_list, main_menu_state.sort_type);
                main_menu_state.cur_window_state = WINDOW_STATE_TASK_DETAILS;
            } else if (cur_key == 'd') {
                // Edit task description
                main_menu_state.cur_window_state = WINDOW_STATE_EDIT_TASK_DESCRIPTION;
                window_update(main_task_list, main_menu_state);
                tasks_sort(main_task_list, main_menu_state.sort_type);
                main_menu_state.cur_window_state = WINDOW_STATE_TASK_DETAILS;
            } else if (cur_key == 'p') {
                // Edit task priority
                main_menu_state.cur_window_state = WINDOW_STATE_EDIT_TASK_PRIORITY;
                window_update(main_task_list, main_menu_state);
                tasks_sort(main_task_list, main_menu_state.sort_type);
                main_menu_state.cur_window_state = WINDOW_STATE_TASK_DETAILS;
            } else if (cur_key == 'l') {
                // Edit task deadline
                main_menu_state.cur_window_state = WINDOW_STATE_EDIT_TASK_DEADLINE;
                window_update(main_task_list, main_menu_state);
                tasks_sort(main_task_list, main_menu_state.sort_type);
                main_menu_state.cur_window_state = WINDOW_STATE_TASK_DETAILS;
            }
        } 

        delay(10);
    }

    quit();
}