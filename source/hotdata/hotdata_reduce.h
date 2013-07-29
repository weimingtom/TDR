#ifndef _H_HOTDATA_REDUCE
#define _H_HOTDATA_REDUCE


#include "hotpot/hp_platform.h"

#include "hotdata_parser.h"

void dp_reduce_Definition_Import(DATA_PARSER *self, const YYLTYPE *yylloc, PN_DEFINITION *pn_current, const PN_IMPORT* pn_import);

void dp_reduce_Definition_Const(DATA_PARSER *self, const YYLTYPE *yylloc, PN_DEFINITION *pn_current, const PN_CONST* pn_const);

void dp_reduce_Import_tok_import(DATA_PARSER *self, const YYLTYPE *yylloc, PN_IMPORT* current, const hpstring *sn_tok_import);

void dp_reduce_ObjectType_tok_identifier(DATA_PARSER *self, const YYLTYPE *yylloc, PN_TYPE* current, const PN_IDENTIFIER *tok_identifier);

void dp_reduce_ContainerType_tok_t_vector(DATA_PARSER *self, const YYLTYPE *yylloc, PN_TYPE *current);

void dp_reduce_ContainerType_tok_t_string(DATA_PARSER *self, const YYLTYPE *yylloc, PN_TYPE *current);

void dp_reduce_SimpleType(DATA_PARSER *self, const YYLTYPE *yylloc, PN_TYPE *current, const SN_SIMPLE_TYPE type);

void dp_reduce_Value_tok_identifier(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const hpbytes sn_identifier);

void dp_reduce_Value_tok_char(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const PN_CHAR pn_char);

void dp_reduce_Value_tok_int64(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const hpint64 i64);

void dp_reduce_Value_tok_hex_int64(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const hpint64 i64);

void dp_reduce_Value_tok_uint64(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const hpuint64 ui64);

void dp_reduce_Value_tok_hex_uint64(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const hpuint64 ui64);

void dp_reduce_Value_tok_double(DATA_PARSER *self, const YYLTYPE *yylloc, PN_VALUE* current, const double d);


void dp_reduce_Const(DATA_PARSER *self, const YYLTYPE *yylloc, PN_CONST* current, const PN_TYPE *type, const PN_IDENTIFIER *identifier, const PN_VALUE *val);

#endif //_H_HOTDATA_REDUCE