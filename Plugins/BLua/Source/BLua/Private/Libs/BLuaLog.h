// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

struct lua_State;

BLUA_API int lua_BLog(lua_State* L);
BLUA_API int lua_BWarning(lua_State* L);
BLUA_API int lua_BError(lua_State* L);

BLUA_API void luaL_openBLogs(lua_State* L);