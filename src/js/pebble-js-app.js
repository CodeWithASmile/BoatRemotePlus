Pebble.addEventListener("ready",
  function(e) {
    console.log("JavaScript app ready and running!");
  }
);

Pebble.addEventListener("showConfiguration", function() {
  console.log("showing configuration");
  var config_url = "http://www.codewithasmile.co.uk/pebble/configuration.html";
  var server = localStorage.getItem("server");
  var port = localStorage.getItem("port");
  config_url = config_url + "?server=" + (server || "") + "&port=" + (port  || "");
  Pebble.openURL(config_url);
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  // webview closed
  var options = JSON.parse(decodeURIComponent(e.response));
  localStorage.clear();
  localStorage.setItem("server", options.server);
  localStorage.setItem("port", options.port);	
  console.log("Options = " + JSON.stringify(options));
});

Pebble.addEventListener("appmessage",
  function(recMessage) {
	var currentScreen = recMessage.payload.screen;
	console.log("received message: screen: " + recMessage.payload.screen);
	var req = new XMLHttpRequest();
	var server = localStorage.getItem("server");
    var port = localStorage.getItem("port");
	var url = server + ':'+ port +'/watch';
    if (server.substr(0,7)  != 'http://'){
        url = 'http://' + url;
    }	
	//console.log("url = " + url);
    req.open('GET', url, true);
    req.onload = function(recData) {
      if (req.readyState == 4 && req.status == 200) {
        if(req.status == 200) {
          //console.log(req.responseText);
          var result = JSON.parse(req.responseText);
          //console.log(result); 
          switch(currentScreen) {
			case 1:
              Pebble.sendAppMessage({ "lat":result.lat, "lon":result.lon, 
                                      "sog":result.sog, "cog":result.cog});
              break;
			case 2:
              Pebble.sendAppMessage({ "boat_speed":result.boat_speed, "depth":result.depth, 
                                      "wind_speed":result.wind_speed, "wind_angle":result.wind_angle});
              break;
            case 3:
              Pebble.sendAppMessage({ "dtw":(result.dtw + ' ' + result.dtw_unit), "btw":result.btw, 
                                      "sog":result.sog, "cog":result.cog});
              break;
			case 4:
              Pebble.sendAppMessage({ "dtw":(result.dtw + ' ' + result.dtw_unit), "btw":result.btw, 
                                      "xte":(result.xte + ' ' + result.xte_unit), 
                                      "heading_to_steer":(result.heading_to_steer + ' ' + result.dir_to_steer),
                                      "heading_to_steer_type":result.heading_to_steer_type});
              break;
			case 5:
              Pebble.sendAppMessage({ "dtw":(result.dtw + ' ' + result.dtw_unit), "btw":result.btw, 
                                      "waypoint":result.waypoint, 
                                      "wpt_lat":(result.wpt_lat + result.wpt_lat_dir),
                                      "wpt_lon":(result.wpt_lon + result.wpt_lon_dir)});
              break;
			case 6:
              Pebble.sendAppMessage({ "temp":(result.temp + ' ' + result.temp_unit), 
                                      "distance_total":result.distance_total, 
                                      "distance_reset":result.distance_reset});
          }
		}
        else { 
          console.log("Error in response from server"); 
        }
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
  }
);