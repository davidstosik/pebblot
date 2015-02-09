$ ->

  try
    settings_hash = JSON.parse decodeURIComponent $.urlParam 'settings'
  catch
    settings_hash = {}

  settings_hash = {} unless typeof settings_hash == 'object'

  $('.debug').append "Received settings: " + JSON.stringify(settings_hash) + "\n"

  if $.urlParam 'debug'
    $('.debug').removeClass 'hidden'
    $('input#submit').addClass 'btn-danger'

  $.each settings_hash, (name, value) ->
    element = $("[name=#{name}]")
    if element.prop('tagName') == 'INPUT'
      switch element.attr('type')
        when 'radio'
          element.filter("[value=#{value}]").click()
          break
        when 'checkbox'
          element.prop 'checked', value
    else
      element.val(value)

  $('form#settings').submit (event) ->
    settings_hash = {}
    $('form#settings select').each () ->
      settings_hash[$(this).prop('name')] = $(this).val()
      true# Don't stop the loop
    $('form#settings input[type=checkbox]').each () ->
      settings_hash[$(this).prop('name')] = $(this).is(':checked')
      true# Don't stop the loop

    $('.debug').append "Prepared settings: " + JSON.stringify(settings_hash) + "\n"

    mixpanel.people.set settings_hash

    location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings_hash))
    $('.debug').append "Returned URL: " + location + "\n"

    if $('input#submit').hasClass 'btn-danger'
      $('.debug').append "Click again!\n"
      $('input#submit').removeClass 'btn-danger'
    else
      mixpanel.track 'Submitted settings form', settings_hash
      document.location = location

    event.preventDefault()

  # Statistics

  if uid = $.urlParam 'account'
    ga 'set', '&uid', uid # Set the user ID using signed-in user_id.
    mixpanel.identify uid

  event_props = (settings_hash == {}) ? {empty_settings: true} || settings_hash
  event_props['debug'] = $.urlParam 'debug'
  event_props['page'] = 'config'
  mixpanel.track 'Page', event_props

  $('select').change (e) ->
    mixpanel.track 'Changed option', { name: $(this).attr('name'), value: $(this).val() }
