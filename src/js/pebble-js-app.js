Pebble.addEventListener("ready",
	function(e) {
		console.log("JavaScript app ready and running!");
	}
);

Pebble.addEventListener("showConfiguration", function() {
	console.log("showing configuration");
	var config_url = "http://rawgit.com/CodeWithASmile/BoatRemote/master/configuration.html";
	var server = localStorage.getItem("server");
	var port = localStorage.getItem("port");
	var phone_gps = localStorage.getItem("phone_gps");
	config_url = config_url + "?server=" + (server || "") + "&port=" + 
		(port  || "") + "&phone_gps=" + (phone_gps  || "");
	console.log(config_url);
	Pebble.openURL(config_url);
});

Pebble.addEventListener("webviewclosed", function(e) {
	console.log("configuration closed");
	// webview closed
	var options = JSON.parse(decodeURIComponent(e.response));
	localStorage.clear();
	localStorage.setItem("server", options.server);
	localStorage.setItem("port", options.port);
	localStorage.setItem("phone_gps", options.phone_gps);
	console.log("Options = " + JSON.stringify(options));
});

function getURL(){
	var server = localStorage.getItem("server");
    var port = localStorage.getItem("port");
	var url = server + ':'+ port;
    if (server.substr(0,7)  != 'http://'){
        url = 'http://' + url;
    }
	return url;
}

function sendPOST(command, params){
	var req = new XMLHttpRequest();
	var url = getURL();
	url = url + '/' + command;
	console.log("POST url = " + url);
	console.log("POST params = " + params);
    req.open('POST', url, true);
	req.send(params);
}

function parseResults(current_screen, result){
	switch(current_screen) {
		case -2:
			Pebble.sendAppMessage({ "test":"test"});
			break;
		case 0:
			Pebble.sendAppMessage({ "lat":result.lat, "lon":result.lon, 
									"sog":result.sog, "cog":result.cog});
			break;
		case 1:
			Pebble.sendAppMessage({ "boat_speed":result.boat_speed, "depth":result.depth, 
									"wind_speed":result.wind_speed, "wind_angle":result.wind_angle});
			break;
		case 2:
			Pebble.sendAppMessage({ "dtw":result.dtw, "btw":result.btw,
									"sog":result.sog, "cog":result.cog});
			break;
		case 3:
			Pebble.sendAppMessage({ "dtw":result.dtw, "btw":result.btw, 
									"waypoint":result.waypoint, 
									"wpt_lat":result.wpt_lat,
									"wpt_lon":result.wpt_lon});
			break;
		case 4:
			Pebble.sendAppMessage({ "temp":result.temp, 
									"distance_total":result.distance_total, 
									"distance_reset":result.distance_reset});
			break;
		case 5:
			Pebble.sendAppMessage({ "drift":result.drift});
	}
	
}

function locationSuccess(pos) {
  var coordinates = pos.coords;
  sendPOST("set_anchor_watch","lat=" + coordinates.latitude + "&lon=" + coordinates.longitude);
	Pebble.sendAppMessage({"location_status": "1"});
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);
  sendPOST("set_anchor_watch",null);
  Pebble.sendAppMessage({"location_status": "2"});
}

var locationOptions = { "timeout": 5000, "maximumAge": 5000 }; 


Pebble.addEventListener("appmessage",
	function(recMessage) {
		//console.log("received message: " + JSON.stringify(recMessage.payload, null, 2));
		if (recMessage.payload.anchor_watch){
			console.log("received anchor watch message");
			if (recMessage.payload.anchor_watch == 1){
				var phone_gps = localStorage.getItem("phone_gps");
				if (phone_gps == "yes"){
					window.navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
				}
				else{
                    sendPOST("set_anchor_watch",null);
					Pebble.sendAppMessage({"location_status": "2"});
				}
			}
			else{
				console.log("resetting anchor watch");
				sendPOST("reset_anchor_watch",null);
			}
		}
		var current_screen = recMessage.payload.screen;
		var req = new XMLHttpRequest();
		var url = getURL() +'/watch';
		//console.log("url = " + url);
		req.open('GET', url, true);
		req.onreadystatechange = function(){
			//console.log("Status of request is " + req.readyState);
			//console.log("Status of response is " + req.status);
		};
		req.onload = function(recData) {
			//console.log("received data");
			if (req.readyState == 4 && req.status == 200) {
				clearTimeout(myTimeout);
				var result = JSON.parse(req.responseText);
				parseResults(current_screen, result); 
			}
			else { 
				console.log("Error in response from server"); 
			}
		};
		req.timeout = 5000;
		req.ontimeout = function () {
			console.error("The request for " + url + " timed out.");
			Pebble.sendAppMessage({"server_error": "1"});
		};
		req.send(null);
		var myTimeout = setTimeout(function(){
			req.abort();
			console.error("The request for " + url + " timed out - own timeout.");
			Pebble.sendAppMessage({"server_error": "1"});
		}, 5000); 
									}
);