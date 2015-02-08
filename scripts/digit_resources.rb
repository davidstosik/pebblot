#!/usr/bin/env ruby

require 'json'

base_path = 'images/digits'
type = 'png'

files =
  (0..3).map do |position|
    (0..10).map do |digit|
      file = "#{base_path}/#{position}/d#{position}_#{digit}.#{type}"
      next unless File.file? "./resources/#{file}"
      {
        file: "#{file}",
        name: "DIGIT_#{position}_#{digit}",
        type: type
      }
    end
  end.flatten.compact

puts JSON.pretty_generate files
