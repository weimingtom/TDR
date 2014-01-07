#include "platform/tlibc_platform.h"
#include "lib/tlibc_error_code.h"

#include "error/error_msg.h"
#include "error/error_msg_reader.h"
#include "error/error_code_reader.h"
TD_ERROR_CODE read_TD_ERROR_MSG(TLIBC_ABSTRACT_READER *self, TD_ERROR_MSG *data)
{
    if(read_struct_begin(self, "TLIBC_ERROR_MSG") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_field_begin(self, "error_code") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_TD_ERROR_CODE(self, &data->error_code) != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_field_end(self, "error_code") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_field_begin(self, "error_msg") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_string(self, data->error_msg, TD_MAX_ERROR_MSG_LENGTH) != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_field_end(self, "error_msg") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_struct_end(self, "TLIBC_ERROR_MSG") != E_TLIBC_NOERROR) goto ERROR_RET;
    return E_TLIBC_NOERROR;
ERROR_RET:
    return E_TLIBC_ERROR;
}
TD_ERROR_CODE read_TD_ERROR_MSG_LIBRARY(TLIBC_ABSTRACT_READER *self, TD_ERROR_MSG_LIBRARY *data)
{
    if(read_struct_begin(self, "TLIBC_ERROR_MSG_LIBRARY") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_counter(self, "error_list_num", &data->error_list_num) != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_field_begin(self, "error_list") != E_TLIBC_NOERROR) goto ERROR_RET;
    {
        tuint32 i;
        if(read_vector_begin(self) != E_TLIBC_NOERROR) goto ERROR_RET;
        for(i = 0; i < data->error_list_num; ++i)
        {
            if(read_vector_item_begin(self, i) != E_TLIBC_NOERROR) goto ERROR_RET;
            if(read_TD_ERROR_MSG(self, &data->error_list[i]) != E_TLIBC_NOERROR) goto ERROR_RET;
            if(read_vector_item_end(self, i) != E_TLIBC_NOERROR) goto ERROR_RET;
        }
        if(read_vector_end(self) != E_TLIBC_NOERROR) goto ERROR_RET;
    }
    if(read_field_end(self, "error_list") != E_TLIBC_NOERROR) goto ERROR_RET;
    if(read_struct_end(self, "TLIBC_ERROR_MSG_LIBRARY") != E_TLIBC_NOERROR) goto ERROR_RET;
    return E_TLIBC_NOERROR;
ERROR_RET:
    return E_TLIBC_ERROR;
}
