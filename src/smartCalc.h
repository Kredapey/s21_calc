#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack_tag {
  char* data;
  size_t size;
  size_t top;
} Stack_t;

Stack_t* create_stack();
void delete_stack(Stack_t** src);
void resize(Stack_t* src);
void push(Stack_t* src, char value);
char pop(Stack_t* src);
char peek(Stack_t* src);
double main_func(char* input, char* str_x);
int is_func(char* input, Stack_t* stack);
double res_calc(char* input, int input_length);
int validator(char* input);
char* close_bracket_parse(Stack_t* stack, int* output_counter);
char* pop_all_elem(Stack_t* stack, int* output_counter);
char* parse_operators(char* input, Stack_t* stack, int* output_counter,
                      char prev, int* unary_counter, int* counter_input);
char* parse_number(char* input, int* dot_counter, char* temp_str_x,
                   int* output_counter, int* counter_input);
void funcs_parse_3_char(Stack_t* stack, char** arr, int* count, char* func);
void funcs_parse_2_char(Stack_t* stack, char** arr, int* count, char* func);
void funcs_parse_4_char(Stack_t* stack, char** arr, int* count, char* func);
char* convert_x(char* temp_str_x, int* output_counter);
char* parse_func(Stack_t* stack, int* output_counter);
void funcs_lexem_calc(int* i, int counter_nums, char* input, double* arr,
                      double a, double b, double* res);
void opers_lexem_calc(double a, double b, double* arr, int* counter_nums,
                      double* res, int i, char* input);
void annuitent_credit_calc(double full_sum, int time, double perc,
                           double* month_payment, double* over_pay,
                           double* all_payment);
void different_credit_calc(double full_sum, int time, double perc,
                           double* first_month_payment,
                           double* last_month_payment, double* over_pay,
                           double* all_payment);

#endif  // SMART_CALC_H
