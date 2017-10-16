(function() {
    setAllLow();

    var vals = [-5.5, -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5];
    var direction = 1;
    var current = 0;

    var min = 1000;
    var max = -1000;
    var MAX = .9;
    var MIN = -.1;
    setInterval(function() {
        var c = direction == 1 ? current : 8 - current;
        for (var row = 0; row < 12; row++) {
            for (var col = 0; col < 12; col++) {
                var x = vals[row];
                var y = vals[col];
                var cmp = Math.sqrt(x*x + y*y + c*c)
                var z = Math.sin(cmp)/cmp;

                var level = ((z - MIN) / (MAX - MIN))
                if (level < 0) level = 0;
                if (level > 1) level = 1;
                setLevel(row, col, level);
            }
        }
        current = (current + 1) % 8;
        if (current == 0) direction *= -1;
    }, 200);
})();