/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  Scope* scope = symtab->currentScope;  //Scope có trong symtab.h
  Object* obj = NULL;

  while ((scope != NULL) && (obj == NULL)) {
    obj = findObject(scope->objList, name);
    scope = scope->outer;
  }
  if (obj == NULL) 
    obj = findObject(symtab->globalObjectList, name);
  return obj;
}

void checkFreshIdent(char *name) {
  Object* obj = findObject(symtab->currentScope->objList, name);
  if (obj != NULL){
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  }
}

Object* checkDeclaredIdent(char* name) {
  Object* obj = lookupObject(name);

  if(obj == NULL){
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredConstant(char* name) {
  Object* obj = lookupObject(name);

  if(obj == NULL){
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }

  if(obj->kind != OBJ_CONSTANT){
    error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredType(char* name) {
  Object* obj = lookupObject(name);

  if(obj == NULL){
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  }

  if(obj->kind != OBJ_TYPE){
    error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredVariable(char* name) {
  Object* obj = lookupObject(name);
    
    if (obj == NULL) {
        error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
    }
    
    if (obj->kind != OBJ_VARIABLE && obj->kind != OBJ_PARAMETER) {
        error(ERR_INVALID_VARIABLE, currentToken->lineNo, currentToken->colNo);
    }
    
    return obj;
}

Object* checkDeclaredFunction(char* name) {
  Object* obj = lookupObject(name);
    
    if (obj == NULL) {
        error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
    }
    
    if (obj->kind != OBJ_FUNCTION) {
        error(ERR_INVALID_FUNCTION, currentToken->lineNo, currentToken->colNo);
    }
    
    return obj;
}

Object* checkDeclaredProcedure(char* name) {
 Object* obj = lookupObject(name);
    
    if (obj == NULL) {
        error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
    }
    
    if (obj->kind != OBJ_PROCEDURE) {
        error(ERR_INVALID_PROCEDURE, currentToken->lineNo, currentToken->colNo);
    }
    
    return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  Object* obj = lookupObject(name);
    
    if (obj == NULL) {
        error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
    }
    
    // L-value có thể là: biến, tham số, hoặc tên hàm (trong Pascal, hàm có thể gán giá trị)
    if (obj->kind != OBJ_VARIABLE && 
        obj->kind != OBJ_PARAMETER && 
        obj->kind != OBJ_FUNCTION) {
        error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
    }
    
    return obj;
}

