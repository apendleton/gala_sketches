var setLight, setLevel, setAll, setAllHigh, setAllLow, setRing, setRingQ, setRingGlobalQ, setRingL, setAllRings, setAllRingsLow, setAllRingsHigh, shuffle, parseQuery;
var LOW = 0, HIGH = 1;

(function() {
    setLight = function(row, col, state) {
        var light = document.querySelectorAll('.row-' + row + ' .col-' + col);
        if (!light.length) console.log('.row-' + row + ' .col-' + col)
        light[0].style.backgroundColor = state ? '#cccccc': '#444444';
    }

    setAll = function(state) {
        var lights = document.querySelectorAll('td');
        for (let light of lights) {
            light.style.backgroundColor = state ? '#cccccc': '#444444';
        }
    }

    setLevel = function(row, col, level) {
        var l = Math.floor((204 - 68) * level) + 68;
        var h = l.toString(16);
        var f = ["#", h, h, h].join("")
        var light = document.querySelectorAll('.row-' + row + ' .col-' + col);
        if (!light.length) console.log('.row-' + row + ' .col-' + col)
        light[0].style.backgroundColor = f;
    }

    setAllLow = function() { setAll(LOW); }
    setAllHigh = function() { setAll(HIGH); }

    random = function(min, max) {
        if (typeof max == 'undefined') {
            max = min;
            min = 0;
        }

        return Math.floor(Math.random() * (max - min)) + min;
    }

    shuffle = function(array, arrayLength) {
        var currentIndex = arrayLength, temporaryValue, randomIndex;

        // While there remain elements to shuffle...
        while (0 !== currentIndex) {

            // Pick a remaining element...
            randomIndex = Math.floor(Math.random() * currentIndex);
            currentIndex -= 1;

            // And swap it with the current element.
            temporaryValue = array[currentIndex];
            array[currentIndex] = array[randomIndex];
            array[randomIndex] = temporaryValue;
        }

        return array;
    }

    parseQuery = function(qstr) {
        var query = {};
        var a = (qstr[0] === '?' ? qstr.substr(1) : qstr).split('&');
        for (var i = 0; i < a.length; i++) {
            var b = a[i].split('=');
            query[decodeURIComponent(b[0])] = decodeURIComponent(b[1] || '');
        }
        return query;
    }

    // LED stuff
    var getColor = function(triple) {
        return 'rgb(' + triple.join(',') + ')';
    }

    setAllRings = function(color) {
        var lights = document.querySelectorAll('circle');
        for (let light of lights) {
            light.setAttributeNS(null, 'fill', getColor(color));
        }
    }

    setAllRingsLow = function() { setAllRings([0,0,0]); }
    setAllRingsHigh = function() { setAllRings([255,255,255]); }

    setRing = function(row, col, color) {
        var lights = document.querySelectorAll('.row-' + row + '.col-' + col + ' circle');
        for (let light of lights) {
            light.setAttributeNS(null, 'fill', getColor(color));
        }
    }

    setRingQ = function(row, col, q, color) {
        var lights = document.querySelectorAll('.row-' + row + '.col-' + col + ' circle.q-' + q);
        for (let light of lights) {
            light.setAttributeNS(null, 'fill', getColor(color));
        }
    }

    setRingL = function(row, col, l, color) {
        var lights = document.querySelectorAll('.row-' + row + '.col-' + col + ' circle.l-' + l);
        for (let light of lights) {
            light.setAttributeNS(null, 'fill', getColor(color));
        }
    }

    var qs = [[3,0],[1,2]]
    setRingGlobalQ = function(rowq, colq, color) {
        var rq = rowq % 2;
        var row = Math.floor(rowq/2);
        var cq = colq % 2;
        var col = Math.floor(colq/2);
        var q = qs[rq][cq];

        var lights = document.querySelectorAll('.row-' + row + '.col-' + col + ' circle.q-' + q);
        for (let light of lights) {
            light.setAttributeNS(null, 'fill', getColor(color));
        }
    }
})();