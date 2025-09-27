// brackets_checker.c
// Checks brackets per spec: ignore non-bracket chars.
// On first error, prints 0-based index per rules.
// Otherwise prints "OK".
#include <stdio.h>

#define MAX 100000

int main(void){
    char s[MAX];
    if(!fgets(s, sizeof s, stdin)) {
        return 0;
    }
    // Stack for openers and their indices
    char st_char[MAX];
    int  st_idx [MAX];
    int top = -1;

    for(int i = 0; s[i] && s[i] != '\n'; ++i){
        char c = s[i];
        if(c == '(' || c == '[' || c == '{'){
            st_char[++top] = c;
            st_idx [top]   = i;
        } else if(c == ')' || c == ']' || c == '}'){
            if(top < 0){
                printf("ERROR %d\n", i);
                return 0;
            }
            char t = st_char[top--];
            if( (c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{') ){
                printf("ERROR %d\n", i);
                return 0;
            }
        } // else: ignore other chars
    }
    if(top >= 0){
        // Unmatched opener remains; per spec print index of the FIRST unmatched opener
        // i.e., the bottom-most element in the stack.
        printf("ERROR %d\n", st_idx[0]);
        return 0;
    }
    printf("OK\n");
    return 0;
}
