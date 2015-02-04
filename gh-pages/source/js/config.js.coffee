//= require "jquery-2.1.3.min"
//= require "bootstrap"


$ ->

  $.urlParam = (name) ->
    results = new RegExp('[\\?&]' + name + '=([^&#]*)').exec(window.location.href)
    if !results
      0
    else
      results[1] || 0
  # End of $.urlParam

  settings = JSON.parse(decodeURIComponent($.urlParam('settings')))

  console.log(settings)

  $.each settings, (name, value) ->
    $('[name=' + name + ']').val(value)

  $('form#settings').submit (event) ->
    settings = {}
    $.each $('form').serializeArray(), ->
      settings[this.name] = parseInt(this.value)

    location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings))
    console.log(location)
    document.location = location
    event.preventDefault()
