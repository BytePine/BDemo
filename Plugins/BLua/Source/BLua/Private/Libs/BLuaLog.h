// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

BLUA_API DECLARE_LOG_CATEGORY_EXTERN(LogBLua, Log, All);

struct lua_State;

BLUA_API int lua_BLog(lua_State* L);
BLUA_API int lua_BWarning(lua_State* L);
BLUA_API int lua_BError(lua_State* L);

BLUA_API void luaL_OpenBLogs(lua_State* L);