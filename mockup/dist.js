(function() {
    setAllLow();

    var n = 12;
    var dist_cache = new Array((n+1)*n/2);
    var max = Math.sqrt(Math.pow(10, 2) + Math.pow(10, 2));
    for (var i = 0; i <= 11; i++) {
        for (var j = 0; j <= i; j++) {
            var offset = i*(i+1)/2+j;
            dist_cache[offset] = Math.sqrt(Math.pow(i, 2) + Math.pow(j, 2)) / max;
        }
    }

    var dist = function(x1, y1, x2, y2) {
        var dx = Math.abs(x2 - x1);
        var dy = Math.abs(y2 - y1);

        if (dx < dy) {
            var tmp = dx;
            dx = dy;
            dy = tmp;
        }
        var offset = dx*(dx+1)/2+dy;
        return dist_cache[offset];
    }


    var current = 0;
    var direction = 1;
    setInterval(function() {
        for (var row = 0; row < 12; row++) {
            for (var col = 0; col < 12; col++) {
                var _current = direction == 1 ? current : 11 - current;
                var level = 1 - dist(_current, _current, row, col);
                setLevel(row, col, level);
            }
        }
        current = (current + 1) % 12;
        if (current == 0) direction *= -1;
    }, 100);
})();