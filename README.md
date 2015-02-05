# Pebblot

![Pebblot
examples](https://github.com/dstosik/pebble-rorschach/blob/master/design/examples/tests.png)

Yet another attempt at making a Pebble watchface that looks like Hermann
Rorschach's famous inkblot test.

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
 - Configurable background color (via a watchface setting)

## To-Do list

 - Add a simple PM indicator when in 12-hour mode
 - Add the third display mode, where digits melt together
 - Vibrate every hour
 - Notify Bluetooth disconnect (vibration and screen color inversion)
 - Display the date (on tap?)
 - Animate transitions with a morphing effect

## Found a bug?

If you are having any problem installing and using this watchface, feel free to
give me a shout on [Pebble's official forum](http://forums.getpebble.com)
(I'm [DavidStosik](http://forums.getpebble.com/profile/77675/DavidStosik)), or
to [file an issue on Github](https://github.com/dstosik/pebble-rorschach/issues).

Suggestions are welcome too!

## Credits

 - [Sam Jerichow](https://www.facebook.com/futurewatches), whose [Rorschach 2 watch
concept](http://blog.tokyoflash.com/2013/03/14/rorschach-2-e-paper-watch-update/)
was a great source of inspiration.
 - [Grégoire Sage](https://github.com/gregoiresage) a.k.a
[perdrolane](http://forums.getpebble.com/profile/6493/pedrolane), for showing
me some Pebble stuff he's been working on, getting me interested into Pebble
development. Also for referring, on [his own version of the Pebble Rorschach
watchface](https://apps.getpebble.com/applications/53470aa9b0b1d3469e00012d),
Sam Jerichow's design (see above).
 - Guillaume for his constant support and input.
