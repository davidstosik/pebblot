(function() {
  $(function() {
    $.delay = function(ms, func) {
      return setTimeout(func, ms);
    };
    return $.urlParam = function(name) {
      var results;
      results = new RegExp('[\\?&]' + name + '=([^&#]*)').exec(window.location.href);
      if (!results) {
        return 0;
      } else {
        return results[1] || 0;
      }
    };
  });

}).call(this);
