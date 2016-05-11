//----------------------------------------------------------
//
//   SA-MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2009 SA-MP Team
//
//----------------------------------------------------------
//
// This provides an interface to call amx library functions
// within samp-server.
//
//----------------------------------------------------------

#include "plugin.h"

//----------------------------------------------------------

void *pAMXFunctions;

//----------------------------------------------------------

typedef uint16_t *  AMXAPI (*amx_Align16_t)(uint16_t *v);
uint16_t * AMXAPI amx_Align16(uint16_t *v)
{
	amx_Align16_t fn = ((amx_Align16_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align16];
	return fn(v);
}

typedef uint32_t *  AMXAPI (*amx_Align32_t)(uint32_t *v);
uint32_t * AMXAPI amx_Align32(uint32_t *v)
{
	amx_Align32_t fn = ((amx_Align32_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align32];
	return fn(v);
}

#if defined _I64_MAX || defined HAVE_I64
typedef   uint64_t *  AMXAPI (*amx_Align64_t)(uint64_t *v);
  uint64_t * AMXAPI amx_Align64(uint64_t *v)
{
	amx_Align64_t fn = ((amx_Align64_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align64];
	return fn(v);
}

#endif
typedef int  AMXAPI (*amx_Allot_t)(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
int AMXAPI amx_Allot(AMX *amx, int cells, cell *amx_addr, cell **phys_addr)
{
	amx_Allot_t fn = ((amx_Allot_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Allot];
	return fn(amx, cells, amx_addr, phys_addr);
}

typedef int  AMXAPI (*amx_Callback_t)(AMX *amx, cell index, cell *result, cell *params);
int AMXAPI amx_Callback(AMX *amx, cell index, cell *result, cell *params)
{
	amx_Callback_t fn = ((amx_Callback_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Callback];
	return fn(amx, index, result, params);
}

typedef int  AMXAPI (*amx_Cleanup_t)(AMX *amx);
int AMXAPI amx_Cleanup(AMX *amx)
{
	amx_Cleanup_t fn = ((amx_Cleanup_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Cleanup];
	return fn(amx);
}

typedef int  AMXAPI (*amx_Clone_t)(AMX *amxClone, AMX *amxSource, void *data);
int AMXAPI amx_Clone(AMX *amxClone, AMX *amxSource, void *data)
{
	amx_Clone_t fn = ((amx_Clone_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Clone];
	return fn(amxClone, amxSource, data);
}

typedef int  AMXAPI (*amx_Exec_t)(AMX *amx, cell *retval, int index);
int AMXAPI amx_Exec(AMX *amx, cell *retval, int index)
{
	amx_Exec_t fn = ((amx_Exec_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Exec];
	return fn(amx, retval, index);
}

typedef int  AMXAPI (*amx_FindNative_t)(AMX *amx, const char *name, int *index);
int AMXAPI amx_FindNative(AMX *amx, const char *name, int *index)
{
	amx_FindNative_t fn = ((amx_FindNative_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindNative];
	return fn(amx, name, index);
}

typedef int  AMXAPI (*amx_FindPublic_t)(AMX *amx, const char *funcname, int *index);
int AMXAPI amx_FindPublic(AMX *amx, const char *funcname, int *index)
{
	amx_FindPublic_t fn = ((amx_FindPublic_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindPublic];
	return fn(amx, funcname, index);
}

typedef int  AMXAPI (*amx_FindPubVar_t)(AMX *amx, const char *varname, cell *amx_addr);
int AMXAPI amx_FindPubVar(AMX *amx, const char *varname, cell *amx_addr)
{
	amx_FindPubVar_t fn = ((amx_FindPubVar_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindPubVar];
	return fn(amx, varname, amx_addr);
}

typedef int  AMXAPI (*amx_FindTagId_t)(AMX *amx, cell tag_id, char *tagname);
int AMXAPI amx_FindTagId(AMX *amx, cell tag_id, char *tagname)
{
	amx_FindTagId_t fn = ((amx_FindTagId_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindTagId];
	return fn(amx, tag_id, tagname);
}

typedef int  AMXAPI (*amx_Flags_t)(AMX *amx,uint16_t *flags);
int AMXAPI amx_Flags(AMX *amx,uint16_t *flags)
{
	amx_Flags_t fn = ((amx_Flags_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Flags];
	return fn(amx,flags);
}

typedef int  AMXAPI (*amx_GetAddr_t)(AMX *amx,cell amx_addr,cell **phys_addr);
int AMXAPI amx_GetAddr(AMX *amx,cell amx_addr,cell **phys_addr)
{
	amx_GetAddr_t fn = ((amx_GetAddr_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetAddr];
	return fn(amx,amx_addr,phys_addr);
}

typedef int  AMXAPI (*amx_GetNative_t)(AMX *amx, int index, char *funcname);
int AMXAPI amx_GetNative(AMX *amx, int index, char *funcname)
{
	amx_GetNative_t fn = ((amx_GetNative_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetNative];
	return fn(amx, index, funcname);
}

typedef int  AMXAPI (*amx_GetPublic_t)(AMX *amx, int index, char *funcname);
int AMXAPI amx_GetPublic(AMX *amx, int index, char *funcname)
{
	amx_GetPublic_t fn = ((amx_GetPublic_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetPublic];
	return fn(amx, index, funcname);
}

typedef int  AMXAPI (*amx_GetPubVar_t)(AMX *amx, int index, char *varname, cell *amx_addr);
int AMXAPI amx_GetPubVar(AMX *amx, int index, char *varname, cell *amx_addr)
{
	amx_GetPubVar_t fn = ((amx_GetPubVar_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetPubVar];
	return fn(amx, index, varname, amx_addr);
}

typedef int  AMXAPI (*amx_GetString_t)(char *dest,const cell *source, int use_wchar, size_t size);
int AMXAPI amx_GetString(char *dest,const cell *source, int use_wchar, size_t size)
{
	amx_GetString_t fn = ((amx_GetString_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetString];
	return fn(dest,source, use_wchar, size);
}

typedef int  AMXAPI (*amx_GetTag_t)(AMX *amx, int index, char *tagname, cell *tag_id);
int AMXAPI amx_GetTag(AMX *amx, int index, char *tagname, cell *tag_id)
{
	amx_GetTag_t fn = ((amx_GetTag_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetTag];
	return fn(amx, index, tagname, tag_id);
}

typedef int  AMXAPI (*amx_GetUserData_t)(AMX *amx, long tag, void **ptr);
int AMXAPI amx_GetUserData(AMX *amx, long tag, void **ptr)
{
	amx_GetUserData_t fn = ((amx_GetUserData_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetUserData];
	return fn(amx, tag, ptr);
}

typedef int  AMXAPI (*amx_Init_t)(AMX *amx, void *program);
int AMXAPI amx_Init(AMX *amx, void *program)
{
	amx_Init_t fn = ((amx_Init_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Init];
	return fn(amx, program);
}

typedef int  AMXAPI (*amx_InitJIT_t)(AMX *amx, void *reloc_table, void *native_code);
int AMXAPI amx_InitJIT(AMX *amx, void *reloc_table, void *native_code)
{
	amx_InitJIT_t fn = ((amx_InitJIT_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_InitJIT];
	return fn(amx, reloc_table, native_code);
}

typedef int  AMXAPI (*amx_MemInfo_t)(AMX *amx, long *codesize, long *datasize, long *stackheap);
int AMXAPI amx_MemInfo(AMX *amx, long *codesize, long *datasize, long *stackheap)
{
	amx_MemInfo_t fn = ((amx_MemInfo_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_MemInfo];
	return fn(amx, codesize, datasize, stackheap);
}

typedef int  AMXAPI (*amx_NameLength_t)(AMX *amx, int *length);
int AMXAPI amx_NameLength(AMX *amx, int *length)
{
	amx_NameLength_t fn = ((amx_NameLength_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NameLength];
	return fn(amx, length);
}

typedef AMX_NATIVE_INFO *  AMXAPI (*amx_NativeInfo_t)(const char *name, AMX_NATIVE func);
AMX_NATIVE_INFO * AMXAPI amx_NativeInfo(const char *name, AMX_NATIVE func)
{
	amx_NativeInfo_t fn = ((amx_NativeInfo_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NativeInfo];
	return fn(name, func);
}

typedef int  AMXAPI (*amx_NumNatives_t)(AMX *amx, int *number);
int AMXAPI amx_NumNatives(AMX *amx, int *number)
{
	amx_NumNatives_t fn = ((amx_NumNatives_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumNatives];
	return fn(amx, number);
}

typedef int  AMXAPI (*amx_NumPublics_t)(AMX *amx, int *number);
int AMXAPI amx_NumPublics(AMX *amx, int *number)
{
	amx_NumPublics_t fn = ((amx_NumPublics_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumPublics];
	return fn(amx, number);
}

typedef int  AMXAPI (*amx_NumPubVars_t)(AMX *amx, int *number);
int AMXAPI amx_NumPubVars(AMX *amx, int *number)
{
	amx_NumPubVars_t fn = ((amx_NumPubVars_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumPubVars];
	return fn(amx, number);
}

typedef int  AMXAPI (*amx_NumTags_t)(AMX *amx, int *number);
int AMXAPI amx_NumTags(AMX *amx, int *number)
{
	amx_NumTags_t fn = ((amx_NumTags_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumTags];
	return fn(amx, number);
}

typedef int  AMXAPI (*amx_Push_t)(AMX *amx, cell value);
int AMXAPI amx_Push(AMX *amx, cell value)
{
	amx_Push_t fn = ((amx_Push_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Push];
	return fn(amx, value);
}

typedef int  AMXAPI (*amx_PushArray_t)(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells);
int AMXAPI amx_PushArray(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells)
{
	amx_PushArray_t fn = ((amx_PushArray_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_PushArray];
	return fn(amx, amx_addr, phys_addr, array, numcells);
}

typedef int  AMXAPI (*amx_PushString_t)(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar);
int AMXAPI amx_PushString(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar)
{
	amx_PushString_t fn = ((amx_PushString_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_PushString];
	return fn(amx, amx_addr, phys_addr, string, pack, use_wchar);
}

typedef int  AMXAPI (*amx_RaiseError_t)(AMX *amx, int error);
int AMXAPI amx_RaiseError(AMX *amx, int error)
{
	amx_RaiseError_t fn = ((amx_RaiseError_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_RaiseError];
	return fn(amx, error);
}

typedef int  AMXAPI (*amx_Register_t)(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
int AMXAPI amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number)
{
	amx_Register_t fn = ((amx_Register_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Register];
	return fn(amx, nativelist, number);
}

typedef int  AMXAPI (*amx_Release_t)(AMX *amx, cell amx_addr);
int AMXAPI amx_Release(AMX *amx, cell amx_addr)
{
	amx_Release_t fn = ((amx_Release_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Release];
	return fn(amx, amx_addr);
}

typedef int  AMXAPI (*amx_SetCallback_t)(AMX *amx, AMX_CALLBACK callback);
int AMXAPI amx_SetCallback(AMX *amx, AMX_CALLBACK callback)
{
	amx_SetCallback_t fn = ((amx_SetCallback_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetCallback];
	return fn(amx, callback);
}

typedef int  AMXAPI (*amx_SetDebugHook_t)(AMX *amx, AMX_DEBUG debug);
int AMXAPI amx_SetDebugHook(AMX *amx, AMX_DEBUG debug)
{
	amx_SetDebugHook_t fn = ((amx_SetDebugHook_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetDebugHook];
	return fn(amx, debug);
}

typedef int  AMXAPI (*amx_SetString_t)(cell *dest, const char *source, int pack, int use_wchar, size_t size);
int AMXAPI amx_SetString(cell *dest, const char *source, int pack, int use_wchar, size_t size)
{
	amx_SetString_t fn = ((amx_SetString_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetString];
	return fn(dest, source, pack, use_wchar, size);
}

typedef int  AMXAPI (*amx_SetUserData_t)(AMX *amx, long tag, void *ptr);
int AMXAPI amx_SetUserData(AMX *amx, long tag, void *ptr)
{
	amx_SetUserData_t fn = ((amx_SetUserData_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetUserData];
	return fn(amx, tag, ptr);
}

typedef int  AMXAPI (*amx_StrLen_t)(const cell *cstring, int *length);
int AMXAPI amx_StrLen(const cell *cstring, int *length)
{
	amx_StrLen_t fn = ((amx_StrLen_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_StrLen];
	return fn(cstring, length);
}

typedef int  AMXAPI (*amx_UTF8Check_t)(const char *string, int *length);
int AMXAPI amx_UTF8Check(const char *string, int *length)
{
	amx_UTF8Check_t fn = ((amx_UTF8Check_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Check];
	return fn(string, length);
}

typedef int  AMXAPI (*amx_UTF8Get_t)(const char *string, const char **endptr, cell *value);
int AMXAPI amx_UTF8Get(const char *string, const char **endptr, cell *value)
{
	amx_UTF8Get_t fn = ((amx_UTF8Get_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Get];
	return fn(string, endptr, value);
}

typedef int  AMXAPI (*amx_UTF8Len_t)(const cell *cstr, int *length);
int AMXAPI amx_UTF8Len(const cell *cstr, int *length)
{
	amx_UTF8Len_t fn = ((amx_UTF8Len_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Len];
	return fn(cstr, length);
}

typedef int  AMXAPI (*amx_UTF8Put_t)(char *string, char **endptr, int maxchars, cell value);
int AMXAPI amx_UTF8Put(char *string, char **endptr, int maxchars, cell value)
{
	amx_UTF8Put_t fn = ((amx_UTF8Put_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Put];
	return fn(string, endptr, maxchars, value);
}

//----------------------------------------------------------
// EOF
