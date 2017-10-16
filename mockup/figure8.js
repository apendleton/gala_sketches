(function() {
    setAllLow();

    var evens = [0, 1, 2, 3, 4, 5];
    var odds = [11, 10, 9, 8, 7, 6];

    var grad = {
        9: 0, 10: 1, 11: 2, 0: 3, 1: 4, 2: 5, 3: 5, 4: 4, 5: 3, 6: 2, 7: 1, 8: 0
    }

    var current = 0;
    var direction = 1;
    var orientation = 1;

    var leftColor = [Math.floor(Math.random() * 256), Math.floor(Math.random() * 256), Math.floor(Math.random() * 256)];
    var rightColor = [Math.floor(Math.random() * 256), Math.floor(Math.random() * 256), Math.floor(Math.random() * 256)];
    setInterval(function() {
        var dot = current % 6;
        var ring = Math.floor(current / 6);

        for (col = 0; col < 12; col++) {
            var hotRing, hotDot, cycle;
            if (col % 2 == 0) {
                cycle = ring % 2 == (direction == 1 ? 0 : 1) ? evens : odds;
                hotRing = ring;
                hotDot = dot;
            } else {
                cycle = ring % 2 == (direction == 1 ? 1 : 0) ? evens : odds;
                hotRing = 11 - ring;
                hotDot = 5 - dot;
            }

            if (orientation) {
                var colorSlot = (6 * col) + grad[cycle[hotDot]];
                var color = [0,1,2].map(function(i) {
                    var lower = Math.min(rightColor[i], leftColor[i]);
                    var upper = Math.max(rightColor[i], leftColor[i]);
                    return Math.floor((colorSlot/72) * (upper - lower)) + lower;
                });
                setRingL(hotRing, col, cycle[hotDot], color);
            } else {
                setRingL(col, hotRing, (cycle[hotDot] + 9) % 12, [0,0,0]);
            }
        }
        current += direction;

        if (direction == 1 && current == 72) {
            current -= 1;
            direction = -1;
        } else if (direction == -1 && current == -1) {
            current += 1;
            direction = 1;
            orientation = !orientation;
            leftColor = [Math.floor(Math.random() * 256), Math.floor(Math.random() * 256), Math.floor(Math.random() * 256)];
            rightColor = [Math.floor(Math.random() * 256), Math.floor(Math.random() * 256), Math.floor(Math.random() * 256)];
        }
    }, 100);
})();