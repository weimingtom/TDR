#include "reduce.h"
#include <string.h>

void dp_reduce_Import(PARSER *self, ST_Import* current, const char* str)
{
	strncpy(current->package_name, str, MAX_PACKAGE_NAME_LENGTH);
	current->package_name[MAX_PACKAGE_NAME_LENGTH - 1] = 0;
}

void dp_reduce_Typedef(PARSER *self, ST_TYPEDEF *current, ST_SIMPLE_TYPE* type, const tchar *tok_identifier)
{
	current->type = *type;
	strncpy(current->name, tok_identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->name[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
}

void dp_reduce_Const(PARSER *self, ST_Const* current, const ST_SIMPLE_TYPE *type, const tchar *identifier, const ST_VALUE *val)
{
	current->type = *type;

	strncpy(current->identifier, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->identifier[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;	
	current->val = *val;
}

void dp_reduce_Enum(PARSER *self, ST_ENUM *current, const tchar *identifier)
{
	strncpy(current->name, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->name[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
}

void dp_reduce_EnumDef_Value(PARSER *self, ST_ENUM_DEF *current, const tchar *identifier, const ST_VALUE *st_value, const ST_UNIX_COMMENT *comment)
{
	strncpy(current->identifier, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->identifier[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
	current->val = *st_value;
	current->comment = *comment;
}

void dp_reduce_EnumDef(PARSER *self, ST_ENUM_DEF *current, const tchar *identifier, tuint32 index, const ST_UNIX_COMMENT *comment)
{
	strncpy(current->identifier, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->identifier[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
	current->val.type = E_SNVT_INT64;
	current->val.val.i64 = index;
	current->comment = *comment;
}

void dp_reduce_ContainerType_tok_t_vector(PARSER *self, ST_TYPE *current, const ST_SIMPLE_TYPE *simple_type, const tchar *tok_identifier)
{
	current->type = E_SNT_CONTAINER;
	current->ct.ct = E_CT_VECTOR;

	current->ct.vector_type = *simple_type;
	strncpy(current->ct.vector_length, tok_identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->ct.vector_length[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
}

void dp_reduce_SimpleType_tok_t_string(PARSER *self, ST_SIMPLE_TYPE *current, const tchar *tok_identifier)
{
	current->st = E_ST_STRING;

	if(tok_identifier == NULL)
	{
		current->string_length[0] = 0;
	}
	else
	{
		strncpy(current->string_length, tok_identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
		current->string_length[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
	}
}

void dp_reduce_SimpleType_tok_identifier(PARSER *self, ST_SIMPLE_TYPE* current, const tchar *tok_identifier)
{
	current->st = E_ST_REFER;
	strncpy(current->st_refer, tok_identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->st_refer[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
}

void dp_reduce_Type_SimpleType(PARSER *self, ST_TYPE *current, const ST_SIMPLE_TYPE *simple_type)
{
	current->type = E_SNT_SIMPLE;
	current->st = *simple_type;
}

void dp_reduce_Value_tok_identifier(PARSER *self, ST_VALUE* current, const tchar *sn_identifier)
{
	current->type = E_SNVT_IDENTIFIER;
	strncpy(current->val.identifier, sn_identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->val.identifier[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
}

void dp_reduce_Value_tok_char(PARSER *self, ST_VALUE* current, const tchar pn_char)
{
	current->type = E_SNVT_CHAR;
	current->val.c = pn_char;
}

void dp_reduce_Value_tok_int64(PARSER *self, ST_VALUE* current, const tint64 i64)
{
	current->type = E_SNVT_INT64;
	current->val.i64 = i64;
}

void dp_reduce_Value_tok_hex_int64(PARSER *self, ST_VALUE* current, const tint64 i64)
{
	current->type = E_SNVT_HEX_INT64;
	current->val.i64 = i64;
}

void dp_reduce_Value_tok_uint64(PARSER *self, ST_VALUE* current, const tuint64 ui64)
{
	current->type = E_SNVT_UINT64;
	current->val.ui64 = ui64;
}

void dp_reduce_Value_tok_hex_uint64(PARSER *self, ST_VALUE* current, const tuint64 ui64)
{
	current->type = E_SNVT_HEX_UINT64;
	current->val.ui64 = ui64;
}

void dp_reduce_Value_tok_double(PARSER *self, ST_VALUE* current, const double d)
{
	current->type = E_SNVT_DOUBLE;
	current->val.d = d;
}

void dp_reduce_Value_tok_string(PARSER *self, ST_VALUE* current, const char* str)
{
	current->type = E_SNVT_STRING;
	strncpy(current->val.str, str, TDATA_MAX_LENGTH_OF_IDENTIFIER);
}

void dp_reduce_ArgumentList_ArgumentList_tok_identifier(PARSER *self, ST_ARGUMENTS* current, const ST_ARGUMENTS* argument_list, const tchar *identifier)
{
	*current = *argument_list;

	strncpy(current->arg_list[current->arg_list_num], identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->arg_list[current->arg_list_num][TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
	++(current->arg_list_num);
}

void dp_reduce_ArgumentList_tok_identifier(PARSER *self, ST_ARGUMENTS* current, const tchar *identifier)
{
	current->arg_list_num = 0;
	strncpy(current->arg_list[current->arg_list_num], identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->arg_list[current->arg_list_num][TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
	++(current->arg_list_num);
}

void dp_reduce_Value_tok_count(PARSER *self, ST_VALUE *current, const tchar *identifier)
{
	const SYMBOL *symbols = symbols_search(&self->symbols, "", identifier);

	current->type = E_SNVT_UINT64;
	switch(symbols->type)
	{
	case EN_HST_ENUM:		
		current->val.ui64 = symbols->body.symbol_enum.enum_def_list_num;
		break;
	case EN_HST_STRUCT:
		current->val.ui64 = symbols->body.struct_field_list_num;
		break;
	case EN_HST_UNION:
		current->val.ui64 = symbols->body.union_symbol.union_field_list_num;
		break;
	default:
		current->val.ui64 = 0;
		break;
	}
}

void dp_reduce_Union(PARSER *self, ST_UNION *current, const tchar *identifier, const ST_Parameters *parameters)
{
	strncpy(current->name, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->name[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;

	current->parameters = *parameters;
}

void dp_reduce_UnionField(PARSER *self, ST_UNION_FIELD *current, const tchar *key, const ST_SIMPLE_TYPE *simple_type, const tchar *identifier, const ST_UNIX_COMMENT *comment)
{
	strncpy(current->key, key, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->key[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;

	current->simple_type = *simple_type;

	strncpy(current->name, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->name[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;

	current->comment = *comment;
}

void dp_reduce_Field(PARSER *self, ST_FIELD *current, const ST_CONDITION *condition, const ST_TYPE *type
					 , const tchar *identifier, const ST_ARGUMENTS *args, const ST_UNIX_COMMENT *comment)
{
	current->condition = *condition;
	current->type = *type;
	strncpy(current->identifier, identifier, TDATA_MAX_LENGTH_OF_IDENTIFIER);
	current->identifier[TDATA_MAX_LENGTH_OF_IDENTIFIER - 1] = 0;
	current->args = *args;
	current->comment = *comment;
}