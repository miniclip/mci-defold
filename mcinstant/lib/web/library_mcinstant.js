

var MCInstantLibrary = {

    $_instance: null,

    $Utils: {
        allocateString: function(str) {
            return allocate(intArrayFromString(str), "i8", ALLOC_NORMAL);
        },
        dynCall: function(fn, in_args) {
            var signature = "v";
            var out_args = [];
            var i;
            for (i=0; i < in_args.length; i++) {
                signature = signature + "i";
                out_args.push((typeof in_args[i] == "string") ? Utils.allocateString(in_args[i]) : in_args[i]);
            }
            Runtime.dynCall(signature, fn, out_args.slice());
            for (i=0; i < in_args.length; i++) {
                if (typeof in_args[i] == "string") Module._free(out_args[i]);
            }
        },
    },

    MCI_InitializeImpl: function(configData, callback){
        console.log("MCInstant initialized");
        var configJson = Pointer_stringify(configData);
        var config = configJson != "" ? JSON.parse(configJson) : null;
        
        console.log("config", configJson);
        if (config == "") config = {};
        _instance = new MCInstant.MCInstant(config);

        window.mci = _instance;

        Runtime.dynCall("vi", callback, [1]);
    },

    MCI_GetChallengesImpl: function(callback)
    {
        _instance.challenges.getAll().then(function(challenges){
            Utils.dynCall(callback, [JSON.stringify(challenges)]);
        });
    },

    MCI_GetChallengeImpl: function(ptr_challenge_id, callback)
    {
        var challenge_id = Pointer_stringify(ptr_challenge_id);

        console.log("trying to get challenge " + challenge_id);
        _instance.challenges.getByChallengeId(challenge_id).then(function(challenge){

            var dataJSON = "{}";
            if (challenge != null){
                dataJSON = JSON.stringify(challenge);
            }
            Utils.dynCall(callback, [dataJSON]);
        })
    },

    //async create_challenge(int score, int duraction, callback):(string challenge_id)
    MCI_CreateChallengeImpl: function(score, duration, callback)
    {
        var challenge = _instance.challenges.create({ "duration": duration });
        challenge.setScore(score);
        challenge.save().then(function(success){
            if (success){
                _instance.challenges.updateList().then(function(){
                    Utils.dynCall(callback, [1, challenge.challengeId]);
                });
            } else {
                Utils.dynCall(callback, [0, ""]);
            }
        })
        
    },

    //async set_challenge_score(string, int, callback):(bool)
    MCI_SetChallengeScoreImpl: function(ptr_challenge_id, score, callback)
    {
        var challenge_id = Pointer_stringify(ptr_challenge_id);
         
        var challenge = _instance.challenges.getByChallengeId(challenge_id).then(function(challenge){
            if (challenge == null){
                Utils.dynCall(callback, [0]);
            } else {

                challenge.setScore(score);
                challenge.save().then(function(success){
                    Utils.dynCall(callback, [success?1:0]);
                })
            }
        })
    },
    
    //get_wallet_balance(callback):(string balance)
    MCI_GetWalletBallanceImpl: function(callback)
    {
        _instance.wallet.getBalance().then(function(balances){
            Utils.dynCall(callback, [JSON.stringify(balances)]);
        })
    },

    MCI_SubscribeEventImpl: function(ptr_event_name, callback)
    {
        var event_name = Pointer_stringify(ptr_event_name);
        _instance.events.on(event_name, function(){
            var args = [];
            for(var i=0;i<arguments.length;i++){
                args.push(arguments[i]);
            }
            Utils.dynCall(callback, [JSON.stringify(args)]);
        })
    }
}

autoAddDeps(MCInstantLibrary, "$_instance")
autoAddDeps(MCInstantLibrary, "$Utils")
mergeInto(LibraryManager.library, MCInstantLibrary)