#include <stdio.h>
#include "platform/tlibc_platform.h"

#include "protocol/tlibc_xml_reader.h"
#include "protocol/tlibc_xml_writer.h"

#include "definition/definition_types.h"
#include "definition/definition_writer.h"
#include "definition/definition_reader.h"


#include <string.h>

#define MAX_BUFF_SIZE 1024

static ST_DEFINITION g_definition;
static ST_Parameters g_parameters ;
void init()
{
	g_definition.type = E_DT_CONST;
	snprintf(g_definition.definition.de_const.identifier, MAX_IDENTIFIER_LENGTH, "hello");
	g_definition.definition.de_const.identifier[MAX_IDENTIFIER_LENGTH - 1] = 0;

	g_definition.definition.de_const.type.type = E_SNT_SIMPLE;
	g_definition.definition.de_const.type.st = E_ST_INT32;

	g_definition.definition.de_const.val.type = E_SNVT_INT64;
	g_definition.definition.de_const.val.val.i64 = 123321;



	g_parameters.par_list_num = 2;
	g_parameters.par_list[0].type.type = E_SNT_SIMPLE;
	g_parameters.par_list[0].type.st = E_ST_UINT32;
	snprintf(g_parameters.par_list[0].identifier, MAX_IDENTIFIER_LENGTH, "boy");

	g_parameters.par_list[1].type.type = E_SNT_CONTAINER;
	g_parameters.par_list[1].type.ct = E_CT_STRING;
	snprintf(g_parameters.par_list[1].identifier, MAX_IDENTIFIER_LENGTH, "girl");

}

TLIBC_XML_READER xml_reader;
void test_xml()
{
	TLIBC_XML_WRITER xml_writer;	
	int ret;

	xml_writer_init(&xml_writer, "t.xml");
	ret = write_ST_DEFINITION(&xml_writer.super, &g_definition);
	xml_writer_fini(&xml_writer);

	memset(&g_definition, 0, sizeof(ST_DEFINITION));

	xml_reader_init(&xml_reader, "t.xml");
	ret = read_ST_DEFINITION(&xml_reader.super, &g_definition);
}
void test_xml2()
{
	TLIBC_XML_WRITER xml_writer;	
	int ret;

	xml_writer_init(&xml_writer, "test_xml2.xml");
	ret = write_ST_Parameters(&xml_writer.super, &g_parameters);
	xml_writer_fini(&xml_writer);

	memset(&g_parameters, 0, sizeof(ST_Parameters));

	xml_reader_init(&xml_reader, "test_xml2.xml");
	ret = read_ST_Parameters(&xml_reader.super, &g_parameters);
}
void test_compact()
{
	
	
}

int main()
{
	init();

	test_xml();

	test_xml2();

	test_compact();

	return 0;
}