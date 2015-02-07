$ ->
  $.delay = (ms, func) -> setTimeout func, ms

  $.urlParam = (name) ->
    results = new RegExp('[\\?&]' + name + '=([^&#]*)').exec(window.location.href)
    if !results
      0
    else
      results[1] || 0
