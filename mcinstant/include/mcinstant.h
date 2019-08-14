#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

typedef void (*OnInitializeCallback)(const int success);
typedef void (*OnGetChallengesCallback)(const char* challenges);
typedef void (*OnGetChallengeCallback)(const int success, const char *challenge);
typedef void (*OnCreateChallengeCallback)(const int success, const char *challenge_id);
typedef void (*OnSetChallengeScoreCallback)(const int success);
typedef void (*OnGetWalletBallanceCallback)(const char *balance);

typedef void (*OnSubscribeEventCallback)(const char *payload);

extern "C" {
    void MCI_InitializeImpl(const char* dataJson, OnInitializeCallback callback);

    //async get_challenges(callback):(string)
    void MCI_GetChallengesImpl(OnGetChallengesCallback callback);

    //async get_challenge(string challenge_id, callback):(string challenge)
    void MCI_GetChallengeImpl(const char* challenge_id, OnGetChallengeCallback callback);

    //async create_challenge(int score, int duraction, callback):(string challenge_id)
    void MCI_CreateChallengeImpl(int score, int duration, OnCreateChallengeCallback callback);

    //async set_challenge_score(string, int, callback):(bool)
    void MCI_SetChallengeScoreImpl(const char* challenge_id, int score, OnSetChallengeScoreCallback callback);
    
    //get_wallet_balance(callback):(string balance)
    void MCI_GetWalletBallanceImpl(OnGetWalletBallanceCallback callback);


    //subscribe_event(string, callback)
    void MCI_SubscribeEventImpl(const char* event_name, OnSubscribeEventCallback callback);
}

#endif