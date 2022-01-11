// Copyright Tencent Games, Inc. All Rights Reserved.

#pragma once

struct lua_State;

UNLUAEXTEND_API int32 Global_Log(lua_State *L);

UNLUAEXTEND_API int32 Global_Warning(lua_State *L);

UNLUAEXTEND_API int32 Global_Error(lua_State *L);

UNLUAEXTEND_API void RegisterLog(lua_State *L);