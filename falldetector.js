"use strict";
const BBCMicrobit = require('bbc-microbit')
const EVENT_FAMILY = 8888;
const EVENT_VALUE_ANY = 0;

console.log('Scanning for microbit');
BBCMicrobit.discover(function(microbit) {
    console.log('\tdiscovered microbit: id = %s, address = %s', microbit.id, microbit.address);


    microbit.on('event', function(id, value) {
        console.log('\ton -> micro:bit event received event: %d value: %d', id, value);
	if(value == 18)
		require('child_process').spawn('sh', ['call.sh'], {stdio: 'inherit'});
    });

    microbit.on('disconnect', function() {
        console.log('\tmicrobit disconnected!');
        process.exit(0);
    });

    console.log('connecting to microbit');
    microbit.connectAndSetUp(function() {
        console.log('\tconnected to microbit');
        console.log('subscribing to event family, any event value');
        microbit.subscribeEvents(EVENT_VALUE_ANY, EVENT_FAMILY, function() {
            console.log('\tsubscribed to micro:bit events of required type');
        });
    });

});
