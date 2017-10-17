(function() {
    setAllRingsLow();

    var current = 0;

    var fade = new Array(72);
    for (var i = 0; i < 72; i++) {
        fade[i] = 6 * i / 71.0;
    }

    var colors = [
        // red
        [255,0,0],

        // orange
        [255,128,0],

        // yellow
        [255,255,0],

        // green
        [0,255,0],

        // blue
        [0,0,255],

        // indigo
        [0,0,128],

        // violet
        [128,0,128]
    ]

    var rowMap = {0:0,1:1,2:2,3:3,4:4,5:5,6:5,7:4,8:3,9:2,10:1,11:0}
    var px = new Array(12*12*12)

    for (var row = 0; row < 12; row++) {
        for (var light = 0; light < 12; light++) {
            var rRow = (6 * row) + rowMap[light];
            var f = fade[rRow];
            var base = Math.floor(f);
            var step = f - base;
            var color;
            if (step == 0) {
                color = colors[base];
            } else {
                color = new Array(3);
                for (var p = 0; p < 3; p++) {
                    color[p] = Math.floor((step * colors[base + 1][p]) + ((1 - step) * colors[base][p]));
                }
            }
            for (var col = 0; col < 12; col++) {
                px[144*row + 12*col + light] = color;
            }
        }
    }

    setInterval(function() {
        if (current < 60) {
            var level = (current + 1) / 60;
            for (var row = 0; row < 12; row++) {
                for (var col = 0; col < 12; col++) {
                    for (var i = 0; i < 12; i++) {
                        var color = px[144*row + 12*col + i];
                        setRingL(row, col, i, [Math.floor(level*color[0]), Math.floor(level*color[1]), Math.floor(level*color[2])]);
                    }
                }
            }
        } else if (current >= 600) {
            current = 0;
            setAllRingsLow();
        }

        current += 1;
    }, 100);
})();