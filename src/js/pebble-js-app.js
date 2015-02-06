Pebble.addEventListener("ready",
  function(e) {
    console.log("PebbleKit JS ready!");
  }
);
Pebble.addEventListener("showConfiguration",
  function(e) {
    var config_url = "https://dstosik.github.io/pebblot/config.html?";
    //config_url = "http://192.168.7.6:8000/config.html?debug=1&"; // Local debug

    var settings = encodeURIComponent(localStorage.getItem("settings"));
    config_url += 'settings=' + settings;

    console.log("Opening Config: " + config_url);
    Pebble.openURL(config_url);
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    var settings_string = decodeURIComponent(e.response);
    console.log("Configuration window returned: " + settings_string);
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
);
