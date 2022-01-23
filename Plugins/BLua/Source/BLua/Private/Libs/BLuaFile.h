// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

struct lua_State;

BLUA_API int lua_BLoadFile(lua_State* L);

BLUA_API void luaL_openBFile(lua_State* L);