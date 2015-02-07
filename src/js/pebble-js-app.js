Pebble.addEventListener("ready",
  function(e) {
    console.log("PebbleKit JS ready!");
  }
);
Pebble.addEventListener("showConfiguration",
  function(e) {
    var config_url = "https://dstosik.github.io/pebblot/config.html?";
    //config_url = "http://192.168.7.6:4567/config.html?debug=1&"; // Local debug

    var settings = localStorage.getItem("settings");
    console.log('localStorage settings= ' + settings);
    var settings_str = encodeURIComponent(settings);
    config_url += 'settings=' + settings_str;

    config_url += '&account=' + Pebble.getAccountToken();

    console.log("Opening Config: " + config_url);
    Pebble.openURL(config_url);
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    var settings_string = decodeURIComponent(e.response);
    console.log("Configuration window returned: " + settings_string);

    if (settings_string != 'CANCELLED') {
      localStorage.setItem("settings", settings_string);

      //Send to Pebble, persist there
      Pebble.sendAppMessage(
        JSON.parse(settings_string),
        function(e) {
          console.log("Sending settings data...");
        },
        function(e) {
          console.log("Settings feedback failed!");
        }
      );
    }
  }
);
