# MCI Defold Extension

---

# Setup
## 1. Add projecte dependencies
You can use this extension by adding this project as a Defold library dependency.
Open you game.project file and in the dependencies field under project add:

```
https://github.com/miniclip/mci-defold/archive/master.zip
```

Or point to the ZIP file of [specific release](https://github.com/miniclip/mci-defold/releases).


## 2. Include mcinstant.js
In the index.html of you project include the mcinstant.js script.


# Usage

## MCInstant API
This extension wraps the [MCInstant SDK](https://github.com/miniclip/mci-sdk) in a Lua interface.

# MCInstant API reference

## mcinstant.initialize(config, callback)
Initialize the MCInstant SDK.

**PARAMETERS**
* ```config``` (string) - JSON encoded object containing sdk configuration (refer to the [MCInstant Configuration Options](https://miniclip.github.io/mci-sdk/api/interfaces/_mcinstant_.mcinstantoptions.html))
* ```callback``` (function) - Function to call when the SDK is initialized

## mcinstant.get_challenges(callback)
Retrieve the list of existing challenges

**PARAMETERS**
* ```callback``` (function) - Function to call with the list of challenges

The ```callback``` function is expected to accept the following values:

* ```self``` (userdata) - Script self reference
* ```challenges``` (string) - JSON encoded array of challenge information

## mcinstant.get_challenge(challenge_id, callback)
Get the challenge information of a specific challenge

**PARAMETERS**
* ```challenge_id``` (string) - Id of the challenge to fetch
* ```callback``` (function) - Function to call with the challenge information

The ```callback``` function is expected to accept the following values:

* ```self``` (userdata) - Script self reference
* ```success``` (boolean) - Indicates if found the challenge or not
* ```challenges``` (string) - JSON encoded object with the challenge information (refer to the [Challenge Class accessors](https://miniclip.github.io/mci-sdk/api/classes/_models_challenge_.challenge.html))

## mcinstant.create_challenge(score, duration, callback)
Create a new challenge

**PARAMETERS**
* ```score``` (integer) - The score of the current player
* ```duration``` (integer) - For how many seconds the challenge should be run 
* ```callback``` (function) - Function to call when the challenge has been created

The ```callback``` function is expected to accept the following values:

* ```self``` (userdata) - Script self reference
* ```success``` (boolean) - Indicates if the operation was successful or not


## mcinstant.set_challenge_score(challenge_id, score, callback)
Updates the score of the current user for a specific challenge

**PARAMETERS**
* ```challenge_id``` (integer) - Id of the challenge to update
* ```score``` (integer) - The new score of the user
* ```callback``` (function) - Function to call when the score has been updated

The ```callback``` function is expected to accept the following values:

* ```self``` (userdata) - Script self reference
* ```success``` (boolean) - Indicates if the operation was successful or not

## mcinstant.get_wallet_balance(callback)
Get the user wallet info

**PARAMETERS**
* ```callback``` (function) - Function to call with the wallet information

The ```callback``` function is expected to accept the following values:

* ```self``` (userdata) - Script self reference
* ```balance``` (string) - JSON encoded array with the balance for each type of currency

## mcinstant.subscribe_event(event_name, callback)
Subscribe to an SDK event

**PARAMETERS**
* ```event_name``` (string) - Name of the event to subscribe to
* ```callback``` (function) - Function to call when the event is triggered

The ```callback``` function is expected to accept the following values:

* ```self``` (userdata) - Script self reference
* ```payload``` (string) - JSON encoded array with the event payload