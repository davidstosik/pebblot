#!/usr/bin/env ruby

require 'json'

type = 'png'

base_path = 'images/digits'
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

sides = %w(top bottom left right)
part = sides + %w(center)
base_path = 'images/melted'
files += (0..3).map do |position|
  Dir["./resources/#{base_path}/#{position}/*.#{type}"].map do |file|
    basename = File.basename file
    {
      file: "#{base_path}/#{position}/#{basename}",
      name: 'MELTED_' + basename.sub(/\.#{type}$/, '').upcase[1..-1],
      type: type,
    }
  end.flatten.compact

end

puts JSON.pretty_generate files.flatten
