#include<stdio.h>
#include<string.h>

/* 2D array of XM2 instruction strings */
const char XM2[25][5] = {
    "CLC","CLN","CLZ","CLV","SEC","SEN","SEZ","SEV","BEQ","BEZ","BNE","BNZ","BGE","BLT","BC","BNC","BN","RET","PULL","PUSH","JUMP","CLR.B","CLR","CLR.W","CALL"
};
/* Compares current token to table of XM2 instructions and returns index of table location*/
int get_index(char *token)
{
    int count = 0;
        while(count <= 25)
        {
            if(strcmp(token,XM2[count]) == 0)
            {
                break;
            }
            count++;
        }
        return count;
}

/* Checks to see if the first char in token string is a ';' to determine if the line is a comment*/
int check_for_comment(char *token)
{
    int comment_flag = 0;
    if(token[0] == ';')
    {
        comment_flag = 1;

    }
    return comment_flag;
}

/* Switch case to print portions of converted instructions and raise flags to print remaining portions of converted instructions later*/
int instruction_switch_case(int index,int arg_and_label_flag)
{
    int instruction_find_bool = 0;
    switch(index)
    {
        case 0:
            printf("CLRCC C");
            arg_and_label_flag = 1;
            instruction_find_bool = 1;            
        break;

        case 1:
            printf("CLCRR N");
            arg_and_label_flag = 1; 
            instruction_find_bool = 1;          
        break;

        case 2:
            printf("CLCRR Z");
            arg_and_label_flag = 1;   
            instruction_find_bool = 1;         
        break;
        
        case 3:
            printf("CLCRR V");
            arg_and_label_flag = 1;  
            instruction_find_bool = 1;          
        break;

        case 4:
            printf("SETCC C");
            arg_and_label_flag = 1;
            instruction_find_bool = 1;            
        break;

        case 5:
            printf("SETCC N");
            arg_and_label_flag = 1; 
            instruction_find_bool = 1;           
        break;

        case 6:
            printf("SETCC Z");
            arg_and_label_flag = 1; 
            instruction_find_bool = 1;           
        break;

        case 7:
            printf("SETCC V");
            arg_and_label_flag = 1; 
            instruction_find_bool = 1;           
        break;

        case 8:
            printf("CEX EQ, #1,#0 BRA");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;            
        break;

        case 9:
            printf("CEX EQ, #1,#0 BRA");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;           
        break;

        case 10:
            printf("CEX NE, #1,#0 BRA");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;          
        break;

        case 11:
            printf("CEX NE, #1,#0 BRA");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;            
        break;

        case 12:
            printf("CEX GE, #1,#0 BRA ");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;            
        break;

        case 13:
            printf("CEX LT, #1,#0 BRA ");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;            
        break;

        case 14:
            printf("CEX CS, #1,#0 BRA ");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;           
        break;

        case 15:
            printf("CEX CC, #1,#0 BRA ");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;           
        break;        

        case 16:
            printf("CEX MI, #1,#0 BRA ");
            arg_and_label_flag = 2;
            instruction_find_bool = 1;
        break;

        case 17:
            printf("MOV R5,R7 ");
            arg_and_label_flag = 1;
            instruction_find_bool = 1;
        break;

        case 18:
            printf("LD r6+, ");
            arg_and_label_flag = 4;
            instruction_find_bool = 1;
        break;

        case 19:
            printf("ST ");
            arg_and_label_flag = 5;
            instruction_find_bool = 1;
        break;       

        case 20:
            printf("MOV ");
            arg_and_label_flag = 6;
            instruction_find_bool = 1;
        break;

        case 21:
            printf("MOVL #0, ");
            arg_and_label_flag = 7;
            instruction_find_bool = 1;
        break;

        case 22:
            printf("MOVLZ #0, ");
            arg_and_label_flag = 7;
            instruction_find_bool = 1;
        break;

        case 23:
            printf("MOVLZ #0, ");
            arg_and_label_flag = 7;
            instruction_find_bool = 1;
        break;
        
        case 24:
            printf("BL ");
            arg_and_label_flag = 3;
            instruction_find_bool = 1;
        break;

        default: 
        arg_and_label_flag = 0;
        instruction_find_bool = 0;   
    }
    return instruction_find_bool;
}

/* Used to check if a token is SPL and convert it */
int check_for_SPL(char *token){
    int instruction_find_bool = 0;
    if((token[0] == 'S') && (token[1] == 'P') && (token[2] == 'L')){
        printf("SPL%c",token[3]);
        instruction_find_bool = 1;
    }
    return instruction_find_bool;
}

/* Used for printing remaining portions of converted instructions */
void operand_switch_case(int arg_and_label_flag,char *token){
    switch(arg_and_label_flag)
    {
        case 2:
            printf("%s",token);  
            arg_and_label_flag = 0;         
        break;
            
        case 4:
            printf("%s",token);
            arg_and_label_flag = 0; 
        break;

        case 5:
            printf("%s, -R6",token);
            arg_and_label_flag = 0; 
        break;

        case 6:
            printf("%s, R7",token);
            arg_and_label_flag = 0; 
        break;

        case 7:
            printf("%s",token);
            arg_and_label_flag = 0; 
        break;
    }
}



int main()
{
    int instruction_find_bool = 0;
    char *token;
    char singleline[150];
    int index;
    FILE * fptr;
    int arg_and_label_flag = 0;
    int comment_flag = 0;
    fptr = fopen("input.txt","r");
    /* Loop to get new line*/
    while(fgets(singleline,150,fptr) != NULL)
    {
        token = strtok(singleline, " \t");
        comment_flag = 0;
        /*Loop to get new token*/
        while(token != NULL)
        {
            
            instruction_find_bool = 0;
            index = get_index(token);
            /* Prints all elements directly after a comment is detected*/
           
            
            if(comment_flag == 1)
            {
                printf("%s ",token);       
            }else if((arg_and_label_flag != 0) || (arg_and_label_flag != 1) || (arg_and_label_flag != 3)) {
                operand_switch_case(arg_and_label_flag,token);
            }else
            {

                index = get_index(token);
                /*instruction_find_bool is 0 if token doesn't match with item in MX2 instruction table*/
                instruction_find_bool = instruction_switch_case(index,arg_and_label_flag);
                if(instruction_find_bool == 0)
                {
                    instruction_find_bool = check_for_SPL(token);
                }
                /* instruction_find_bool would be 0 if instruction is not an SPL instruction*/
                else if(instruction_find_bool == 0)
                { 
                    comment_flag = check_for_comment(token);
                }
                else
                {
                    printf("%s ",token);
                }
            }
            token = strtok(NULL, " ");
        }
        
        
    }
    return 0;
}

