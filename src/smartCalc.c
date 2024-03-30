#include "smartCalc.h"

// int main() {
//   double res =
//   main_func("(1+2)*4*cos(x*7-2)+sin(2*x)-sqrt(x^log(5-x))+ln(55/(2+x))",
//   "1"); printf("res = %f\n", res);
// }

Stack_t *create_stack() {
  Stack_t *res = calloc(1, sizeof(Stack_t));
  if (res != NULL) {
    res->size = 1;
    res->data = calloc(res->size, sizeof(char));
    if (res->data != NULL) {
      res->top = 0;
    } else {
      res->size = 0;
      res->top = 0;
      free(res);
    }
  }
  return res;
}

void delete_stack(Stack_t **src) {
  free((*src)->data);
  free(*src);
  *src = NULL;
}

void resize(Stack_t *src) {
  src->size += 1;
  src->data = realloc(src->data, src->size * sizeof(char));
  if (src->data == NULL) {
    exit(-100);
  }
}

void push(Stack_t *src, char value) {
  if (src->top >= src->size) {
    resize(src);
  }
  src->data[src->top] = value;
  src->top++;
}

char pop(Stack_t *src) {
  if (src->top == 0) {
    exit(-101);
  }
  src->top--;
  return src->data[src->top];
}

char peek(Stack_t *src) {
  if (src->top <= 0) {
    exit(-101);
  }
  return src->data[src->top - 1];
}

double main_func(char *input, char *str_x) {
  char temp_str_x[100] = "\0", prev = '\0', output[512] = "\0";
  strcpy(temp_str_x, str_x);
  double final_result = 0;
  int dot_counter = 0, steps = 0, output_counter = 0, unary_counter = 0,
      counter_input = 0;
  ;
  Stack_t *stack = create_stack();
  for (; *input != '\0'; input++) {
    dot_counter = 0;
    if ((*input >= '0' && *input <= '9') || *input == 'x') {
      char *parse_number_temp = parse_number(input, &dot_counter, temp_str_x,
                                             &output_counter, &counter_input);
      if (parse_number_temp != NULL) {
        strcat(output, parse_number_temp);
        free(parse_number_temp);
      }
      for (int i = 0; i < counter_input; i++) {
        input += 1;
      }
      if (unary_counter == 1) {
        unary_counter = 0;
        output[output_counter++] = prev;
      }
    } else if (*input == '(') {
      push(stack, *input);
    } else if (*input == ',') {
      while (peek(stack) != '(') {
        output[output_counter++] = ' ';
        output[output_counter++] = pop(stack);
      }
    } else if (*input == '+' || *input == '-' || *input == '*' ||
               *input == '/' || *input == '^' ||
               (*input == 'm' && *(input + 1) == 'o' && *(input + 2) == 'd')) {
      counter_input = 0;
      char *temp_parse_opers = parse_operators(
          input, stack, &output_counter, prev, &unary_counter, &counter_input);
      if (temp_parse_opers != NULL) {
        strcat(output, temp_parse_opers);
        free(temp_parse_opers);
      }
      for (int i = 0; i < counter_input; i++) {
        input++;
      }
    } else if (*input == ')') {
      char *cl_br_parse_temp = close_bracket_parse(stack, &output_counter);
      if (cl_br_parse_temp != NULL) {
        strcat(output, cl_br_parse_temp);
        free(cl_br_parse_temp);
      }
    } else {
      steps = is_func(input, stack);
      if (steps > 0) {
        for (int i = 0; i < steps; i++) {
          input++;
        }
      }
    }
    if (*input != ' ') {
      prev = *input;
    }
  }
  char *temp_pop_elems = pop_all_elem(stack, &output_counter);
  if (temp_pop_elems != NULL) {
    strcat(output, temp_pop_elems);
    free(temp_pop_elems);
  }
  final_result = res_calc(output, output_counter);
  delete_stack(&stack);
  return final_result;
}

int is_func(char *input, Stack_t *stack) {
  int result = 0;
  if (*input == 'c' && *(input + 1) == 'o' && *(input + 2) == 's') {
    push(stack, 'c');
    result = 2;
  } else if (*input == 's' && *(input + 1) == 'i' && *(input + 2) == 'n') {
    push(stack, 'i');
    push(stack, 's');
    result = 2;
  } else if (*input == 't' && *(input + 1) == 'a' && *(input + 2) == 'n') {
    push(stack, 't');
  } else if (*input == 'a' && *(input + 1) == 'c' && *(input + 2) == 'o' &&
             *(input + 3) == 's') {
    push(stack, 'c');
    push(stack, 'a');
    result = 2;
  } else if (*input == 'a' && *(input + 1) == 's' && *(input + 2) == 'i' &&
             *(input + 3) == 'n') {
    push(stack, 's');
    push(stack, 'a');
    result = 3;
  } else if (*input == 'a' && *(input + 1) == 't' && *(input + 2) == 'a' &&
             *(input + 3) == 'n') {
    push(stack, 't');
    push(stack, 'a');
    result = 3;
  } else if (*input == 's' && *(input + 1) == 'q' && *(input + 2) == 'r' &&
             *(input + 3) == 't') {
    push(stack, 'q');
    push(stack, 's');
    result = 3;
  } else if (*input == 'l' && *(input + 1) == 'n') {
    push(stack, 'n');
    push(stack, 'l');
    result = 1;
  } else if (*input == 'l' && *(input + 1) == 'o' && *(input + 2) == 'g') {
    push(stack, 'g');
    push(stack, 'l');
    result = 2;
  }
  return result;
}

double res_calc(char *input, int input_length) {
  double a = 0, b = 0, res = 0, arr[256] = {0};
  char sign = 0, number[256] = "\0";
  int counter_nums = 0, number_counter = 0, unaryCounter = 0;
  for (int i = 0; i < input_length; i++) {
    unaryCounter = 0;
    for (int i = 0; i <= number_counter; i++) {
      number[i] = '\0';
    }
    number_counter = 0;
    if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
      while ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
        if ((input[i + 1] == '-' || input[i + 1] == '+') && i < 255) {
          sign = input[i + 1];
          unaryCounter = 1;
          number[number_counter++] = input[i];
          input[i + 1] = ' ';
          i++;
        } else {
          number[number_counter++] = input[i];
          i++;
        }
      }
      if (unaryCounter == 1) {
        if (sign == '-') {
          arr[counter_nums] = (-1) * atof(number);
        } else if (sign == '+') {
          if (atof(number) < 0) {
            arr[counter_nums] = atof(number) * (-1);
          } else {
            arr[counter_nums] = atof(number);
          }
        }
      } else {
        arr[counter_nums] = atof(number);
      }
      counter_nums++;
    }
    if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
        input[i] == '/' || input[i] == '^') {
      opers_lexem_calc(a, b, arr, &counter_nums, &res, i, input);
      arr[counter_nums - 1] = res;
    }
    funcs_lexem_calc(&i, counter_nums, input, arr, a, b, &res);
  }
  for (int i = 1; i < counter_nums; i++) {
    arr[i] = 0;
  }
  return arr[0];
}

void annuitent_credit_calc(double full_sum, int time, double perc,
                           double *month_payment, double *over_pay,
                           double *all_payment) {
  int month = time * 12;
  double month_perc = perc / (100 * 12);
  *month_payment = full_sum * month_perc / (1 - pow((1 + month_perc), -month));
  *all_payment = *month_payment * month;
  *over_pay = *all_payment - full_sum;
}

void different_credit_calc(double full_sum, int time, double perc,
                           double *first_month_payment,
                           double *last_month_payment, double *over_pay,
                           double *all_payment) {
  double start_full_sum = full_sum;
  int month = time * 12;
  double current_mon_pay = 0;
  double month_perc = perc / (100 * 12);
  *all_payment = 0;
  for (int i = 1; i <= month; i++) {
    current_mon_pay = full_sum / month +
                      (full_sum - (i - 1) * (full_sum / month)) * month_perc;
    if (i == 1) {
      *first_month_payment = current_mon_pay;
    } else if (i == month) {
      *last_month_payment = current_mon_pay;
    }
    *all_payment += current_mon_pay;
  }
  *over_pay = *all_payment - start_full_sum;
}

void funcs_lexem_calc(int *i, int counter_nums, char *input, double *arr,
                      double a, double b, double *res) {
  if (input[*i] == 'c' && input[*i + 1] == 'o' && input[*i + 2] == 's') {
    *i += 2;
    arr[counter_nums - 1] = cos(arr[counter_nums - 1]);
  } else if (input[*i] == 's' && input[*i + 1] == 'i' && input[*i + 2] == 'n') {
    *i += 2;
    arr[counter_nums - 1] = sin(arr[counter_nums - 1]);
  } else if (input[*i] == 't' && input[*i + 1] == 'a' && input[*i + 2] == 'n') {
    *i += 2;
    arr[counter_nums - 1] = tan(arr[counter_nums - 1]);
  } else if (input[*i] == 'a' && input[*i + 1] == 'c' && input[*i + 2] == 'o' &&
             input[*i + 3] == 's') {
    *i += 3;
    arr[counter_nums - 1] = acos(arr[counter_nums - 1]);
  } else if (input[*i] == 'a' && input[*i + 1] == 's' && input[*i + 2] == 'i' &&
             input[*i + 3] == 'n') {
    *i += 3;
    arr[counter_nums - 1] = asin(arr[counter_nums - 1]);
  } else if (input[*i] == 'a' && input[*i + 1] == 't' && input[*i + 2] == 'a' &&
             input[*i + 3] == 'n') {
    *i += 3;
    arr[counter_nums - 1] = atan(arr[counter_nums - 1]);
  } else if (input[*i] == 's' && input[*i + 1] == 'q' && input[*i + 2] == 'r' &&
             input[*i + 3] == 't') {
    *i += 3;
    arr[counter_nums - 1] = sqrt(arr[counter_nums - 1]);
  } else if (input[*i] == 'l' && input[*i + 1] == 'o' && input[*i + 2] == 'g') {
    *i += 2;
    arr[counter_nums - 1] = log10(arr[counter_nums - 1]);
  } else if (input[*i] == 'm' && input[*i + 1] == 'o' && input[*i + 2] == 'd') {
    *i += 2;
    a = arr[counter_nums - 2];
    b = arr[counter_nums - 1];
    *res = fmod(a, b);
    counter_nums -= 2;
    arr[counter_nums] = *res;
    counter_nums++;
  } else if (input[*i] == 'l' && input[*i + 1] == 'n') {
    *i += 1;
    arr[counter_nums - 1] = log(arr[counter_nums - 1]);
  }
}

void opers_lexem_calc(double a, double b, double *arr, int *counter_nums,
                      double *res, int i, char *input) {
  a = arr[*counter_nums - 2];
  b = arr[*counter_nums - 1];
  if (input[i] == '+') {
    *res = a + b;
  } else if (input[i] == '-') {
    *res = a - b;
  } else if (input[i] == '*') {
    *res = a * b;
  } else if (input[i] == '/') {
    *res = a / b;
  } else if (input[i] == '^') {
    *res = pow(a, b);
  }
  *counter_nums -= 1;
}

char *parse_func(Stack_t *stack, int *output_counter) {
  char *arr = calloc(511, sizeof(char));
  int count = 0;
  if (arr != NULL) {
    if (peek(stack) == 'c') {
      funcs_parse_3_char(stack, &arr, &count, "cos");
    } else if (peek(stack) == 's') {
      pop(stack);
      if (peek(stack) == 'i') {
        funcs_parse_3_char(stack, &arr, &count, "sin");
      } else if (peek(stack) == 'q') {
        funcs_parse_4_char(stack, &arr, &count, "sqrt");
      }
    } else if (peek(stack) == 't') {
      funcs_parse_3_char(stack, &arr, &count, "tan");
    } else if (peek(stack) == 'a') {
      pop(stack);
      if (peek(stack) == 'c') {
        funcs_parse_4_char(stack, &arr, &count, "acos");
      } else if (peek(stack) == 's') {
        funcs_parse_4_char(stack, &arr, &count, "asin");
      } else if (peek(stack) == 't') {
        funcs_parse_4_char(stack, &arr, &count, "atan");
      }
    } else if (peek(stack) == 'l') {
      pop(stack);
      if (peek(stack) == 'n') {
        funcs_parse_2_char(stack, &arr, &count, "ln");
      } else if (peek(stack) == 'g') {
        funcs_parse_3_char(stack, &arr, &count, "log");
      }
    }
  }
  *output_counter += count;
  return arr;
}

void funcs_parse_3_char(Stack_t *stack, char **arr, int *count, char *func) {
  pop(stack);
  *arr[*count] = ' ';
  *count += 1;
  strcat(*arr, func);
  *count += 3;
}

void funcs_parse_4_char(Stack_t *stack, char **arr, int *count, char *func) {
  pop(stack);
  *arr[*count] = ' ';
  *count += 1;
  strcat(*arr, func);
  *count += 4;
}

void funcs_parse_2_char(Stack_t *stack, char **arr, int *count, char *func) {
  pop(stack);
  *arr[*count] = ' ';
  *count += 1;
  strcat(*arr, func);
  *count += 2;
}

char *convert_x(char *temp_str_x, int *output_counter) {
  char *res = calloc(511, sizeof(char *));
  if (res != NULL) {
    size_t len_str = strlen(temp_str_x);
    if (temp_str_x[0] == '-') {
      char temp = temp_str_x[0];
      for (int i = 0; i < (int)len_str - 1; i++) {
        temp_str_x[i] = temp_str_x[i + 1];
      }
      temp_str_x[len_str - 1] = temp;
    }
    strcpy(res, temp_str_x);
    *output_counter += strlen(temp_str_x);
  }
  return res;
}

char *parse_number(char *input, int *dot_counter, char *temp_str_x,
                   int *output_counter, int *counter_input) {
  char *res = calloc(511, sizeof(char));
  int count = 0, temp_output_counter = 0;
  if (res != NULL) {
    while ((*input >= '0' && *input <= '9') || (*input == '.') ||
           (*input == 'x')) {
      if (*input == '.' && *dot_counter == 0) {
        res[count++] = *input;
        *output_counter += 1;
        *dot_counter += 1;
      } else if (*input == '.' && dot_counter != 0) {
        break;
      } else {
        if (*input != 'x') {
          res[count++] = *input;
          *output_counter += 1;
        }
      }
      if (*input == 'x') {
        temp_output_counter = *output_counter;
        char *temp = convert_x(temp_str_x, output_counter);
        count += *output_counter - temp_output_counter;
        if (temp != NULL) {
          strcat(res, temp);
          free(temp);
        }
      }
      if (*(input + 1) == '.') {
        input += 1;
        *counter_input += 1;
      } else if (*(input + 1) >= '0' && *(input + 1) <= '9') {
        input += 1;
        *counter_input += 1;
      } else {
        break;
      }
    }
  }
  return res;
}

char *parse_operators(char *input, Stack_t *stack, int *output_counter,
                      char prev, int *unary_counter, int *counter_input) {
  char *res = calloc(511, sizeof(char));
  int count = 0;
  if (res != NULL) {
    if (*input == '^') {
      push(stack, *input);
    } else if (*input == '*' || *input == '/' ||
               (*input == 'm' && *(input + 1) == 'o' && *(input + 2) == 'd')) {
      if (stack->top > 0) {
        if (peek(stack) == '*' || peek(stack) == '/' || peek(stack) == '^' ||
            peek(stack) == 'm') {
          res[count++] = ' ';
          *output_counter += 1;
          if (peek(stack) != 'm') {
            res[count++] = pop(stack);
            *output_counter += 1;
          } else {
            strcat(res, "mod");
            pop(stack);
          }
        }
      }
      push(stack, *input);
      if (*input == 'm') {
        for (int i = 0; i < 1; i++) {
          input++;
          *counter_input += 1;
        }
      }
    } else if (*input == '+' || *input == '-') {
      if (prev == ')' || (prev >= '0' && prev <= '9') || prev == 'x') {
        if (stack->top > 0) {
          if (peek(stack) == '*' || peek(stack) == '/' || peek(stack) == '^' ||
              peek(stack) == '+' || peek(stack) == '-') {
            res[count++] = ' ';
            *output_counter += 1;
            res[count++] = pop(stack);
            *output_counter += 1;
          }
        }
        push(stack, *input);
      } else {
        *unary_counter = 1;
      }
    }
    res[count++] = ' ';
    *output_counter += 1;
  }
  return res;
}

char *close_bracket_parse(Stack_t *stack, int *output_counter) {
  char *res = calloc(511, sizeof(char));
  int count = 0;
  if (res != NULL) {
    while (peek(stack) != '(') {
      res[count++] = ' ';
      *output_counter += 1;
      res[count++] = pop(stack);
      *output_counter += 1;
    }
    pop(stack);
    if (stack->top > 0) {
      char *temp = parse_func(stack, output_counter);
      if (temp != NULL) {
        strcat(res, temp);
        free(temp);
      }
    }
  }
  return res;
}

char *pop_all_elem(Stack_t *stack, int *output_counter) {
  char *res = calloc(511, sizeof(char));
  int count = 0;
  if (res != NULL) {
    while (stack->top > 0) {
      res[count++] = ' ';
      *output_counter += 1;
      if (peek(stack) != 'm') {
        res[count++] = pop(stack);
        *output_counter += 1;
      } else {
        strcat(res, "mod");
        *output_counter += 3;
        pop(stack);
      }
    }
  }
  return res;
}
