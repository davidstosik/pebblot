(function() {
  $(function() {
    var settings, uid;
    if (uid = $.urlParam('account')) {
      ga('set', '&uid', uid);
    }
    settings = JSON.parse(decodeURIComponent($.urlParam('settings')));
    settings || (settings = {});
    $('.debug').append("Received settings: " + JSON.stringify(settings) + "\n");
    if ($.urlParam('debug')) {
      $('.debug').removeClass('hidden');
      $('input#submit').addClass('btn-danger');
    }
    $.each(settings, function(name, value) {
      var element;
      element = $("[name=" + name + "]");
      if (element.attr('type') === 'radio') {
        return element.filter("[value=" + value + "]").click();
      } else {
        return element.val(value);
      }
    });
    return $('form#settings').submit(function(event) {
      var location;
      settings = {};
      $.each($('form').serializeArray(), function() {
        return settings[this.name] = parseInt(this.value);
      });
      $('.debug').append("Prepared settings: " + JSON.stringify(settings) + "\n");
      location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings));
      $('.debug').append("Returned URL: " + location + "\n");
      if ($('input#submit').hasClass('btn-danger')) {
        $('.debug').append("Click again!\n");
        $('input#submit').removeClass('btn-danger');
      } else {
        document.location = location;
      }
      return event.preventDefault();
    });
  });

}).call(this);
