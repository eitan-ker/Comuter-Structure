#include <stdio.h>
#include <stdlib.h>
void deal_with_last_case_when_num_is_positive(FILE *file, int k) {
  int cnt = 0,cntn=0,cntm=0,power_of_two = 1,started_hovering_flag=0,first_assign_to_registerebx=0, first_assign_to_registerecx=0;
  int first_time_to_assign_to_eax=0,first_command_flag = 0,stand_on_first_bit_flag=0, contiue_hovering_flag = 0,first_use_of_eax_flag =0;
  int wheretostartshiftforb=0,wheretostartshiftforc=0,wheretostartshift=0, didsubtractwithecx=0;
  fprintf(file, "kefel: movl %%edi, %%eax\n");
  while (power_of_two<k) {
    if ((k & power_of_two) > 0 && started_hovering_flag == 0) {
      started_hovering_flag = 1;
      cntn = cnt;
      cntm=(cnt-wheretostartshift);
      wheretostartshift=cnt;
    } else if ((k & power_of_two) > 0 && started_hovering_flag == 1) {
      contiue_hovering_flag = 1;
      cntn++;
    } else {
      if (started_hovering_flag == 1 && contiue_hovering_flag == 0) {
        started_hovering_flag=0;
        if (first_time_to_assign_to_eax == 0) {
          first_time_to_assign_to_eax = 1;
          if (cntm != 0) {
            fprintf(file, "shl $%d, %%eax\n", cntm);
          }
        } else {
          if (first_assign_to_registerebx == 0) {
            first_assign_to_registerebx = 1;
            fprintf(file, "movl %%edi, %%ebx\n");
            fprintf(file, "shl $%d, %%ebx\n", wheretostartshift);
          } else {
            fprintf(file, "shl $%d, %%ebx\n", cntm);
          }
          fprintf(file, "leal (%%ebx,%%eax), %%eax\n");
        }
      } else if (started_hovering_flag == 1 && contiue_hovering_flag == 1) {
        started_hovering_flag=0;
        contiue_hovering_flag=0;
        if (first_time_to_assign_to_eax == 0) {
          first_time_to_assign_to_eax = 1;
          if (cntn != 0) {
            fprintf(file, "shl $%d, %%eax\n", cntn + 1);
            if(first_assign_to_registerebx==0) {
              first_assign_to_registerebx=1;
              fprintf(file, "movl %%edi, %%ebx\n");
            }
            if (cntm != 0) {
              fprintf(file, "shl $%d, %%ebx\n", cntm);
            }
            fprintf(file, "sub %%ebx,%%eax\n");
          }
        } else{
          wheretostartshiftforc=(cntm+1+cntn);
          if(first_assign_to_registerebx==0) {
            first_assign_to_registerebx=1;
            fprintf(file, "movl %%edi, %%ebx\n");
          }
            fprintf(file, "movl %%edi, %%ecx\n");
          fprintf(file, "shl $%d, %%ecx\n", cnt);
            fprintf(file, "shl $%d, %%ebx\n", cntm);
            fprintf(file, "sub %%ebx, %%ecx\n");
          fprintf(file, "leal (%%eax, %%ecx), %%eax\n");
        }
      }
    }
    power_of_two*=2;
    cnt++;
  }
  if(started_hovering_flag==1 && contiue_hovering_flag==0) {
      if(first_time_to_assign_to_eax==0) {
        if(first_assign_to_registerebx==0) {
          first_assign_to_registerebx=1;
          fprintf(file, "movl %%edi, %%ebx\n");
        }
        wheretostartshiftforb=wheretostartshift-wheretostartshiftforb;
        fprintf(file, "shl $%d, %%ebx\n", cntm);
        fprintf(file, "shl $%d, %%eax\n", cnt);
        fprintf(file, "sub %%ebx, %%eax\n");
      } else {
        if(first_assign_to_registerebx==0) {
          first_assign_to_registerebx=1;
          fprintf(file, "movl %%edi, %%ebx\n");
        }
        wheretostartshiftforb=wheretostartshift-wheretostartshiftforb;
        fprintf(file, "shl $%d, %%ebx\n", cntm);
        fprintf(file, "leal (%%ebx,%%eax), %%eax\n");
      }
    }else {
    if(first_time_to_assign_to_eax==0) {
      if (first_assign_to_registerebx == 0) {
        first_assign_to_registerebx=1;
        fprintf(file, "movl %%edi, %%ebx\n");
      }
      fprintf(file, "shl $%d, %%ebx\n", cntm);
      fprintf(file, "shl $%d, %%eax\n", cnt);
      fprintf(file, "sub %%ebx, %%eax\n");
    }else {
        fprintf(file, "movl %%edi, %%ecx\n");
      fprintf(file, "shl $%d, %%ecx\n", cnt);
        fprintf(file, "shl $%d, %%ebx\n", cntm);
        fprintf(file, "sub %%ebx, %%ecx\n");
        fprintf(file, "leal (%%eax, %%ecx), %%eax\n");
      }
    }
}

int check_if_condition_three_possible(int k) {
  int power_of_two = 2;
  int cnt=0;
  while (k%power_of_two == 0) {
    power_of_two *= 2;
    cnt++;
  }
  power_of_two /=2;
  k = k / power_of_two;
  if (k%9 == 0) {
    if(k/9 == 1) {
      return 1;
    } else {
      return 0;
    }
  } else if (k%5==0) {
    if(k/5 == 1) {
      return 1;
    } else {
      return 0;
    }
  } else if(k%3==0) {
    if(k/3 == 1) {
      return 1;
    } else {
      return 0;
    }
  }
  return 0;
}
int check_if_num_is_power_of_two(int k) {
  int cnt =0;
  int power_of_two = 2;
  if (k%2 !=0) {
    return 0;
  }
  while (k%power_of_two == 0) {
    power_of_two *= 2;
    cnt++;
  }
  power_of_two /=2;
  k = k / power_of_two;
  if (k==1) {
    return 1;
  } else {
    return 0;
  }
}
void deal_when_num_is_power_of_two(FILE* file, int k) {
  int cnt =0;
  int power_of_two = 2;
  while (k%power_of_two == 0) {
    power_of_two *= 2;
    cnt++;
  }
  power_of_two /=2;
  k = k / power_of_two;
  fprintf(file, "kefel:  sall $%d,%%eax\n",cnt);
}
void deal_with_three(FILE* file, int k) {
  fprintf(file, "kefel: leal (%%edi,%%edi,2), %%eax\n");
}
void deal_with_five(FILE* file, int k) {
  fprintf(file, "kefel: leal (%%edi,%%edi,4), %%eax\n");
}
void deal_with_nine(FILE* file, int k) {
  fprintf(file, "kefel:  leal (%%edi,%%edi,8), %%eax\n");
}
int fill_number_with_power_of_two(FILE* file, int k) {
  int power_of_two = 2;
  int cnt=0;
  while (k%power_of_two == 0) {
    power_of_two *= 2;
    cnt++;
  }
  power_of_two /=2;
  k = k / power_of_two;
  fprintf(file, "sall $%d,%%eax\n",cnt);
  return k;
}
int main(int argc, char *argv[]) {
  int neg_flag = 0, first_command_flag = 0;
  int j = 0;
  int k = atoi(argv[1]);
  FILE* file = fopen("kefel.s","w");
  fprintf(file, ".section .text\n");
  fprintf(file, ".globl  kefel\n");
  if (k==0) {
    fprintf(file, "kefel :  movl $0, %%eax\n");
    fprintf(file, "ret\n");
    fclose(file);
    return 0;
  } else if (k==1) {
    fprintf(file, "kefel:\n");
    fprintf(file, "ret\n");
    fclose(file);
    return 0;
  } else if(k==-1){
    fprintf(file, "kefel:  movl %%edi, %%eax\n");
    fprintf(file, "neg %%eax\n");
    fprintf(file, "ret\n");
    fclose(file);
    return 0;
  }
  if(k==9){
    deal_with_nine(file,k);
  }else if (k==5) {
    deal_with_five(file,k);
  }else if (k==3) {
    deal_with_three(file,k);
  }
  if (k < 0) {
    k = k * -1;
    neg_flag = 1;
  }
  if(check_if_condition_three_possible(k)==1){
    if (k % 2 == 0 && k % 9 == 0) {
      deal_with_nine(file,k);
      k = k/9;
      k = fill_number_with_power_of_two(file, k);
    } else if (k % 2 == 0 &&  k % 5 == 0) {
      deal_with_five(file,k);
      k = k/5;
      k = fill_number_with_power_of_two(file, k);
    } else if (k % 2 == 0 &&  k%3 ==0){
      deal_with_three(file,k);
      k = k/3;
      k = fill_number_with_power_of_two(file, k);
    }
  } else if(check_if_num_is_power_of_two(k) == 1) {
    deal_when_num_is_power_of_two(file,k);
  } else{
    deal_with_last_case_when_num_is_positive(file,k);
  }
  if (neg_flag == 1) {
    fprintf(file, "neg %%eax\n");
  }
  fprintf(file, "ret\n");
  fclose(file);
  return 0;
}
