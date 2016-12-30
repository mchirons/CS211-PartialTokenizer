/*
 * tokenizer.c
 * 
 * Mark Hirons  mch165  Feb.12, 2016   Computer Architecture   Russell
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/*
 * Defines the states used in the finite state machine (fsm) that occurs
   in the TKGetNextToken function. 
 */

enum t_state {
		t_state0, 		
		t_state1, 		
		t_state2, 		
		t_state3,		 
		t_state4,	
		t_state5,
		t_state6,
		t_state7,
		t_state8,
		t_state9,
		t_state10,
		t_state11,
		t_state_err,		
		t_state_w,  	
		t_state_mal,		
		t_state_init		
};


/*
 * Tokenizer type. input holds a pointer 
 */

struct TokenizerT_ {
	char *input; 			//pointer to copy of cmd line args
	int arglength;			//length of cmd line args
	int index;			//tracks index of input iterated by TKGetNextToken
	enum t_state type;		//holds state of current valid token
};


typedef struct TokenizerT_ TokenizerT;


/*
 * isoctaldigit returns nonzero value if c is an octal digit, returns 0 if it is not.
 */
 
int isoctaldigit(char c){
	return (isdigit(c) && ((c -'0') < 8));
}


/*
 * returns ishexdigit returns nonzero value if c is a hex digit, returns 0 if it is not.
 */
 
int ishexdigit(char c){
	return (isdigit(c) || ((c >= 'a' && c<= 'f') || (c >= 'A' && c <= 'F')));  
}


/*
 * findstate returns the state of fsm for first character in input.
 */

enum t_state findstate(char c){
	enum t_state state;
	if (c == '0'){
		state = t_state0;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else if (isdigit(c)){
		state = t_state6;
	}
	else{
		state = t_state_mal;
	}
	return state;
}


/*
 * t_state0fnc returns the state of fsm currently in state 0 after current character is processed.
 */ 

enum t_state t_state0fnc(char c){			
	
	enum t_state state;
	if (isoctaldigit(c)){
		state = t_state1;
	}
	else if (c == 'x' || c == 'X'){
		state = t_state2;
	}
	else if (c == '.'){
		state = t_state4;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else {
		state = t_state_err;
	}
	return state;
}


/*
 * t_state1fnc returns the state of fsm currently in state 1 after current character is processed.
 */

enum t_state t_state1fnc(char c){			
	
	enum t_state state;
	if (isoctaldigit(c)) {
		state =  t_state1;
	}
	else if(isspace(c)){
		state = t_state_w;
	} 
	else {
		state = t_state_err;
	}
	return state;
}


/*
 * t_state2fnc returns the state of fsm currently in state 2 after current character is processed.
 */

enum t_state t_state2fnc(char c){			

	enum t_state state;
	if (ishexdigit(c)){ 
		state = t_state3;
	}
	else{
		state = t_state_mal;
	}
	return state;
}


/*
 * t_state3fnc returns the state of fsm currently in state 3 after current character is processed.
 */

enum t_state t_state3fnc(char c){			

	enum t_state state;
	if (ishexdigit(c)){  
		state = t_state3;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else{
		state = t_state_err;
	}
	return state;
}

/*
 * t_state4fnc returns the state of fsm currently in state 4 after current character is processed.
 */

enum t_state t_state4fnc(char c){			

	enum t_state state;
	if (isdigit(c)){
		state = t_state5;
	}
	else {
		state = t_state_mal;
	}
	return state;
}


/*
 * t_state5fnc returns the state of fsm currently in state 5 after current character is processed.
 */

enum t_state t_state5fnc(char c){			

	enum t_state state;
	if (c == 'e' || c == 'E'){
		state = t_state9;
	}
	else if(isdigit(c)){
		state = t_state5;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else {
		state = t_state_err;
	}
	return state;
}


/*
 * t_state6fnc returns the state of fsm currently in state 6 after current character is processed.
 */

enum t_state t_state6fnc(char c){			

	enum t_state state;
	if (isdigit(c)){
		state = t_state6;
	}
	else if (c == '.'){
		state = t_state7;
	}
	else if (c == 'e' || c == 'E'){
		state = t_state9;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else {
		state = t_state_err;
	}
	return state;
}


/*
 * t_state7fnc returns the state of fsm currently in state 7 after current character is processed.
 */

enum t_state t_state7fnc(char c){		

	enum t_state state;
	if (isdigit(c)){
		state = t_state8;
	}
	else {
		state = t_state_mal;
	}
	return state;
}


/*
 * t_state8fnc returns the state of fsm currently in state 8 after current character is processed.
 */

enum t_state t_state8fnc(char c){			

	enum t_state state;
	if (isdigit(c)){
		state = t_state8;
	}
	else if (c == 'e' || c == 'E'){
		state = t_state9;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else{
		state = t_state_err;
	}
	return state;
}


/*
 * t_state9fnc returns the state of fsm currently in state 9 after current character is processed.
 */

enum t_state t_state9fnc(char c){		

	enum t_state state;
	if (c == '+' || c == '-'){
		state = t_state10;
	}
	else if (isdigit(c)){
		state = t_state11;
	}
	else{
		state = t_state_mal;
	}
	return state;
}


/*
 * t_state10fnc returns the state of fsm currently in state 10 after current character is processed.
 */

enum t_state t_state10fnc(char c){			

	enum t_state state;
	if (isdigit(c)){
		state = t_state11;
	}
	else {
		state = t_state_mal;
	}
	return state;
}


/*
 * t_state11fnc returns the state of fsm currently in state 11 after current character is processed.
 */

enum t_state t_state11fnc(char c){			

	enum t_state state;
	if (isdigit(c)){
		state = t_state11;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else {
		state = t_state_err;
	}
	return state;
}


/*
 * t_statewfnc returns the state of fsm currently in state w after current character is processed.
 */

enum t_state t_statewfnc(char c){			
	
	enum t_state state;
	if (c == '0'){
		state = t_state0;
	}
	else if (isdigit(c)){
		state = t_state6;
	}
	else if (isspace(c)){
		state = t_state_w;
	}
	else {
		state = t_state_mal;
	}
	return state;
}


/*
 * isabsorbing returns 1 if state is an absorbing state and returns 0 if not an absorbing state.
 * An absorbing state is one in which the current token is valid.
 */

int isabsorbing(enum t_state state){	
	if (state == t_state0 || state == t_state1 ||
	 state == t_state3 || state == t_state5 || 
	 state == t_state6 || state == t_state8 || 
	 state == t_state11)
	 {
	 	return 1;
	 }
	 else {
	 	return 0;
	}

}


/* 
 * append returns a new char* pointing to a new string with c appended to the end. returns NULL
 * if the realloc fails and frees the original string s.
 */
 
char* append(char* s, char c){
	int len;
	char *stemp;
	
	len = strlen(s);
	stemp = (char*)realloc(s, len + sizeof(char));
	if (stemp == NULL){
		printf("realloc in function:append failed\n");
		free(s);
		return NULL;
	}
	s = stemp;
	stemp = NULL;
	free(stemp);
	s[len] = c;
	s[len + 1] = '\0';
	return s;
	
}

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate copies arguments so that it is not dependent on
 * them staying immutable after returning.  
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 */
 
TokenizerT *TKCreate( char * ts ) {
	
	if (ts == NULL){
		return NULL;
	}
	
	TokenizerT *tk = (TokenizerT*)malloc(sizeof(TokenizerT));
	char *copy;
	copy = (char*)malloc(strlen(ts) + 1);
	
	if (copy == NULL){
		return NULL;
	}
	
	strcpy(copy, ts);
	tk->input = copy; 
	
	tk->index = 0;
	tk->arglength = strlen(tk->input);
	tk->type = t_state_init;
	
  	return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It frees all dynamically
 * allocated memory that is part of the object being destroyed
 */

void TKDestroy( TokenizerT * tk ) {
	free(tk->input);
	free(tk);
}


/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.
 
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * This function implements a finite state machine in the form of a looping
 * switch statement with some special case statements appended. The beginning 
 * state of the fsm is always t_state_init. The next state is determined by
 * findstate. Further states are determined by the state functions defined 
 * above. 
 * 
 * If state becomes t_state_err(prints error message) or t_state_w while a valid
 * token is being processed, the function ends and returns the token.
 * If state becomes t_state_mal(prints error message), there are no valid tokens 
 * in the token stream, or if creation of a token fails, the function returns 0.
 *
 * This function also determines the type of a valid token and updates the 
 * tokenizer type variable to reflect this.
 */

char *TKGetNextToken( TokenizerT * tk ) {
	
	char* token;
	token = (char*)malloc(sizeof(char));
	token[0] = '\0';
	
	enum t_state state;
	enum t_state finalstate;		//stores the state of fsm is in an absorbing state
	state = t_state_init;
	finalstate = state;

	
	while (tk->index < tk->arglength){
		
		switch(state){
			
			case t_state0:
				state = t_state0fnc(tk->input[tk->index]);
				break;
			case t_state1:
				state = t_state1fnc(tk->input[tk->index]);
				break;
			case t_state2:
				state = t_state2fnc(tk->input[tk->index]);
				break;
			case t_state3:
				state = t_state3fnc(tk->input[tk->index]);
				break;
			case t_state4:
				state = t_state4fnc(tk->input[tk->index]);
				break;
			case t_state5:
				state = t_state5fnc(tk->input[tk->index]);
				break;
			case t_state6:
				state = t_state6fnc(tk->input[tk->index]);
				break;
			case t_state7:
				state = t_state7fnc(tk->input[tk->index]);
				break;
			case t_state8:
				state = t_state8fnc(tk->input[tk->index]);
				break;
			case t_state9:
				state = t_state9fnc(tk->input[tk->index]);
				break;
			case t_state10:
				state = t_state10fnc(tk->input[tk->index]);
				break;
			case t_state11:
				state = t_state11fnc(tk->input[tk->index]);
				break;
			case t_state_init:
				state = findstate(tk->input[tk->index]);
				break;
			case t_state_w:
				state = t_statewfnc(tk->input[tk->index]);
				break;
			case t_state_err:
				break;
			case t_state_mal:
				break;
			default:
				break;
		}
		
		if (state == t_state_mal){
			finalstate = state;
			tk->index++;
			free(token);
			printf("error:\t\tmal token\n");
			return 0;
		}
		else if (state == t_state_err){
			printf("error:\t\tbad character [%#02x]\n", tk->input[tk->index]);
			tk->type = finalstate;
			tk->index++;
			if (strlen(token) == 0){return 0;}
			return token;
		}
		else if (state == t_state_w){
			tk->index++;
			if (strlen(token) > 0){
				tk->type = finalstate;
				return token;
			}
		}
		else if (isabsorbing(state)){
			token = append(token, tk->input[tk->index]);
			if (token == NULL){return 0;}
			tk->index++;
			finalstate = state;
			if (tk->index == tk->arglength){ 
				tk->type = finalstate;
				return token;
			}
		}
		else{
			if (tk->index == tk->arglength)
			{
				printf("error:\t\tmal token\n");
				return 0;
			}
			token = append(token, tk->input[tk->index]);
			tk->index++;
			if (token == NULL){return 0;}
		}
	} 
	if (strlen(token) == 0){return 0;};
	return token;
	
}


/*
 * TKGetType returns the type of the token as a string. 
 */

char *TKGetType(TokenizerT *tk) {
	
	enum t_state state = tk->type;

	if (state == t_state0){
		return "zero";
	}
	if (state == t_state1){
		return "octal";
	}
	if (state == t_state3){
		return "hex";
	}
	if (state == t_state5){
		return "float";
	}
	if (state == t_state6){
		return "decimal";
	}
	if (state == t_state8){
		return "float";
	}
	if (state == t_state11){
		return "float";
	}
	else{
		return 0;
	}
}

	

/*
 * main will have a string argument (in argv[1]). The string argument contains 
 * the tokens.main creates a new TokenizerT object using the string argument.
 * Tokens are printed on a new line in the form:
 
 * type		token
 * 
 * After a token has been returned by TKGetNextToken and printed 
 * the token is freed. When all tokens have been printed, the
 * object is destroyed and the program ends.
 * 
 */

int main(int argc, char **argv) {
	TokenizerT *tk = TKCreate(argv[1]);
	
	if (tk == NULL){
		exit(1);
	}
	
	char *nextToken;
	char *type;
	while (tk->index < tk->arglength){
		nextToken = TKGetNextToken(tk);
		type = TKGetType(tk);
		if (nextToken!= NULL){
			printf("%s\t\t%s\n", type, nextToken);
			free(nextToken);
		}
	}
	TKDestroy(tk);
	return 0;
}
