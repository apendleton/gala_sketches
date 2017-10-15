var setLight, setLevel, setAllHigh, setAllLow, shuffle;
var LOW = 0, HIGH = 1;

(function() {
    setLight = function(row, col, state) {
        var light = document.querySelectorAll('.row-' + row + ' .col-' + col);
        if (!light.length) console.log('.row-' + row + ' .col-' + col)
        light[0].style.backgroundColor = state ? '#cccccc': '#444444';
    }

    var setAll = function(state) {
        var lights = document.querySelectorAll('td');
        for (let light of lights) {
            light.style.backgroundColor = state ? '#cccccc': '#444444';
        }
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
})();