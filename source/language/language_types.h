/**
 * Autogenerated by TData Compiler (0.0.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#ifndef _H_LANGUAGE_LANGUAGE_TYPES_H
#define _H_LANGUAGE_LANGUAGE_TYPES_H

#include "platform/tlibc_platform.h"



typedef enum _EN_TD_LANGUAGE_STRING EN_TD_LANGUAGE_STRING;
enum _EN_TD_LANGUAGE_STRING
{
	E_LS_UNKNOW = 0,
	E_LS_IDENTIFIER_NOT_DEFINED = 1,
	E_LS_IDENTIFIER_REDEFINITION = 2,
	E_LS_IDENTIFIER_NOT_TYPE = 3,
	E_LS_IDENTIFIER_NOT_POSITIVE_INTEGER = 4,
	E_LS_IDENTIFIER_NOT_VALUE = 5,
	E_LS_IDENTIFIER_LENGTH_ERROR = 6,
	E_LS_IDENTIFIER_NOT_STRING = 7,
	E_LS_STRING_LENGTH_NOT_DEFINED = 8,
	E_LS_CANNOT_USE_RESERVED_LANGUAGE_KEYWORD = 9,
	E_LS_CANNOT_OPEN_FILE = 10,
	E_LS_SYNTAX_ERROR = 11,
	E_LS_OUT_OF_MEMORY = 12,
	E_LS_CHARACTER_CONSTANT_FORMAT_ERROR = 13,
	E_LS_STRING_CONSTANT_FORMAT_ERROR = 14,
	E_LS_NUMBER_ERROR_RANGE = 15,
	E_LS_CAN_NOT_DEFINE_STRING_LENGTH_HERE = 16,
	E_LS_CONSTANT_TYPES_DO_NOT_MATCH = 17,
	E_LS_CONSTANT_OVER_THE_RANGE = 18,
	E_LS_CONST_TYPE_ERROR = 19,
	E_LS_ENUM_HAVE_EQUAL_ELEMENTS = 20,
	E_LS_TOO_MANY_MEMBERS = 21,
	E_LS_TOO_MANY_PARAMETERS = 22,
	E_LS_TOO_MANY_ARGUMENTS = 23,
	E_LS_NOT_INTEGER_VALUE = 24,
	E_LS_NOT_INTEGER_TYPE = 25,
	E_LS_ARGUMENT_TYPE_MISMATCH = 26,
	E_LS_NOT_ENUM_TYPE = 27,
};

#define TD_LANGUAGE_STRING_NUM 28

#define TD_MAX_LANGUAGE_STRING_LENGTH 1024

typedef struct _ST_TD_LANGUAGE_STRING ST_TD_LANGUAGE_STRING;
struct _ST_TD_LANGUAGE_STRING
{
	EN_TD_LANGUAGE_STRING language_string_number;
	tchar language_string[TD_MAX_LANGUAGE_STRING_LENGTH];
};

typedef struct _ST_TD_LANGUAGE_STRING_LIBRARY ST_TD_LANGUAGE_STRING_LIBRARY;
struct _ST_TD_LANGUAGE_STRING_LIBRARY
{
	tuint16 language_string_list_num;
	ST_TD_LANGUAGE_STRING language_string_list[TD_LANGUAGE_STRING_NUM];
};

#endif //_H_LANGUAGE_LANGUAGE_TYPES_H

