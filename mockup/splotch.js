(function() {
    setAllLow();

    var bgrid;
    var splotch = function() {
        var grid = [];
        for (var i = 0; i < 12; i++) {
            grid[i] = [];
            for (var j = 0; j < 12; j++) grid[i][j] = 0;
        }

        for (var i = 0; i < 3; i++) {
            grid[random(12)][random(12)] = 1;
        }

        var size = random(5, 10);
        for (var i = 0; i < size; i++) {
            var candidates = [];
            for (var row = 0; row < 12; row++) {
                for (var col = 0; col < 12; col++) {
                    if (
                        (row > 0 && grid[row - 1][col]) ||
                        (row < 11 && grid[row + 1][col]) ||
                        (col > 0 && grid[row][col - 1]) ||
                        (col < 11 && grid[row][col + 1])
                    ) {
                        candidates.push([row, col]);
                    }
                }
            }

            var cCount = random(candidates.length);
            for (var j = 0; j < cCount; j++) {
                grid[candidates[j][0]][candidates[j][1]] = 1;
            }
        }

        // box blur
        bgrid = [];
        for (var i = 0; i < 12; i++) {
            bgrid[i] = [];
            for (var j = 0; j < 12; j++) {
                var cells = [grid[i][j]];
                if (i > 0) {
                    cells.push(grid[i-1][j]);
                    if (j > 0) cells.push(grid[i-1][j-1]);
                    if (j < 11) cells.push(grid[i-1][j+1]);
                }
                if (j > 0) cells.push(grid[i][j-1]);
                if (j < 11) cells.push(grid[i][j+1]);
                if (i < 0) {
                    cells.push(grid[i-1][j]);
                    if (j > 0) cells.push(grid[i+1][j-1]);
                    if (j < 11) cells.push(grid[i+1][j+1]);
                }
                var acc = 0;
                for (var k = 0; k < cells.length; k++) acc += cells[k];

                bgrid[i][j] = acc / cells.length;
            }
        }
    }

    var current = 1;
    var interval;
    var anim = function() {
        for (var row = 0; row < 12; row++) {
            for (var col = 0; col < 12; col++) {
                setLevel(row, col, current * bgrid[row][col]);
            }
        }
        current -= .025;

        if (current <= 0) {
            setAllLow();
            clearInterval(interval);
            setTimeout(start, random(1500));
        }
    }

    var start = function() {
        splotch();
        current = 1;
        interval = setInterval(anim, 100);
    }

    start();
})();