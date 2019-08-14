#include "mcinstant.h"
#include "luautils.h"
#include <dmsdk/sdk.h>

#define LIB_NAME "MCInstant"
#define MODULE_NAME "mcinstant"
//#define DLIB_LOG_DOMAIN LIB_NAME

#if defined(DM_PLATFORM_HTML5)

// ===============================================
// INITIALIZE
// ===============================================
lua_Listener mcInitializeAsyncListener;

static void MCI_InitializeResponse(const int success){
	lua_State* L = mcInitializeAsyncListener.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mcInitializeAsyncListener);
	lua_pushboolean(L, success);
	int ret = lua_pcall(L, 2, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_InitializeProxy(lua_State* L) {
	int top = lua_gettop(L);

    const char* configJson;
    if (lua_isstring(L, 1)){
        configJson = luaL_checkstring(L,1);
    } else {
        configJson = "";
    }

	luaL_checklistener(L, 2, mcInitializeAsyncListener);
	MCI_InitializeImpl(configJson, (OnInitializeCallback)MCI_InitializeResponse);

	assert(top == lua_gettop(L));
	return 0;
}

// ===============================================
// Get Challenges
// ===============================================
lua_Listener mcGetChallengesListener;

static void MCI_GetChallengesResponse(const char* challenges){
	lua_State* L = mcGetChallengesListener.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mcGetChallengesListener);
	lua_pushstring(L, challenges);
	int ret = lua_pcall(L, 2, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_GetChallengesProxy(lua_State* L) {
	int top = lua_gettop(L);

	luaL_checklistener(L, 1, mcGetChallengesListener);
	MCI_GetChallengesImpl((OnGetChallengesCallback)MCI_GetChallengesResponse);

	assert(top == lua_gettop(L));
	return 0;
}


// ===============================================
// GET CHALLENGE
// ===============================================
lua_Listener mc_listener_getChallenge;

static void MCI_GetChallengeResponse(const int success, const char* challenge){
	lua_State* L = mc_listener_getChallenge.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mc_listener_getChallenge);
	lua_pushboolean(L, success);
	lua_pushstring(L, challenge);
	int ret = lua_pcall(L, 3, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_GetChallengeProxy(lua_State* L) {
	int top = lua_gettop(L);

    const char* challenge_id = luaL_checkstring(L,1);

	luaL_checklistener(L, 2, mc_listener_getChallenge);
	MCI_GetChallengeImpl(challenge_id, (OnGetChallengeCallback)MCI_GetChallengeResponse);

	assert(top == lua_gettop(L));
	return 0;
}

// ===============================================
// CREATE CHALLENGE
// ===============================================
lua_Listener mc_listener_createChallenge;

static void MCI_CreateChallengeResponse(const int success, const char* challenge_id){
	lua_State* L = mc_listener_createChallenge.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mc_listener_createChallenge);
	lua_pushboolean(L, success);
	lua_pushstring(L, challenge_id);
	int ret = lua_pcall(L, 3, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_CreateChallengeProxy(lua_State* L) {
	int top = lua_gettop(L);

	const int score = luaL_checkinteger(L,1);
	const int duration = luaL_checkinteger(L,2);

	luaL_checklistener(L, 3, mc_listener_createChallenge);
	MCI_CreateChallengeImpl(score, duration, (OnCreateChallengeCallback)MCI_CreateChallengeResponse);

	assert(top == lua_gettop(L));
	return 0;
}

// ===============================================
// SET CHALLENGE SCORE
// ===============================================
lua_Listener mc_listener_setChallengeScore;

static void MCI_SetChallengeScoreResponse(const int success){
	lua_State* L = mc_listener_setChallengeScore.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mc_listener_setChallengeScore);
	lua_pushboolean(L, success);
	int ret = lua_pcall(L, 2, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_SetChallengeScoreProxy(lua_State* L) {
	int top = lua_gettop(L);

	const char* challenge_id = luaL_checkstring(L,1);
	const int score = luaL_checkinteger(L,2);

	luaL_checklistener(L, 3, mc_listener_setChallengeScore);
	MCI_SetChallengeScoreImpl(challenge_id, score, (OnSetChallengeScoreCallback)MCI_SetChallengeScoreResponse);

	assert(top == lua_gettop(L));
	return 0;
}

// ===============================================
// GET WALLET BALANCE
// ===============================================
lua_Listener mc_listener_getWalletBalance;

static void MCI_GetWalletBallanceResponse(const char* balance){
	lua_State* L = mc_listener_getWalletBalance.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mc_listener_getWalletBalance);
	lua_pushstring(L, balance);
	int ret = lua_pcall(L, 2, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_GetWalletBallanceProxy(lua_State* L) {
	int top = lua_gettop(L);

	luaL_checklistener(L, 1, mc_listener_getWalletBalance);
	MCI_GetWalletBallanceImpl((OnGetWalletBallanceCallback)MCI_GetWalletBallanceResponse);

	assert(top == lua_gettop(L));
	return 0;
}


// ===============================================
// SUBSCRIBE EVENT
// ===============================================
lua_Listener mc_listener_subscribeEvent;

static void MCI_SubscribeEventResponse(const char* payload){
	lua_State* L = mc_listener_subscribeEvent.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, mc_listener_subscribeEvent);
	lua_pushstring(L, payload);
	int ret = lua_pcall(L, 2, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int MCI_SubscribeEventProxy(lua_State* L) {
	int top = lua_gettop(L);

    const char* event_name = luaL_checkstring(L,1);

	luaL_checklistener(L, 2, mc_listener_subscribeEvent);
	MCI_SubscribeEventImpl(event_name, (OnSubscribeEventCallback)MCI_SubscribeEventResponse);

	assert(top == lua_gettop(L));
	return 0;
}


// ===============================================
// HANDLERS
// ===============================================
static const luaL_reg Module_methods[] = {
	{"initialize", MCI_InitializeProxy},
	
	{"get_challenges", MCI_GetChallengesProxy},
	{"get_challenge", MCI_GetChallengeProxy},
	{"create_challenge", MCI_CreateChallengeProxy},
	{"set_challenge_score", MCI_SetChallengeScoreProxy},
	{"get_wallet_balance", MCI_GetWalletBallanceProxy},
	{"subscribe_event", MCI_SubscribeEventProxy},
    {0,0}
};

static void LuaInit(lua_State* L) {
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);


    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

#endif

dmExtension::Result AppInitializeMCInstantExtension(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeMCInstantExtension(dmExtension::Params* params) {
	#if defined(DM_PLATFORM_HTML5)
		LuaInit(params->m_L);
	#else
		printf("Extension %s is not supported\n", MODULE_NAME);
	#endif
	return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeMCInstantExtension(dmExtension::AppParams* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeMCInstantExtension(dmExtension::Params* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result UpdateMCInstantExtension(dmExtension::Params* params) {
	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(MCInstant, LIB_NAME, AppInitializeMCInstantExtension, AppFinalizeMCInstantExtension, InitializeMCInstantExtension, UpdateMCInstantExtension, 0, FinalizeMCInstantExtension)
