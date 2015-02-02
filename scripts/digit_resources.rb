#!/usr/bin/ruby

require 'json'

type = 'png'

files = %w(hours minutes).map do |t|
  %w(first last).map do |p|
    path = "images/digits/#{t}/#{p}"
    Dir["./resources/#{path}/*.#{type}"].map do |file|
      basename = File.basename file, ".#{type}"
      {
        file: "#{path}/#{basename}.#{type}",
        name: "#{t}_#{p}_#{basename}".upcase,
        type: type
      }
    end
  end
end.flatten

puts JSON.pretty_generate files
