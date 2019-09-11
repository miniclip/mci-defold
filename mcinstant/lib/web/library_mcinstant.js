

var MCInstantLibrary = {

    $_instance: null,

    $MCUtils: {
        minVersion: "0.1.6",
        isCompatibleVersion: function(){
            var compatible = MCUtils.minVersion;
            var current = MCInstant.MCInstant.version;
            if (MCUtils.compareVersions(compatible, current) <= 0){
                return true;
            } else {
                return false;
            }
        },
        compareVersions: function(a,b){
            var pa = a.split('.');
            var pb = b.split('.');
            for (var i = 0; i < 3; i++) {
                var na = Number(pa[i]);
                var nb = Number(pb[i]);
                if (na > nb) return 1;
                if (nb > na) return -1;
                if (!isNaN(na) && isNaN(nb)) return 1;
                if (isNaN(na) && !isNaN(nb)) return -1;
            }
            return 0;
        },
        allocateString: function(str) {
            return allocate(intArrayFromString(str), "i8", ALLOC_NORMAL);
        },
        dynCall: function(fn, in_args) {
            var signature = "v";
            var out_args = [];
            var i;
            for (i=0; i < in_args.length; i++) {
                signature = signature + "i";
                out_args.push((typeof in_args[i] == "string") ? MCUtils.allocateString(in_args[i]) : in_args[i]);
            }
            Runtime.dynCall(signature, fn, out_args.slice());
            for (i=0; i < in_args.length; i++) {
                if (typeof in_args[i] == "string") Module._free(out_args[i]);
            }
        },
    },

    MCI_InitializeImpl: function(configData, callback){
        if (!MCUtils.isCompatibleVersion()){
            var mciVersion = MCInstant.MCInstant.version;
            var minVersion = MCUtils.minVersion;
            console.error("[MCI-Defold] This mcinstant version("+mciVersion+") used might be incompatible.");
            console.error("[MCI-Defold] This extension requires at least mcinstant version "+minVersion+".");
        }
        console.log("[MCI-Defold] Initialized");
        var configJson = Pointer_stringify(configData);
        var config = configJson != "" ? JSON.parse(configJson) : null;
        
        if (config == "") config = {};
        _instance = new MCInstant.MCInstant(config);

        Runtime.dynCall("vi", callback, [1]);
    },

    MCI_GetChallengesImpl: function(callback)
    {
        _instance.challenges.getAll().then(function(challenges){
            MCUtils.dynCall(callback, [JSON.stringify(challenges)]);
        });
    },

    MCI_GetChallengeImpl: function(ptr_challenge_id, callback)
    {
        var challenge_id = Pointer_stringify(ptr_challenge_id);

        _instance.challenges.getByChallengeId(challenge_id).then(function(challenge){

            if (challenge != null){
                var dataJSON = JSON.stringify(challenge);
                MCUtils.dynCall(callback, [1, dataJSON]);
            } else {
                MCUtils.dynCall(callback, [0, ""]);
            }
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
                    MCUtils.dynCall(callback, [1, challenge.challengeId]);
                });
            } else {
                MCUtils.dynCall(callback, [0, ""]);
            }
        })
        
    },

    //async set_challenge_score(string, int, callback):(bool)
    MCI_SetChallengeScoreImpl: function(ptr_challenge_id, score, callback)
    {
        var challenge_id = Pointer_stringify(ptr_challenge_id);
         
        var challenge = _instance.challenges.getByChallengeId(challenge_id).then(function(challenge){
            if (challenge == null){
                MCUtils.dynCall(callback, [0]);
            } else {

                challenge.setScore(score);
                challenge.save().then(function(success){
                    MCUtils.dynCall(callback, [success?1:0]);
                })
            }
        })
    },
    
    //get_wallet_balance(callback):(string balance)
    MCI_GetWalletBallanceImpl: function(callback)
    {
        _instance.wallet.getBalance().then(function(balances){
            MCUtils.dynCall(callback, [JSON.stringify(balances)]);
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
            MCUtils.dynCall(callback, [JSON.stringify(args)]);
        })
    }
}

autoAddDeps(MCInstantLibrary, "$_instance")
autoAddDeps(MCInstantLibrary, "$MCUtils")
mergeInto(LibraryManager.library, MCInstantLibrary)