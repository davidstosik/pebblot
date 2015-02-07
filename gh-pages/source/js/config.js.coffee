$ ->

  try
    settings = JSON.parse decodeURIComponent $.urlParam 'settings'
  catch
    settings = {}

  settings = {} unless typeof settings == 'object'

  $('.debug').append "Received settings: " + JSON.stringify(settings) + "\n"

  if $.urlParam 'debug'
    $('.debug').removeClass 'hidden'
    $('input#submit').addClass 'btn-danger'

  $.each settings, (name, value) ->
    element = $("[name=#{name}]")
    if element.attr('type') == 'radio'
      element.filter("[value=#{value}]").click()
    else
      element.val(value)

  $('form#settings').submit (event) ->
    settings = {}
    $.each $('form').serializeArray(), ->
      settings[this.name] = parseInt(this.value)
    $('.debug').append "Prepared settings: " + JSON.stringify(settings) + "\n"

    mixpanel.people.set settings

    location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings))
    $('.debug').append "Returned URL: " + location + "\n"

    if $('input#submit').hasClass 'btn-danger'
      $('.debug').append "Click again!\n"
      $('input#submit').removeClass 'btn-danger'
    else
      mixpanel.track 'Submitted settings form', settings
      document.location = location

    event.preventDefault()

  # Statistics

  if uid = $.urlParam 'account'
    ga 'set', '&uid', uid # Set the user ID using signed-in user_id.
    mixpanel.identify uid

  event_props = (settings == {}) ? {empty_settings: true} || settings
  event_props['debug'] = $.urlParam 'debug'
  mixpanel.track 'Opened config page', event_props

  $('select').change (e) ->
    mixpanel.track 'Changed option', { name: $(this).attr('name'), value: $(this).val() }
