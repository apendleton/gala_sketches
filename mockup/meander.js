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

    var row = 0;
    var col = 0;

    var nextRows = new Array(4);
    var nextCols = new Array(4);
    var count = 0;
    setInterval(function() {
        count = 0;

        if (row > 0) {
            nextRows[count] = row - 1;
            nextCols[count] = col;
            count++;
        }

        if (row < 11) {
            nextRows[count] = row + 1;
            nextCols[count] = col;
            count++;
        }

        if (col > 0) {
            nextRows[count] = row;
            nextCols[count] = col - 1;
            count++;
        }

        if (col < 11) {
            nextRows[count] = row;
            nextCols[count] = col + 1;
            count++;
        }

        var pick = random(count);
        row = nextRows[pick];
        col = nextCols[pick];

        for (var r = 0; r < 12; r++) {
            for (var c = 0; c < 12; c++) {
                var level = 1 - dist(r, c, row, col);
                setLevel(r, c, level);
            }
        }
    }, 200);
})();