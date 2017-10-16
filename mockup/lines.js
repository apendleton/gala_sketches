(function() {
    var qs = parseQuery(window.location.search);
    var state = qs.invert ? LOW : HIGH;
    setAll(!state);

    function switchToOctantZeroFrom(octant, x, y) {
        switch(octant) {
            case 0: return [x, y]
            case 1: return [y, x]
            case 6: return [-y, x]
            case 7: return [x, -y]
        }
    }

    function switchFromOctantZeroTo(octant, x, y) {
        switch(octant) {
            case 0: return [x, y]
            case 1: return [y, x]
            case 6: return [y, -x]
            case 7: return [x, -y]
        }
    }

    var plotLine = function(_x0, _y0, _x1, _y1) {
        if (_x0 > _x1) {
            var tmp = _x0;
            _x0 = _x1;
            _x1 = tmp;
            tmp = _y0;
            _y0 = _y1;
            _y1 = tmp;
        }

        var _dx = _x1 - _x0;
        var _dy = _y1 - _y0;

        var octant;
        if (_dy >= 0) {
            if (_dx >= Math.abs(_dy)) octant = 0;
            else octant = 1;
        } else {
            if (_dx <= Math.abs(_dy)) octant = 6;
            else octant = 7;
        }

        var coords0 = switchToOctantZeroFrom(octant, _x0, _y0);
        var x0 = coords0[0];
        var y0 = coords0[1];

        var coords1 = switchToOctantZeroFrom(octant, _x1, _y1);
        var x1 = coords1[0];
        var y1 = coords1[1];

        var dx = x1 - x0;
        var dy = y1 - y0;
        var D = 2 * dy - dx;
        var y = y0;

        for (var x = x0; (x0 <= x1 ? x <= x1 : x >= x1); x += (x0 > x1 ? -1 : 1)) {
            var rc = switchFromOctantZeroTo(octant, x, y);
            if (rc[0] >= 0 && rc[0] < 12 && rc[1] >= 0 && rc[1] < 12) setLight(rc[0], rc[1], state);
            if (D > 0) {
                y = y + 1;
                D = D - (2*dx);
            }
            D = D + (2*dy);
        }
    }

    var i = 0;
    var entries = [0, 8, 16];
    setInterval(function() {
        setAll(!state);
        for (var j = 0; j < 3; j++) {
            var pos = (entries[j] + i) % 23;
            var row, col;
            if (pos < 12) {
                row = 0;
                col = pos;
            } else {
                row = pos - 11;
                col = 11;
            }
            plotLine(11, 0, row, col);
        }

        i = (i + 1) % 23;
    }, 100);
})();