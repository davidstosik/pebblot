//= require "jquery-2.1.3.min"
//= require "bootstrap"

$ ->

  delay = (ms, func) -> setTimeout func, ms

  $.urlParam = (name) ->
    results = new RegExp('[\\?&]' + name + '=([^&#]*)').exec(window.location.href)
    if !results
      0
    else
      results[1] || 0
  # End of $.urlParam

  settings = JSON.parse decodeURIComponent $.urlParam 'settings'
  settings ||= {}

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

    location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(settings))
    $('.debug').append "Returned URL: " + location + "\n"

    if $('input#submit').hasClass 'btn-danger'
      $('.debug').append "Click again!\n"
      $('input#submit').removeClass 'btn-danger'
    else
      document.location = location

    event.preventDefault()
