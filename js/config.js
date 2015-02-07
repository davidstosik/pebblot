(function() {
  $(function() {
    var event_props, settings, uid, _ref;
    try {
      settings = JSON.parse(decodeURIComponent($.urlParam('settings')));
    } catch (_error) {
      settings = {};
    }
    if (typeof settings !== 'object') {
      settings = {};
    }
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
    $('form#settings').submit(function(event) {
      var location;
      settings = {};
      $.each($('form').serializeArray(), function() {
        return settings[this.name] = parseInt(this.value);
      });
      $('.debug').append("Prepared settings: " + JSON.stringify(settings) + "\n");
      mixpanel.people.set(settings);
      location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings));
      $('.debug').append("Returned URL: " + location + "\n");
      if ($('input#submit').hasClass('btn-danger')) {
        $('.debug').append("Click again!\n");
        $('input#submit').removeClass('btn-danger');
      } else {
        mixpanel.track('Submitted settings form', settings);
        document.location = location;
      }
      return event.preventDefault();
    });
    if (uid = $.urlParam('account')) {
      ga('set', '&uid', uid);
      mixpanel.identify(uid);
    }
    event_props = ((_ref = settings === {}) != null ? _ref : {
      empty_settings: true
    }) || settings;
    event_props['debug'] = $.urlParam('debug');
    event_props['page'] = 'config';
    mixpanel.track('Page', event_props);
    return $('select').change(function(e) {
      return mixpanel.track('Changed option', {
        name: $(this).attr('name'),
        value: $(this).val()
      });
    });
  });

}).call(this);
