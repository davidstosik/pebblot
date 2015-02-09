(function() {
  $(function() {
    var event_props, settings_hash, uid, _ref;
    try {
      settings_hash = JSON.parse(decodeURIComponent($.urlParam('settings')));
    } catch (_error) {
      settings_hash = {};
    }
    if (typeof settings_hash !== 'object') {
      settings_hash = {};
    }
    $('.debug').append("Received settings: " + JSON.stringify(settings_hash) + "\n");
    if ($.urlParam('debug')) {
      $('.debug').removeClass('hidden');
      $('input#submit').addClass('btn-danger');
    }
    $.each(settings_hash, function(name, value) {
      var element;
      element = $("[name=" + name + "]");
      if (element.prop('tagName') === 'INPUT') {
        switch (element.attr('type')) {
          case 'radio':
            element.filter("[value=" + value + "]").click();
            break;
          case 'checkbox':
            return element.prop('checked', value);
        }
      } else {
        return element.val(value);
      }
    });
    $('form#settings').submit(function(event) {
      var location;
      settings_hash = {};
      $('form#settings select').each(function() {
        settings_hash[$(this).prop('name')] = parseInt($(this).val());
        return true;
      });
      $('form#settings input[type=checkbox]').each(function() {
        settings_hash[$(this).prop('name')] = $(this).is(':checked');
        return true;
      });
      $('.debug').append("Prepared settings: " + JSON.stringify(settings_hash) + "\n");
      mixpanel.people.set(settings_hash);
      location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings_hash));
      $('.debug').append("Returned URL: " + location + "\n");
      if ($('input#submit').hasClass('btn-danger')) {
        $('.debug').append("Click again!\n");
        $('input#submit').removeClass('btn-danger');
      } else {
        mixpanel.track('Submitted settings form', settings_hash);
        document.location = location;
      }
      return event.preventDefault();
    });
    if (uid = $.urlParam('account')) {
      ga('set', '&uid', uid);
      mixpanel.identify(uid);
    }
    event_props = ((_ref = settings_hash === {}) != null ? _ref : {
      empty_settings: true
    }) || settings_hash;
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
