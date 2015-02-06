#!/usr/bin/env ruby

require 'json'


type = 'png'

files = %w(hours minutes).map do |t|
  %w(first last).map do |p|
    path = "images"
    Dir["./resources/#{path}/#{t}_#{p}_*.#{type}"].map do |file|
      basename = File.basename file
      no_ext = File.basename file, ".#{type}"
      {
        file: "#{path}/#{basename}",
        name: "#{no_ext}".upcase,
        type: type
      }
    end
  end
end.flatten

puts JSON.pretty_generate files
