Pebble.addEventListener("ready",
  function(e) {
    console.log("PebbleKit JS ready!");
  }
);
Pebble.addEventListener("showConfiguration",
  function(e) {
    var config_url = "http://dstosik.github.io/pebble-rorschach/config.html";
    //config_url = "http://192.168.7.6:8000/gh-pages/config.html"; // Local debug

    var settings = encodeURIComponent(localStorage.getItem("settings"));
    config_url += '?settings=' + settings;

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
