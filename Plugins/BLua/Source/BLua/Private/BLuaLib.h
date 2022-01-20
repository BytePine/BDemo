// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

struct lua_State;

BLUA_API void lua_BLog(lua_State* L);
BLUA_API void lua_BWarning(lua_State* L);
BLUA_API void lua_BError(lua_State* L);

BLUA_API void luaL_openBLibs(lua_State* L);