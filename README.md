# Pebblot

Yet another attempt at making a Pebble watch face that looks like Hermann
Rorschach's famous inkblot test.

![Pebblot
examples](https://raw.githubusercontent.com/dstosik/pebblot/master/design/examples/tests.png)

## Basis

The watch face gets its desired look by giving digits a fat, round font,
mirroring them, then melting them together.

## How to use

When idle, hours are displayed on the top right part while minutes are on the
bottom left part of the watch face. Depending on your display mode, digits can be
mirrored, then melted together.

## Feature list

 - Current time display
 - 12/24 hour mode (uses the Pebble's setting by default, but can be forced)
 - 2 display modes: simple and symmetric
 - Configurable background color (via a watch face setting)

## How to get it?

Until I officially release it on Pebble's app store, you can get the watch
face's .pbw file on Github's [Releases page](https://github.com/dstosik/pebblot).
Feel free to clone this repository and compile the watch face from the sources
to get latest improvements (code stability is only guaranteed on official releases).

## To-Do list

 - Add a simple PM indicator when in 12-hour mode
 - Add the third display mode, where digits melt together
 - Vibrate every hour
 - Notify Bluetooth disconnect (vibration and screen color inversion)
 - Display the date (on tap?)
 - Animate transitions with a morphing effect

## Found a bug?

If you are having any problem installing and using this watch face, feel free to
give me a shout on [Pebble's official forum](http://forums.getpebble.com)
(I'm [DavidStosik](http://forums.getpebble.com/profile/77675/DavidStosik)), or
to [file an issue on Github](https://github.com/dstosik/pebblot/issues).

Suggestions are welcome too!

## Credits

 - [Sam Jerichow](https://www.facebook.com/futurewatches), whose [Rorschach 2 watch
concept](http://blog.tokyoflash.com/2013/03/14/rorschach-2-e-paper-watch-update/)
was a great source of inspiration.
 - [Grégoire Sage](https://github.com/gregoiresage) a.k.a
[perdrolane](http://forums.getpebble.com/profile/6493/pedrolane), for showing
me some Pebble stuff he's been working on, getting me interested into Pebble
development, and also for referring, on [his own version of the Pebble Rorschach
watch face](https://apps.getpebble.com/applications/53470aa9b0b1d3469e00012d),
Sam Jerichow's design (see above).
 - Guillaume for his constant support and input.
